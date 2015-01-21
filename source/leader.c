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

static volatile int score;
static volatile int direction;
static volatile int order[6];
static volatile int draw_timer;
LEVEL level;

void leader_timer_ISR(){
	draw_timer = 1;
}

void leader_init() {

	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_256;

	dmaCopy(emptyTile, &BG_TILE_RAM_SUB(1)[0], 64);
	dmaCopy(fullTile, &BG_TILE_RAM_SUB(1)[32], 64);

	TIMER0_DATA = TIMER_FREQ_1024(5);
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	irqSet(IRQ_TIMER0, &leader_timer_ISR);

	BG_PALETTE_SUB[0] = GREYVAL;

	leader_new_order();
	leader_draw();

	score = 0;
	level = VERYEASY;

}

void leader_new_order() {

	int rand_order[6];
	int i, j, max, loop = 0;

	for(i = 0; i < 6 ; i++) {
		rand_order[i] = rand();
	}

	while(loop < 6){
		max = -1;

		for(i = 0; i < 6; i++) {
			if(rand_order[i] >= max){
				max = rand_order[i];
				j = i;
			}
		}
		order[loop] = j;
		rand_order[j] = 0;
		loop++;
	}

}

void leader_draw() {

	direction = rand()%2;

	if(direction == 1)		{	BG_PALETTE_SUB[1] = BLUEVAL;}
	else					{	BG_PALETTE_SUB[1] = REDVAL;}

	int i, draw_level, row, col;

	for(row = 0; row < 32; row++){
		for(col = 0; col < 32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0;
		}
	}

	if(level == VERYEASY)		{ draw_level = 3; }
	else if(level == EASY) 		{ draw_level = 4; }
	else if(level == MEDIUM)	{ draw_level = 5; }
	else						{ draw_level = 6; }

	draw_timer = 0;
	irqEnable(IRQ_TIMER0);

	for(i = 0; i < draw_level; i++){

		while(draw_timer == 0);

		switch(order[i]){

		case 0:
			for(row = 4; row < 10; row++){
				for(col = 2; col < 10; col++){
					BG_MAP_RAM_SUB(0)[row*32+col] = 1;
				}
			}
			break;
		case 1:
			for(row = 14; row < 20; row++){
				for(col = 2; col < 10; col++){
					BG_MAP_RAM_SUB(0)[row*32+col] = 1;
				}
			}
			break;
		case 2:
			for(row = 4; row < 10; row++){
				for(col = 12; col < 20; col++){
					BG_MAP_RAM_SUB(0)[row*32+col] = 1;
				}
			}
			break;
		case 3:
			for(row = 14; row < 20; row++){
				for(col = 12; col < 20; col++){
					BG_MAP_RAM_SUB(0)[row*32+col] = 1;
				}
			}
			break;
		case 4:
			for(row = 4; row < 10; row++){
				for(col = 22; col < 30; col++){
					BG_MAP_RAM_SUB(0)[row*32+col] = 1;
				}
			}
			break;
		case 5:
			for(row = 14; row < 20; row++){
				for(col = 22; col < 30; col++){
					BG_MAP_RAM_SUB(0)[row*32+col] = 1;
				}
			}
			break;
		default:
			break;
		}

		if(i == 5) {irqDisable(IRQ_TIMER0);}
		draw_timer = 0;
	}
}
