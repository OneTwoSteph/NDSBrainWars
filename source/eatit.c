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

#define NORMALPAL	6

ROW row;
FOOD up[4];
FOOD down[4];

int score;
int wrong;

STATE state;

void eatit_wrong(void){
	// Play effect
	if(wrong == 0) mmEffect(SFX_BOING);

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
	// Desactivate BG1
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to memory
	swiCopy(eatit_pacmanTiles, BG_TILE_RAM_SUB(BG0TILE), eatit_pacmanTilesLen);

	// Set up palette colors
	BG_PALETTE_SUB[0x61] = WHITE;
	BG_PALETTE_SUB[0x62] = GREY;
	BG_PALETTE_SUB[0x63] = GREEN;
	BG_PALETTE_SUB[0x64] = WHITE;
	BG_PALETTE_SUB[0x65] = GREY;

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

	// Activate BG0
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

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
	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[0] | (NORMALPAL << 12);
		}
	}

	// If we are not in the wrong case, draw figures
	if((wrong%2)==0){
		for(x = 0; x < W; x++){
			for(y = 0; y < H; y++){
				// Up and down
				if(y<height){
					// 0, 1, 2, 3 position (0 = left)
					if(x<lFood)
						BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[y*L+x+up[0]*lFood] | (NORMALPAL << 12);
					else{
						if(x<2*lFood)
							BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[y*L+(x-lFood)+up[1]*lFood] | (NORMALPAL << 12);
						else{
							if(x<3*lFood)
								BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[y*L+(x-2*lFood)+up[2]*lFood] | (NORMALPAL << 12);
							else{
								if(x<4*lFood)
									BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[y*L+(x-3*lFood)+up[3]*lFood] | (NORMALPAL << 12);
								else
									BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[y*L+(x-4*lFood)+3*lFood+row*lPac] | (NORMALPAL << 12);
							}
						}
					}
				}
				else{
					if(x<lFood)
						BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[(y-height)*L+x+down[0]*lFood] | (NORMALPAL << 12);
					else{
						if(x<2*lFood)
							BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[(y-height)*L+(x-lFood)+down[1]*lFood] | (NORMALPAL << 12);
						else{
							if(x<3*lFood)
								BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[(y-height)*L+(x-2*lFood)+down[2]*lFood] | (NORMALPAL << 12);
							else{
								if(x<4*lFood)
									BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[(y-height)*L+(x-3*lFood)+down[3]*lFood] | (NORMALPAL << 12);
								else
									BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_pacmanMap[(y-height)*L+(x-4*lFood)+3*lFood+(row+1)%2*lPac] | (NORMALPAL << 12);
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

	// Return true for the game to continue
	return false;
}

void eatit_next(void){
	// Increment score
	score++;

	// Update infos
	info_update_score(score, 0);

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

	// Desactivate BG0
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	score = 0;
	wrong = 0;
}
