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
#include "leader.h"


/****************************************************************** Constants */
// Palettes
#define BLUEPAL			6
#define REDPAL			7
#define GREYPAL			8

// Tiles
#define FULL			0
#define	CORNER			1

// Image/tile infos
#define SIDE 		   	6							// block side in tiles
#define MAXB 		   	9  							// max nb of blocks
const int block_x[3] = {6, 13, 20};					// x positions of blocks
const int block_y[3] = {2, 9, 16};					// y positions of blocks

// Game constants
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
TAPORDER taporder;			// order in which the blocks have to be taped
int order[MAXB];			// order of the blocks

// Game state
int score;			
LEVEL level;		
int nb_blocks;				// number of blocks to draw (depends on level)
int block;					// gives the next block the player has to touch

// Timer variables
int draw;					// block drawing counter for timer
int wrong;					// wrong blinking counter for timer

// Drawing status
bool occupied;	


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
void leader_init() {
	// Deactivate BG1 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Load tiles in BG0 SUB and put correct colors in palette
	swiCopy(fullT, (u8*)BG_TILE_RAM_SUB(BG0TILE) + FULL*8*8*4/8, 8*8*4/8/2);
	swiCopy(cornerT, (u8*)BG_TILE_RAM_SUB(BG0TILE) + CORNER*8*8*4/8, 8*8*4/8/2);

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

	// Activate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Timer 0 for block drawing
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER0_DATA = TIMER_FREQ_1024(5);
	irqSet(IRQ_TIMER0, &leader_timer_ISR0);
	irqEnable(IRQ_TIMER0);
	
	// Timer 1 for wrong blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &leader_timer_ISR1);
	irqEnable(IRQ_TIMER1);
	
	// Initialize variables
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
	// Fill the block
	int row, col;

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
int leader_game() {
	// Scan the keys and the touch screen only the game is not in block drawing
	// or blinking mode
	if(!occupied){
		u16 keys = keysDown();

		if(keys & KEY_TOUCH){
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
						leader_correct();
						break;
					}
					else {
						leader_wrong();
						break;
					}
				}
			}
		}
	}

	// Return score
	return score;
}

// Correct function
void leader_correct(){
	// Play sound
	mmEffect(SFX_BON);

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

		// Update level
		level = score/LEADERLEVEL;
		nb_blocks = level + 3;

		// Launch new configuration
		leader_new_config();
	}
}

// Wrong function
void leader_wrong(){
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
void leader_reset() {
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

	occupied = false;
}