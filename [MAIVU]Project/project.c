/*
===============================================================================
 Name        : Exercise01.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

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

bool initgame(); //PRINT INTRO
bool validPoint(char mat[MATRIX_SIZE][MATRIX_SIZE], int row, int col); //CHECK VALID POINT TO INIT MATRIX OR TO CHECK USER INPUT COORDINATE
bool surrounded(char mat[MATRIX_SIZE][MATRIX_SIZE], int row, int col); //CHECK SURROUNDING POINTS TO INIT MATRIX WITHOUT SHIPS LAYING NEXT TO EACH OTHER
void initmatrix(char mat[MATRIX_SIZE][MATRIX_SIZE], int mode); //INIT MATRIX WITH 2 MODE. MODE 0 INIT WITH SHIPS. MODE 1 INIT WITH DEFAULT VALUE
void printGame(char mat1[MATRIX_SIZE][MATRIX_SIZE], char mat2[MATRIX_SIZE][MATRIX_SIZE]); //PRINT 2 GRIDS, PRINT THE GAME
bool shot(char mat1[MATRIX_SIZE][MATRIX_SIZE], char mat2[MATRIX_SIZE][MATRIX_SIZE], int row, int col); //SHOT AT A PARTICULAR POINT
int playerTurn(char mat[MATRIX_SIZE][MATRIX_SIZE], char matShow[MATRIX_SIZE][MATRIX_SIZE], int hitShip[NUMBER_OF_SHIP], int *count); //PLAYER TURN FUNCTION
int compTurn(char mat[MATRIX_SIZE][MATRIX_SIZE], int hitShip[NUMBER_OF_SHIP], bool direction[NUMBER_OF_SURROUNDING_SQUARE2], int *mode, int *row, int*col, int *count, bool *isShiphitting); //COMPUTER TURN FUNCTION

bool initgame()
{
    char ch;
    char line[STRING_SIZE];
    //PRINT INTRODUCTION
    printf("\n");
    printf("\t---------------------------------------------------------------------------------------------------\n");
    printf("\t|                                        THE BATTLESHIP GAME                                      |\n");
    printf("\t---------------------------------------------------------------------------------------------------\n");
    printf("\n");
    printf("\t------------------------------------------------ RULE ---------------------------------------------\n");
    printf("\t - You will have two 10 x 10 grids. One is the map of your own ships and the other belongs to your\n");
    printf("\t opponent - computer. Computer ships' locations are unknown to you.\n");
    printf("\t - The goal is to be the first one to take down all 5 ships of the opponent.\n");
    printf("\t - You and the computer take turn to shot. If a ship is hit, that player got another shot.\n");
    printf("\t - A ship is counted to be sunk when all the part of the ship are hit.\n");
    printf("\t - Coordinate is in row-col format. For examples, 1-3, 3-4 or 7-3.");
    printf("\n");
    printf("\t Ready to play? (Y/N): ");
    //ASK IF USER WANTS TO PLAY
    do
    {
    	if (fgets(line, LINE_SIZE, stdin) != NULL)
    	{
    		if (sscanf(line, "%c", &ch)==1)
    		{
    			if (ch == 'Y' || ch == 'y') return true;
    			else if (ch == 'N' || ch == 'n') return false;
    		}
			printf("\t One character (Y or N) only. Try again!\n");
			printf("\t Ready to play? (YES/NO): ");
    	}
    }
    while (1);
}

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

int playerTurn(char mat[MATRIX_SIZE][MATRIX_SIZE], char matShow[MATRIX_SIZE][MATRIX_SIZE], int hitShip[NUMBER_OF_SHIP], int *count)
{
	int row = 0, col = 0;
	bool checkValidPoint = false;
	if (*count>0) printf("\tYou get another shot. Type the coordinate (row-col): ");
	else printf("\tYour turn. Type the coordinate (row-col): ");
	do
	{
		scanf("%d-%d", &row, &col);
		checkValidPoint = validPoint(matShow,row,col);
		if (!checkValidPoint) printf("\tPoint is not valid! Try another coordinate. Type the coordinate (row-col): ");
	}
	while (!checkValidPoint);
	printf("\tYou shot at point %d-%d. ", row, col);

	char chtemp = mat[row][col];
	(*count)++;
	if (shot(mat, matShow, row, col) == false)
	{
		printf("Missed!\n");
		return -1;
	}

	hitShip[chtemp - 'A']--;
	if (hitShip[chtemp - 'A'] != 0) printf("Hit the opponent ship!\n");
	else
	{
		printf("The opponent's ship %c has been sunk\n", chtemp);
		for(int i = 0; i < MATRIX_SIZE; i++)
		    for (int j = 0; j < MATRIX_SIZE; j++)
		    	if (mat[i][j] == chtemp) matShow[i][j] = chtemp;
		for (int i = 0; i < NUMBER_OF_SHIP; i++)
			if (hitShip[i]!=0) return 0;
		return 1;
	}
	return 0;

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
    		if (*row < 0 || *row > 9 || *col < 0 || *col > 9)
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

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif
    //INIT THE GAME. IF FALSE MEANS USER ISN'T READY TO PLAY
    if (initgame()== false)
    {
    	printf("\t Okay, return next time and play ^^");
    	return 0;
    }
	printf("\n\t------------------------------------- LET THE BATTLE BEGINS ---------------------------------------");
	printf("\n\t%30s%s\n"," ","(wait for computer to init the girds)");

	char compmat[MATRIX_SIZE][MATRIX_SIZE]; //COMPUTER MAP
	char compShowmat[MATRIX_SIZE][MATRIX_SIZE]; //PLAYER VIEW TO COMPUTER MAT
	char playermat[MATRIX_SIZE][MATRIX_SIZE]; //PLAYER MAP
	/*GENERATE MAPS WITH RANDOMLY LOCATED SHIPS.
	  THE SECOND PARAMETER IS THE MODE.
	  MODE = 0 MEANS INIT WITH RANDOM SHIPS LOCATED.
	  MODE = 1 MEANS INIT WITH DEFAUL o VALUE ONLY. (Player cannot view computer ships) */
	initmatrix(compmat, 0);
	initmatrix(compShowmat, 1);
	initmatrix(playermat, 0);

	int limit = 0;
	int count = 0; //Count how many shot a player shot in a turn
	int total = 0; //Count the total of player shots
	int turn = 0;  //Count the total of player turns
	int playerAlvieShipLenght[NUMBER_OF_SHIP] = {5,4,3,3,2};
	int compAliveShipLength[NUMBER_OF_SHIP] = {5,4,3,3,2};
	bool playerWin = false, compWin = false; //Bounded variable
	int endTurn = 0; //Variable to check whether a player finish the turn
	/*endTurn = 0 means player got a or another shot.
	  endTurn = -1 means player is out of shot.
	  endTurn = 1 means player win, stop the game.*/
	int compmode = 0;
	int comprow = 0, compcol = 0;
	bool compdirection[NUMBER_OF_SURROUNDING_SQUARE2] = {true,true,true,true};
	bool isShiphitting = false;

	//PLAYER TAKES TURN TO SHOT UNTIL ONE OF THE PLAYER WINS
	do
	{
		limit++;
		printGame(playermat,compShowmat); //PRINT BOTH CURRENT MAPS

		endTurn = 0; count = 0; turn++; //Init before player's turn
		//Player shot until endTurn != 0
		do endTurn = playerTurn(compmat, compShowmat, compAliveShipLength, &count);
		while (endTurn == 0);
		total += count;
		if (endTurn == 1) //When player wins
		{
			playerWin = true;
			break;
		}

		endTurn = 0; count = 0; //Init before player's turn
		//Player shot until endTurn != 0
		do endTurn = compTurn(playermat, playerAlvieShipLenght, compdirection, &compmode , &comprow, &compcol, &count, &isShiphitting);
		while (endTurn == 0);
		if (endTurn == 1) //When computer wins
		{
			compWin = true;
			break;
		}

	} while ((playerWin == false) && (compWin == false));

	printGame(playermat,compShowmat); //Print final grids
	if (playerWin)
	{
		printf("\n\t----------------------------------------- ! GAME ENDS ! -------------------------------------------");
		printf("\n\t%-25sAfter %d turns and %d shots, you won the game!", " ",turn, total);
	}
	if (compWin) printf("\n\tGame ends! Computer won!");
    return 0;
}
