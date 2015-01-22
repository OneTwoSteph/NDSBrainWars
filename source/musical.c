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

void musical_wrong(){

}

void musical_init(){
	// Configure Backgrounds
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;
	BGCTRL_SUB[2] = BG_TILE_BASE(3) | BG_MAP_BASE(25) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory
	swiCopy(jankenpon_handTiles, BG_TILE_RAM_SUB(1), jankenpon_handTilesLen);

	// Copy palette
	swiCopy(jankenpon_handPal, BG_PALETTE_SUB, jankenpon_handPalLen);
	swiCopy(jankenpon_handPal, &BG_PALETTE_SUB[16], jankenpon_handPalLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[2] = BLUEVAL;
	BG_PALETTE_SUB[3] = GREYVAL;
	BG_PALETTE_SUB[4] = BLACKVAL;

	BG_PALETTE_SUB[17] = WHITEVAL;
	BG_PALETTE_SUB[18] = REDVAL;
	BG_PALETTE_SUB[19] = GREYVAL;
	BG_PALETTE_SUB[20] = BLACKVAL;

	// Set draw on screen
	shape = rand()%3;
	color = BLUE;
	U = SCISSOR;
	M = PAPER;
	D = ROCK;
	jankenpon_draw();

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	//irqInit();
	irqSet(IRQ_TIMER1, &jankenpon_wrong);
	irqEnable(IRQ_TIMER1);

	// Set global variables
	score = 0;
	wrong = 0;
	level = EASY;
}
void musical_draw(){

}

bool musical_game(){

}

void musical_next(){

}

void musical_reset(){

}
