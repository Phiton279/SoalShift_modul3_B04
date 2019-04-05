#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int agmal_status    = 0;
int iraj_status     = 100;
int agmal_flag      = 0;
int iraj_flag       = 0;

void * agmal(void *ptr){
    while (1){
        if(agmal_flag==3){
            printf("(Fitur Agmal Ayo Bangun disabled 10 s)\n");
            sleep(10); 
            agmal_flag=0;
        }
    }
}

void * iraj(void *ptr){
    while(1){
        if(iraj_flag ==3){
            printf("(Fitur Iraj Ayo Tidur disabled 10 s)\n"); 
            sleep(10);
            iraj_flag=0;
        }
    }
}

int main(){

    pthread_t thread1,thread2,thread3;
    char str1[20];
    char str2[] = "All Status";
    char str3[] = "Agmal Ayo Bangun";
    char str4[] = "Iraj Ayo Tidur";
    
    pthread_create(&(thread1), NULL, test, NULL);
    pthread_create(&(thread2), NULL, agmal, NULL);
    pthread_create(&(thread3), NULL, iraj, NULL);
    
    printf("Agmal Wake up Status = %d\n",agmal_status);
    printf("Iraj Spirit Status = %d\n",iraj_status);
    
    printf("1. All Status = Menampilkan status\n");
    printf("2. Agmal Ayo bangun = Menambah wake up status agmal \n");
    printf("3. Iraj Ayo Tidur = Mengurangi spirit status iraj\n");;
    while (1){
        printf("%d %d\n",agmal_flag,iraj_flag);
        printf("Masukan Pilihan = ");
        scanf("%[^\n]s",str1); 
        
        printf("\n");

        if(strcasecmp(str1,str2) == 0){
            printf("Agmal Wake up Status = %d\n",agmal_status);
            printf("Iraj Spirit Status = %d\n\n",iraj_status);
        }
        else if (strcasecmp(str1,str3) == 0){
            
            if (agmal_flag==3){
                printf("Fitur Agmal Ayo Bangun Masih disabled\n");  
            }
            else{
                agmal_status+=15;
                agmal_flag +=1;
            }
            
        }
        else if (strcasecmp(str1,str4) == 0){
            if (iraj_flag==3){
                printf("Fitur Iraj Ayo Tidur Masih disabled\n");
            }
            else {
                iraj_status -=20;
                iraj_flag +=1;
            }
        }
        else{
            printf("command salah\n\n");
        }

        if (agmal_status >= 100){
            printf("end\n");
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            exit(0);
            break;

        }
        else if (iraj_status <= 0){
            printf("end\n");
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            exit(0);
            break;
        }
        getchar();
    }
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
}

