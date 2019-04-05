#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void ngelist(int nomor){
    char location[] = "/home/phiton2/Documents/";
    char dirname[sizeof "mkdir -p /home/phiton2/Documents/FolderProsesx"];
    char filename[sizeof "ps -ax | head -10 > /home/phiton2/Documents/FolderProsesx/SimpanProsesx.txt"];
    sprintf(dirname,"mkdir -p %sFolderProses%d",location,nomor);
    system(dirname);
    sprintf(filename,"ps -ax | head -10 > /home/phiton2/Documents/FolderProses1/SimpanProses%d.txt",nomor);
    system(filename);
}

void ngekompres(int nomor){
    char location[] = "/home/phiton2/Documents/";
    char filename[sizeof "/home/phiton2/Documents/FolderProsesx/SimpanProsesx.txt"];
    char zipname[sizeof "/home/phiton2/Documents/FolderProsesx/KompresProsesx.zip"];
    char zipfile[sizeof "zip -r /home/phiton2/Documents/FolderProsesx/KompresProsesx.zip /home/phiton2/Documents/FolderProsesx/SimpanProsesx.txt"];
    char delete[sizeof "rm /home/phiton2/Documents/FolderProsesx/KompresProsesx.txt"];

    sprintf(filename,"%s/FolderProses%d/SimpanProses%d.txt",location,nomor,nomor);   
    sprintf(zipname,"%s/FolderProses%d/KompresProses%d.zip",location,nomor,nomor);
    
    sprintf(zipfile,"zip -r %s %s",zipname,filename);
    system(zipfile);

    sprintf(delete,"rm %sFolderProses%d/SimpanProses%d.txt",location,nomor,nomor);
    system(delete);
}

void ngekstrak(int nomor){

    char location[sizeof "/home/phiton2/Documents/FolderProsesx/"];
    char extractname[sizeof "unzip -j /home/phiton2/Documents/FolderProsesx/KompresProsesx.zip"];
    sprintf(location,"/home/phiton2/Documents/FolderProses%d/",nomor);

    sprintf(extractname,"unzip -j %sKompresProses%d.zip %s",location,nomor,location);
    system(extractname);
}


void * file1(void *ptr){
    ngelist(1);
    sleep(1);
    ngekompres(1);
    printf("Menunggu 15 detik untuk mengekstrak kembali file 1\n");
    sleep(15);
    ngekstrak(1);
}

void * file2(void *ptr){
    ngelist(2);
    sleep(2);
    ngekompres(2);
    printf("Menunggu 15 detik untuk mengekstrak kembali file 2\n");
    sleep(15);
    ngekstrak(2);
}

int main(){
    pthread_t thread1,thread2;

    pthread_create(&(thread1), NULL, file1, NULL);
    pthread_create(&(thread2), NULL, file2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 

}