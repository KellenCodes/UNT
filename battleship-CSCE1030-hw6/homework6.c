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

#define EASY   30	/*EASY MEDIUM and HARD are all definitions for difficulty settings*/
#define MEDIUM 25
#define HARD   20
#define SQUARE 10	/*SQUARE is the size of the board.*/
#define SHIPS  2	/*Number of ships allowed on board.*/
#define LARGE  5	/*Size of the largest ship on the board.*/
#define SMALL  1	/*smallest size ship allowed on board.*/

void prn_info();
int prn_intro(int level);
int  assign(char *board[SQUARE]);
int  ship(int k, char *board[SQUARE], int lap);
void prn_board(char *board[SQUARE]);

int main()
{
	prn_info();

	int z;
	char **board;
	board = calloc(SQUARE, sizeof(char *));
	for(z =0; z < SQUARE; z++)
	{
		board[z] = calloc(SQUARE, sizeof(char));
	}
	int i = 0, j;
	int level = 0, done = 1; /*Level is number of turns left, done is successful creation board check.*/

	level = prn_intro(level);
	while(done)		/*This loop will continue running until a board is made successfully.*/
	{
		for( i = 0; i < SQUARE; i++)
		{
			for( j = 0; j < SQUARE; j++)
			{
				board[i][j] = ' ';
			}
		}
		done = assign(board);
	}
	prn_board(board);

	for( z = 0; z < SQUARE; z++)
		free(board[z]);
	free(board);
	return 0;
}

/*
Function: assign
Parameters: 2D array of characters representing sections of "ship"
Return: a integer to let the calling environment know if this function ran correctly.
*/

int assign(char *board[SQUARE])
{
	int i, k, l;
	k = LARGE;			/*This is here so that I can manipulate the size of the ships.*/

	for( i = 0; i < SHIPS; i++)
	{
		l = ship(k, board, i); /*If this function returns a 0, the assign() is set to end prematurely.*/
		if( l == 0)
			return 1;
		k--;
		if( k < SMALL)
			k = SMALL;
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
int ship(int k, char *board[SQUARE], int lap)
{
				/*in the header, k is for the elngth of the battleship*/
				/*in the header, lap is the number of times this function has run.*/
	int j;			/*j is for the orientation of the ship*/
	int h;			/*h is for the static number in the coordinate*/
	int l;			/*l is a for loop counter*/
	int i;			/*i is for the long side of the battle ship.*/
	srand(time(NULL)+lap);		/*The "+lap" helps to keep randomization more random.*/
	j = (rand() % 2 );		/*Horizontal or vertical*/
	h = (rand() % SQUARE);		/*This number is for the row OR column that the ship ISN"T facing.*/
	i = (rand() % SQUARE);
	if((i + k) >= SQUARE)		/*This line checks to see if a ship fell off the map.*/
		return 0;
	;
	if(j == 0)			/*This if/else statement reads the number for j and will orient (vertical Horizontal) the ship based on j.*/
	{
		for(l = 0; l < k; l++)
			if(board[i+l][h] == ' ')	/*This checks to see if a ship is already occupying the space.*/
				board[i+l][h] = ('A' + lap);
			else
				return 0;
	}
	else
	{
		for(l = 0; l < k; l++)
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
	printf("----------------------------------------------------------\n");
	printf("-  The board will be %d x %d. you will have %d chances   -\n",SQUARE,SQUARE, level);
	printf("-  to sink the enemy ships. Remember, these are zombies  -\n");
	printf("-  so try to imagine that the entire time. It'll be fun! -\n");
	printf("-  The zombies have %02d total ships. The largest ship will-\n", SHIPS);
	printf("-  be %02d units long. The second largest will be %02d long. -\n", LARGE, LARGE - 1);
	printf("-  The ships will dercrement in size until they are %02d   -\n", SMALL);
	printf("-  long. The computer will now randomly generate a board.-\n");
	printf("----------------------------------------------------------\n");

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
void prn_board(char *board[SQUARE])
{
	int j;			/*j is for columns*/
	int i;			/*i is rows.*/

	/*The formatting was a bit confusing. But after some counting I figured it out.
	This is dynamic for larger board sizes.
	But the numbers won't allign unless you change the first prntf conversion to "%02d" and change both for loops which print "--" per loop instead print "---" per loop.*/
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
