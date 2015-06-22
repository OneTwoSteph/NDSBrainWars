/*
 * leader.c
 *
 *  Created on: Jan 20, 2015
 *      Author: Nawaaz GS modified by Stephanie Amati
 *
 */


/******************************************************************** Modules */
// General
#include "general.h"
#include "info.h"
#include "leader.h"


/****************************************************************** Constants */
// Block infos
#define SIDE 		   	6							// block side in tiles
#define MAXB 		   	9  						// max nb of blocks
const int block_x[3] = {6, 13, 20};		// x positions of blocks
const int block_y[3] = {2, 9, 16};		// y positions of blocks

// Palettes
#define BLUEPAL			6
#define REDPAL			7
#define GREYPAL			8

// Tiles
#define FULL			0
#define	CORNER			1

typedef enum TAPORDER TAPORDER;
enum TAPORDER
{
	SAME = 0,
	INVERSE = 1
};

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


/*********************************************************** Global variables */
// Game variables
STATE state;				// general game state

TAPORDER taporder;			// order in which the blocks have to be taped
int order[MAXB];			// order of the blocks

int score;					// score of the player
LEVEL level;				// level of the player
int nb_blocks;				// number of blocks to draw (depends on level)
int block;					// gives at what block the player is

int draw;					// block drawing counter for timer
int wrong;					// wrong blinking counter for timer

bool occupied;				// drawing status


/***************************************************************** Timer ISRs */
// Block drawing ISR
void leader_timer_ISR0(){
	// Draw current block every two interrupts
	if(((draw+1)%2) == 0) {
		// Draw block
		int x, y;

		x = block_x[order[draw/2]%3];
		y = block_y[order[draw/2]/3];
		swiWaitForVBlank();
		leader_draw_block(x, y, ((taporder == SAME) ? BLUEPAL : REDPAL));
	}

	// Increment draw variable
	draw++;

	// When blocks are all drawn, update flag and unable timer
	if(draw == (nb_blocks*2)) {
		TIMER0_CR &= ~(TIMER_ENABLE);
		occupied = false;
	}
}

// Wrong blinking ISR
void leader_timer_ISR1(){
	// Draw for blinking effect
	leader_draw_blinking();

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status, disable timer and launch new
	// config
	if(wrong == 5){
		occupied = false;
		TIMER1_CR &= ~(TIMER_ENABLE);
		leader_new_config();
	}
}


/****************************************************************** Functions */
// Initialization
void leader_init(int gameState) {
	// Desactivate BG1
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Load tiles in RAM
	swiCopy(fullT, (u8*)BG_TILE_RAM_SUB(BG0TILE) + FULL*8*8*4/8, 8*8*4/8/2);
	swiCopy(cornerT, (u8*)BG_TILE_RAM_SUB(BG0TILE) + CORNER*8*8*4/8, 8*8*4/8/2);

	// Set up palette colors
	BG_PALETTE_SUB[0x61] = BLUE;
	BG_PALETTE_SUB[0x62] = GREY;

	BG_PALETTE_SUB[0x71] = RED;
	BG_PALETTE_SUB[0x72] = GREY;

	BG_PALETTE_SUB[0x81] = GREY;
	BG_PALETTE_SUB[0x82] = GREY;

	// Set whole BG0 in grey
	int row, col;

	swiWaitForVBlank();
	for(row = 0; row < H; row++){
		for(col = 0; col < W; col++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W+col] = FULL | (GREYPAL << 12);
		}
	}

	// Activate BG0
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Configure interrupts and timer for block display every 0.4s
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER0_DATA = TIMER_FREQ_1024(5);
	irqSet(IRQ_TIMER0, &leader_timer_ISR0);
	irqEnable(IRQ_TIMER0);
	
	// Configure interrupts and timer for false blinking effect every 0.123s
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &leader_timer_ISR1);
	irqEnable(IRQ_TIMER1);
	
	// Initialize variables
	state = gameState;

	taporder = SAME;
	int i;
	for(i = 0; i < MAXB; i++) order[i] = i;

	score = 0;
	level = VERYEASY;
	nb_blocks = level + 3;
	block = 0;

	draw = 0;
	wrong = 0;

	occupied = false;

	// Draw infos
	info_init(state);

	// Launch first configuration
	leader_new_config();
}

// New configuration
void leader_new_config() {
	// Set status to occupied
	occupied = true;

	// Reset variable
	block = 0;

	// Find in which order the blocks have to be touched
	taporder = rand()%2;

	// Initialize an array with random values
	int i;
	int rand_order[MAXB];

	for(i = 0; i < MAXB; i++) {
		rand_order[i] = rand();
	}
	
	// Set the apparition order of the block by comparing the numbers in the
	// above array
	int position, max, blockid;

	for(position=0; position<nb_blocks; position++){
		// Find biggest number
		max = 0;
		for(i = 0; i < MAXB; i++) {
			if(rand_order[i] >= max){
				max = rand_order[i];
				blockid = i;
			}
		}

		// Assign block to current position in function of biggest number find
		// above and delete the number from array
		order[position] = blockid;
		rand_order[blockid] = -1;
	}

	// Draw new blocks
	leader_draw_blocks();
}

// Draw configuration
void leader_draw_blocks(){
	// Set whole background to grey
	int row, col;

	swiWaitForVBlank();
	for(row = 0; row < W; row++){
		for(col = 0; col < H; col++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W+col] = 0 | (GREYPAL<<12);
		}
	}

	// Reset drawing variable
	draw = 0;

	// Launch timer to draw block sequencially
	TIMER0_CR |= TIMER_ENABLE;
}

// Draw wrong case
void leader_draw_blinking() {
	// Draw or undraw only the blocks that weren't taped yet
	int start, stop;

	if(taporder == SAME){
		start = block;
		stop = nb_blocks;
	}
	else{
		start = 0;
		stop = nb_blocks - block;
	}

	// Undraw if wrong pair, draw if wrong unpair
	int i;
	int x, y;

	swiWaitForVBlank();
	if((wrong%2) == 0) {
		for(i = 0; i < stop; i++){
			x = block_x[order[i]%3];
			y = block_y[order[i]/3];
			leader_draw_block(x, y, GREYPAL);
		}
	}
	else {
		for(i=start; i<stop; i++){
			x = block_x[order[i]%3];
			y = block_y[order[i]/3];
			leader_draw_block(x, y, ((taporder == SAME) ? BLUEPAL : REDPAL));
		}
	}
}

// Draw one block
void leader_draw_block(int x, int y, int palette){
	int row, col;

	// Fill the block
	for(col = x; col < x+SIDE; col++){
		for(row = y; row < y+SIDE; row++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W+col] = FULL | (palette << 12);
		}
	}

	// Change the 4 corners
	BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = CORNER | (palette<<12);
	BG_MAP_RAM_SUB(BG0MAP)[(y+SIDE-1)*W+x] = CORNER | (palette<<12) | (1<<11);
	BG_MAP_RAM_SUB(BG0MAP)[y*W+(x+SIDE-1)] = CORNER | (palette<<12) | (1<<10);
	BG_MAP_RAM_SUB(BG0MAP)[(y+SIDE-1)*W+(x+SIDE-1)] = CORNER | (palette<<12) | (1<<10) | (1<<11);
}

// Main function
bool leader_game(bool player, int gameCounter) {
	// Stop game if START button pressed or time crossed 15 sec
	// Else check if the correct block was touched
	int time;

	time = info_get_time();
	if(state != TRAIN) info_store_temp_score(player, gameCounter, score);

	// Scan the keys and the touch screen only the game is not in block drawing
	// or blinking mode
	if(occupied) return false;
	else{
		scanKeys();
		u16 keys = keysDown();

		if((keys & KEY_START)) return true;
		else if(keys & KEY_TOUCH){
			// Check at which position the touch screen was touched
			touchPosition touch;
			touchRead(&touch);

			// Check at which position we are
			int current;

			if(taporder == SAME) current = block;
			else current = nb_blocks - block - 1;

			// Check if correct position was touched
			int i;
			int xl, yh, xr, yl;

			for(i=0; i<nb_blocks; i++){
				xl = block_x[order[i]%3]*8 - 1;
				yh = block_y[order[i]/3]*8 - 1;
				xr = xl + SIDE*8;
				yl = yh + SIDE*8 ;

				if((touch.px > xl) && (touch.px < xr) && (touch.py > yh) && (touch.py < yl)){
					if(i == current) {
						leader_correct(player);
						break;
					}
					else {
						leader_wrong();
						break;
					}
				}
			}
		}

		// Return false because game not ended
		return false;
	}
}

// Correct answer
void leader_correct(bool player){
	// Erase taped block
	int x, y;
	int current;

	if(taporder == SAME) current = block;
	else current = (nb_blocks-1) - block;

	x = block_x[order[current]%3];
	y = block_y[order[current]/3];
	swiWaitForVBlank();
	leader_draw_block(x, y, GREYPAL);

	// Update player state
	block++;

	// If the current configuration is finished and was correctly found
	if(block == (nb_blocks)) {
		// Update score
		score++;

		// Update displayed score
		info_update_score(score, player);

		// Update level
		level = score/LEADERLEVEL;
		nb_blocks = level + 3;

		// Launch new configuration
		leader_new_config();
	}
}

// Wrong answer
void leader_wrong(){
	// Update status
	occupied = true;

	// Reset wrong variable
	wrong = 0;

	// Launch wrong timer
	TIMER1_CR |= TIMER_ENABLE;

	// Play wrong effect
	mmEffect(SFX_BOING);
}

// Reset game 
void leader_reset() {
	// Suppress displayed infos
	info_finish(score, "leader", state);

	// Desactivate BG0
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Disable timers
	irqDisable(IRQ_TIMER0);
	irqClear(IRQ_TIMER0);
	TIMER0_CR = 0;

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER0_CR = 1;

	// Reset variables
	taporder = SAME;
	int i;
	for(i = 0; i < MAXB; i++) order[i] = i;

	score = 0;
	level = VERYEASY;
	nb_blocks = level + 3;
	block = 0;

	draw = 0;
	wrong = 0;
}