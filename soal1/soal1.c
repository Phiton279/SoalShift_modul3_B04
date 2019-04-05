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