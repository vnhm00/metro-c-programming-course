/*EX4 HOW LONG YOU WANT TO SLEEP
Write a program that asks user to enter current time in 24 hour format and asks how long you want
to sleep. Program then calculates your wake up time and prints it. The program must check that
values are entered in correct format and must print an error message if invalid input is entered.
Program must also check that the entered numbers are in valid range (0 - 23 / 0 - 59). */

#include <stdio.h>

int main()
{
	int currentHour = 0; 
	int currentMin = 0;
	int amountHour = 0;
	int amountMin = 0;
	
	//program must not allow numbers not in the valid range
	do
	{
		printf("Enter current time (hh:mm): ");
		scanf("%d:%d", &currentHour, &currentMin);
		if ((currentHour > 23) || (currentHour < 0) || (currentMin > 59) || (currentMin < 0)) printf("Entered numbers must be in range (0 - 23 : 0 - 59). Try again!\n");
	} while ((currentHour > 23) || (currentHour < 0) || (currentMin > 59) || (currentMin < 0));
	
	do
	{
		printf("How long do you want to sleep (hh:mm): ");
		scanf("%d:%d", &amountHour, &amountMin);
		if ((amountHour > 23) || (amountHour < 0) || (amountMin > 59) || (amountMin < 0)) printf("Entered numbers must be in range (0 - 23 : 0 - 59). Try again!\n");
	} while ((amountHour > 23) || (amountHour < 0) || (amountMin > 59) || (amountMin < 0));
	
	if ((currentMin + amountMin) < 60) printf("If you go to bed now you must wake up at %d:%d", (currentHour + amountHour)%24, currentMin + amountMin);
	else printf("If you go to bed now you must wake up at %d:%d", (currentHour + amountHour + 1)%24, (currentMin + amountMin)%60);
	return 0;
}
