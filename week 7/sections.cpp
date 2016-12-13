/*
* We define two sections for two funcions: ini() that initializes an array 
* and sum() that calculates the sum of the values of an array.
* It is ensured that the sum is calculated after the array has been initialized 
* this with the bool variable
*/

#include <iostream>
#include <stdlib.h>
using namespace std;
#include <omp.h>
bool boolean = false;

double suma(int n,double b[]);
void ini(int n,double b[]);
int num_random(void);

int main(int argc,char *argv[])
{	
	srand(time(NULL));
	int N = 100000;
	double sum;
	double A[N];
	double start;
	omp_set_num_threads(5);
	#pragma omp parallel shared(N,A) 
	{
	#pragma omp master
	start = omp_get_wtime();
	#pragma omp barrier
	
	#pragma omp sections
	{
		#pragma omp critical
		{
		ini(N,A);
		}
		#pragma omp section
		{
		sum = suma(N,A);
		}
	}
	#pragma omp single
	{
	cout<<"The sum is: "<<sum<<endl;
	}
	
	#pragma omp master
	cout<<"Time is: "<<omp_get_wtime()-start<<endl;
	#pragma omp barrier
	}
}

int num_random(void)
{	
  int p;
  
  p = (( rand() / (float)RAND_MAX )*9)+1; //random number (Range 1-10)
  return p;
}

void ini(int n,double b[])
{		
	int i;
	for(i = 0;i <n ; i++) b[i] = num_random();
	boolean = true;	
}

double suma(int n,double b[])
{	
	if(boolean == true)
	{	
		int i;
		double a=0.0;
		for(i = 0; i<n ; i++)	a += b[i];
		return a;
	}
}


