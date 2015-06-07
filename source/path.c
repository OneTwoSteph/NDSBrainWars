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

DIRECTION direction;
COLOR color;

int score;
int wrong;
LEVEL level;

STATE state;

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
	path_draw();
}

void path_init(int gameState){
	// Copy tiles to memory
	swiCopy(path_arrowTiles, BG_TILE_RAM_SUB(1), path_arrowTilesLen/2);

	// Copy palette
	swiCopy(path_arrowPal, BG_PALETTE_SUB, path_arrowPalLen/2);
	swiCopy(path_arrowPal, &BG_PALETTE_SUB[16], path_arrowPalLen);
	swiCopy(path_arrowPal, &BG_PALETTE_SUB[16*2], path_arrowPalLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[5] = WHITEVAL;
	BG_PALETTE_SUB[6] = BLUEVAL;
	BG_PALETTE_SUB[7] = GREYVAL;

	BG_PALETTE_SUB[21] = WHITEVAL;
	BG_PALETTE_SUB[22] = REDVAL;
	BG_PALETTE_SUB[23] = GREYVAL;

	BG_PALETTE_SUB[37] = WHITEVAL;
	BG_PALETTE_SUB[38] = GREENVAL;
	BG_PALETTE_SUB[39] = GREYVAL;

	BG_PALETTE_SUB[53] = WHITEVAL;
	BG_PALETTE_SUB[54] = YELLOWVAL;
	BG_PALETTE_SUB[55] = GREYVAL;

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
	state = gameState;

	// Draw infos
	info_init(state);
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

bool path_game(bool player, int gameCounter){
	// Scan keys to find pressed ones
	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed or time crossed 15 sec
	int time;
	time = info_get_time();

	if(state != TRAIN) { info_store_temp_score(player, gameCounter, score); }

	if((keys & KEY_START) || (time > GAMETIME)) return true;
	else{
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
			case BLUE:
				if((keys & KEY_RIGHT) && (direction == RIGHT)) path_next();
				else if((keys & KEY_LEFT) && (direction == LEFT)) path_next();
				else if((keys & KEY_UP) && (direction == UP)) path_next();
				else if((keys & KEY_DOWN) && (direction == DOWN)) path_next();
				else path_wrong();
				break;
			case RED:
				if((keys & KEY_RIGHT) && (direction == LEFT))  path_next();
				else if((keys & KEY_LEFT) && (direction == RIGHT)) path_next();
				else if((keys & KEY_UP) && (direction == DOWN)) path_next();
				else if((keys & KEY_DOWN) && (direction == UP)) path_next();
				else path_wrong();
				break;
			case GREEN:
				if((keys & KEY_A) && (direction == RIGHT)) path_next();
				else if((keys & KEY_Y) && (direction == LEFT)) path_next();
				else if((keys & KEY_X) && (direction == UP)) path_next();
				else if((keys & KEY_B) && (direction == DOWN)) path_next();
				else path_wrong();
				break;
			case YELLOW:
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
	}

	// Update infos
	info_update(score, state, player);

	// In the case the player was wrong, wait until wrong blinking ends
	while(wrong != 0);

	// Return with game not ended
	return false;
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

void path_reset(){
	// Suppress infos
	info_finish(score, "path", state);

	// Draw nothing
	wrong = 1;
	path_draw();

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	score = 0;
	wrong = 0;
}
