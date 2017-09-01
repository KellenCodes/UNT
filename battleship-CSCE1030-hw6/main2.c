#include "battle.h"

int main()
{
	prn_info();

	Play one;
	int i = 0, j;
	int z;
	char **board, **game;
	int reveal = 1, level = 0, done = 1; /*Level is number of turns left, done is for while loops.*/


	game = calloc(SQUARE, sizeof(char *));
	for(z = 0; z < SQUARE; z++)
	{
		game[z] = calloc(SQUARE, sizeof(char));
	}
	for( i = 0; i < SQUARE; i++)
	{
		for( j = 0; j < SQUARE;  j++)
		{
			game[i][j] = ' ';
		}
	}
	board = calloc(SQUARE, sizeof(char *));
	for(z = 0; z < SQUARE; z++)
	{
		board[z] = calloc(SQUARE, sizeof(char));
	}
/*^^^^^^^^^^^^^^^^^^^^^^Just a bunch of allocation ^^^^^^^^^^^*/

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
		 assign(board);
		sleep(1);
		prn_board(board);
	}

        one.aircraftShip = 0;
        one.battleShip   = 0;
	while(reveal)
	{
		reveal = commander(board, game, &one, &level);
	}

	prn_board(board);

	for( z = 0; z < SQUARE; z++)
		free(board[z]);
	free(board);
	return 0;
}
