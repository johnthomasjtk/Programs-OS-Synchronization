#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include <string.h>

    sem_t mutex,writeblock;
    int rcount = 0;
    char *chdata[5]={"amrita","vishwa","vidya","peetham","amritapuri"};
    char buffer[20] = "Welcome to";

 void *reader(void *arg)
{
      int f;
      f = ((int)arg);
      sem_wait(&mutex);
      rcount = rcount + 1;
      if(rcount==1)
       sem_wait(&writeblock);
      sem_post(&mutex);
      printf("Data read by the reader%d is : ",f);
      printf("%s\n",buffer);
       sleep(1);
      sem_wait(&mutex);
      rcount = rcount - 1;
      if(rcount==0)
       sem_post(&writeblock);
      sem_post(&mutex);
}

 void *writer(void *arg)
{
      int f,i;
      f = ((int) arg);
      sem_wait(&writeblock);
      strcpy(buffer, chdata[f]);
      printf("Data writen by the writer%d is %s\n",f, buffer);
      sleep(1);
      sem_post(&writeblock);
}

 main()
{
      int i;
      pthread_t rtid[5],wtid[5];
      sem_init(&mutex,0,1);
      sem_init(&writeblock,0,1);


 for(i=0;i<=1;i++)
  {
      pthread_create(&wtid[i],NULL,writer,(void *)i);
      pthread_create(&rtid[i],NULL,reader,(void *)i);
  }
  sleep(2);
for(;i<=4;i++)
  {
	pthread_create(&wtid[i],NULL,writer,(void *)i);    
	pthread_create(&rtid[i],NULL,reader,(void *)i);
  }
  for(i=0;i<=4;i++)
  {
    pthread_join(rtid[i],NULL);
    pthread_join(wtid[i],NULL);
  }
}
