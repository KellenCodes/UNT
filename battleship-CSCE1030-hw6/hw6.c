/*
Author: Michael kellen Mills  mkm0222  (Michaelmills5@my.unt.edu)
course; CSCE1030.001
date: 11.24.2014
Instructor: Mark Thompson
Purpose:
Creating the game board for a little game of battlship.
Randomly generate two whole ships on the board.
Offer a difficulty Setting.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define EASY   30		/*EASY MEDIUM and HARD are all difficuly settings. Here i can change the definition of these settings.*/
#define MEDIUM 25
#define HARD   20
#define SQUARE 10		/*SQUARE is the size of the battleship board.*/
#define SHIPS  1		/*SHIPS is the number of ships on the board.*/
#define LARGE  4		/*LARGE is the size of the largest ship.*/
#define SMALL  1		/*SMALL is the size of the smallest ship allowed. Only used if there are more ships than there are unique sizes.*/
#define UNIQUE 1		/*UNIQUE sets the number of ships in each particular size.*/

void prn_info();
int prn_intro(int level);
int  assign(char board[][SQUARE], char export[][SQUARE], int *k);
int  ship(int *k, char board[][SQUARE], int lap);
void prn_board(char board[][SQUARE]);

int main()
{
	prn_info();

	char export[SQUARE][SQUARE];
	char board[SQUARE][SQUARE];
	int i = 0, j, z = LARGE;
	int level = 0, done = 1, *k = &z; /*Level is number of turns left, done is successful creation board check.*/
	for( i = 0; i < SQUARE; i++)
	{
		for(j = 0; j < SQUARE; j++)
		{
			export[i][j] = ' ';
		}
	}

	level = prn_intro(level);
	while(done)		/*This loop will continue running until a board is made successfully.*/
	{
		for( i = 0; i < SQUARE; i++)
		{
			for( j = 0; j < SQUARE; j++)
			{
				board[i][j] = export[i][j];
			}
		}
		done = assign(board, export, k);
	}
	prn_board(board);
	prn_board(export);
	return 0;
}

/*
Function: assign
Parameters: 2D array of characters representing sections of "ship"
Return: a integer to let the calling environment know if this function ran correctly.
*/

int assign(char board[][SQUARE], char export[][SQUARE], int *k)
{
	int i, l, j;
	int x, y;			/*x and y are counters used only to save the board[][] into export[][] to speed up randomization time for alrge numbers of ships.*/

	for( i = 0; i < SHIPS; i++)
	{
		for( j = 0; j < UNIQUE; j++)
		{
			l = ship(k, board, i); /*If this function returns a 0, the assign() is set to load from previous successful ship placement.*/
			if( l == 0)
			{
				return 1;
			}
			else
			{
				for( x = 0; x < SQUARE; x++)
				{
					for ( y = 0; y < SQUARE; y++)
						export[x][y] = board[x][y];
				}
			}
		}
		k--;
		if( *k < SMALL )
			*k = SMALL;
	}

	return 0;
}
/*
Function: ship
Paramenters: int asking for a specific size for this ship.
2D array of chars representing the battleship board.
int letting THIS function know how many ships have been made already...this helps randomization.
Return: int letting the calling environment know if the function ran correctly.
*/
int ship(int *k, char board[][SQUARE], int lap)
{
				/*in the header, k is for the elngth of the battleship*/
				/*in the header, lap is the number of times this function has run.*/
	int j;			/*j is for the orientation of the ship*/
	int h;			/*h is for the static number in the coordinate*/
	int l;			/*l is a for loop counter*/
	int i;			/*i is for the long side of the battle ship.*/
	srand(time(NULL)+lap);
	j = (rand() % 2 );		/*Horizontal or vertical*/
	h = (rand() % SQUARE);		/*This number is for the row OR column that the ship ISN"T facing.*/
	i = (rand() % SQUARE);
	if((i + *k) >= SQUARE)		/*This line checks to see if a ship fell off the map.*/
		return 0;
	;
	if(j == 0)			/*This if/else statement reads the number for j and will orient (vertical Horizontal) the ship based on j.*/
	{
		for(l = 0; l < *k; l++)
			if(board[i+l][h] == ' ')	/*This checks to see if a ship is already occupying the space.*/
				board[i+l][h] = ('A' + lap);
			else
				return 0;
	}
	else
	{
		for(l = 0; l < *k; l++)
			if(board[h][i+l] == ' ')
				board[h][i+l] = ('A' + lap);
			else
				return 0;
	}
}

/*
Function: prn_intro
Parameters: int letting the function know that a difficulty has not been selected yet.
In the future, i think this will help any kind of "play again?" feature.
Return: the number of turns allowed by a particular difficulty setting.
*/
int prn_intro(int level)
{
	int i;
	char easy[] = "easy", medium[] = "normal", hard[] = "hard";
	char c, difficultString[20];
	printf("----------------------------------------------------------\n");
	printf("-         Welcome to Zombie Battleship!                  -\n");
	printf("-      There are ZOMBIES on these battleships!           -\n");
	printf("-                                                        -\n");
	printf("-             Game By: Kellen Mills                      -\n");
	printf("-          UNT CSCE1030.001 Mark Thompson                -\n");
	printf("----------------------------------------------------------\n");
	while(level == 0)
	{
		printf("\nPlease enter a difficulty setting (easy, normal, hard): ");
		for( i = 0; (c = getchar()) != '\n'; i++)
		{
			difficultString[i] = c;
		}
		difficultString[i] = '\0';
		if( strcmp(difficultString, easy) == 0)
		{
			level = EASY;
		}
		else if( strcmp(difficultString, medium) == 0)
		{
			level = MEDIUM;
		}
		else if( strcmp(difficultString, hard) == 0)
		{
			level = HARD;
		}
		else
			printf("\nI didn't quite catch that, could you type more clearly?");
	}
	printf("%s\n", difficultString);
	return level;
}
/*
Function: prn_info
Parameters: N/A
Parameters: N/A
This is printing my info for the class
*/
void prn_info()
{
	printf("\nCSCE1030.001\nHW6\nMichael Kellen Mills\nMKM0222\nmichaelmills5@my.unt.edu\n");
}

/*
Function: prn_board
Parameters: 2D char array representing the game board.
Return: nothing,
*/
void prn_board(char board[][SQUARE])
{
	int j;			/*j is for columns*/
	int i;			/*i is rows.*/

	/*The formatting was a bit confusing. But after some counting I figured it out.
	This is dynamic for larger board sizes.*/
	printf("\n    ");
	for( i = 0; i < SQUARE; i++)
		printf("%d ", i+1);
	printf("\n");
	printf("   ");
	for( i = -1; i < SQUARE; i++)
		printf("--");
	printf("\n");
	for( i = 0; i < SQUARE; i++)
	{
	printf("%c | ", 'A'+i);
		for( j = 0; j < SQUARE; j++)
		{
			printf("%c ", board[i][j]);
		}
	printf("|\n");
	}
	printf("   ");
	for( i = -1; i < SQUARE; i++)
		printf("--");
	printf("\n");
}