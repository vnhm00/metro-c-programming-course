#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

bool fileDataGenerate(char filename[]);
bool fileRead(char filename[], char *str, int *size);
void writeFile(char filename[], char *str, int size, int position, int num);

bool fileDataGenerate(char filename[])
{
    FILE *file;
    int i = 0, ran = 0;
    char ch = '\0';

    file = fopen(filename,"wb"); //open writing binary file
    if (file == NULL) return false; //if not find file return false

    srand(time(NULL));
    i = rand()%50 + 50; //get a random value from 50 to 100f
    for (; i > 0 ; i--)
    {
        ran = (rand()%940)%94 + 33; //get a random value from 33 to 126 (printable character from ASCII table)
        ch = ran;
        fwrite(&ch, sizeof(char), 1, file); //write into file in binary mode
    }

    fclose(file); //close file after writing
    return true; //return true means writing successful
}


bool fileRead(char filename[], char *str, int *size)
{
    FILE *file;
    int count = 0;
    char ch = '\0';
    file = fopen(filename,"rb"); //open reading binary file
    if (file == NULL) return false; //if not find file return false

    while (!feof(file))
    {
        fread(&ch, sizeof(char), 1, file); //read from file in binary mode
        str[count] = ch;
        count++;
    }
    fclose(file); //close file after reading

    *size = count - 1;
    return true;
}

void writeFile(char filename[], char *str, int size, int position, int num)
{
    FILE *file;
    file = fopen(filename,"wb");
    int i = 0;

    //////////DEBUG PART//////////////////
    printf("\nTHE ORIGINAL DATA\n");
    for (i = 0; i < size; i++) printf("%c",str[i]);
    printf("\n");
    for (i = 0; i < position-1; i++) printf("%c",str[i]);
    for (i = position + num - 1; i < size; i++ ) printf("%c",str[i]);
    printf("\nAFTER REMOVING\n");
    //////////////////////////////////////

    //OVERWRITE DATA IN THE FILE
    for (i = 0; i < position-1; i++) fwrite(&str[i], sizeof(char), 1, file);
    for (i = position + num - 1; i < size; i++ ) fwrite(&str[i], sizeof(char), 1, file);
    fclose(file);
}


int main()
{
    char filename[10]; //string to hold the name of the file
    char *str = {'\0'};
    str = (char *)malloc(MAX*sizeof(char));
    int size = 0, position = 0, num = 0; //variables to hold the file size, position to remove and number of byte(s) to remove

    //ASK USER TO ENTER THE NAME OF THE FILE AND CHUNK SIZE
    printf("Type the name of the file: ");
    scanf("%s",filename);

    if (!fileDataGenerate(filename)) return 0; //Generate data for the file
    if (!fileRead(filename,str,&size)) return 0; //Read data from file remember to str

    //ASK USER THE OFFSET AND NUMBER OF BYTE(S) TO REMOVE
    printf("The file size is %d.\nFrom which position you want to remote byte(s): ",size);
    scanf("%d",&position);
    if (position > size) //if out of data size
    {
        printf("The offset is not valid!");
        return 0;
    }
    printf("Enter number of bytes you want to remove: ");
    scanf("%d",&num);

    //if the remove part is fully in the data
    if (position + num - 1 <= size) writeFile(filename, str, size, position, num);
    else printf("You are trying to remote data that past the end of file!");

    free(str); //free after using
    return 0;
}


