#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t mutex;
pthread_t prod[5],con[5];
sem_t full,empty;
int a[5],pos=0,var=0,cpos=0;
void *producer(){
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	a[pos%5]=var;
	printf("produced %d in a[%d]\n",var,pos);
	pos++;
	var=var+10;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
}

void *consumer(){
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	if(cpos<pos){
	int temp=a[cpos%5];
	cpos++;
	if(temp==1000){
		printf("consumed 1000\n");
		exit(EXIT_SUCCESS);
	}
	printf("consumed %d \n",temp);
	}
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	
}
void initialise(){
	sem_init(&full,0 ,5);
        sem_init(&empty,0 ,0);
	pthread_mutex_init(&mutex,NULL);
}
void main(){
	initialise();
	int i;
	while(1){
	for(i=0;i<5;i++){
		pthread_create(&prod[i],NULL,&producer,NULL);
		pthread_create(&con[i],NULL,&consumer,NULL);
	}
	}
	for(i=0;i<5;i++){
		pthread_join(prod[i],NULL);
		pthread_join(con[i],NULL);
	}
		
}

