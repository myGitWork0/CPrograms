#include<omp.h>
#include<stdio.h>
#include<time.h>
int main(){
	int a=1000,b=2000,c=3000,d=10,e=20,f=30,i,t;
	clock_t start_time,end_time;
	double cpu_time_used;
	start_time=clock();
	#pragma omp parallel private(i)reduction(+:a,b,c)
	{
		printf("running %d \n",omp_get_thread_num());
		for(i=0;i<100;i++){
			a=a+1;
			b=b+d;
			c=e+f;
		}
	}
	end_time=clock();
	printf("a value is %d \n",a);
	printf("b value is %d \n",b);
	printf("c value is %d \n",c);
	cpu_time_used=((double)(end_time-start_time))/CLOCKS_PER_SEC;
	printf("time taken to run a program %e \n",cpu_time_used);
	double iops=30/cpu_time_used;
	double giops=iops/1000000000;
	printf("giops is: %f \n",giops);
}
