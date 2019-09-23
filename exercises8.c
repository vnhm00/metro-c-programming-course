/*EX8 converts the first letter of every word in a string to uppercase
Write a function that converts the first letter of every word in a string to uppercase.
Write a program that asks user to enter a string and then calls the function above. 
The program keeps asking for strings until user enters "stop" or "STOP". When user enters
stop the program terminates.*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void convert(char *str);

void convert(char *str)
{
    const char s[2] = " ";
    char *token;
    
    //get the first token
    token = strtok(str, s);
    //walk through other tokens
    while( token != NULL )
    {
        token[0] = toupper(token[0]); //change the first letter to upper case
        printf( "%s ", token ); //print
        token = strtok(NULL, s);
    }
    printf("\n");
}

int main () {
    char str[256];
    bool checked = false; //Variable to check when to stop the program
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

