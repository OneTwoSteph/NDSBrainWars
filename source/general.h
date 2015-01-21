/*
 * general.h
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 */

#include <nds.h>
#include <stdio.h>
#include <string.h>

#define BLACKVAL 	ARGB16(1,11,11,11)
#define GREYVAL 	ARGB16(1,28,28,28)
#define WHITEVAL 	ARGB16(1,28,28,29)
#define BLUEVAL 	ARGB16(1,4,18,31)
#define REDVAL 		ARGB16(1,31,13,22)
#define GREENVAL 	ARGB16(1,7,22,14)
#define YELLOWVAL 	ARGB16(1,31,26,0)
#define TRUERED		ARGB16(1,31,0,0)
#define TRUEGREEN	ARGB16(1,0,31,0)

#define PATHMEDIUM 20
#define PATHHARD 40

#define LEADEREASY 10
#define LEADERMEDIUM 15
#define LEADERHARD 30

typedef enum STATE STATE;
enum STATE
{
    INIT = 0,
    TRAIN = 1,
    ONEP = 2
};

typedef enum GAME GAME;
enum GAME
{
    NOGAME = 0,
	PATH = 1,
	JANKENPON = 2,
	LEADER = 3
};

typedef enum COLOR COLOR;
enum COLOR
{
    BLUE = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    GREY = 4
};

typedef enum DIRECTION DIRECTION;
enum DIRECTION
{
    RIGHT = 0,
    LEFT = 1,
    UP = 2,
    DOWN = 3
};

typedef enum SHAPE SHAPE;
enum SHAPE
{
    PAPER = 0,
    ROCK = 1,
    SCISSOR = 2
};

typedef enum LEVEL LEVEL;
enum LEVEL
{
	VERYEASY = 0,
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
};
