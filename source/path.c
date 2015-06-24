/*
 * path.c
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 *
 */

#include "general.h"
#include "info.h"
#include "path.h"
#include "path_arrow.h"

#define BLUEPAL		6
#define REDPAL		7
#define GREENPAL	8
#define YELLOWPAL	9

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

DIRECTION direction;
COLOR color;

int score;
int wrong;
LEVEL level;

void path_wrong(){
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
	swiWaitForVBlank();
	path_draw();
}

void path_init(){
	// Desactivate BG1
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to memory
	swiCopy(path_arrowTiles, BG_TILE_RAM_SUB(BG0TILE), path_arrowTilesLen/2);

	// Set up palette colors (palette contains back, arrow, circle in this order)
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

	// Draw first background with grey
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*H+x] = path_arrowMap[0] | (BLUEPAL << 12);
		}
	}

	// Set initial random direction and color
	direction = rand()%4;
	color = rand()%2;

	// Set draw on screen
	path_draw();

	// Activate BG0
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &path_wrong);
	irqEnable(IRQ_TIMER1);

	// Set global variables
	score = 0;
	wrong = 0;
	level = EASY;
}

void path_draw(){
	int x, y;
	int L = 32;	// length of the image

	// If we are not in the wrong case, draw figures
	if((wrong%2) == 0){
		for(x = 0; x < W; x++){
			for(y = 0; y < H; y++){
				// Direction
				switch(direction){
				case RIGHT:
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_arrowMap[(y+32+4)*L+x];
					break;
				case LEFT:
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_arrowMap[(y+32+4)*L+(31-x)]^(1<<10);
					break;
				case UP:
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_arrowMap[(y+4)*L+x];
					break;
				case DOWN:
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = path_arrowMap[(31-4-y)*L+x]^(1<<11);
					break;
				default:
					break;
				}

				// Color
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = BG_MAP_RAM_SUB(BG0MAP)[y*W+x] | ((color+6) << 12);
			}
		}
	}
	else{
		for(x = 0; x < W; x++){
			for(y = 0; y < H; y++){
				BG_MAP_RAM_SUB(BG0MAP)[y*H+x] = path_arrowMap[0] | (BLUEPAL << 12);
			}
		}
	}
}

int path_game(){
	// Scan keys to find pressed ones
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
			if((keys & KEY_RIGHT) && (direction == RIGHT)) path_next();
			else if((keys & KEY_LEFT) && (direction == LEFT)) path_next();
			else if((keys & KEY_UP) && (direction == UP)) path_next();
			else if((keys & KEY_DOWN) && (direction == DOWN)) path_next();
			else path_wrong();
			break;
		case R:
			if((keys & KEY_RIGHT) && (direction == LEFT))  path_next();
			else if((keys & KEY_LEFT) && (direction == RIGHT)) path_next();
			else if((keys & KEY_UP) && (direction == DOWN)) path_next();
			else if((keys & KEY_DOWN) && (direction == UP)) path_next();
			else path_wrong();
			break;
		case G:
			if((keys & KEY_A) && (direction == RIGHT)) path_next();
			else if((keys & KEY_Y) && (direction == LEFT)) path_next();
			else if((keys & KEY_X) && (direction == UP)) path_next();
			else if((keys & KEY_B) && (direction == DOWN)) path_next();
			else path_wrong();
			break;
		case Y:
			if((keys & KEY_A) && (direction == LEFT)) path_next();
			else if((keys & KEY_Y) && (direction == RIGHT)) path_next();
			else if((keys & KEY_X) && (direction == DOWN)) path_next();
			else if((keys & KEY_B) && (direction == UP)) path_next();
			else path_wrong();
			break;
		default:
			break;
		}
	}

	// In the case the player was wrong, wait until wrong blinking ends
	while(wrong != 0);

	// Return score
	return score;
}


void path_next(){
	// Increment score
	score++;

	// Check level
	if(score == PATHMEDIUM) level = MEDIUM;
	if(score == PATHHARD) level = HARD;

	// Random numbers for direction and color
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
	path_draw();
}

void path_reset(){
	// Desactivate BG0
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	score = 0;
	wrong = 0;
}
