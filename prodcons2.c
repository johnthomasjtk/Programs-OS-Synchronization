#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int buf[5],p,c;
sem_t mutex,full,empty;

void *produce(void *arg)
{
    int i;
    for(i=0;i<10;i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("produced item in buf[%d] is %d\n",p%5,i);
        buf[p++%5]=i;
        sem_post(&mutex);
        sem_post(&full);
	sleep(1);
    }
    pthread_exit((void *)0);
}
void *consume(void *arg)
{
        int item,i;
        for(i=0;i<10;i++)
        {
                sem_wait(&full);
        	sem_wait(&mutex);
                item=buf[c++%5];
                printf("consumed item from buf[%d] is %d\n",(c-1)%5,item);

                sem_post(&mutex);
                sem_post(&empty);
		sleep(1);

       }
       pthread_exit((void *)0);
}
int main()
{
    pthread_t tid1,tid2;
    sem_init(&mutex,0,1);
    sem_init(&full,0,0);
    sem_init(&empty,0,5);
    pthread_create(&tid1,NULL,produce,NULL);
    pthread_create(&tid2,NULL,consume,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}
