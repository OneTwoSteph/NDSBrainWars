/*
 * leader.c
 *
 *  Created on: Jan 20, 2015
 *      Author: Nawaaz GS modified by Stephanie Amati
 *
 */

#include "general.h"
#include "info.h"
#include "leader.h"

// Tiles with 16-colors palettes
u8 fullT[] = {
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11
};

u8 cornerT[] = {
	0x22,0x22,0x22,0x12,
	0x22,0x22,0x22,0x11,
	0x22,0x22,0x11,0x11,
	0x22,0x12,0x11,0x11,
	0x22,0x11,0x11,0x11,
	0x22,0x11,0x11,0x11,
	0x12,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11
};

#define SIDE 6

int block_x[9] = {6, 13, 20};
int block_y[9] = {2, 9, 16};

TAPORDER taporder;
int order[9];

int score;
int wrong;
LEVEL level;

int step;

int draw_timer;

STATE state;

void leader_timer_ISR(){
	draw_timer++;
}

void leader_wrong(){
	// Play effect
	if(wrong == 0) mmEffect(SFX_BOING);

	// Update wrong variable
	wrong++;

	// Start timer at beginning and stop after two blinking effect
	if(wrong == 1) TIMER1_CR |= TIMER_ENABLE;
	if(wrong < 4) leader_draw();
	if(wrong == 4){
		int row, col;
			// Set whole background to grey
				for(row = 0; row < 32; row++){
					for(col = 0; col < 32; col++){
						BG_MAP_RAM_SUB(0)[row*32+col] = 0 | (1<<12);
					}
				}

		TIMER1_CR &= ~(TIMER_ENABLE);
		wrong = 0;
		step = 0;
		leader_new_config();
	}
}

void leader_init(int gameState) {
	// Load tiles in RAM
	dmaCopy(fullT, (u8*)BG_TILE_RAM_SUB(1), 8*8*4/8);
	dmaCopy(cornerT, (u8*)BG_TILE_RAM_SUB(1) + 8*8*4/8, 8*8*4/8);
	
	// Set up palette colors
	BG_PALETTE_SUB[1] = BLUEVAL;
	BG_PALETTE_SUB[2] = GREYVAL;
	BG_PALETTE_SUB[17] = REDVAL;
	BG_PALETTE_SUB[18] = GREYVAL;
	BG_PALETTE_SUB[33] = GREYVAL;
	BG_PALETTE_SUB[34] = GREYVAL;

	// Configure interrupts and timer for block display every 2s
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER0_DATA = TIMER_FREQ_1024(4);
	irqSet(IRQ_TIMER0, &leader_timer_ISR);
	irqEnable(IRQ_TIMER0);
	
	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &leader_wrong);
	irqEnable(IRQ_TIMER1);
	
	// Initialize variables
	score = 0;
	step = 0;
	draw_timer = 0;
	wrong = 0;
	level = VERYEASY;
	state = gameState;
	int i;
	for(i=0; i<9; i++) order[i] = i;

	// Draw infos
	info_init(state);

	// Launch game
	leader_new_config();
}

void leader_new_config() {
	int nb_blocks = level+3;
	int rand_order[9];
	int i, max, position, block;

	// Find in which order the blocks have to be touched
	taporder = rand()%2;

	// Initialize an array with random values
	for(i = 0; i < 9 ; i++) {
		rand_order[i] = rand();
	}
	
	// Set the apparition order of the block by comparing the numbers in the
	// above array
	for(position=0; position<nb_blocks; position++){
		// Find biggest number
		max = 0;
		for(i = 0; i < 9; i++) {
			if(rand_order[i] >= max){
				max = rand_order[i];
				block = i;
			}
		}

		// Assign block to current position in function of biggest number find
		// above and delete the number from array
		order[position] = block;
		rand_order[block] = -1;
	}

	// Draw new blocks
	leader_draw_blocks();
}

void leader_draw_blocks(){
	int x, y;
	int row, col;
	int i;
	int palette;

	// Set whole background to grey
	for(row = 0; row < 32; row++){
		for(col = 0; col < 32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0 | (2<<12);
		}
	}

	// Assign palette in function of order to tap
	if(taporder == SAME) palette = 0;
	else palette = 1;

	// Start drawing with timer to make the blocks appear
	// Also create a map which will be used
	draw_timer = 0;
	TIMER0_CR |= TIMER_ENABLE;

	// Progressively draw all tiles that are needed
	for(i = 0; i<(level+3); i++){
		// Wait the timers time before drawing next block
		while(draw_timer == 0);

		// Draw current block
		x = block_x[order[i]%3];
		y = block_y[order[i]/3];
		leader_draw_block(x, y, palette);

		// Reinistialize timer
		draw_timer = 0;
	}

	// Disable Timer
	TIMER0_CR &= ~(TIMER_ENABLE);
}

void leader_draw_block(int x, int y, int palette){
	int row, col;

	// Fill the block
	for(col = x; col < x+SIDE; col++){
		for(row = y; row < y+SIDE; row++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0 | (palette<<12);
		}
	}

	// Change the 4 corners
	BG_MAP_RAM_SUB(0)[y*32+x] = 1 | (palette<<12);
	BG_MAP_RAM_SUB(0)[(y+SIDE-1)*32+x] = 1 | (palette<<12) | (1<<11);
	BG_MAP_RAM_SUB(0)[y*32+(x+SIDE-1)] = 1 | (palette<<12) | (1<<10);
	BG_MAP_RAM_SUB(0)[(y+SIDE-1)*32+(x+SIDE-1)] = 1 | (palette<<12) | (1<<10) | (1<<11);
}

void leader_draw() {
	int i, start, stop, palette;
	int x, y;
	int row, col;

	// Set whole background to grey
	for(row = 0; row < 32; row++){
		for(col = 0; col < 32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0 | (2<<12);
		}
	}

	// Check color
	if((wrong%2)==0){
		// Check for color
		if(taporder == SAME) palette = 0;
		else palette = 1;

		// Draw only the blocks that weren't taped yet
		if(taporder == SAME){
			start = step;
			stop = (level+3);
		}
		else{
			start = 0;
			stop = (level+3) - step;
		}
		for(i=start; i<stop; i++){
			x = block_x[order[i]%3];
			y = block_y[order[i]/3];
			leader_draw_block(x, y, palette);
		}
	}
}

bool leader_game(bool player, int gameCounter) {
	// Scan the keys and the touch screen
	scanKeys();
	u16 keys = keysDown();
	
	// Stop game if START button pressed or time crossed 15 sec
	// Else check if the correct block was touched
	int time;
	time = info_get_time();

	if(state != TRAIN) info_store_temp_score(player, gameCounter, score);

	if((keys & KEY_START) || (time > GAMETIME)) return true;
	else if(keys & KEY_TOUCH){
		int current;

		// Check at which position the touch screen was touched
		touchPosition touch;
		touchRead(&touch);

		// Check at which position we are
		if(taporder == SAME) current = step;
		else current = (level+3) - step - 1;

		// Check if correct position was touched
		int i;
		int xl, yh, xr, yl;

		for(i=0; i<(level+3); i++){
			xl = block_x[order[i]%3]*8 - 1;
			yh = block_y[order[i]/3]*8 - 1;
			xr = xl + SIDE*8;
			yl = yh + SIDE*8 ;

			if((touch.px > xl) && (touch.px < xr) && (touch.py > yh) && (touch.py < yl)){
				if(i==current){
					leader_correct();
					break;
				}
				else{
					leader_wrong();
					break;
				}
			}
		}
	}

	// Update infos
	info_update(score, state, player);

	// Wait
	while(wrong!=0);

	// Return false because game not ended
	return false;
}

void leader_correct(){
	// Update player state
	step++;

	// Draw new config with one block less
	leader_draw();

	// If the current configuration is finished and was correctly found
	if(step >= (level + 3)) {
		// Update score
		score++;

		// Reinitialize step
		step = 0;

		// See if level changed
		level = score/LEADERLEVEL;

		// Create new configuration
		leader_new_config();
	}
}

void leader_reset() {
	// Suppress infos
	info_finish(score, "leader", state);

	// Draw nothing
	int row, col;
	for(row = 0; row < 32; row++){
		for(col = 0; col < 32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0;
		}
	}

	// Disable timers
	irqDisable(IRQ_TIMER0);
	irqClear(IRQ_TIMER0);
	TIMER0_CR = 0;
	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER0_CR = 1;

	// Reset variables
	score = 0;
	step = 0;
	draw_timer = 0;
	wrong = 0;
	level = VERYEASY;
}
