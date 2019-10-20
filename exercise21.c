#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

bool fileDataGenerate(char filename[]);
bool fileCharaterCount(char filename[]);

bool fileDataGenerate(char filename[])
{
    FILE *file;
    int i = 0, ran = 0;
    char ch = '\0';

    file = fopen(filename,"wb"); //open writing binary file
    if (file == NULL) return false; //if not find file return false

    srand(time(NULL));
    for (i = 1000; i >= 0; i--)
    {
        ran = (rand()%2550)%255; //pick random value for r (from 0 to 255)
        ch = ran;
        fwrite(&ch, sizeof(char), 1, file); //write into file in binary mode
    }

    fclose(file); //close file after writing
    return true; //return true means writing successful
}

bool fileCharaterCount(char filename[])
{
    FILE *file;
    int i = 0, j = 0;
    char ch = '\0';
    int count[256] = {0}; //array to hold the frequency of characters

    file = fopen(filename,"rb"); //open reading binary file
    if (file == NULL) return false; //if not find file return false

    while (!feof(file))
    {
        fread(&ch, sizeof(char), 1, file); //read from file in binary mode
        j = ch;
        if (j<0) j = 256 + j;
        count[j]++; //increment value in j position means the character that has j value appears 1 more time
    }

    fclose(file); //close file after reading

    for (i = 0; i < 10; i++) //find 10 most frequency characters
    {
        int max = 0, pos = 0; //init before scanning
        for (j = 0; j < 256; j++)
        {
            if (max < count[j])
            {
                max = count[j];
                ch = j;
                pos = j;
            }
        }
        count[pos] = -1; //marks that character is already counted
        printf("%.2d. | %c | - char num %d - appears %d\n", i+1, ch, pos, max);
    }

    return true; //return true means count successful
}

int main()
{
    char filename[10]; //string to hold the name of the file

    //ASK USER TO ENTER THE NAME OF THE FILE
    printf("Type the name of the file (.bin): ");
    scanf("%s",filename);

    //GENERATE DATA FOR THE FILE
    if (!fileDataGenerate(filename)) return 0;
    //COUNT CHARATERS FROM THE FILE
    if (!fileCharaterCount(filename)) return 0;

    return 0;
}

