/*
 * plusminus.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS modified by Stephanie Amati
 *
 */

// Modules
#include "general.h"
#include "info.h"
#include "plusminus.h"

// Images
#include "plusminus_im.h"

// Constants
#define POSX1 		8
#define POSX2		12
#define POSY		4
#define NBW			8
#define NBH			16

// Variable
STATE state;

int number;
int compare;

int score;

int draw;					// number draw counter for timer
int wrong;					// wrong blinking counter for timer

bool occupied;				// drawing status

int draw_timer;

// Timer for number display
void plusminus_timer_ISR0(){
	// Draw nothing at the beginnin
	if(draw == 0) plusminus_draw_number(1);

	// Draw after 0.2s
	if(draw == 1) plusminus_draw_number(0);

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
	if((wrong%2) == 0) plusminus_draw_number(1);
	else plusminus_draw_number(0);

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status, disable timer and launch new
	// number
	if(wrong == 4){
		occupied = false;
		TIMER1_CR &= ~(TIMER_ENABLE);
	}
}

void plusminus_init(int gameState) {
	// Copy images containing numbers in BG1 and palette in second palette
	swiCopy(plusminus_imTiles, BG_TILE_RAM_SUB(SUBBG0TILE), plusminus_imTilesLen/2);
	swiCopy(plusminus_imPal, BG_PALETTE_SUB, plusminus_imPalLen/2);

	// Configure palette with correct colors
	BG_PALETTE_SUB[1] = BLUE;
	BG_PALETTE_SUB[2] = GREY;

	BG_PALETTE_SUB[17] = GREY;
	BG_PALETTE_SUB[18] = GREY;

	// Put grey background
	int row, col;

	swiWaitForVBlank();
	for(col = 0; col < W; col++){
		for(row = 0; row < H; row++){
			BG_MAP_RAM_SUB(SUBBG0MAP)[row*W + col] = plusminus_imMap[0] | (1<<12);
		}
	}

	// Configure timer for initial 0 display
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER0_DATA = TIMER_FREQ_1024(5);
	irqSet(IRQ_TIMER0, &plusminus_timer_ISR0);
	irqEnable(IRQ_TIMER0);

	// Configure interrupts and timer for false blinking effect every 0.123s
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &plusminus_timer_ISR1);
	irqEnable(IRQ_TIMER1);

	// Initialize variables
	state = gameState;

	number = 0;
	compare = GREATER;

	score = 0;

	draw = 0;
	wrong = 0;

	// Draw infos
	info_init(state);

	// Launch first number 0
	plusminus_start();
}

void plusminus_start(){
	// Set status to occupied
	occupied = true;

	// Reset drawing variable
	draw = 0;

	// Launch timer to draw block sequencially
	TIMER0_CR |= TIMER_ENABLE;
}

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
		plusminus_draw_digit(POSX1, 0, 1);
		plusminus_draw_digit(POSX1 + NBW, 0, 1);
		plusminus_draw_digit(POSX2, dig2, palette);
	}
}

void plusminus_draw_digit(int xstart, int digit, int palette){
	int row, col;
	int x = 0;
	int y = 0;

	for(col = xstart; col < xstart + NBW; col++){
		for(row = POSY; row < POSY + NBH; row++){
			BG_MAP_RAM_SUB(SUBBG0MAP)[row*W+col] = plusminus_imMap[y*10*NBW + digit*NBW + x] | (palette<<12);
			y++;
		}
		y = 0;
		x++;
	}
}

bool plusminus_game(bool player, int gameCounter) {
	// Stop game if START button pressed or time crossed 15 sec
	// Else check if the correct block was touched
	int time;

	time = info_get_time();
	if(state != TRAIN) info_store_temp_score(player, gameCounter, score);

	// Scan the keys only the game is not in drawing
	// mode or in error blinking mode
	if(occupied){
		return false;
	}
	else{
		// Scan keys
		scanKeys();
		u16 keys = (u16) keysDown();

		// Check if game stops or if answer needs to be checked
		if((keys & KEY_START) || (time > GAMETIME)) return true;
		else{
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

		// Update infos
		info_update(score, state, player);

		// Return game not ended
		return false;
	}
}

void plusminus_correct() {
	// Update score
	score++;

	// Generate new number
	plusminus_new_number();
}

void plusminus_wrong(){
	// Update status
	occupied = true;

	// Reset wrong variable
	wrong = 0;

	// Launch wrong timer
	TIMER1_CR |= TIMER_ENABLE;

	// Play wrong effect
	if(wrong == 0) mmEffect(SFX_BOING);
}

void plusminus_reset(void) {
	// Suppress infos
	info_finish(score, "plusminus", state);

	// Draw grey screen
	int row, col;

	swiWaitForVBlank();
	for(col = 0; col < W; col++){
		for(row = 0; row < H; row++){
			BG_MAP_RAM_SUB(SUBBG0MAP)[row*W + col] = plusminus_imMap[0] | (1<<12);
		}
	}

	// Disable timers
	irqDisable(IRQ_TIMER0);
	irqClear(IRQ_TIMER0);
	TIMER0_CR = 0;

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER0_CR = 1;

	// Reset variable

	number = 0;
	compare = GREATER;

	score = 0;

	draw = 0;
	wrong = 0;
}
