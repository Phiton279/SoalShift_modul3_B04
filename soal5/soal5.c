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
int food        = 0;
int *foodmarket ; 
int bathready   = 0;
int mode=0;

void * hungers (void *argv){

}

void * hygiene (void *argv){


}

void * regenerasi(void *argv){

}

void * modestandby(void *argv){


}

void * modebattle(void *argv){


}

void * modeshoping(void *argv){


}




int main (){
    pthread_t thread1,thread2,thread3,thread4,thread5,thread6;
    scanf("%s",monsname);

    pthread_create(&thread1, NULL, hungers, NULL);
    pthread_create(&thread2, NULL, hygiene, NULL);
    pthread_create(&thread3, NULL, regenerasi, NULL);
    pthread_create(&thread4, NULL, modestandby, NULL);
    pthread_create(&thread5, NULL, modebattle, NULL);
    pthread_create(&thread6, NULL, modeshoping, NULL);


    while(1){
        if ( mode == 0){
            printf("Mode stand Bye\n");
            printf("Health Status\t : %d\n",healthstat);
            printf("Hygiene Status\t : %d\n",hygienestat);
            printf("Hunger Status\t : %d\n",hungerstat)
            printf("Food left\t : %d\n",food);
            if(bathready==0){
                printf("Bath is ready\n");
            }
            else{
                printf("Bath will be ready in \t : %d second\n",bathready);
            }
        }
        else if ( mode == 1 ){
            

        }
        else if ( mode == 2 ){

        }
    }

}
