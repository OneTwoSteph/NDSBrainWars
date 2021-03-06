/*
 * plusminus.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS modified by Stephanie Amati
 *
 */


/******************************************************************** Modules */
// General
#include "general.h"
#include "plusminus.h"

// Images
#include "plusminus_im.h"


/****************************************************************** Constants */
// Palettes
#define NORMALPAL	6
#define GREYPAL		7

// Image infos
#define POSX1 		8
#define POSX2		12
#define POSY		4
#define NBW			8
#define NBH			16

// Game constants
#define GREATER 	1
#define SMALLER 	2


/*********************************************************** Global variables */
// Game variable
int number;					// current number
int compare;				// current number status comparing to previous one

// Game state
int score;

// Timer variables
int draw;					// number drawing pause				
int wrong;					// wrong blinking effect

// Drawing status
bool occupied;				// block actions while drawing


/***************************************************************** Timer ISRs */
// Number drawing ISR
void plusminus_timer_ISR0(){
	// Draw nothing at the beginnin
	if(draw == 0) plusminus_draw_number(GREYPAL);

	// Draw after 0.2s
	if(draw == 1) plusminus_draw_number(NORMALPAL);

	// Increment draw variable
	draw++;

	// If we are in the start display of 0, eras it after 1s and start game
	// Otherwise stop timer after drawing number
	if((score == 0) && (number == 0)){
		if(draw == 5)  {
			occupied = false;
			TIMER0_CR &= ~(TIMER_ENABLE);
			plusminus_new_number();
		}
	}
	else{
		if(draw > 1){
			occupied = false;
			TIMER0_CR &= ~(TIMER_ENABLE);
		}
	}
}

// Wrong blinking ISR
void plusminus_timer_ISR1(){
	// Draw for blinking effect
	if((wrong%2) == 0) plusminus_draw_number(GREYPAL);
	else plusminus_draw_number(NORMALPAL);

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status, disable timer and launch new
	// number
	if(wrong == 4){
		occupied = false;
		TIMER1_CR &= ~(TIMER_ENABLE);
	}
}


/****************************************************************** Functions */
// Initialization
void plusminus_init() {
	// Deactivate BG1 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles in BG0 of SUB and put correct colors in palette
	swiCopy(plusminus_imTiles, BG_TILE_RAM_SUB(BG0TILE), plusminus_imTilesLen/2);

	BG_PALETTE_SUB[0x61] = BLUE;
	BG_PALETTE_SUB[0x62] = GREY;

	BG_PALETTE_SUB[0x71] = GREY;
	BG_PALETTE_SUB[0x72] = GREY;

	// Put grey background
	int row, col;

	swiWaitForVBlank();
	for(col = 0; col < W; col++){
		for(row = 0; row < H; row++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W + col] = plusminus_imMap[0] | (GREYPAL << 12);
		}
	}

	// Configure timer 0 for drawing
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER0_DATA = TIMER_FREQ_1024(5);
	irqSet(IRQ_TIMER0, &plusminus_timer_ISR0);
	irqEnable(IRQ_TIMER0);

	// Configure timer 1 for wrong blinking
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &plusminus_timer_ISR1);
	irqEnable(IRQ_TIMER1);

	// Initialize variables
	number = 0;
	compare = GREATER;

	score = 0;

	draw = 0;
	wrong = 0;

	occupied = false;

	// Activate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Launch first number
	plusminus_start();
}

// Draw first the 0 to start
void plusminus_start(){
	// Set status to occupied
	occupied = true;

	// Reset drawing variable
	draw = 0;

	// Launch timer to draw block sequencially
	TIMER0_CR |= TIMER_ENABLE;
}

// Find new number
void plusminus_new_number() {
	// Put flag
	occupied = true;

	// Find new number not equal to precedent one
	int temp = 0;

	while((temp = rand()%100) == number);
	
	// Check for status of this new number
	if(temp > number) compare = GREATER;
	else compare = SMALLER;

	// Set new number
	number = temp;

	// Reset drawing variable
	draw = 0;

	// Launch timer to draw block sequencially
	TIMER0_CR |= TIMER_ENABLE;
}

// Draw number 
void plusminus_draw_number(int palette){
	// Check digits of the number
	int dig1, dig2;

	dig1 = number/10;
	dig2 = number%10;

	// Check if we are in double digit case or unique digit case and draw
	// number
	swiWaitForVBlank();
	if(dig1 > 0){
		// First digit
		plusminus_draw_digit(POSX1, dig1, palette);

		// Second digit
		plusminus_draw_digit(POSX1 + NBW, dig2, palette);
	}
	else {
		plusminus_draw_digit(POSX1, 0, GREYPAL);
		plusminus_draw_digit(POSX1 + NBW, 0, GREYPAL);
		plusminus_draw_digit(POSX2, dig2, palette);
	}
}

// Draw digit of number
void plusminus_draw_digit(int xstart, int digit, int palette){
	int row, col;
	int x = 0;
	int y = 0;

	for(col = xstart; col < xstart + NBW; col++){
		for(row = POSY; row < POSY + NBH; row++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W+col] = plusminus_imMap[y*10*NBW + digit*NBW + x] | (palette<<12);
			y++;
		}
		y = 0;
		x++;
	}
}

// Main function
int plusminus_game() {
	// Scan the keys only the game is not in drawing
	// mode or in error blinking mode
	if(!occupied){
		// Scan keys
		u16 keys = (u16) keysDown();

		// Check how many of the active keys were pressed
		int counter = 0;

		if(keys & KEY_UP) counter ++;
		if(keys & KEY_DOWN) counter ++;

		// If both keys were pressed, it is wrong, otherwise check answer
		if(counter > 1) plusminus_correct();
		else if(counter == 1){
			if((compare==GREATER) && (keys & KEY_UP)) plusminus_correct();
			else if((compare==SMALLER) && (keys & KEY_DOWN)) plusminus_correct();
			else plusminus_wrong();
		}
		
	}

	// Return score
	return score;
}

// Correct function
void plusminus_correct() {
	// Play sound
	mmEffect(SFX_BON);

	// Update score
	score++;

	// Generate new number
	plusminus_new_number();
}


// Wrong function
void plusminus_wrong(){
	// Play sound
	mmEffect(SFX_NUL);

	// Update status
	occupied = true;

	// Reset wrong variable
	wrong = 0;

	// Launch wrong timer
	TIMER1_CR |= TIMER_ENABLE;
}

// Reset function
void plusminus_reset(void) {
	// Deactivate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Disable timer 0
	irqDisable(IRQ_TIMER0);
	irqClear(IRQ_TIMER0);
	TIMER0_CR = 0;

	// Disable timer 1
	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER0_CR = 1;

	// Reset all global variables
	number = 0;
	compare = GREATER;

	score = 0;

	draw = 0;
	wrong = 0;

	occupied = false;
}