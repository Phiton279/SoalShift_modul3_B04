#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <termios.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

char monsname[32];
int hungerstat  = 200;
int hygienestat = 100;
int healthstat  = 300;
int npchealth   = 100;
int food        = 0;
int *foodmarket ; 
int bathready   = 0;
int mode=0;

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}

void * hungers (void *argv){
    while (1){
        if(mode != 1){
            if (hungerstat >=200){
                hungerstat = 200;
            }
            else if (hungerstat <= 0){
                printf("monster kelaparan\n");
                printf("monser mati , game over\n");
                exit(0);
            }
            sleep(10);
            hungerstat -= 5;
        }
        
    }

}

void * hygiene (void *argv){
    while(1){
        if (mode != 1){
            sleep(10);//seharusnya 30
            hygienestat-=10;

            if(hygienestat <= 0){
                printf("monster sangat tidak bersih\n");
                printf("monstermu mati\n");
                exit(0);
            }
        }
    }

}

void * regenerasi(void *argv){
    while (1){
        if (mode!=1){

            if (healthstat < 300){
                healthstat += 5;
                sleep(10);
            }

            if (healthstat > 300){
                healthstat = 300;
            }
        }
    }
}

void * takeabath(void *argv){
    while(1){
        if(bathready > 0){
            while(1){
                sleep(1);
                bathready-=1;
            }
        }

    }

}

void * modebattle(void *argv){
    char input;
    
    while (1){
        
        if (mode == 1 ){
            printf("battle mode\n");
            input = getch();
            printf("%c",input);
        
            if (input == '1'){
                printf("attack monster npc\n");
                printf("deal 20 demange to npc\n");
                
                npchealth-=20;

                printf("npc attack you\n");    
                printf("npc deal 20 demage to you\n");
                
                healthstat-=20;


                if(npchealth <= 0){
                    printf("you win \n");
                    mode = 0;
                }
                else if (healthstat <= 0){
                    printf("you lose and die\n");
                    exit(0);
                }

                sleep(1);    
            }
            else if (input == '2'){
                printf("kabur\n");
                npchealth = 100;
                mode = 0;
            }
        }
    }
}

void * modeshoping(void *argv){
    char input;
    
    while (1){
        if (mode == 2){
            input = getch();

            if (input == '1'){
            
                if (*foodmarket>0){
                    *foodmarket-=1;
                    food+=1;
                }
                else printf("stock toko habis\n");

            }
            else if (input == '2'){
                mode = 0;
            }
        
        }

        
    }

}

void * modeawal(void *argv){
    char input;
    while (1){
        if (mode == 0){
            input = getch();

            if (input == '1'){
                if (food!=0){
                    food-=1;
                    hungerstat+=15;
                    printf("monster telah makan\n");
                }
                else printf ("makanan habis\n");

            }
            else if (input == '2'){
                
                if (bathready <= 0){
                    printf ("mandi ...\n");
                    hygienestat+=30;
                    bathready=20;
                }
                else printf("bath belum ready\n");
                
            }
            else if (input == '3'){
                printf("masuk mode Battle\n");
                mode = 1;
            }
            else if (input == '4'){
                printf("masuk mode Pasar\n");
                mode = 2;
            }
            else if (input == '5'){
                printf("keluar dari game ..\n");
                sleep(1);
                exit(0);
            }
        }
    }
}


int main (){
    printf("input monster name : ");
    scanf("%s",monsname);
    pthread_t thread1,thread2,thread3,thread4,thread5,thread6,thread7;
    key_t pids = 2799;
    int shmid  = shmget(pids, sizeof(int), IPC_CREAT | 0666);
    foodmarket = shmat(shmid, NULL, 0);

    pthread_create(&thread1, NULL, hungers, NULL);
    pthread_create(&thread2, NULL, hygiene, NULL);
    pthread_create(&thread3, NULL, regenerasi, NULL);
    pthread_create(&thread4, NULL, takeabath, NULL);
    pthread_create(&thread5, NULL, modebattle, NULL);
    pthread_create(&thread6, NULL, modeshoping, NULL);
    pthread_create(&thread7, NULL, modeawal, NULL);

    


    while(1){
        if ( mode == 0){
            printf("Mode stand Bye\n");
            printf("Health Status\t : %d\n",healthstat);
            printf("Hygiene Status\t : %d\n",hygienestat);
            printf("Hunger Status\t : %d\n",hungerstat);
            printf("Food left\t : %d\n",food);

            if(bathready<=0){
                printf("Bath is ready\n");
            }
            else if(bathready > 0){
                printf("Bath will be ready in \t : %d second\n",bathready);
            }

            printf(" pilihan : \n");
            printf(" 1  = Makana   \n");
            printf(" 2  = Mandi    \n");
            printf(" 3  = Battle   \n");
            printf(" 4  = Shopping \n");
            printf(" 5  = ExitGame \n");

        }
        else if ( mode == 1 ){
            printf("Mode Battle\n");
            printf("Health Status\t : %d\n",healthstat);
            printf("NPC Health Status\t : %d\n",npchealth);

            printf("pilihan :\n");
            printf(" 1  = Attack\n");
            printf(" 2  = Run\n");


        }
        else if ( mode == 2 ){
            printf("Mode Shopping\n");
            printf("Shop food stock \t : %d\n",*foodmarket);
            printf("Your food stock\t : %d\n",food);

            printf("pilihan :\n");
            printf(" 1  = Buy\n");
            printf(" 2  = Back\n");            
        }
        sleep(1);
        system("clear");
    }

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    pthread_join(thread6,NULL);
    pthread_join(thread7,NULL);
}

