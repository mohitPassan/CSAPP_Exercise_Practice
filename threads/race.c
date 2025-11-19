#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define N 4

void * thread(void *vargp);

int main()
{
    pthread_t tid[N];
    int i;

    for(i = 0; i < N; i++)
        pthread_create(&tid[i], NULL, thread, &i);
    for(i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    exit(0);
}

void * thread(void *vargp)
{
    int myid = *((int *)vargp);
    printf("Hello from thread %d\n", myid);
    return NULL;
}

// There is a race between i++ and deferencing the vargp for getting the id