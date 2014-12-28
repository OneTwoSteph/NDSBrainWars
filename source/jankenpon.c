/*
 * jankenpon.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati
 */

#include "general.h"
#include "jankenpon.h"
#include "jankenpon_hand.h"

SHAPE shape;
COLOR color;

int score;
int wrong;
LEVEL level;

void jankenpon_init(){
	// Copy tiles to memory
	swiCopy(jankenpon_handTiles, BG_TILE_RAM_SUB(1), jankenpon_handTilesLen/2);

	// Copy palette
	swiCopy(jankenpon_handPal, BG_PALETTE_SUB, jankenpon_handPalLen/2);
	swiCopy(jankenpon_handPal, &BG_PALETTE_SUB[16], jankenpon_handPalLen);
	swiCopy(jankenpon_handPal, &BG_PALETTE_SUB[16*2], jankenpon_handPalLen);
	swiCopy(jankenpon_handPal, &BG_PALETTE_SUB[16*3], jankenpon_handPalLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[2] = BLUEVAL;
	BG_PALETTE_SUB[3] = GREYVAL;
	BG_PALETTE_SUB[4] = BLACKVAL;

	BG_PALETTE_SUB[17] = WHITEVAL;
	BG_PALETTE_SUB[18] = REDVAL;
	BG_PALETTE_SUB[19] = GREYVAL;
	BG_PALETTE_SUB[20] = BLACKVAL;

	BG_PALETTE_SUB[65] = WHITEVAL;
	BG_PALETTE_SUB[66] = REDVAL;
	BG_PALETTE_SUB[67] = GREYVAL;
	BG_PALETTE_SUB[68] = BLACKVAL;

	// Set draw on screen
	shape = PAPER;
	color = BLUE;
	jankenpon_draw(shape, color);

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	//irqInit();
	//irqSet(IRQ_TIMER1, &path_wrong);
	//irqEnable(IRQ_TIMER1);

	// Set global variables
	score = 0;
	wrong = 0;
	level = EASY;
}

void jankenpon_draw(shape, color){
	int x, y;
	int length = 22;
	int W = 76;

	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			// Big hand and mini hand
			if(x<23){
				switch(shape){
				case PAPER:
					BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[y*W+x];
					break;
				case ROCK:
					BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[y*W+length+x];
					break;
				case SCISSOR:
					BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[y*W+2*length+x];
					break;
				default:
					break;
				}
			}
			else{
				BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[y*W+3*length+(x-23)];
			}

			// Color
			BG_MAP_RAM_SUB(0)[y*32+x] = BG_MAP_RAM_SUB(0)[y*32+x]|(color<<12);
		}
	}
}

bool jankenpon_game(void){

	return true;
}

void jankenpon_next(void){


}
void jankenpon_wrong(void){


}

void jankenpon_reset(){


}
