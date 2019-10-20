//EX10
#include <stdio.h>

int main()
{
	#define INPUT "input.txt"
	#define LINESIZE 100
    //INIT FILE AND VARIABLES
	FILE *input_file;
	input_file = fopen(INPUT,"r");
	char line[LINESIZE];
	int number = 0; //THE INPUT TOTAL NUMBERS
	int count = 0; //THE ACTUAL INPUT NUMBERS
	float value = 0, sum = 0;

	//IF CANNOT FIND INPUT FILE
	if (input_file == NULL)
	{
		printf("Input file does not exist");
		return 0;
	}

    //READ THE FIRST LINE OF INPUT AND SCAN FOR THE TOTAL OF NUMBERS
	fgets(line, LINESIZE, input_file);
	sscanf(line, "%d", &number);
	//READ THE REST OF THE INPUT
	while (!feof(input_file))
	{
		if (fgets(line, LINESIZE, input_file) != NULL)
		{
			sscanf(line, "%f", &value);
	    	count++;
    		sum += value; //ADD NUMBER TO THE SUM
	    }
	}
	fclose(input_file); //CLOSE INPUT AFTER READING

	//IF THE ACTUAL TOTAL OF NUMBERS EQUALS TO THE INPUT TOTAL OF NUMBERS
	if (count == number) printf("Average of %d numbers is: %.2f",number,(float)sum / number);
	else //ELSE PRINT ERROR
	{
		printf("Error! Tried to read %d numbers, %d numbers were read.\n",number,count);
		printf("Average of %d numbers is: %.2f",count, (float)sum / count);
	}

	return 0;
}
