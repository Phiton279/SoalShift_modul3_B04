#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <termios.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int *foodmarket;

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

void * shop (void * argv){
    char input;

    while (1){
        input = getch();
        if(input == '1'){
            printf("menambah stock 1 makanan\n");
            *foodmarket +=1;
        }
        else if (input == '2') exit(0);    
    }
}


int main (){
    //
    key_t pids = 2799;
    
    int shmid  = shmget(pids, sizeof(int), IPC_CREAT | 0666);
    foodmarket = shmat(shmid, NULL, 0);
    
    pthread_t thread1;
    pthread_create(&thread1, NULL, shop, NULL);

    while (1){
        printf("Shop\n");
        printf("Food Stock\t : %d\n",*foodmarket);

        printf("Pilihan\n");
        printf("1. Restock\n");
        printf("2. Exit\n");

        sleep(1);
        system("clear");
    }
}
