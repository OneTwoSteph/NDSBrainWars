/*
 * general.h
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati & Nawaaz GS
 *
 */

#ifndef GENERAL_H_
#define GENERAL_H_

/******************************************************************** Modules */
// NDS
#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"
#include <sys/dir.h>
#include <fat.h>
#include <dirent.h>
#include "string.h"

// C
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


/****************************************************************** Constants */
// Screen dimensions
#define W			   32				// width of screen in tiles
#define H 			   24				// height of screen in tile
#define WP			  256				// width of screen in pixels
#define HP			  192				// height of screen in pixels

// Backgrounds memory infos
#define BG0TILE		1
#define BG0MAP		0
#define BG1TILE		3
#define BG1MAP		3
#define BG2TILE		5
#define BG2MAP		6


// Colors
#define BLACK 		ARGB16(1,11,11,11)
#define BLACKGREY 	ARGB16(1,21,21,21)
#define GREY		ARGB16(1,28,28,28)
#define WHITE 		ARGB16(1,31,31,31)
#define BLUE 		ARGB16(1,4,18,31)
#define RED			ARGB16(1,31,13,22)
#define GREEN 		ARGB16(1,7,22,14)
#define YELLOW 		ARGB16(1,31,26,0)

// Display pause infos
#define TIMERF			5
#define PAUSE			0.6

// Game level tresholds
#define LEADERLEVEL		4

#define PATHMEDIUM 		4
#define PATHHARD 		8

#define MUSICALMEDIUM 	3
#define MUSICALHARD 	9

#define JANKENPONMEDIUM 4
#define JANKENPONHARD 	8

// 1p and 2p info
#define GAMETIME	    20

// Players
#define P1               0
#define P2               1
#define PLAYERONE        0
#define PLAYERTWO        1

/*************************************************************** Enumerations */
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

#endif /* GENERAL_H_ */
