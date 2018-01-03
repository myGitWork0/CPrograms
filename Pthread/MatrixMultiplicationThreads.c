#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int mul[3][3],tot[3][3];
void *matrixmul(void *);
void main()
{   
    void *status;
    int i,j;
    int pos[2];	
    printf("Enter the Number :\n");
    for(i=0;i<3;i++)
    	for(j=0;j<3;j++){
		printf("\nenter element for mul[%d][%d] ",i,j);
		scanf("%d",&mul[i][j]);
	}
            
       for(i=0;i<3;i++)
	for(j=0;j<3;j++){
	 pos[0]=i;
	 pos[1]=j;
	 pthread_t t1;
            pthread_create(&t1,NULL,&matrixmul,&pos);     
               pthread_join(t1, NULL);                            
       } 
        
        for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf(" %d ",tot[i][j]);
		}
		printf("\n");
	}
}
void *matrixmul(void *t)
{ 
   int *temp=(int *)t;
   int k;
   for(k=0;k<3;k++){
	tot[*temp][*(temp+1)]+=mul[*temp][k]*mul[k][*(temp+1)];
   }
    return NULL;
}