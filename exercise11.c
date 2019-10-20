//EX11
#include <stdio.h>

int main()
{
	#define READFILE "file.txt"
	#define LINESIZE 100

	FILE *file;
	char line[LINESIZE];
	file = fopen(READFILE,"r");
	int a = 0, b = 0, c = 0; //3 variables holding value of 3 numbers
	if (file == NULL) //if cannot find input file
	{
		printf("Input file does not exist");
		return 0;
	}

	fgets(line, LINESIZE, file);
	sscanf(line, "%d %d %d", &a, &b, &c); //scan to get 3 value
	fclose(file); //after reading input, close the file

	//sort 3 numbers
	int aa = a, bb = b, cc = c;
    a = (aa < bb) ? (aa < cc ? aa : cc) : (bb < cc ? bb : cc);
    b = (bb < cc) ? (aa < bb ? bb : (aa < cc ? aa : cc)) : (aa < cc ? cc : (aa < bb ? aa : bb));
    c = (aa < cc) ? (bb < cc ? cc : bb) : (aa < bb ? bb : aa);

    file = fopen(READFILE,"w"); //open file to write 3 number in new order
    fprintf(file, "%d %d %d",a,b,c);
    fclose(file); //close the file after writing

	return 0;
}
