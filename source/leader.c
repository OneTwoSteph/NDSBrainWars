/*
 * leader.c
 *
 *  Created on: Jan 20, 2015
 *      Author: Nawaaz GS
 */

#include "general.h"
#include "leader.h"

u8 emptyTile[64] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

u8 fullTile[64] = {
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1
};

int score;
int direction;
int order[6];
LEVEL level;

void leader_init() {

	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_256;

	//swiCopy(emptyTile, BG_TILE_RAM_SUB(1),64);
	//swiCopy(fullTile, &BG_TILE_RAM_SUB(1)[32], 64);

	dmaCopy(emptyTile, &BG_TILE_RAM_SUB(1)[0], 64);
	dmaCopy(fullTile, &BG_TILE_RAM_SUB(1)[32], 64);

	direction = rand()%2;

	BG_PALETTE_SUB[0] = GREYVAL;

	if(direction == 1)	BG_PALETTE_SUB[1] = BLUEVAL;
	else				BG_PALETTE_SUB[1] = REDVAL;

	int row, col;

	for(row = 0; row < 32; row++){
		for(col = 0; col < 32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0;
		}
	}

	for(row = 4; row < 10; row++){
		for(col = 2; col < 10; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 1;
		}
	}

}
