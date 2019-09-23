/*EX7 converts all white space in a string to underscores
Write a function that converts all white space in a string to underscores.
Write a program that asks user to enter a string and then calls the function above. The program
keeps asking for strings until user enters "stop" or "STOP". When user enters stop the program
terminates */

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void convert(char *str);

void convert(char *str)
{
    int i = 0;
    //scan all the letters in the string
    while (str[i])
    {
        if (str[i] == ' ') str[i] = '_'; //if letter is space, change it to underscore
        i++;
    }
    printf("%s\n",str);
}

int main () {
    char str[256];
    bool checked = false; //variable to check when to stop the program
    do
    {
        printf("Enter a string: ");
        gets(str);
        //if the entered string isn't "stop" or "STOP", run the convert function
        if (strcmp(str,"stop") != 0 && strcmp(str,"STOP") != 0) convert(str);
        else checked = true; //else stop the program
    } while (checked == false);
    printf("Program stopped.");
    return(0);
}
