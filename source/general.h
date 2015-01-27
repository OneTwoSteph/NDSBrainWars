/*
 * general.h
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati & Nawaaz GS
 *
 */

#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"
#include <sys/dir.h>
#include <fat.h>
#include <dirent.h>
#include "string.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define BLACKVAL 	ARGB16(1,11,11,11)
#define GREYVAL 	ARGB16(1,28,28,28)
#define WHITEVAL 	ARGB16(1,31,31,31)
#define BLUEVAL 	ARGB16(1,4,18,31)
#define REDVAL 		ARGB16(1,31,13,22)
#define GREENVAL 	ARGB16(1,7,22,14)
#define YELLOWVAL 	ARGB16(1,31,26,0)

#define PATHMEDIUM 		5
#define PATHHARD 		10

#define MUSICALMEDIUM 	5
#define MUSICALHARD 	10

#define JANKENPONMEDIUM 10
#define JANKENPONHARD 	20

#define LEADEREASY 		10
#define LEADERMEDIUM 	15
#define LEADERHARD 		30

#define GAMETIME		15

#define PLAYERONE		0
#define PLAYERTWO		1

typedef enum STATE STATE;
enum STATE
{
    MAIN = 0,
    TRAIN = 1,
    ONEP = 2,
    TWOP = 3,
    SCORE = 4,
    CREDITS = 5

};

typedef enum GAME GAME;
enum GAME
{
	LEADER = 0,
	EATIT = 1,
	MUSICAL = 2,
	PATH = 3,
	ADDITION = 4,
	PLUSMINUS = 5,
	JANKENPON = 6,
	NOGAME = 7,
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
    SCISSOR = 0,
    PAPER = 1,
    ROCK = 2
};

typedef enum ORDER ORDER;
enum ORDER
{
    SPR = 0,
    RSP = 1,
    PRS = 2,
    PSR = 3,
    RPS = 4,
    SRP = 5,
};

typedef enum ROW ROW;
enum ROW
{
    FIRST = 0,
    SECOND = 1,
};

typedef enum FOOD FOOD;
enum FOOD
{
    EMPTY = 0,
    MONSTER = 1,
    CHERRY = 2
};

typedef enum MUSIC MUSIC;
enum MUSIC
{
	DO = 0,
	RE = 1,
	MI = 2,
	FA = 3
};

typedef enum LEVEL LEVEL;
enum LEVEL
{
	VERYEASY = 0,
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
};


