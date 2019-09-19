//EX2 FLOATING ARRAY
#include <stdio.h>

int main()
{
	float a[12]; //array with 12 elements
	float income; //yearly gross income variable
	
	printf("Enter yearly gross income: "); 
	scanf("%f", &income);
	
	//SCAN THE ARRAY
	for (int i=0; i<12; i++)
	{
	    a[i] = income / 12.5; //assigns values to the array by diving gross income with 12.5
	    if (i==6) a[i] = a[i] * 1.5; //element 6 is assigned value that you get from  gross/12.5 * 1.5
	    printf("element[%d] = %.4f\n",i,a[i]); //print a[i]
	}
	printf("total = %f",income); //print the total
	
	return 0;
}
