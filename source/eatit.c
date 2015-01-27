/*
 * eatit.c
 *
 *  Created on: Jan 21, 2015
 *      Author: Stephanie Amati
 *
 */

#include "general.h"
#include "info.h"
#include "eatit.h"
#include "eatit_pacman.h"

ROW row;
FOOD up[4];
FOOD down[4];

int score;
int wrong;

STATE state;

void eatit_wrong(void){
	// Update wrong variable
	wrong++;

	// Start timer at beginning and stop after two blinking effect
	if(wrong==1) TIMER1_CR |= TIMER_ENABLE;
	if(wrong==4){
		TIMER1_CR &= ~(TIMER_ENABLE);
		wrong = 0;
	}

	// Draw
	eatit_draw();
}

void eatit_init(int gameState){
	// Configure Background
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory
	swiCopy(eatit_pacmanTiles, BG_TILE_RAM_SUB(1), eatit_pacmanTilesLen);

	// Copy palette
	swiCopy(eatit_pacmanPal, BG_PALETTE_SUB, eatit_pacmanPalLen);

	// Set up palette colors
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[3] = GREYVAL;
	BG_PALETTE_SUB[4] = BLACKVAL;
	BG_PALETTE_SUB[5] = REDVAL;
	BG_PALETTE_SUB[7] = GREENVAL;
	BG_PALETTE_SUB[6] = BLUEVAL;


	// Set draw on screen
	up[0] = CHERRY;
	up[1] = CHERRY;
	up[2] = EMPTY;
	up[3] = CHERRY;

	down[0] = EMPTY;
	down[1] = EMPTY;
	down[2] = MONSTER;
	down[3] = EMPTY;

	row = FIRST;

	eatit_draw();

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);

	irqSet(IRQ_TIMER1, &eatit_wrong);
	irqEnable(IRQ_TIMER1);

	// Set global variables
	score = 0;
	wrong = 0;
	state = gameState;

	// Draw infos
	info_init(state);
}

void eatit_draw(){
	int x, y;

	int lPac = 8; 			// length of pacman
	int lFood = 6; 			// length of food
	int height = 12; 		// height of one raw

	int L = 34;				// length of the whole image

	// Draw first background with grey
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[0];
		}
	}

	// If we are not in the wrong case, draw figures
	if((wrong%2)==0){
		for(x=0; x<32; x++){
			for(y=0; y<24; y++){
				// Up and down
				if(y<height){
					// 0, 1, 2, 3 position (0 = left)
					if(x<lFood)
						BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+x+up[0]*lFood];
					else{
						if(x<2*lFood)
							BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-lFood)+up[1]*lFood];
						else{
							if(x<3*lFood)
								BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-2*lFood)+up[2]*lFood];
							else{
								if(x<4*lFood)
									BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-3*lFood)+up[3]*lFood];
								else
									BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-4*lFood)+3*lFood+row*lPac];
							}
						}
					}
				}
				else{
					if(x<lFood)
						BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+x+down[0]*lFood];
					else{
						if(x<2*lFood)
							BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-lFood)+down[1]*lFood];
						else{
							if(x<3*lFood)
								BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-2*lFood)+down[2]*lFood];
							else{
								if(x<4*lFood)
									BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-3*lFood)+down[3]*lFood];
								else
									BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-4*lFood)+3*lFood+(row+1)%2*lPac];
							}
						}
					}
				}
			}
		}
	}
}

bool eatit_game(bool player, int gameCounter){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed or time crossed 15 sec
	int time;
	time = info_get_time();

	if(state != TRAIN) { info_store_temp_score(player, gameCounter, score); }

	if((keys & KEY_START) || (time > GAMETIME)) { return true; }
	else{
		// If up arrow was pressed
		if(keys & KEY_UP){
			// Update pacman position
			row = FIRST;

			// Check if up[3] is cherry
			if((up[3] == CHERRY) || (down[3] == MONSTER))
				eatit_next();
			else
				eatit_wrong();
		}

		// If down arrow was pressed
		if(keys & KEY_DOWN){
			// Update pacman position
			row = SECOND;

			// Check if up[3] is cherry
			if((down[3] == CHERRY) || (up[3] == MONSTER))
				eatit_next();
			else
				eatit_wrong();
		}
	}

	// Update infos
	info_update(score, state, player);

	// Return true for the game to continue
	return false;
}

void eatit_next(void){
	// Increment score
	score++;

	// Random food for up[0] and down[0]
	int nb1, nb2;

	nb1 = rand()%3;

	if(nb1 == MONSTER) while((nb2 = rand()%3) == MONSTER);
	else{
		if(nb1 == CHERRY) while((nb2 = rand()%3) == CHERRY);
		else while((nb2 = rand()%3) == EMPTY);
	}

	// Update up and down rows
	int i;

	for(i=3; i>0; i--){
		up[i] = up[i-1];
		down[i] = down[i-1];
	}
	up[0] = nb1;
	down[0] = nb2;

	// Redraw screen
	eatit_draw();
}

void eatit_reset(){
	// Suppress infos
	info_finish(score, "eatit", state);

	// Draw nothing
	wrong = 1;
	eatit_draw();

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	score = 0;
	wrong = 0;
}
