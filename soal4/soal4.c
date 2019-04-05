#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[2];


void* makeDir1(void* arg){
	system("mkdir ~/Documents/FolderProses1");
}
void* makeDir2(void* arg){
	system("mkdir ~/Documents/FolderProses2");
}

void* storeList1(void *arg){
	system("ps -aux | head -11 | tail -10 > ~/Documents/FolderProses1/SimpanProses1.txt");
}
void* storeList2(void *arg){
	system("ps -aux | head -11 | tail -10 > ~/Documents/FolderProses2/SimpanProses2.txt");
}

void* compress1(void *arg){
	system("zip -m -j -q ~/Documents/FolderProses1/KompresProses1.zip ~/Documents/FolderProses1/SimpanProses1.txt");
}
void* compress2(void *arg){
	system("zip -m -j -q ~/Documents/FolderProses2/KompresProses2.zip ~/Documents/FolderProses2/SimpanProses2.txt");
}

void* extract1(void *arg){
	system("unzip -q ~/Documents/FolderProses1/KompresProses1.zip -d ~/Documents/FolderProses1");
}
void* extract2(void *arg){
	system("unzip -q ~/Documents/FolderProses2/KompresProses2.zip -d ~/Documents/FolderProses2");
}

int main(){
	int* file1 = (int*)1;
	int* file2 = (int*)2;

  pthread_create(&tid[0], NULL, &makeDir1, (void*)&file1);
	pthread_create(&tid[1], NULL, &makeDir2, (void*)&file2);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_create(&tid[0], NULL, &storeList1, (void*)&file1);
	pthread_create(&tid[1], NULL, &storeList2, (void*)&file2);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_create(&tid[0], NULL, &compress1, (void*)&file1);
	pthread_create(&tid[1], NULL, &compress2, (void*)&file2);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    for (int i=1; i<=15; i++){
        printf("%d\n", i);
        sleep(1);
    }

	pthread_create(&tid[0], NULL, &extract1, (void*)&file1);
	pthread_create(&tid[1], NULL, &extract2, (void*)&file2);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
