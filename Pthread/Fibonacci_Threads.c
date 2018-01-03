#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int fib,a[10000];
void *fibonacci(void *);
void *storing(void *);
void main()
{  
    void *status;
    int index[2],c=1,f;
    index[0]=0;
    index[1]=1;
    a[0]=0;
    a[1]=1;
    a[2]='\0'; 
    printf("\nenter element till which you need fibonacci series :");
    scanf("%d",&f);   
     	while(fib<=f){
         c++;
	 pthread_t t,s;
            pthread_create(&t,NULL,&fibonacci,&index);     
               pthread_join(t, NULL);  
            pthread_create(&s,NULL,&storing,&c);
               pthread_join(s, NULL); 
       } 
      int l=0;
      printf("\n");
      while(l<c){
                
		printf("%d , ",a[l]);
                l++;
	}
}
void *fibonacci(void *param){ 
   int *temp=(int *)param;
   fib=*temp+*(temp+1);
   *temp=*(temp+1);
    *(temp+1)=fib;
    pthread_exit(0);
}

void *storing(void *param){
      int *temp=(int *)param;
      a[*temp]=fib;
      a[*(temp+1)]='\0';
      pthread_exit(0);
}
