/*
* Ordered loop
*/

#include <iostream>
#include <omp.h>
using namespace std;

int main(int argc,char *argv[])
{
	int i,j;
	int n = 9;
	int a[n],b[n];

	omp_set_num_threads(3);

	#pragma omp parallel private(i) shared(a,b,n)
	{	
	
	
	
	#pragma omp single
		{
			cout<<"thread: "<<omp_get_thread_num()<<endl;
		}

	#pragma omp for schedule(runtime) ordered //ordered for ordered print
						  // runtime no specified then(dynamic,1)
	for(i = 0; i <n ; i++)
	{	
			
			a[i] = i;
			#pragma omp ordered
			cout<<"thread: "<<omp_get_thread_num()<<", execute iteracion: "<<i<<", a_i: "<<a[i]<<endl;
	}
	
	#pragma omp single
		{
			cout<<"thread: "<<omp_get_thread_num()<<endl;
		}
	
	#pragma omp for schedule(runtime) ordered //"ordered" for ordered print
						  // runtime no specified then (dynamic,1)
	for(i = 0; i < n ;i++)
	{	
		
		b[i] = 2*a[i];
		#pragma omp ordered
		cout<<"thread: "<<omp_get_thread_num()<<", execute iteracion: "<<i<<", b_i: "<<b[i]<<endl;
	}
		
	}
	
}	
