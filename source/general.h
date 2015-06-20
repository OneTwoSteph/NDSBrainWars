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

#define W	32
#define H 	24

#define NBMAIN	6

#define BLACK 		ARGB16(1,11,11,11)
#define BLACKGREY 	ARGB16(1,21,21,21)
#define GREY		ARGB16(1,28,28,28)
#define WHITE 		ARGB16(1,31,31,31)
#define BLUE 		ARGB16(1,4,18,31)
#define RED			ARGB16(1,31,13,22)
#define GREEN 		ARGB16(1,7,22,14)
#define YELLOW 		ARGB16(1,31,26,0)

#define PATHMEDIUM 		4
#define PATHHARD 		8

#define MUSICALMEDIUM 	4
#define MUSICALHARD 	8

#define JANKENPONMEDIUM 4
#define JANKENPONHARD 	8

#define LEADERLEVEL		4

#define GAMETIME		20

#define PLAYERONE		0
#define PLAYERTWO		1

#define MAINBG0TILE		4
#define MAINBG0MAP		63
#define MAINBG1TILE		0
#define MAINBG1MAP		16
#define MAINBG2TILE		3
#define MAINBG2MAP		25

#define SUBBG0TILE		4
#define SUBBG0MAP		63
#define SUBBG1TILE		0
#define SUBBG1MAP		16
#define SUBBG2TILE		3
#define SUBBG2MAP		25

#define TIMER3F			5
#define PAUSE			0.6

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
    B = 0,
    R = 1,
    G = 2,
    Y = 3,
    N = 4
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
    HARD = 3,
    VERHARD = 4,
    EXTREME = 5,
    PRO = 6
};

typedef enum TAPORDER TAPORDER;
enum TAPORDER
{
	SAME = 0,
	INVERSE = 1
};
