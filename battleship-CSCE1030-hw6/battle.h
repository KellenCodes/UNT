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
#define SHIPS  6	/*Number of ships allowed on board.*/
#define LARGE  5	/*Size of the largest ship on the board.*/
#define SMALL  2	/*smallest size ship allowed on board.*/

typedef struct newGame
{
        char yCo;
        int  xCo;
        int  aircraftShip;
        int  battleShip;
        int  realShip[SHIPS];
	int  missile;
	int  bomb;
	int  cluster;
	int  cash;
	char **board, **game;
}Play;


void prn_info();
int  prn_intro(int level);
int  assign(Play* one);
int  ship(int k, Play* one, int lap);
void prn_board(char *board[SQUARE]);
void battle(Play* one, int shot);
int torpedo(Play* one);
int commander(Play* one, int* level);
