#include<pthread.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include <errno.h>
extern int errno ;
int tot = 1;
void *factorial(void *);
void *dec(void *);
void main()
{   
    void *status;
    int fact,temp;	
    pthread_t t1,t2;    
    printf("Enter the Number :\n");
    scanf("%d",&fact);
    if(fact==0){
	printf("Factorial of %d is = 1\n",fact);
    }
    if(fact > 0 && fact <= 2) {   
       printf("Factorial of %d is = %d\n",fact,tot);
    }
    else {           
       while(fact > 0 )   
       {
            if(pthread_create(&t1,NULL,&factorial,&fact)) {  
		printf( "Error Value is : %s\n", strerror(errno) );      
              exit(EXIT_FAILURE);
            }
                if(pthread_join(t1, &status)) {               
			printf( "Error Value is : %s\n", strerror(errno) );             
                   exit(EXIT_FAILURE);
                }                    
            if(pthread_create(&t2,NULL,&dec,&fact)) {
		printf( "Error Value is : %s\n", strerror(errno) );
              exit(EXIT_FAILURE);
            }
                if(pthread_join(t2, &status)) {
			printf( "Error Value is : %s\n", strerror(errno) );
                   exit(EXIT_FAILURE);
                }           
       } 
		printf("factorial is = %d\n",tot);   
       } 
	
}
void *factorial(void *t)
{ 
   int *temp=(int *)t;
    tot = (tot)*(*temp) ;
    return NULL;
}
void *dec(void *b)
{ 
     int *temp = (int *)b;
     --(*temp); 
    return NULL;
}