/*
* Fibonacci algorithm with parallel directive task
*
*/

#include <stdio.h>
#include <omp.h>

int fib(int n){
	int i,j;
	if( n < 2 ) 
	return n;
	else{
		#pragma omp taskwait
		i = fib(n - 1);
		#pragma omp taskwait
		j = fib(n - 2);
		return i+j;
	    }
}

int main(int argc,char *argv)
{
	int p;
	printf("Insert n: ");
	scanf("%d",&p);
	omp_set_num_threads(4);
	#pragma omp parralel
	{
	#pragma omp single
	p = fib(p);
	}

	printf("\nfib=%d\n",p);

}
	
