/*
 * addition.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS modified by Stephanie Amati
 *
 */


/******************************************************************** Modules */
 // General
#include "general.h"
#include "addition.h"

 // Image
#include "addition_im.h"


/****************************************************************** Constants */
// Palettes
#define NORMALPAL		6
#define GREYPAL			7

// Numbers
#define	MINNB			3
#define MAXNB			24

// Drawing infos
#define XSTART 			3
#define YSTART 			2
#define SIDE			5
#define WIM				50
#define POSX1			19
#define POSX2			22
#define POSY			4
#define HNB				11
#define WNB				5

#define XSTARTP			24
#define YSTARTP			20
#define SIDEP			32
#define INTP 			8


/*********************************************************** Global variables */
// Game infos
int number;

// Game variables
int counter;
int numbers[3];

int score;
int touchedNb;

// Timer variables
int draw;
int wrong;

// Drawing tatus
bool occupied;


/***************************************************************** Timer ISRs */
// New number draw ISR
void addition_timer_ISR0(){	
	// Check if time to draw blocks and number
	if(draw == 1){
		TIMER0_CR &= ~(TIMER_ENABLE);
		swiWaitForVBlank();
		addition_draw_blocks();
		addition_draw_number(NORMALPAL);
		occupied = false;
	}

	// Increment counter
	draw++;
}

// Wrong blinking ISR
void addition_timer_ISR1(){
	// Draw for blinking effect
	addition_draw_number(((wrong%2) == 0) ? GREYPAL : NORMALPAL);

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status, disable timer and launch new
	// config
	if(wrong == 6){
		occupied = false;
		TIMER1_CR &= ~(TIMER_ENABLE);
		addition_next();
	}
}


/****************************************************************** Functions */
// Initialization
void addition_init() {
	// Desactivate BG1
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to BG0 SUB and put colors in palettes
	swiCopy(addition_imTiles, BG_TILE_RAM_SUB(BG0TILE), addition_imTilesLen/2);

	BG_PALETTE_SUB[0x61] = BLUE;
	BG_PALETTE_SUB[0x62] = YELLOW;
	BG_PALETTE_SUB[0x63] = WHITE;
	BG_PALETTE_SUB[0x64] = GREY;

	BG_PALETTE_SUB[0x71] = GREY;
	BG_PALETTE_SUB[0x72] = GREY;
	BG_PALETTE_SUB[0x73] = GREY;
	BG_PALETTE_SUB[0x74] = GREY;

	// Set whole BG0 in grey
	int row, col;

	for(row = 0; row < H; row++){
		for(col = 0; col < W; col++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W+col] = addition_imMap[0] | (NORMALPAL << 12);
		}
	}

	// Configure timer 0 for drawing
	TIMER0_DATA = TIMER_FREQ_1024(4);
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	irqSet(IRQ_TIMER0, &addition_timer_ISR0);
	irqEnable(IRQ_TIMER0);

	// Configure timer 1 for wrong blinking
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &addition_timer_ISR1);
	irqEnable(IRQ_TIMER1);

	// Initialize global variables
	number = MINNB;

	counter = 0;
	int i;
	for(i = 0; i < 3; i++) numbers[i] = 0;

	score = 0;
	touchedNb = 0;

	draw = 0;
	wrong = 0;

	occupied = false;

	// Activate BG0
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Launch first number
	addition_next();
}

// New number
void addition_next() {
	// Save previous number
	int prevNumber = number;

	// Find new number
	while((number = (rand()%(MAXNB-MINNB+1) + MINNB)) == prevNumber);

	// Change status
	occupied = true;

	// Reset counter
	counter = 0;

	// Reset drawing
	draw = 0;

	// Start timer to draw new number
	TIMER0_CR |= TIMER_ENABLE;
}

// Draw blocks
void addition_draw_blocks() {
	// Draw all numbers
	int x, y;

	for(x = 0; x < XSTART + 3*SIDE; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W + x] = addition_imMap[y*WIM + x] | (NORMALPAL << 12);
		}
	}
}

// Draw one block
void addition_draw_block(int palette){
	// Draw tone with palette
	int x, y;
	int block = touchedNb-1;
	int x1, x2, y1, y2;

	swiWaitForVBlank();
	if(block != -1){
		x1 = XSTART + (block%3)*SIDE;
		x2 = XSTART + (block%3 + 1)*SIDE;
		y1 = YSTART + (block/3)*SIDE;
		y2 = YSTART + (block/3 + 1)*SIDE;
	}
	else{
		x1 = XSTART + 1*SIDE;
		x2 = XSTART + 2*SIDE;
		y1 = YSTART + 3*SIDE;
		y2 = YSTART + 4*SIDE;
	}

	for(x = x1; x < x2; x++){
		for(y = y1; y < y2; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W + x] = (BG_MAP_RAM_SUB(BG0MAP)[y*W + x] & (0x0fff)) | (palette << 12);
		}
	}
}

// Draw number
void addition_draw_number(int pal){
	// Find digits
	int dig[2];

	dig[0] = number/10;
	dig[1] = number%10;

	// Check if we are in double digit case or unique digit case and draw
	// number
	if(dig[0] > 0){
		// First digit
		addition_draw_digit(POSX1, dig[0], pal);

		// Second digit
		addition_draw_digit(POSX1 + WNB, dig[1], pal);
	}
	else {
		addition_draw_digit(POSX1, 0, GREYPAL);
		addition_draw_digit(POSX1 + WNB, 0, GREYPAL);
		addition_draw_digit(POSX2, dig[1], pal);
	}
	
}

// Draw digits of the number
void addition_draw_digit(int xstart, int digit, int pal){
	int row, col;
	int x = 0;
	int y = H;

	for(col = xstart; col < xstart + WNB; col++){
		for(row = POSY; row < POSY + HNB; row++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W+col] = addition_imMap[y*WIM + digit*WNB + x] | (pal<<12);
			y++;
		}
		y = H;
		x++;
	}
}

// Man function
int addition_game() {
	// Scan keys only if game not occupied
	if(!occupied){
		u16 keys = (u16) keysDown();

		if(keys & KEY_TOUCH) {
			// Check what number was touched
			touchPosition touch;
			touchRead(&touch);

			int nb = -1;
			int i, j;

			for(i = 0; i < 3; i++){
				for(j = 0; j < 3; j++){
					if((touch.px >= (XSTARTP + i*(SIDEP + INTP))) &&
					   (touch.px < (XSTARTP + i*(SIDEP + INTP) + SIDEP)) &&
					   (touch.py >= (YSTARTP + j*(SIDEP + INTP))) &&
					   (touch.py < (YSTARTP + j*(SIDEP + INTP) + SIDEP))){
					   	nb = (i+1) + 3*j;
						break;
					} 
				}
			}

			if(nb == -1){
				if((touch.px >= (XSTARTP + 1*(SIDEP + INTP))) &&
				   (touch.px < (XSTARTP + 1*(SIDEP + INTP) + SIDEP)) &&
				   (touch.py >= (YSTARTP + 3*(SIDEP + INTP))) &&
				   (touch.py < (YSTARTP + 3*(SIDEP + INTP) + SIDEP))) nb = 0;
			}

			// Check if previous touched number was touched
			if(nb != -1){
				// Check if number already touched and go out if yes, 
				// otherwise continue
				int i;
				for(i = 0; i < counter; i++){
					if(nb == numbers[i]) nb = -1;
				}
			}

			// Check if touched number ok
			if(nb != -1){
				// Save touched number
				touchedNb = nb;

				// Add new number to list
				numbers[counter] = nb;

				// Compute sum
				int sum = 0;
				for(i = 0; i <= counter; i++){
					sum += numbers[i];
				}

				// Check if sum above number or equal to it if last touch
				if(((counter == 2) && (sum == number)) || 
				   ((counter < 2) && (sum <= number))) addition_correct();
				else addition_wrong();	
			}
		}
	}

	// Return score
	return score;
}

// Correct function
void addition_correct() {
	// Play music
	mmEffect(SFX_BON);

	// Make number pressed disappear
	addition_draw_block(GREYPAL);

	// Increment counter
	counter++;

	// Check if last number to tap
	if(counter >= 3){
		// Increment score
		score++;

		// Launch next number
		addition_next();
	}
}

// Wrong function
void addition_wrong() {
	// Play wrong effect
	mmEffect(SFX_NUL);

	// Make number pressed disappear
	addition_draw_block(GREYPAL);

	// Update status
	occupied = true;

	// Reset wrong counter
	wrong = 0;

	// Launch timer
	TIMER1_CR |= TIMER_ENABLE;
}

// Reset function
void addition_reset() {
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
	TIMER1_CR = 0;
	
	// Reset global variables
	number = MINNB;

	counter = 0;
	int i;
	for(i = 0; i < 3; i++) numbers[i] = 0;

	score = 0;
	touchedNb = 0;

	draw = 0;
	wrong = 0;

	occupied = false;
}
