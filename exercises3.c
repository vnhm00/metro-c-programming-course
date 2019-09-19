/*EX3 STUDENT GRADE
Write a function that takes an array of integers and array size as a parameter and returns a float.
The function calculates average value of the array and returns it.

Write a program that uses an array to hold course grades. The array is initialized to zero in the
beginning. The program asks user how many students are to be graded. Program must not allow
values that are greater that the array size. Then the program asks user to enter a grade for
each student. Only values in the range 0-5 are accepted. Student number that is displayed to
the user is array index + 45000. (For example if array index is 2 user is asked to enter grade for student nr: 45002)

Program must check that array bounds are not violated!
In the end program calculates the average of course grades using the average function and 
prints the average with two decimal accuracy. */

#include <stdio.h>

float Average(float a[],int n);

float Average(float a[],int n)
{
	float sum = 0;
	for (int i=0; i<n; i++) sum+=a[i];
	return sum / n;
}

int main()
{
	float grade[11] = { 0 }; //an array holding course grades is initialized to zero
	int n = 0; //number of students
	int i = 0; //counting variable
	
	//program must not allow the number of students that are greater that the array size
	do
	{
		printf("Enter the number of students: ");
		scanf("%d", &n);
		if (n >11) printf("Number of students must be less or equal to 11. Try again!\n");
	} while (n > 11);
	
	while (i < n) //read the grade of student number i
	{
		printf("Student %d grade: ",i+45000);
		scanf("%f",&grade[i]);
        
		//check whether the grade is in the range 0-5
		if ((grade[i]>=0) && (grade[i]<=5)) i++;
		else printf("Grade should be in the range 0-5!\n");
	}
    
	printf("Average: %.2f",Average(grade,n)); //prints the average with two decimal accuracy
	
	return 0;
}
