/*
 * eatit.c
 *
 *  Created on: Jan 21, 2015
 *      Author: Stephanie Amati
 *
 */


/******************************************************************** Modules */
// General
#include "general.h"
#include "info.h"
#include "eatit.h"

// Image
#include "eatit_im.h"


/****************************************************************** Constants */
// Palette
#define NORMALPAL	6
#define GREYPAL 	7

// Image infos
#define WIM			26
#define HIM			12
#define WPAC 		8
#define WFOOD		6

// Game
typedef enum ROW ROW;
enum ROW
{
    UP = 0,
    DOWN = 1,
};

typedef enum FOOD FOOD;
enum FOOD
{
    EMPTY = 0,
    MONSTER = 1,
    CHERRY = 2
};


/*********************************************************** Global variables */
// Global game variable
STATE state;

// Game variables
ROW row;
FOOD up[4];
FOOD down[4];

// Game state variables
int score;
int wrong;

// Drawing variables
bool occupied;


/***************************************************************** Timer ISRs */
// Wrong blinking effect
void eatit_timer_ISR1(void){
	// Draw for blinking effect
	swiWaitForVBlank();
	eatit_draw_blinking();

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status and disable timer
	if(wrong == 6){
		occupied = false;
		TIMER1_CR &= ~(TIMER_ENABLE);
	}
}


/****************************************************************** Functions */
// Initialization
void eatit_init(int gameState){
	// Desactivate BG1
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to memory
	swiCopy(eatit_imTiles, BG_TILE_RAM_SUB(BG0TILE), eatit_imTilesLen);

	// Set up palette colors
	BG_PALETTE_SUB[0x61] = RED;
	BG_PALETTE_SUB[0x62] = BLUE;
	BG_PALETTE_SUB[0x63] = GREEN;
	BG_PALETTE_SUB[0x64] = WHITE;
	BG_PALETTE_SUB[0x65] = GREY;
	BG_PALETTE_SUB[0x66] = BLACKGREY;

	BG_PALETTE_SUB[0x71] = GREY;
	BG_PALETTE_SUB[0x72] = GREY;
	BG_PALETTE_SUB[0x73] = GREY;
	BG_PALETTE_SUB[0x74] = GREY;
	BG_PALETTE_SUB[0x75] = GREY;
	BG_PALETTE_SUB[0x76] = GREY;


	// Initialize variables
	int i;

	for(i = 0; i < 4; i++){
		up[i] = EMPTY;
		down[i] = EMPTY;
	}

	row = UP;

	// Run 4 times new config in order to set the food random
	for(i = 0; i < 4; i++) eatit_next();

	// Draw pacman for the first time
	eatit_draw_pacman();

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);

	irqSet(IRQ_TIMER1, &eatit_timer_ISR1);
	irqEnable(IRQ_TIMER1);

	// Set global variables
	score = 0;
	wrong = 0;
	state = gameState;

	// Draw infos
	info_init(state);

	// Activate BG0 of SUB to draw first configuration
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;
}

// new config
void eatit_next(void){
	// Random food for new entries
	int nb1, nb2;

	nb1 = rand()%3;

	if(nb1 == MONSTER) while((nb2 = rand()%3) == MONSTER);
	else if(nb1 == CHERRY) while((nb2 = rand()%3) == CHERRY);
	else while((nb2 = rand()%3) == EMPTY);

	// Update up and down rows
	int i;

	for(i = 0; i < 3; i++){
		up[i] = up[i+1];
		down[i] = down[i+1];
	}
	up[3] = nb1;
	down[3] = nb2;

	// Redraw screen
	swiWaitForVBlank();
	eatit_draw_food();
}

// Draw pacman
void eatit_draw_pacman(){
	// Draw grey background first
	int x, y;

	for(x = 0; x < WPAC; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_imMap[0] | (NORMALPAL << 12);
		}
	}

	// Draw pacman
	int xm, ym;

	xm = 3*WFOOD;
	ym = 0;
	for(x = 0; x < WPAC; x++){
		for(y = row*HIM; y < (row+1)*HIM; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_imMap[ym*WIM + xm] | (NORMALPAL << 12);
			ym++;
		}
		ym = 0;
		xm++;
	}
}


// Draw food
void eatit_draw_food(){
	// Draw space in grey first
	int x, y;

	for(x = WPAC; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_imMap[0] | (NORMALPAL << 12);
		}
	}

	// Draw food
	int i, j;
	int xm, ym;

	for(j = 0; j < 2; j++){
		for(i = 0; i < 4; i++){
			xm = ((j == 0) ? up[i]*WFOOD : down[i]*WFOOD);
			ym = 0;
			for(x = WPAC + i*WFOOD; x < WPAC + (i+1)*WFOOD; x++){
				for(y = j*HIM; y < (j+1)*HIM; y++){
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_imMap[ym*WIM + xm] | (NORMALPAL << 12);
					ym++;
				}
				ym = 0;
				xm++;
			}
		}
	}
}

// Draw wrong blinking effect
void eatit_draw_blinking(){
	// Undraw if wrong pair, draw if wrong unpair
	int palette = ((wrong%2) == 0) ? GREYPAL : NORMALPAL;
	int x, y;

	for(x = 0; x < WPAC; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = (BG_MAP_RAM_SUB(BG0MAP)[y*W+x] & (0x0fff)) | (palette << 12);
		}
	}
}

// Main function
bool eatit_game(bool player, int gameCounter){
	// Stop game if START button pressed or time crossed 15 sec
	int time;
	time = info_get_time();

	if(state != TRAIN) { info_store_temp_score(player, gameCounter, score); }

	if(occupied) return false;
	else{
		// Scan keys
		scanKeys();
		u16 keys = (u16) keysDown();

		// Check which key was pressed and if it is correct or false
		if(keys & KEY_START) return true;
		else{
			int counter = 0;
			if(keys & KEY_UP) counter++;
			if(keys & KEY_DOWN) counter++;

			if(counter == 1){
				row = ((keys & KEY_UP) ? UP : DOWN); 
				if(((keys & KEY_UP) && ((up[0] == MONSTER) || (down[0] == CHERRY))) || 
				   ((keys & KEY_DOWN) && ((down[0] == MONSTER) || (up[0] == CHERRY)))) eatit_wrong();
				else eatit_correct();
			}
		}

		return false;
	}
}

// Correct answer
void eatit_correct(){
	// Draw pacman
	swiWaitForVBlank();
	eatit_draw_pacman();

	// Increment score
	score++;

	// Update infos
	info_update_score(score, 0);

	// Launch next config
	eatit_next();
}

void eatit_wrong(){
	// Draw false position
	swiWaitForVBlank();
	eatit_draw_pacman();

	// Update status
	occupied = true;

	// Reset wrong variable
	wrong = 0;

	// Launch wrong timer
	TIMER1_CR |= TIMER_ENABLE;

	// Play wrong effect
	if(wrong == 0) mmEffect(SFX_BOING);
}

// Reset game
void eatit_reset(){
	// Suppress infos
	info_finish(score, "eatit", state);

	// Desactivate BG0
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	int i;

	for(i = 0; i < 4; i++){
		up[i] = EMPTY;
		down[i] = EMPTY;
	}

	row = UP;

	score = 0;
	wrong = 0;
}
