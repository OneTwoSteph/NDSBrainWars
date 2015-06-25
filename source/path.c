/*
 * path.c
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 *
 */


/******************************************************************** Modules */
// General
#include "general.h"
#include "path.h"

// Image
#include "path_im.h"


/****************************************************************** Constants */
// Palette
#define BLUEPAL		6
#define REDPAL		7
#define GREENPAL	8
#define YELLOWPAL	9
#define GREYPAL		10

// Game constants
typedef enum DIRECTION DIRECTION;
enum DIRECTION
{
    RIGHT = 0,
    LEFT = 1,
    UP = 2,
    DOWN = 3
};

typedef enum COLOR COLOR;
enum COLOR
{
    B = 0,
    R = 1,
    G = 2,
    Y = 3,
    N = 4
};


/*********************************************************** Global variables */
// Game variables
DIRECTION direction;
COLOR color;

// Game state
int score;
LEVEL level;

// Timer variables
int wrong;

// Drawing status
bool occupied;


/***************************************************************** Timer ISRs */
// Wrong blinking ISR
void path_timer_ISR1(){
	// Draw for blinking effect
	path_draw(((wrong%2) == 0) ? GREYPAL : color + 6);

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status, disable timer and launch new
	// configuration
	if(wrong == 6){
		TIMER1_CR &= ~(TIMER_ENABLE);
		occupied = false;
	}
}


/****************************************************************** Functions */
// Initialization
void path_init(){
	// Deactivate BG1 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to BG0 SUB and put correct colors in palettes
	swiCopy(path_imTiles, BG_TILE_RAM_SUB(BG0TILE), path_imTilesLen/2);

	BG_PALETTE_SUB[0x61] = BLUE;
	BG_PALETTE_SUB[0x62] = WHITE;
	BG_PALETTE_SUB[0x63] = GREY;

	BG_PALETTE_SUB[0x71] = RED;
	BG_PALETTE_SUB[0x72] = WHITE;
	BG_PALETTE_SUB[0x73] = GREY;

	BG_PALETTE_SUB[0x81] = GREEN;
	BG_PALETTE_SUB[0x82] = WHITE;
	BG_PALETTE_SUB[0x83] = GREY;

	BG_PALETTE_SUB[0x91] = YELLOW;
	BG_PALETTE_SUB[0x92] = WHITE;
	BG_PALETTE_SUB[0x93] = GREY;

	BG_PALETTE_SUB[0xa1] = GREY;
	BG_PALETTE_SUB[0xa2] = GREY;
	BG_PALETTE_SUB[0xa3] = GREY;

	// Draw first background with grey
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*H+x] = path_imMap[0] | (BLUEPAL << 12);
		}
	}

	// Initialize global variables
	direction = UP;
	color = B;

	score = 0;
	level = EASY;

	wrong = 0;
	
	occupied = false;

	// Configure timer 1 for wrong blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &path_timer_ISR1);
	irqEnable(IRQ_TIMER1);

	// Launch first arrow
	path_next();

	// Activate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;
}

// Find next arrow
void path_next(){
	// Find andom numbers for direction and color
	int nb1, nb2;
	while((nb1 = rand()%4) == direction);
	if(level == EASY) nb2 = rand()%2;
	else{
		if(level == MEDIUM) nb2 = rand()%3;
		else nb2 = rand()%4;
	}

	direction = nb1;
	color = nb2;

	// Redraw screen
	swiWaitForVBlank();
	path_draw(color + 6);
}

// Draw arrow
void path_draw(int pal){
	int x, y;

	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			// Direction
			switch(direction){
			case RIGHT:
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_imMap[(y+H)*W+x];
				break;
			case LEFT:
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_imMap[(y+H)*W+((W-1)-x)]^(1<<10);
				break;
			case UP:
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_imMap[y*W+x];
				break;
			case DOWN:
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_imMap[((H-1)-y)*W+x]^(1<<11);
				break;
			default:
				break;
			}

			// Color
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = BG_MAP_RAM_SUB(BG0MAP)[y*W+x] | (pal << 12);
		}
	}
}

// Main function
int path_game(){
	// Scan keys to find pressed ones only if game not occupied
	if(!occupied){
		// Scan
		u16 keys = (u16) keysDown();

		// Check how many keys were pressed
		int counter = 0;
		if(keys & KEY_RIGHT) counter++;
		if(keys & KEY_LEFT) counter++;
		if(keys & KEY_UP) counter++;
		if(keys & KEY_DOWN) counter++;
		if(keys & KEY_A) counter++;
		if(keys & KEY_B) counter++;
		if(keys & KEY_X) counter++;
		if(keys & KEY_Y) counter++;

		// Decide what to do in function of how many keys were pressed
		// If several keys, wrong
		// If one key, check if ok
		// If no key, do nothing
		if(counter > 1) path_wrong();
		else if(counter == 1){
			// Check  if the key which was pressed is correct
			switch(color){
			case B:
				if((keys & KEY_RIGHT) && (direction == RIGHT)) path_correct();
				else if((keys & KEY_LEFT) && (direction == LEFT)) path_correct();
				else if((keys & KEY_UP) && (direction == UP)) path_correct();
				else if((keys & KEY_DOWN) && (direction == DOWN)) path_correct();
				else path_wrong();
				break;
			case R:
				if((keys & KEY_RIGHT) && (direction == LEFT))  path_correct();
				else if((keys & KEY_LEFT) && (direction == RIGHT)) path_correct();
				else if((keys & KEY_UP) && (direction == DOWN)) path_correct();
				else if((keys & KEY_DOWN) && (direction == UP)) path_correct();
				else path_wrong();
				break;
			case G:
				if((keys & KEY_A) && (direction == RIGHT)) path_correct();
				else if((keys & KEY_Y) && (direction == LEFT)) path_correct();
				else if((keys & KEY_X) && (direction == UP)) path_correct();
				else if((keys & KEY_B) && (direction == DOWN)) path_correct();
				else path_wrong();
				break;
			case Y:
				if((keys & KEY_A) && (direction == LEFT)) path_correct();
				else if((keys & KEY_Y) && (direction == RIGHT)) path_correct();
				else if((keys & KEY_X) && (direction == DOWN)) path_correct();
				else if((keys & KEY_B) && (direction == UP)) path_correct();
				else path_wrong();
				break;
			default:
				break;
			}
		}
	}

	// Return score
	return score;
}

// Correct function
void path_correct(){
	// Play sound
	mmEffect(SFX_BON);

	// Increment score
	score++;

	// Check level
	if(score == PATHMEDIUM) level = MEDIUM;
	if(score == PATHHARD) level = HARD;

	// Launch next arrow
	path_next();
}

// Wrong function
void path_wrong(){
	// Play sound
	mmEffect(SFX_NUL);

	// Update status
	occupied = true;

	// Reset wrong variable
	wrong = 0;

	// Launch wrong timer
	TIMER1_CR |= TIMER_ENABLE;
}

void path_reset(){
	// Deactivate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Disable timer 1
	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	direction = UP;
	color = B;

	score = 0;
	level = EASY;

	wrong = 0;
	
	occupied = false;
}