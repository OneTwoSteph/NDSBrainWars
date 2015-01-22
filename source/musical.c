/*
 * musical.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Stephanie Amati
 *
 */

#include "general.h"
#include "musical.h"
#include "musical_tone.h"

MUSIC music[4];
ANSWER answer[4];

int score;
int wrong;
LEVEL level;

void musical_wrong(){

}

void musical_init(){
	// Configure Backgrounds
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory
	swiCopy(musical_toneTiles, BG_TILE_RAM_SUB(1), musical_toneTilesLen);

	// Copy palette
	swiCopy(musical_tonePal, BG_PALETTE_SUB, musical_tonePalLen);
	swiCopy(musical_tonePal, &BG_PALETTE_SUB[16], musical_tonePalLen);
	swiCopy(musical_tonePal, &BG_PALETTE_SUB[32], musical_tonePalLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[7] = BLUEVAL;
	BG_PALETTE_SUB[8] = GREYVAL;

	BG_PALETTE_SUB[23] = GREENVAL;
	BG_PALETTE_SUB[24] = GREYVAL;

	BG_PALETTE_SUB[39] = REDVAL;
	BG_PALETTE_SUB[40] = GREYVAL;

	// Set draw on screen
	musical_draw();

	// Configure interrupts and timer for false blinking effect
	/*TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);

	irqSet(IRQ_TIMER1, &musical_wrong);
	irqEnable(IRQ_TIMER1);*/

	// Set global variables
	music[0] = DO;
	music[1] = RE;
	music[2] = MI;
	music[3] = FA;

	answer[0] = NO;
	answer[1] = NO;
	answer[2] = NO;

	score = 0;
	wrong = 0;
	level = EASY;
}

void musical_draw(){
	int x, y;
	int xstart = 4;
	int length = 6; 	// of the tones
	int L = 32;			// length of the whole image

	// Draw first background with grey
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*32+x] = musical_toneMap[0];
		}
	}

	// Draw tones in function of the level
	for(x=0; x<xstart + (level+2)*length; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*32+x] = musical_toneMap[y*L+x];
		}
	}

	/*// Change color of already selected ones
	switch(level){
	case EASY:

	case MEDIUM:
	case HARD:
	}*/
}

bool musical_game(){
	/*// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed
	if(keys & KEY_START) return true;
	else{
		// If touchscreen was touched, check if correct
		if(keys & KEY_TOUCH){
			// Find position touched on touchscreen
			touchPosition touch;
			touchRead(&touch);

			// Find out at which tone we are
			int i;
			int tone = 0;
			for(i=0; i<4; i++){
				if(answer[i]==YES) tone = i+1;
			}

			// Check if touched correct symbol
			switch(level){
			case HARD:
				// Check if in fourth tone
				if((touch.px>=179)&&(touch.px<=205)&&(touch.py>=79)&&(touch.py<=100)){

				}

			case MEDIUM:
				// Check if in third tone
				if((touch.px>=131)&&(touch.px<=157)&&(touch.py>=102)&&(touch.py<=123)){

				}
			case EASY:
				// Check if in second tone
				if((touch.px>=83)&&(touch.px<=109)&&(touch.py>=126)&&(touch.py<=147)){
					if(music[tone]==RE) musical_correct();
					else musical_wrong();
				}

				// Check if in first tone
				if((touch.px>=35)&&(touch.px<=61)&&(touch.py>=150)&&(touch.py<=171)){
					if(music[tone]==DO) musical_correct();
				}

				break;
			default: break;
			}

		}

		// Return true for the game to continue
		return false;
	}*/

	return false;
}

void musical_next(){

}

void musical_reset(){

}
