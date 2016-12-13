/*
* Matrix multiplication vector 
*
*/

#include <iostream>
#include <omp.h>
using namespace std;
#define NMAX 1000
#define MMAX 1000

int main(int argc,char *argv[])
{
	omp_set_num_threads(2);
	int i,j,n,m;
	double a[NMAX],b[NMAX*MMAX],c[MMAX];
	
	cout<<"Enter n: "<<endl;
	cin>>n;
	cout<<"Enter m: "<<endl;
	cin>>m;
	cout<<endl;
	double start = omp_get_wtime();
	#pragma omp parallel private(i,j) shared(a,b,c)
	{
	
	
	#pragma omp for 
	for(i = 0 ;i<m ; i++)
	{	
		c[i] = 2.0;
	}
	
	#pragma omp for 
	for(i = 0 ;i<m ; i++)
	{	 
		for(j = 0; j<n ;j++)
		{
			b[i*n+j] = i;
		}
	}
	
	#pragma omp for schedule(static)
	for(i = 0 ; i<n ; i++)
	{
		a[i] = 0.0;
		for(j = 0 ; j<m; j++)
		{
			a[i] += b[i*n+j]+c[j];
		}	
	}
	
	#pragma omp for ordered
	for( i = 0; i<n; i++)
	{	
		#pragma omp ordered
		cout<<"thread "<<omp_get_thread_num()<<"a["<<i<<"] = "<<a[i]<<endl;
		cout<<"\t"<<endl;
	}
	
	}
	
	cout<<"\t Time is: "<<omp_get_wtime()-start<<endl;
		
}

