#include <stdio.h>
#include <omp.h>

int main(void)
{
	float i,startx,endx,h,s1,s2,s3,s4,s,yp,yp1;
	
	startx = 0;
	endx = 1;
	//1st case
	h = 0.1;
	//2nd case
	// h = 0.001;
	//3rd case
	 //h = 0.0001;

	#pragma omp parallel shared(yp,startx,endx,h) private(i)
	{
	#pragma omp master
	yp = 1;
	#pragma omp barrier

	#pragma omp single
	for(i = startx; i<=endx+h ; i = i+h){
		#pragma omp task
		s1 = i*yp;	// yp initial value de y(t), first slope
		
		#pragma omp taskwait
		s2 = (i+(h/2))*(yp+((h/2)*s1));	// slope 2
		
		#pragma omp taskwait
		s3 = (i+(h/3))*(yp+((h/2)*s2)); // slope 3		
		#pragma omp taskwait
		s4 = (i+h)*(yp+(h*s3));  // slope 4
	

		#pragma omp taskwait
		s = (s1 + (2*s2) + (2*s3) + s4) / 6;  // avg
		yp1 = yp + (h*s);  // next value yp
		yp = yp1;
		
	}
	
	#pragma omp single
	printf("h = %f, f = %f\n",h,yp);
	}
}

