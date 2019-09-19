/*EX6 CAESAR CIPHER
Write a function that performs Caesar cipher on the given string.
The function takes two parameters: the string to be encrypted and an integer indicating the amount
of shift. Assume that only letters A-Z and whitespace characters are used. White space characters
must not be affected by the encryption.

Write a program that uses the function above to create encrypt and decrypt a given text. The
program must ask user to enter the amount of shift and the text to encrypt. The program converts
the string to uppercase before using the encryption function. When user has entered the values the
program prints the original text, the encrypted text and the decrypted text. If the program works
correctly the original text and decrypted text are identical. */

#include <stdio.h>
#include <string.h>

void Shift(char *str, int num);

void Shift(char *str, int key)
{
	char ch;
	for (int i = 0; i < strlen(str); i++) 
	{
		ch = str[i];
		if(ch >= 'A' && ch <= 'Z')
		{
			ch = ch + key;
			if(ch > 'Z') ch = ch - 'Z' + 'A' - 1;
			if(ch < 'A') ch = ch + 'Z' - 'A' + 1;
		}
		str[i] = ch;
	}
	printf("%s\n",str);
}

int main()
{
	char str[256];
	int shiftNumber = 0;
	int i = 0;
    
	printf("Enter a string: ");
	gets(str);
	printf("Enter amount of shift: ");
	scanf("%d", &shiftNumber);
	
	printf("%s\n",str); //print the original text
	//converts the string to uppercase before using the encryption function
	while (str[i])
	{
		str[i] = toupper(str[i]);
		i++;
	}
    
	Shift(str,shiftNumber); //print the encrypted text
	//since encrypt means moving letter shiftNumber to the right, decrypt is moving letter shiftNumber to the left
	Shift(str,-shiftNumber); //print the decrypted text
	
	return 0;
}
