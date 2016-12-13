/*
*  Programa that modifies two private
*  variables "i","j" within a parallel directive 
*  without changing their original values
*/

#include <stdio.h>
#include <assert.h>
#include <omp.h>

int main(argc,argv)
int argc;
char *argv[];
{
	int nthread,tid;
	int i,j;
	int *ptr_i,*ptr_j;
	omp_set_num_threads(4);
	i = 1;
	ptr_i = &i;
	j = 2;
	ptr_j = &j;
	printf("Sequential start: \ni: %d\nj: %d\n",i,j);
	printf("Parallel: \n");
	#pragma omp parallel private (i,j)
	{
		i = 100;
		j = 200;
		tid = omp_get_thread_num();
		assert(*ptr_i== 1 && *ptr_j == 2);
		printf("Thread %d:\n",tid);
		printf("i : %d\n",i);
		printf("j : %d\n",j);	
	}
	assert(i == 1 && j == 2);		
	printf("Sequential :  \ni : %d\nj : %d\n",i,j);
}

		
