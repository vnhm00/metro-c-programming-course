// TODO: insert other include files here
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
// TODO: insert other definitions and declarations here
#define STRING_SIZE 256
#define MATRIX_SIZE 10
#define LINE_SIZE 100
#define NUMBER_OF_SHIP 5
#define NUMBER_OF_SURROUNDING_SQUARE 8
#define NUMBER_OF_SURROUNDING_SQUARE2 4


bool validPoint(char mat[MATRIX_SIZE][MATRIX_SIZE], int row, int col)
{
	if (row < 0 || row > 10 || col < 0 || col > 10) return false;
	if (mat[row][col] == 'x' || mat[row][col] == '-' || mat[row][col] != 'o') return false;
	return true;
}

bool surrounded(char mat[MATRIX_SIZE][MATRIX_SIZE],int row, int col)
{
	int rowAdd[NUMBER_OF_SURROUNDING_SQUARE] = {-1,-1, 0, 1, 1, 1, 0, -1}; //ROW COORDINATE TO ADD
	int colAdd[NUMBER_OF_SURROUNDING_SQUARE] = { 0, 1, 1, 1, 0,-1,-1,-1}; //COLUMN COORDINATE TO ADD
	for (int i = 0; i < NUMBER_OF_SURROUNDING_SQUARE; i++)
		if (!validPoint(mat,row + rowAdd[i], col + colAdd[i])) return false; //If the surrounding point already has ships return false
	return true;
}

void initmatrix(char mat[MATRIX_SIZE][MATRIX_SIZE], int mode)
{
	//INIT FIRST WITH DEFAULT VALUE
    for(int i = 0; i < MATRIX_SIZE; i++)
    	for (int j = 0; j < MATRIX_SIZE; j++) mat[i][j] = 'o';
    if (mode == 1) return; //DON'T NEED TO INIT SHIPS

    int shipsLength[NUMBER_OF_SHIP] = {5,4,3,3,2};
    int count = 0;
    bool isShip = false;
    srand(time(NULL));
    while (count<5)
    {
    	srand(time(NULL));
        int isVertical = (rand() % 100)%2;
        int rowAdd = 0, colAdd = 0, row = 0, col = 0;

        if (isVertical == 0) rowAdd = 1;
        else colAdd = 1;

        do
        {
        	//Random 2 row and column variables to set the ship
        	row = (rand() % 100)%10;
        	col = (rand() % 100)%10;
        } while ( (row +shipsLength[count]*rowAdd>9) || (col + shipsLength[count]*colAdd>9) ); //random until the ship fits in the grid

        for (int i = 0; i < shipsLength[count]; i++)
        	if (mat[row+i*rowAdd][col+i*colAdd]!='o' || surrounded(mat,row+i*rowAdd,col+i*colAdd)==false) isShip = true;
        if (isShip == false)
        {
        	for (int i = 0; i < shipsLength[count]; i++) mat[row+i*rowAdd][col+i*colAdd]=(count) + 'A';
        	count++;
        } else isShip = false;
    }
};

void printGame(char mat1[MATRIX_SIZE][MATRIX_SIZE], char mat2[MATRIX_SIZE][MATRIX_SIZE])
{
    printf("\n");
    int i = 0, j = 0;
    printf("\t%-35s%-35s\n\t","You","Computer");
    for (i = 0; i < MATRIX_SIZE; i++)
    	printf("%-3d",i);
    printf("%-5c",' ');
    for (i = 0; i < MATRIX_SIZE; i++)
        	printf("%-3d",i);
    for (i = 0; i < MATRIX_SIZE; i++)
    {
        printf("\n\t");
        for (j = 0; j < MATRIX_SIZE; j++) printf("%-3c",mat1[i][j]);
        printf("%-1c%d%-3c",' ',i,' ');
        for (j = 0; j < MATRIX_SIZE; j++) printf("%-3c",mat2[i][j]);
        printf("%-3c",' ');
        switch (i)
        {
            case 4:
                printf("-- NOTE --");
                break;
            case 5:
                printf("o : Hasn't shot point");
                break;
            case 6:
                printf("- : Shot point");
                break;
            case 7:
            	printf("x : Ship hit");
                break;
            case 8:
            	printf("A/B/C/D/E : Your alive ship");
				break;
            case 9:
            	printf("%-6s%s"," ", "or opponent sink ship");
                break;
        }
    }
    printf("\n");
}

bool shot(char mat1[MATRIX_SIZE][MATRIX_SIZE], char mat2[MATRIX_SIZE][MATRIX_SIZE], int row, int col)
{
	if (mat1[row][col] == 'o')
	{
		mat2[row][col] = '-';
		return false;
	}

	mat2[row][col] = 'x';
	return true;
}

int compTurn(char mat[MATRIX_SIZE][MATRIX_SIZE], int hitShip[NUMBER_OF_SHIP], bool direction[NUMBER_OF_SURROUNDING_SQUARE2], int *mode, int *row, int*col, int *count, bool *isShiphitting)
{
	srand(time(NULL)); srand(time(NULL));
	int rowAdd[NUMBER_OF_SURROUNDING_SQUARE2] = {-1, 0, 1, 0}; //ROW COORDINATE TO ADD
	int colAdd[NUMBER_OF_SURROUNDING_SQUARE2] = { 0, 1, 0,-1}; //COLUMN COORDINATE TO ADD
	if (*isShiphitting == false)
    {
    	do
    	{
    		*row = (rand() % 100)%10;
    		*col = (rand() % 100)%10;
    	} while (mat[*row][*col]=='x' || mat[*row][*col]=='-');
    }
    else
    {
        if (*count == 0)
        {
            do
            {
                (*mode)++;
                if (*mode==4) *mode=0;
            } while (mat[*row + rowAdd[*mode]][*col + colAdd[*mode]]=='-' || direction[*mode] == false);
        }
	    direction[*mode] = false;
	    if (mat[*row + rowAdd[*mode]][*col + colAdd[*mode]] != '-')
	    {
            *row += rowAdd[*mode];
    		*col += colAdd[*mode];
    		if (*row < 0 || *row > 10 || *col < 0 || *col > 10)
    		{
    			switch (*mode)
    			{
    				case 0:
    					*mode = 2;
    					break;
    				case 1:
    					*mode = 3;
    					break;
    				case 2:
    					*mode = 0;
    					break;
    				case 3:
    					*mode = 1;
    					break;
    				default:
    					break;
    			}
    		}
	    }
	    else
	    {
	        switch (*mode)
			{
				case 0:
					*mode = 2;
					break;
				case 1:
					*mode = 3;
					break;
				case 2:
					*mode = 0;
					break;
				case 3:
					*mode = 1;
					break;
				default:
					break;
			}
	    }
		while (mat[*row][*col] == 'x')
		{
			*row += rowAdd[*mode];
			*col += colAdd[*mode];
		}
    }

	if (*count>0) printf("\tComputer get another shot. Computer shot at point %d-%d. ", *row, *col);
	else printf("\tComputer's turn. Computer shot at point %d-%d. ", *row, *col);

	char chtemp = mat[*row][*col];
	(*count)++;
	if (shot(mat, mat, *row, *col) == false)
	{
		printf("Missed!\n");
		if (*isShiphitting == true)
		{
		    *row -= rowAdd[*mode];
    		*col -= colAdd[*mode];
		    *mode = -1;
		}
		return -1;
	}

	hitShip[chtemp - 'A']--;
	if (hitShip[chtemp - 'A'] != 0)
	{
	    if (*isShiphitting == false)
	    {
	        do *mode = ((rand() % 100)%4);
        	while (*row + rowAdd[*mode] < 0 || *row + rowAdd[*mode] > 9 || *col + colAdd[*mode] < 0 || *col + colAdd[*mode] > 9 || mat[*row + rowAdd[*mode]][*col + colAdd[*mode]]=='-');

    	    direction[*mode] = false;
		    *isShiphitting = true;
	    } else
	    {
	        if (*mode == 0 || *mode == 2)
	        {
	            direction[1] = false;
	            direction[3] = false;
	        }
	        if (*mode == 1 || *mode == 3)
	        {
	            direction[0] = false;
	            direction[2] = false;
	        }
	    }
		printf("Hit your ship!\n");
	}
	else
	{
		printf("Your ship %c has been sunk\n", chtemp);
		*mode = -1; *isShiphitting = false;
		for (int i = 0; i < NUMBER_OF_SURROUNDING_SQUARE2; i++) direction[i] = true;
		for (int i = 0; i < NUMBER_OF_SHIP; i++)
			if (hitShip[i]!=0) return 0;
		return 1;
	}
	return 0;
}

int main(void)
{
	char playermat[MATRIX_SIZE][MATRIX_SIZE]; //PLAYER MAP
	initmatrix(playermat, 0);

	int limit = 0;
	int count = 0; //Count how many shot a player shot in a turn
	int playerAlvieShipLenght[NUMBER_OF_SHIP] = {5,4,3,3,2};
	bool compWin = false; //Bounded variable
	int endTurn = 0; //Variable to check whether a player finish the turn
	/*endTurn = 0 means player got a or another shot.
	  endTurn = -1 means player is out of shot.
	  endTurn = 1 means player win, stop the game.*/
	int compmode = 0;
	int comprow = 0, compcol = 0;
    bool compdirection[NUMBER_OF_SURROUNDING_SQUARE2] = {true,true,true,true};

	for (int i = 0 ; i < 4; i++) printf("%d",compdirection[i]);
    bool isShiphitting = false;

	//PLAYER TAKES TURN TO SHOT UNTIL ONE OF THE PLAYER WINS
	do
	{
		limit++;
		printGame(playermat,playermat); //PRINT BOTH CURRENT MAPS

		endTurn = 0; count = 0; //Init before player's turn
		//Player shot until endTurn != 0
		do endTurn = compTurn(playermat, playerAlvieShipLenght, compdirection, &compmode , &comprow, &compcol, &count, &isShiphitting);
		while (endTurn == 0);
		if (endTurn == 1) //When computer wins
		{
			compWin = true;
			break;
		}

	} while (compWin == false);
	printGame(playermat,playermat);
    printf("\nEND GAME\n");
	if (compWin) printf("\tGame ends! Computer won!");
    return 0;
}
