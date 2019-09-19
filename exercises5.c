/*EX5 MATRIX AND VECTOR MULTIPLICATION
Write a program which multiplies a 3 element vector (3 by 1 matrix) with 3 by 3 matrix.
Program asks user to enter initial values for vector and matrix.
Write a function to do matrix multiplication. Function takes three parameters: Result vector, source
vector, source matrix. Function returns no value but modifies result vector. Function may not modify
source values.
Program must print the initial values before multiplication and result after multiplication.
The matrix multiplication function must do only the multiplication and may not print anything */

#include <stdio.h>

void Multiplication(int result[], int vector[], int matrix[3][3]);

void Multiplication(int result[], int vector[], int matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) result[i] += matrix[i][j] * vector[j];
    }
}

int main()
{
	int matrix[3][3] = { 0 };
	int result[3] = { 0 };
	int vector[3] = { 0 };
	int i = 0;
	int j = 0;

	for (i = 0; i < 3; i++)
	{
        printf("Enter values for matrix %d row: ",i+1);
        scanf("%d %d %d", &matrix[i][0], &matrix[i][1], &matrix[i][2]);
	}
	
	printf("\n");
	printf("Enter values for vector: ");
	scanf("%d %d %d", &vector[0], &vector[1], &vector[2]);
	
	Multiplication(result, vector, matrix);
	
	printf("\n");
	//PRINT THE MATRIX
	printf("Matrix = \n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++) printf("%d ",matrix[i][j]);
		printf("\n");
	}
	
	printf("\n");
	//PRINT THE VETOR
	printf("Vector = \n");
	for (i = 0; i < 3; i++) printf("%d\n",vector[i]);
	
	printf("\n");
	//PRINT THE RESULT MATRIX
	printf("Result = \n");
	for (i = 0; i < 3; i++) printf("%d\n",result[i]);
	
	return 0;
}
