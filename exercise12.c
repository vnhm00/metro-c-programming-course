//EX12

#include <stdio.h>
#include <string.h>

int readInput();
#define LINESIZE 100

struct item_record
{
    char name[256];
    float price;
} items[21];

int readInput()
{
    char filename[10];
    char line[LINESIZE];
    FILE *file;
    float tprice = 0;
    char tname[256] = {'\0'};
    int count = 0;
    //Open file
    printf("Type the name of the file: ");
    scanf("%s",filename);
    file = fopen(filename,"r");
    if (file == NULL) return 0; //if cannot find file, exit

    //while not read till the end of the file
	while (!feof(file))
	{
		if (fgets(line, LINESIZE, file) != NULL)
		{
		    count++;
		    if (count<=20) //assure the number of items can be hold on the array
            {
                if (sscanf(line, "%f;%[^\n]s", &tprice, tname) == 2)
                {
                    items[count-1].price = tprice;
                    strcpy(items[count-1].name,tname);
                }
                else return -count; //input error in item number count
            }
        }
	}
	fclose(file); //close file after reading
	if (count>0) return count; // if count > 0 means all items are successful read
	return count;  //else there is an error, the return value will be negative
}

int main()
{
    int count = readInput(); //count = number of valid items were read or the position of invalid input
    switch (count)
    {
        case -20 ... -1: //There is an error in line count
            printf("Error in reading file. Check line %d and try again",-count);
            break;

        case 0: //Cannot file input file
            printf("Input file does not exist");
            break;

        case 1 ... 20: //Successful read count items
            printf("%d items were read\n", count);
            printf("%-40s%-40s\n","NAME","PRICE");
            for (int i = 0; i<count; i++)
            {
                printf("%-40s%-40.2f\n",items[i].name,items[i].price);
            }
            break;

        default: //Too many items
            printf("Too many items! 20 first items were read\n");
            printf("%-40s%-40s\n","NAME","PRICE");
            for (int i = 0; i<20; i++)
            {
                printf("%-40s%-40.2f\n",items[i].name,items[i].price);
            }
            break;
    }
    return 0;
}
