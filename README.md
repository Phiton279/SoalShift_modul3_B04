# SoalShift_modul3_B04
Pengerjaan Soal Shift Modul 3 Sisop 2019

# Soal Shift Modul 3

## Kelompok B4
#### ***Ersad Ahmad Ishlahuddin***

#### ***05111740000016***

#### ***Philip Antoni Siahaan***

#### ***05111740000111***

### **Nomor 1**

#### Soal

```
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
    ./faktorial 5 3 4
    3! = 6
    4! = 24
    5! = 120
```

#### Pemahaman Soal 1
```
Pemanfaatan thread untuk menghitung Faktorial secara paralel.
```

#### Jawaban

#### Source code
```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

int store[100];

void* fact(void* arg){
    int *in = arg;
    store[0] = 1;
    store[1] = 1;
    for(int i = 2; i <= *in; i++)
    {
        store[i] = i * store[i-1];
    }
}

void sort(int in[], int ite) 
{ 
    for(int i = 0; i < ite; i++)
    {
        for(int j = i; j < ite; j++)
        {
            while(in[i] > in[j])
            {
                int temp = in[j];
                in[j] = in[i];
                in[i] = temp; 
            }
        }
    }
} 


int main(int argc, char *argv[]){

    int ite = argc-1;
    pthread_t t_id[100];
    int in[100];

    for(int i = 0; i < ite; i++)
    {
        in[i] = atoi(argv[i+1]);
    }

    sort(in, ite);

    for(int i = 0; i < ite; i++) pthread_create(&t_id[i], NULL, &fact, &in[i]);

    for(int i = 0; i < ite; i++) pthread_join(t_id[i], NULL);

    for(int i = 0; i < ite; i++) printf("%d! = %d\n", in[i], store[in[i]]);

    return 0;
    
}
```
#### Penjelasan
```c
int ite = argc-1;
```
Untuk menyimpan banyaknya argumen yang masuk namun dikurangi satu karena parameter awal merupakan nama file.
```c
for(int i = 0; i < ite; i++)
{
    in[i] = atoi(argv[i+1]);
}
```
Untuk mengubah argument value manjadi integer.
```c
sort(in, ite);
```
Untuk memanggil fungsi yang akan mengurutkan array.
```c
void sort(int in[], int ite) 
{ 
    for(int i = 0; i < ite; i++)
    {
        for(int j = i; j < ite; j++)
        {
            while(in[i] > in[j])
            {
                int temp = in[j];
                in[j] = in[i];
                in[i] = temp; 
            }
        }
    }
} 
```
Untuk mengurutkan array dari terkecil ke terbesar menggunakan algoritma Bubble Sort.
```c
for(int i = 0; i < ite; i++) pthread_create(&t_id[i], NULL, &fact, &in[i]);
```
Untuk membuat thread.
```c
int store[100];
```
Untuk menyimpan hasil faktorial yang telah terurut.
```c
void* fact(void* arg){
    int *in = arg;
    store[0] = 1;
    store[1] = 1;
    for(int i = 2; i <= *in; i++)
    {
        store[i] = i * store[i-1];
    }
}
```
Untuk mengenerate bilangan faktorial memanfaatkan nilai awal store[0] dan store[1] yang kemudian diiterasi.
```c
for(int i = 0; i < ite; i++) pthread_join(t_id[i], NULL);
```
Agar thread berjalan secara bergantian (seperti wait()).
```c
for(int i = 0; i < ite; i++) printf("%d! = %d\n", in[i], store[in[i]]);
```
Untuk mencetak hasil yang telah terurut yang disimpan di variable store[].


### **Nomor 2**

#### Soal 2

```
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
    Terdapat 2 server: server penjual dan server pembeli
    1 server hanya bisa terkoneksi dengan 1 client
    Server penjual dan server pembeli memiliki stok barang yang selalu sama
    Client yang terkoneksi ke server penjual hanya bisa menambah stok
        Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
    Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
        Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
    Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
    Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
    Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
    Server penjual akan mencetak stok saat ini setiap 5 detik sekali

Menggunakan thread, socket, shared memory

```
#### Pemahaman Soal 2
```
Pemanfaatan thread untuk perintah "Server penjual akan mencetak stok saat ini setiap 5 detik sekali"
Pemanfaatan socket untuk komunikasi antara server dan client
Pemanfaatan shared memory untuk perintah "Server penjual dan server pembeli memiliki stok barang yang selalu sama"
```

#### Jawaban 2

Ada 4 Source Code. Server Penjual dan Pembeli, Client Penjual dan Pembeli.
Untuk pembuatan thread, socket, dan shared memory menggunakan yang sama dengan modul dengan beberapa modifikasi.
#### Source Code
server_penjual.c
```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define PORT 8080

int* value;

void* check(){
    while(1){
        printf("Stok saat ini %d\n", *value);
        sleep(5);
    }
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
    *value = 7;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    pthread_t t_id;
    pthread_create(&t_id, NULL, check, NULL);


    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while(1) {
        valread = read( new_socket , buffer, 1024);
        if(strcmp(buffer, "tambah") == 0){
            *value = *value + 1;
        }
        if(valread == 0) break;
        memset(buffer,0,sizeof(buffer));
    }
    return 0;
}
```

#### Penjelasan
```c
pthread_t t_id;
pthread_create(&t_id, NULL, check, NULL);
```
Membuat thread untuk menampilkan ketersediaan stok setiap 5 detik.
```c
void* check(){
    while(1){
        printf("Stok saat ini %d\n", *value);
        sleep(5);
    }
}
```
Fungsi yang akan dijalankan oleh thread untuk menampilkan stok setiap 5 detik.
```c
while(1) {
    valread = read( new_socket , buffer, 1024);
    if(strcmp(buffer, "tambah") == 0){
        *value = *value + 1;
    }
    if(valread == 0) break;
    memset(buffer,0,sizeof(buffer));
}
```
Membaca input secara terus menerus selama koneksi antara client dan server tidak terputus.  
Input disimpan di variable buffer, kemudian melakukan pengecekan apakah buffer sama dengan "tambah", jika "tambah" maka stok akan bertambah 1.
#### Source Code
client_penjual.c
```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char query[1000]={0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    while(1){
        scanf("%s",query);
        send(sock, query, strlen(query), 0);
        memset(query,0,sizeof(query));
    }
    return 0;
}
```

#### Penjelasan
```c
#define PORT 8080
```
Mendefinisikan port yang sama dengan server.
```c
while(1){
    scanf("%s",query);
    send(sock, query, strlen(query), 0);
    memset(query,0,sizeof(query));
}
```
Selama koneksi tidak terputus, maka client akan melakukan scanf untuk input lalu mengirimnya ke server.

#### Source Code
server_pembeli.c
```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define PORT 9090

int* value;

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    char success[] = "transaksi berhasil\n";
    char fail[] = "transaksi gagal\n";
    char wrong[] = "query salah\n";

    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
    *value = 7;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while(1) {
        valread = read( new_socket , buffer, 1024);
        if(strcmp(buffer, "beli") == 0){
            if(*value > 0){
                send(new_socket, success, strlen(success), 0);
                *value = *value - 1;
            }else{
                send(new_socket, fail, strlen(fail), 0);
            }  
        }else send(new_socket, wrong, strlen(wrong), 0);
        if(valread == 0) break;
        memset(buffer,0,sizeof(buffer));
    }
    return 0;
}

```

#### Penjelasan
```c
while(1) {
    valread = read( new_socket , buffer, 1024);
    if(strcmp(buffer, "beli") == 0){
        if(*value > 0){
            send(new_socket, success, strlen(success), 0);
            *value = *value - 1;
        }else{
            send(new_socket, fail, strlen(fail), 0);
        }  
    }else send(new_socket, wrong, strlen(wrong), 0);
    if(valread == 0) break;
    memset(buffer,0,sizeof(buffer));
}
```
Membaca input secara terus menerus selama koneksi antara client dan server tidak terputus.  
Input disimpan di variable buffer, kemudian melakukan pengecekan apakah buffer sama dengan "beli", jika "beli" maka stok akan berkurang satu 1.  
Jika stok lebih dari 0 maka akan mengirim "transaksi berhasil" ke client.  
Jika stok kurang dari 1 maka akan mengirim "transaksi gagal" ke client.  
Jika query yang dimasukkan salah maka akan mengirim "query salah" ke client.
```c
char success[] = "transaksi berhasil\n";
char fail[] = "transaksi gagal\n";
char wrong[] = "query salah\n";
```
Variable yang menyimpan pesan yang dikirim ke client.
#### Source Code
client_pembeli.c
```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9090
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char query[1000]={0};
    
    while(1){
        scanf("%s",query);
        send(sock, query, strlen(query), 0);
        valread = read( sock , buffer, 1024);
        printf("%s\n", buffer);
        memset(query,0,sizeof(query));
        memset(buffer,0,sizeof(buffer));
    }
    return 0;
}

```

#### Penjelasan
```c
#define PORT 9090
```
Mendefinisikan port yang sama dengan server.
```c
while(1){
    scanf("%s",query);
    send(sock, query, strlen(query), 0);
    valread = read( sock , buffer, 1024);
    printf("%s\n", buffer);
    memset(query,0,sizeof(query));
    memset(buffer,0,sizeof(buffer));
}
```
Selama koneksi tidak terputus, maka client akan melakukan scanf untuk input lalu mengirimnya ke server.  
Selain itu juga menerima pesan yang dikirin oleh server, apakah transaksi berhasil, sukses, atau query yang salah.

### **Nomor 3**

### Soal

```
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
Terdapat 2 karakter Agmal dan Iraj
Kedua karakter memiliki status yang unik
Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
Iraj memiliki Spirit_Status, di awal program memiliki status 100
Terdapat 3 Fitur utama
All Status, yaitu menampilkan status kedua sahabat
Ex: Agmal WakeUp_Status = 75 
      Iraj Spirit_Status = 30
“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
Terdapat Kasus yang unik dimana:
Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
Program akan berhenti jika Salah Satu :
WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)


Syarat Menggunakan Lebih dari 1 Thread

```
### Pemahaman Soal 3

Disoal No 3 Kita diminta Untuk Membuat sebuah program yang menampilkan kegiatan 2 orang iraj dan agmal. Dimana Nantinya program
dapat menampilkan status kemudian membuat pilihan yang mengganti status. Diakhir ketika salah satu status telah terpenuhi maka program
akan berakhir dan menampilkan keadaan akhir yakni agmal terbangun atau iraj tidur. disini menggunakan dua thread untuk membagi antara
dua karakter agmal dan iraj

#### Jawaban 3
#### Source Code
```c
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int agmal_status    = 0;
int iraj_status     = 100;
int agmal_flag      = 0;
int iraj_flag       = 0;


void * test(void *ptr){


}

void * agmal(void *ptr){
    while (1){
        if(agmal_flag==3){
            printf("(Fitur Agmal Ayo Bangun disabled 10 s)\n");
            sleep(10); 
            agmal_flag=0;
        }
    }
    //printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
    
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
```

### Penjelasan
```C
    pthread_t thread1,thread2,thread3;
    char str1[20];
    char str2[] = "All Status";
    char str3[] = "Agmal Ayo Bangun";
    char str4[] = "Iraj Ayo Tidur";
    
    pthread_create(&(thread1), NULL, test, NULL);
    pthread_create(&(thread2), NULL, agmal, NULL);
    pthread_create(&(thread3), NULL, iraj, NULL);
```
Pertama-tama melakukan pembuatan thread dengan pthread_t kemudian melakukan create agar thread dapat berjalan. Dalam keadaan ini 
semua thread akan berjalan secara bersamaan.

```C
while (1){
        if(strcasecmp(str1,str2) == 0){
        }
        else if (strcasecmp(str1,str3) == 0){
            
        }
        else if (strcasecmp(str1,str4) == 0){
        }
        else{
        }
```

Dalam fungsi ini kita melaukan pemilihan fitur terhadap string yang dimasukan. pemilihan dilakukan dengan strcasecmp agar bsa melakukan
compare terhadap dua string dan tidak berpengaruh terhadap huruf kecil maupun besar.

```C
    str1==str2
    printf("Agmal Wake up Status = %d\n",agmal_status);
    printf("Iraj Spirit Status = %d\n\n",iraj_status);

    str1==str3
    if (agmal_flag==3){
        printf("Fitur Agmal Ayo Bangun Masih disabled\n");  
    }
    else{
        agmal_status+=15;
        agmal_flag +=1;
    }

    str1==str4
    if (iraj_flag==3){
        printf("Fitur Iraj Ayo Tidur Masih disabled\n");
    }
    else {
        iraj_status -=20;
        iraj_flag +=1;
    }

```

dalam fungsi ini menampilkan ketika string masukan yang dicompare sesuai dengan inputan. bila sama dengan string kedua yakni all stat
maka akan memunculkan info tentang status dari kedua orang. bila sama dengan string ketiga yakni agmal ayo bangun , maka stat agmal akan bertambah
dan terakhir string 4 iraj ayo tidur. maka akan mengurangi status iraj. flag ditambahkan karena nantinya jika fitur agmal dan iraj telah 
dipilih 3 kali maka fitur itu akan berhenti selama 10 detik.

```C
void * agmal(void *ptr){
    while (1){
        if(agmal_flag==3){
            printf("(Fitur Agmal Ayo Bangun disabled 10 s)\n");
            sleep(10); 
            agmal_flag=0;
        }
    }
    //printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
    
}
```
Dalam thread agmal terdapat control untuk disable fitur agmal kemudian diberikan sleep() untuk melakukan tunggu sehingga thread tidak berjalan
selama sepuluh detik kemudian stelah itu flag dijadikan 0 kembali agar dapat diakses kembali.begitu juga dalam thread iraj

```C
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
```
Terakhir diberikan thread join untuk mengahkiri thread.

### **Nomor 4**

### Soal

```

Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
Ketika Mengekstrak file .zip juga harus secara bersama-sama
Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
Wajib Menggunakan Multithreading
Boleh menggunakan system

```
### Pemahaman Soal 4

Penerapan thread untuk menjalankan 2 command secara bersamaan.  


Mengambil data dari proses, kemudian memasukkan ke sebuah file.  
Setelah itu melakukan kompresi pada file tersebut.  
File yang lama dihapus.  
Setelah 15 detik maka melakukan ekstrasi pada file zip.
