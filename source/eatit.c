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
#include "eatit.h"

// Image
#include "eatit_im.h"


/****************************************************************** Constants */
// Palettes
#define NORMALPAL	6
#define GREYPAL 	7

// Image infos
#define WIM			26
#define HIM			12
#define WPAC 		8
#define WFOOD		6

// Game constants
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
// Game variables
ROW row;					// gives where the pacman is
FOOD up[4];					// occupation from left to right of up row
FOOD down[4];				// occupation from left to right of down row

// Game state 
int score;

// Time variables
int wrong;					// wrong blinking effect

// Drawing variables
bool occupied;


/***************************************************************** Timer ISRs */
// Wrong blinking effect ISR
void eatit_timer_ISR1(void){
	// Draw for blinking effect
	swiWaitForVBlank();
	eatit_draw_blinking();

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status and disable timer
	if(wrong == 6){
		TIMER1_CR &= ~(TIMER_ENABLE);
		occupied = false;
	}
}


/****************************************************************** Functions */
// Initialization
void eatit_init(){
	// Deactivate BG1 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles in BG0 SUB and put colors in palette
	swiCopy(eatit_imTiles, BG_TILE_RAM_SUB(BG0TILE), eatit_imTilesLen);

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

	// Draw grey background first
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = eatit_imMap[0] | (NORMALPAL << 12);
		}
	}

	// Initialize global variables
	int i;

	for(i = 0; i < 4; i++){
		up[i] = EMPTY;
		down[i] = EMPTY;
	}

	row = UP;

	score = 0;

	wrong = 0;

	// Configure timer 1 for blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &eatit_timer_ISR1);
	irqEnable(IRQ_TIMER1);
	
	// Draw pacman for the first time and run 4 times new config in order to set the 
	// food randomly
	eatit_draw_pacman();
	for(i = 0; i < 4; i++) eatit_next();

	// Activate BG0 of SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;
}

// New config
void eatit_next(){
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
int eatit_game(){
	if(!occupied){
		// Scan keys
		u16 keys = (u16) keysDown();

		// Check which key was pressed and if it is correct or false
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

	// Return the score
	return score;
}

// Correct function
void eatit_correct(){
	// Play sound
	mmEffect(SFX_BON);

	// Draw pacman
	swiWaitForVBlank();
	eatit_draw_pacman();

	// Increment score
	score++;

	// Launch next config
	eatit_next();
}

// Wrong function
void eatit_wrong(){
	// Play wrong effect
	mmEffect(SFX_NUL);

	// Draw false position
	swiWaitForVBlank();
	eatit_draw_pacman();

	// Update status
	occupied = true;

	// Reset wrong variable
	wrong = 0;

	// Launch wrong timer
	TIMER1_CR |= TIMER_ENABLE;
}

// Reset function
void eatit_reset(){
	// Deactivate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Reset timer 1
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

	occupied = false;
}