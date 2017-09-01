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

#define EASY   30
#define MEDIUM 25
#define HARD   20
#define SQUARE 10
#define SHIPS  2
#define LARGE  5

void prn_info();
int prn_intro(int level);
/*
For Battleship: if((i+4) > SQUARE) return 1;
*/
int  assign(char board[][SQUARE]);
int  ship(int k, char board[][SQUARE], int lap);
void prn_board(char board[][SQUARE]);

int main()
{
	prn_info();


	char board[SQUARE][SQUARE];
	int i = 0, j;
	int level = 0, done = 1; /*Level is number of turns left, done is successful creation board check.*/


	level = prn_intro(level);
	while(done)
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

	return 0;
}


int assign(char board[][SQUARE])
{
	int orient, length, i, j, k, l;
	k = LARGE;

	for( i = 0; i < SHIPS; i++)
	{
		l = ship(k, board, i); /*If this function returns a 0, the assign() is set to end prematurely.*/
		if( l == 0)
			return 1;
		k--;
		if( k == 0)
			k = 1;
	}

	return 0;
}
int ship(int k, char board[][SQUARE], int lap)
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
	if((i + k) >= SQUARE)
		return 0;
	;
	if(j == 0)
	{
		for(l = 0; l < k; l++)
			if(board[i+l][h] == ' ')
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


int prn_intro(int level)
{
	int i;
	char easy[] = "easy", medium[] = "medium", hard[] = "hard";
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
		printf("Please enter a difficulty setting (easy, normal, hard): ");
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
	}
	printf("%s\n", difficultString);
	return level;
}

void prn_info()
{
}

void prn_board(char board[][SQUARE])
{
	int j;			/*j is for columns*/
	int i;			/*i is going to do a lot of counting.*/

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
