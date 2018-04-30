#include<stdio.h>
#include<omp.h>
#include<time.h>
int main()
{
float a=0.0,b=1.1,c=2.2,d=3.3,e=4.4,f=5.5,g=6.6;
int t,i;
clock_t start_time,end_time;
double cpu_time_used;
start_time=clock();
#pragma omp parallel private(t,i) reduction(+:g,a,d)
{
t=omp_get_thread_num();
printf("running %d\n",t);
for(i=0;i<100;i++)
{
g=g+1;
a=b+c;
d=e+f;
}
}
end_time=clock();
printf("total is %f\n",g);
printf("total is %f\n",a);
printf("total is %f\n",d);
//printf("number of threads is %d",omp_get_thread_num());
cpu_time_used=((double)(end_time-start_time))/CLOCKS_PER_SEC;
printf("time taken to run program is %e\n",cpu_time_used);
double flops=100/cpu_time_used;
double gflops=flops/1000000000;
printf("gflops cal %f\n",gflops);
}

