#include "battle.h"

/*
Function: commander
Parameters: Two 2D arrays representing the board before and after.
one pointed to a structure of typedef Play.
one pointer to an integer storing the number of shots left.
Return: an int, letting the calling environment know if the game has ended yet.
Purpose: This function micromanages the overall  process of the game.
*/
int commander(Play* one, int* level)
{
	int win = 0, i;
	win = 0;
	for(i = 0; i < SHIPS; i++)
	{
		if(win <= 0)
		{
			win = one->realShip[i];
		}
	}
		if(win == 0)
		{
                        printf("\nCongratulations! You stopped the zombie apocalypse!\n");
                	return 0;

		}
                if(*level != 0)
                {
			prn_board(one->board);
                        prn_board(one->game);
                        printf("We have %d missiles left. Where shall we fire next?\n> ", *level);

                        if(torpedo(one))
                                *level -= 1;
			return 1;
                }
                else
                {
                        printf("\nYou could not sink all of the zombie's ships! Better luck next time!\n");
			return 0;
                }
}



/*
Function: torpedo

*/
int torpedo(Play* one)
{
		int y, x, s;
		char c;
               	char badCoord[] = "Cannot lock onto target.\nCoordinates must be given as one alpha character and one or two numeric characters.\n A1, A10, a1, a7 etc.\n";

		one->yCo = getchar();
/*		scanf("%c", &one->yCo);*/
                scanf("%d", &one->xCo);
		while((c = getchar())!= '\n')
			;

                if(one->yCo >= 'a' && one->yCo <= 'z')
                {
                        one->yCo -= 32;          /*If it's lower case make it upper case.*/
                }

                x = one->xCo;
                x -= 1;
                y = (one->yCo - 'A');

		if( x < 0 || x > (SQUARE-1) || y < 0 || (y > SQUARE-1))
		{
			printf("%s", badCoord);
			return 0;
		}

                switch(one->board[y][x])
                {
/*                        case 'A':
                        {
                                one->aircraftShip++;
                                board[y][x] = '%';
                                game[y][x] = '%';
                                if(one->aircraftShip < 5)
                                        printf("You hit the zombies aircraft carrier!");
                                else
                                        printf("You sank the zombies aircraft carrier!");
                                break;
                        }
                        case 'B':
                        {
                                one->battleShip++;
                                board[y][x] = '%';
                                game[y][x] = '%';
                                if(one->battleShip < 4)
                                        printf("You hit the zombies's battleship!");
                                else
                                        printf("You sank the zombie's battleship!");
                                break;
                        }*/
                        case '%':
                        {
                                printf("You already hit that spot!");
                        }
                        case '*':
                        {
                                printf(" A wasted shot!\n");
                                break;
                        }
                        case ' ':
                        {
                                one->board[y][x] = '*';
                                one->game[y][x] = '*';
                                printf("Miss...");
				break;
                        }
			default:
			{
				s = one->board[y][x] - 'A';
				one->realShip[s]--;
				one->board[y][x] = '%';
				one->game[y][x] = '%';
				if(one->realShip[s] == 0)
					printf("You sank zombie ship %c!", s + 'A');
				else
					printf("You hit zombie ship %c!", s + 'A');
			}
                }

		return 1;
}




/*
Function: assign
Parameters: 2D array of characters representing sections of "ship"
Return: a integer to let the calling environment know if this function ran correctly.
*/

int assign(Play* one)
{
	int i, k, l;
	k = LARGE;			/*This is here so that I can manipulate the size of the ships.*/

	for( i = 0; i < SHIPS; i++)
	{
		l = ship(k, one, i); /*If this function returns a 0, the assign() is set to end prematurely.*/
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
int ship(int k, Play* one, int lap)
{
				/*in the header, k is for the elngth of the battleship*/
				/*in the header, lap is the number of times this function has run.*/
	int j;			/*j is for the orientation of the ship*/
	int h;			/*h is for the static number in the coordinate*/
	int l;			/*l is a for loop counter*/
	int ok = 1;		/*ok helps to program check if a ship will be placed correctly before it places it*/
	int i;			/*i is for the long side of the battle ship.*/
	int kill;		/*if kill is set to 1, the ship currently being placed will be erased.*/
	while(ok)
	{
		kill = 0;
		srand(time(NULL)+lap);		/*The "+lap" helps to keep randomization more random.*/
		j = (rand() % 2 );		/*Horizontal or vertical*/
		h = (rand() % SQUARE);		/*This number is for the row OR column that the ship ISN"T facing.*/
		i = (rand() % (SQUARE - k));    /*By directly changing the modulo to pick among only coordinates that will fit the ship, I have decreased the risk of failure considerably.*/

		if((i + k) >= SQUARE)		/*This line checks to see if a ship fell off the map. It is old code since I have changed the random Modulo. (See previous comment)*/
			return 0;
		;
		if(j == 0)			/*This if/else statement reads the number for j and will orient (vertical Horizontal) the ship based on j.*/
		{
			for(l = 0; l < k; l++)
			{
				if(one->board[i+l][h] == ' ')	/*This checks to see if a ship is already occupying the space.*/
					one->board[i+l][h] = ('A' + lap);
				else
				{
					kill = 1;
					break;
				}
			}
			if(kill)
			{
				while( l > 0 )			/*This block is very important. It will undo the last ship if a fault was found.*/
				{
					l--;
					one->board[i+l][h] = ' ';
				}
			}
		}
		else
		{
			for(l = 0; l < k; l++)
			{
				if(one->board[h][i+l] == ' ')
					one->board[h][i+l] = ('A' + lap);
				else
				{
					kill = 1;
					break;
				}
			}
			if(kill)
			{
				while( l > 0 )			/*This block is very important. It will undo the last ship if a fault was found.*/
				{
					l--;
					one->board[h][i+l] = ' ';
				}
			}
		}
		if(l == k)		/*Because l is the incremental counter for ship placement, I can use it to check if the ship was placed by comparing it to the size the call environment sent.*/
		{
			one->realShip[lap] = k;
			ok = 0;
		}
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
