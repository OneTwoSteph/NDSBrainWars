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

u8 correctTile[64] = {
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2
};

static volatile int leader_score;
static volatile int order[6];
static volatile int draw_timer;
static volatile int direction;
static volatile int wrong;

static volatile int leader_step;

LEVEL level;

void leader_timer_ISR(){
	draw_timer++;
}

void leader_init() {
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_256;

	dmaCopy(emptyTile, &BG_TILE_RAM_SUB(1)[0], 64);
	dmaCopy(fullTile, &BG_TILE_RAM_SUB(1)[32], 64);
	dmaCopy(correctTile, &BG_TILE_RAM_SUB(1)[64], 64);

	TIMER0_DATA = TIMER_FREQ_1024(4);
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	irqSet(IRQ_TIMER0, &leader_timer_ISR);

	BG_PALETTE_SUB[0] = GREYVAL;
	BG_PALETTE_SUB[2] = GREENVAL;

	leader_score = 0;
	leader_step = 0;
	draw_timer = 0;
	wrong = 0;
	level = VERYEASY;

	leader_new_order();
	leader_draw();

}

void leader_new_order() {

	int max_loop = level+3;
	int rand_order[6];
	int i, j, max, loop = 0;

	for(i = 0; i < 6 ; i++) {
		rand_order[i] = rand();
	}

	while(loop < max_loop){
		max = 0;

		for(i = 0; i < 6; i++) {
			if(rand_order[i] >= max){
				max = rand_order[i];
				j = i;
			}
		}
		order[loop] = j;
		rand_order[j] = -1;
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

	draw_level = level + 3;

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

		draw_timer = 0;
	}
	irqDisable(IRQ_TIMER0);
}

bool leader_game() {

	scanKeys();
	u16 keys = keysDown();

	if(keys & KEY_START) 		{ return true; }
	else if(keys & KEY_TOUCH){

		touchPosition touch;
		touchRead(&touch);

		int row, col;
		int next_step;

		if(direction == 1)	{ next_step = leader_step;}
		else				{ next_step = level+2 -leader_step;}

		switch(order[next_step]){
		case 0:
			if((touch.px < 85) &&
			   (touch.py < 96))	{

				for(row = 4; row < 10; row++){
					for(col = 2; col < 10; col++){
						BG_MAP_RAM_SUB(0)[row*32+col] = 2;
					}
				}

				leader_correct();
			}
			else { leader_wrong();	}
			break;

		case 1:
			if((touch.px < 85) &&
			   (touch.py >= 96)) {;

				for(row = 14; row < 20; row++){
					for(col = 2; col < 10; col++){
						BG_MAP_RAM_SUB(0)[row*32+col] = 2;
					}
				}
				leader_correct();
			}
			else { leader_wrong();	}
			break;

		case 2:
			if((touch.px >= 85) && (touch.px < 170) &&
			   (touch.py < 96))	{

				for(row = 4; row < 10; row++){
					for(col = 12; col < 20; col++){
						BG_MAP_RAM_SUB(0)[row*32+col] = 2;
					}
				}
				leader_correct();
			}
			else { leader_wrong();	}
			break;

		case 3:
			if((touch.px >= 85) && (touch.px < 170) &&
			   (touch.py >= 96)) {

				for(row = 14; row < 20; row++){
					for(col = 12; col < 20; col++){
						BG_MAP_RAM_SUB(0)[row*32+col] = 2;
					}
				}
				leader_correct();
			}
			else { leader_wrong();	}
			break;

		case 4:
			if((touch.px >= 170) &&
			   (touch.py < 96))	{

				for(row = 4; row < 10; row++){
					for(col = 22; col < 30; col++){
						BG_MAP_RAM_SUB(0)[row*32+col] = 2;
					}
				}
				leader_correct();
			}
			else { leader_wrong();	}
			break;

		case 5:
			if((touch.px >= 170) &&
			   (touch.py >= 96)) {

				for(row = 14; row < 20; row++){
					for(col = 22; col < 30; col++){
						BG_MAP_RAM_SUB(0)[row*32+col] = 2;
					}
				}
				leader_correct();
			}
			else { leader_wrong();	}
			break;

		default:
			break;
		}

	return false;

	}

	return false;


}

void leader_correct(){

	leader_step++;

	if(leader_step >= (level + 3)) {

		leader_score++;
		wrong = 0;
		leader_step = 0;

		BG_PALETTE_SUB[0] = GREENVAL;

		draw_timer = 0;
		irqEnable(IRQ_TIMER0);
		while(draw_timer <= 2);
		irqDisable(IRQ_TIMER0);

		BG_PALETTE_SUB[0] = GREYVAL;

		if(leader_score >= LEADERHARD) 			{ level = HARD; }
		else if(leader_score >= LEADERMEDIUM)	{ level = MEDIUM; }
		else if(leader_score >= LEADEREASY)		{ level = EASY; }

		leader_new_order();
		leader_draw();

	}



}

void leader_wrong() {

	BG_PALETTE_SUB[0] = TRUERED;

	leader_step = 0;
	wrong++;

	draw_timer = 0;
	irqEnable(IRQ_TIMER0);
	while(draw_timer <= 2);
	irqDisable(IRQ_TIMER0);

	BG_PALETTE_SUB[0] = GREYVAL;

	if(wrong >= 3) {
		wrong = 0;
		leader_score--;

		if(level != VERYEASY){
			level = level-1;
		}
	}

	leader_new_order();
	leader_draw();
}

void leader_reset() {

	int row,col;

	for(row = 0; row < 32; row++){
		for(col = 0; col < 32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0;
		}
	}
	leader_score = 0;
	leader_step = 0;
	draw_timer = 0;
	wrong = 0;
	level = VERYEASY;
}
