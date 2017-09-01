#include "battle.h"

int main()
{
	prn_info();

	Play one;
	int i = 0, j;
	int z;
	int reveal = 1, level = 0, done = 1; /*Level is number of turns left, done is for while loops.*/


	one.game = calloc(SQUARE, sizeof(char *));
	for(z = 0; z < SQUARE; z++)
	{
		one.game[z] = calloc(SQUARE, sizeof(char));
	}
	for( i = 0; i < SQUARE; i++)
	{
		for( j = 0; j < SQUARE;  j++)
		{
			one.game[i][j] = ' ';
		}
	}
	one.board = calloc(SQUARE, sizeof(char *));
	for(z = 0; z < SQUARE; z++)
	{
		one.board[z] = calloc(SQUARE, sizeof(char));
	}

	for( i = 0; i < SHIPS; i++)
	{
		one.realShip[i] = SHIPS - i;
		if(one.realShip[i] <= 0)
		{
			one.realShip[i] = SMALL;
		}
	}
/*^^^^^^^^^^^^^^^^^^^^^^Just a bunch of allocation ^^^^^^^^^^^*/

	level = prn_intro(level);

	while(done)		/*This loop will continue running until a board is made successfully.*/
	{
		for( i = 0; i < SQUARE; i++)
		{
			for( j = 0; j < SQUARE; j++)
			{
				one.board[i][j] = ' ';
			}
		}
		done = assign(&one);
	}

        one.aircraftShip = 0;
        one.battleShip   = 0;
	while(reveal)
	{
		reveal = commander(&one, &level);
	}

	prn_board(one.board);

	for( z = 0; z < SQUARE; z++)
		free(one.game[z]);
	free(one.game);
	for( z = 0; z < SQUARE; z++)
		free(one.board[z]);
	free(one.board);
	return 0;
}
