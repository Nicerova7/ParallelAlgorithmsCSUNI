#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(argc,argv) 
int argc;
char *argv[];
{	
	srand(time(NULL));
	int i;
	float *array_r,max,min;
	omp_set_num_threads(2);
	
	#pragma omp parallel shared(array_r,max,min) private(i) 
	{

	#pragma omp master					
  	array_r = (float *)malloc(sizeof(float) * 10);	
	#pragma omp barrier
	
 
	#pragma omp for
  	for (i = 0; i < 10; i++) 
 	array_r[i] = ( rand() / (float)RAND_MAX )*49 + 1;
  	
	#pragma omp for ordered	
	for(i = 0 ; i <10 ; i++)
	#pragma omp ordered
	printf("hilo: %d,indice: %d, valor : %f\n",omp_get_thread_num(),i,array_r[i]);

	#pragma omp master	
	max = min = array_r[0];
	#pragma omp barrier

	#pragma omp for schedule(dynamic,1)		
	for( i = 1 ; i < 10 ; i++)
	{	
		
		if( array_r[i] > max)
			max = array_r[i];
		
		if(array_r[i] < min)
			min = array_r[i];
	
	}
		
	#pragma omp single
	printf("\nmax: %f\nmin: %f\n",max,min);

	}
}
