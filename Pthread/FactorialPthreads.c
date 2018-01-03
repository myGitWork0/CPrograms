#include<pthread.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include <errno.h>
#define NUM_THREADS 10
extern int errno ;

int tot[3][3];
void *factorial(void *);
void main()
{   
    void *status;
    int mul[3][3],i,j;
    int fact[2];	
        
    printf("Enter the Number :\n");
    for(i=0;i<3;i++){
    	for(j=0;j<3;j++){
		scanf("%d",&mul[i][j]);
	}
    }         
       for(i=0;i<3;i++){
	for(j=0;j<3;j++){
	 fact[0]=i;
	 fact[1]=j;
	pthread_t t1;
	 pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
            if(pthread_create(&t1,&attr,&factorial,&fact)) {  
		printf( "Error Value is : %s\n", strerror(errno) );      
              exit(EXIT_FAILURE);
            }
               pthread_join(t1, NULL);                            
       } 
       } 
        
}
void *factorial(void *t)
{ 
   int *temp=(int *)t;
    printf("%d %d\n",*temp,*temp+1);
    pthread_exit(0);
} 
