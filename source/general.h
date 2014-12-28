/*
 * general.h
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie amati
 */

#include <nds.h>
#include <stdio.h>
#include <string.h>

#define GREYVAL ARGB16(1,28,28,28)
#define WHITEVAL ARGB16(1,28,28,29)
#define BLUEVAL ARGB16(1,4,18,31)
#define REDVAL ARGB16(1,31,13,22)
#define GREENVAL ARGB16(1,7,22,14)
#define YELLOWVAL ARGB16(1,31,26,0)

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

