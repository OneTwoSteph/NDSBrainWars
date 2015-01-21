/*
 * general.h
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 */

#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BLACKVAL ARGB16(1,11,11,11)
#define GREYVAL ARGB16(1,28,28,28)
#define WHITEVAL ARGB16(1,28,28,29)
#define BLUEVAL ARGB16(1,4,18,31)
#define REDVAL ARGB16(1,31,13,22)
#define GREENVAL ARGB16(1,7,22,14)
#define YELLOWVAL ARGB16(1,31,26,0)

#define PATHMEDIUM 5
#define PATHHARD 10

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
	JANKENPON = 2
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

typedef enum LEVEL LEVEL;
enum LEVEL
{
    EASY = 0,
    MEDIUM = 1,
    HARD = 2
};
