#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define N 4

void * thread(void *vargp);

int main()
{
    pthread_t tid[N];
    int i, *ptr;

    for(i = 0; i < N; i++)
    {
        // Create a copy and then pass to the thread
        ptr = malloc(sizeof(int));
        *ptr = i;
        pthread_create(&tid[i], NULL, thread, ptr);
    }
    for(i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    exit(0);
}

void * thread(void *vargp)
{
    int myid = *((int *)vargp);
    free(vargp);
    printf("Hello from thread %d\n", myid);
    return NULL;
}