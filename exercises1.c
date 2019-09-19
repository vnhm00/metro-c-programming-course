/*EX1 CALCULATE AVERAGE WITHOUT USING ARRAY
Do not use an array to hold numbers that user enters in this exercise!
Write a program that calculates average of positive numbers that user enters.
Program asks user to enter numbers and calculates the average of entered numbers when user enters 0 as the number.
The zero is not included in the average. If user enters a negative number the program must print a
message telling that only positive numbers are accepted and ignore the negative number. */

#include <stdio.h>

int main()
{
	int n = 0; //input reading variable
	int count = 0; //the total number of valid entered number
	int sum = 0; //sum of the valid number
    
    //READ THE INPUT UNTIL NUMBER 0 IS ENTERED
	do
	{
		printf("Enter a number: ");
		scanf("%d", &n);
		if (n < 0) //if the entered number is negative
		{
			printf("Only positive numbers are accepted!");
			printf("\n");
		}
		else if (n > 0) //if the entered number is positive
		{
			sum += n; //add the number to the sum
			count++; //increment the total number
		}
		else if (count != 0) printf("Average: %f", sum / (float) count); //if 0 print the result
		else printf("No entered number"); //if count = 0, meaning no number is entered
	} while (n != 0); 
	return 0;
}
