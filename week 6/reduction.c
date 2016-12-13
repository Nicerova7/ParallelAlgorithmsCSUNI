/*
* Calculate the sum of n numbers with threads
* with parallel directives
*/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc,char *argv[])
{
	int a,i;
	omp_set_num_threads(3);
	#pragma omp parallel shared(a) private(i) 
						 
	{
	#pragma omp master			  
	a = 0;
	#pragma omp barrier			 
	#pragma omp for reduction(+:a) 	
	for( i = 0 ; i < 10; i++)
	{
		a += i;
	}
	#pragma omp single			
	printf("The sum is: %d\n",a);
	
	}	
	
}

