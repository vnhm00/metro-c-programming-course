#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 256

int main(void)
{
    FILE *file;
    file = fopen("file.txt","w"); //open the writing file

    char *string;
    char line[LINESIZE];

    //read input line and write it to the writing file
    while (fgets(line, LINESIZE, stdin)!=NULL && strcmp(line,".\n")!=0)
    {
        string = (char *) malloc(LINESIZE * sizeof(char));
        sscanf(line, "%[^\n]s", string);
        fprintf(file, "%d:%s\n",strlen(string),string);
        if(string == NULL) printf("ERROR");
        free(string); //free string after reading
    }

    fclose(file); //close file after writing
    return 0;
}
