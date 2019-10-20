#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void passwordGenerator(char *pass, int length, const char *words[]);

void passwordGenerator(char *pass, int length, const char *words[])
{
    pass = (char*)malloc(length*sizeof(char));
    int ran = 0, i = 0, ranpos = 0;
    for (i = 0; i < length; i++)
    {
        ran = (rand()%940)%94 + 33; //get a random value from 33 to 126 (printable character from ASCII table)
        pass[i] = ran; //assign that character to password
    }
    ran = (rand()%100)%10; //get a random position to get a random word
    i = length - strlen(words[ran]);
    ranpos = (rand()%i*10)%i; //get a random value to get the position in the password array to copy the word

    for (i = 0; i < strlen(words[ran]); i++) //assign the word into the password array
    {
        pass[ranpos] = words[ran][i];
        ranpos++;
    }
    //PRINT PASSWORD
    printf("%d letters random password: ",length);
    for (i = 0; i < length; i++) printf("%c", pass[i]);
    printf("\n");

    free(pass); //free pass after using
    return;
}

int main()
{
    srand(time(NULL)); //to get random value
    const char *words[11] = {"fish", "cloud", "shark", "flower", "moon",
                             "sky", "stars", "sleep", "tea", "songs", "\0"}; //array of constant char pointers
    printf("Array of ten words: ");
    for (int i = 0; i < 10; i++) printf("%s ", words[i]);
    printf("\n");

    char *password; //array to hold the password
    passwordGenerator(password, 15, words);
    passwordGenerator(password, 25, words);
    passwordGenerator(password, 35, words);

    return 0;
}
