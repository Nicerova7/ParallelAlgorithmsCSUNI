/*
* Show numbers from 1 to 100, 5 for each tread
*/


#include <stdio.h>
#include <omp.h>
#define N 99
int main(argc,argv)
int argc;
char *argv[];
{
	int tid,i;
	int a[N];
	omp_set_num_threads(4);
	#pragma omp parallel shared(a) private(i)
	{

	
	#pragma omp for	
	for(i = 0 ; i <= N ; i++)	
	a[i]=i; 
	

	#pragma omp for schedule(dynamic,5) ordered
	for( i = 0 ;i <= N; i++)
	{	
	    #pragma omp ordered
	    printf("Index %d in thread %d\n",a[i],omp_get_thread_num());
        }

	}
}

