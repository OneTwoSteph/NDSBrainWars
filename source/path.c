/*
 * path.c
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 *
 */

#include "general.h"
#include "path.h"
#include "path_arrow.h"

DIRECTION direction;
COLOR color;

int score;
int wrong;
LEVEL level;

void path_init(){
	// Configure Background
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory
	swiCopy(path_arrowTiles, BG_TILE_RAM_SUB(1), path_arrowTilesLen/2);

	// Copy palette
	swiCopy(path_arrowPal, BG_PALETTE_SUB, path_arrowPalLen/2);
	swiCopy(path_arrowPal, &BG_PALETTE_SUB[16], path_arrowPalLen);
	swiCopy(path_arrowPal, &BG_PALETTE_SUB[16*2], path_arrowPalLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[0] = GREYVAL;
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[2] = BLUEVAL;

	BG_PALETTE_SUB[17] = WHITEVAL;
	BG_PALETTE_SUB[18] = REDVAL;

	BG_PALETTE_SUB[33] = WHITEVAL;
	BG_PALETTE_SUB[34] = GREENVAL;

	BG_PALETTE_SUB[49] = WHITEVAL;
	BG_PALETTE_SUB[50] = YELLOWVAL;

	// Set initial random direction and color
	direction = rand()%4;
	color = rand()%2;

	// Set draw on screen
	path_draw();

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

	// Draw first background with grey
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[0];
		}
	}

	// If we are not in the wrong case, draw figures
	if((wrong%2)==0){
		for(x=0; x<32; x++){
			for(y=0; y<24; y++){
				// Direction
				switch(direction){
				case RIGHT:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(y+32+4)*L+x];
					break;
				case LEFT:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(y+32+4)*L+(31-x)]^(1<<10);
					break;
				case UP:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(y+4)*L+x];
					break;
				case DOWN:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(31-4-y)*L+x]^(1<<11);
					break;
				default:
					break;
				}

				// Color
				BG_MAP_RAM_SUB(0)[y*32+x] = BG_MAP_RAM_SUB(0)[y*32+x]|(color<<12);
			}
		}
	}
}

bool path_game(){
	// Scan keys to find pressed ones
	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed
	if(keys & KEY_START) return false;
	else{
		// Check which key was pressed and if it is correct
		switch(color){
		case BLUE:
			if(keys & KEY_RIGHT){
				if(direction == RIGHT) path_next();
				else path_wrong();
			}

			if(keys & KEY_LEFT){
				if(direction == LEFT) path_next();
				else path_wrong();
			}

			if(keys & KEY_UP){
				if(direction == UP) path_next();
				else path_wrong();
			}

			if(keys & KEY_DOWN){
				if(direction == DOWN) path_next();
				else path_wrong();
			}
			if((keys & KEY_Y) ||( keys & KEY_X) || (keys & KEY_B) || (keys & KEY_A))
				path_wrong();
			break;
		case RED:
			if(keys & KEY_RIGHT){
				if(direction == LEFT) path_next();
				else path_wrong();
			}

			if(keys & KEY_LEFT){
				if(direction == RIGHT) path_next();
				else path_wrong();
			}

			if(keys & KEY_UP){
				if(direction == DOWN) path_next();
				else path_wrong();
			}

			if(keys & KEY_DOWN){
				if(direction == UP) path_next();
				else path_wrong();
			}
			if((keys & KEY_Y) ||( keys & KEY_X) || (keys & KEY_B) || (keys & KEY_A))
				path_wrong();
			break;
		case GREEN:
			if(keys & KEY_A){
				if(direction == RIGHT) path_next();
				else path_wrong();
			}

			if(keys & KEY_Y){
				if(direction == LEFT) path_next();
				else path_wrong();
			}

			if(keys & KEY_X){
				if(direction == UP) path_next();
				else path_wrong();
			}

			if(keys & KEY_B){
				if(direction == DOWN) path_next();
				else path_wrong();
			}
			if((keys & KEY_A) ||( keys & KEY_Y) || (keys & KEY_X) || (keys & KEY_B))
				path_wrong();
			break;
		case YELLOW:
			if(keys & KEY_A){
				if(direction == LEFT) path_next();
				else path_wrong();
			}

			if(keys & KEY_Y){
				if(direction == RIGHT) path_next();
				else path_wrong();
			}

			if(keys & KEY_X){
				if(direction == DOWN) path_next();
				else path_wrong();
			}

			if(keys & KEY_B){
				if(direction == UP) path_next();
				else path_wrong();
			}
			if((keys & KEY_A) ||( keys & KEY_Y) || (keys & KEY_X) || (keys & KEY_B))
				path_wrong();
			break;
		default:
			break;
		}
		return true;
	}
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
	path_draw();
}

void path_wrong(){
	// Update wrong variable
	wrong++;

	// Start timer at beginning and stop after two blinking effect
	if(wrong==1) TIMER1_CR |= TIMER_ENABLE;
	if(wrong==4){
		TIMER1_CR &= ~(TIMER_ENABLE);
		wrong = 0;
	}

	// Draw
	path_draw();
}

void path_reset(){
	// Draw nothing
	wrong = 1;
	path_draw();

	// Reset all global variables
	score = 0;
	wrong = 0;
}
