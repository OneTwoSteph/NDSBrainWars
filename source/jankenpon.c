/*
 * jankenpon.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati
 *
 */


/******************************************************************** Modules */
 // General
#include "general.h"
#include "jankenpon.h"

// Image
#include "jankenpon_hand.h"


/****************************************************************** Constants */
// Palettes
#define BLUEPAL		6
#define	REDPAL		7
#define	GREYPAL		8

// Game constants
typedef enum SHAPE SHAPE;
enum SHAPE
{
    SCISSOR = 0,
    PAPER = 1,
    ROCK = 2
};

typedef enum ORDER ORDER;
enum ORDER
{
    SPR = 0,
    RSP = 1,
    PRS = 2,
    PSR = 3,
    RPS = 4,
    SRP = 5,
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
SHAPE shape;
COLOR color;
SHAPE U, M, D;

// Game state
int score;
LEVEL level;

// Timer variable
int wrong;

// Drawing status
bool occupied;


/***************************************************************** Timer ISRs */
// Wrong blinking ISR
void jankenpon_timer_ISR1(){
	// Draw for blinking effect
	jankenpon_draw(((wrong%2) == 0) ? GREYPAL : color + 6);

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
void jankenpon_init(){
	// Deactivate BG1 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to BG0 and put colors in palette
	swiCopy(jankenpon_handTiles, BG_TILE_RAM_SUB(BG0TILE), jankenpon_handTilesLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[0x61] = BLUE;
	BG_PALETTE_SUB[0x62] = WHITE;
	BG_PALETTE_SUB[0x63] = GREY;
	BG_PALETTE_SUB[0x64] = BLACK;

	BG_PALETTE_SUB[0x71] = RED;
	BG_PALETTE_SUB[0x72] = WHITE;
	BG_PALETTE_SUB[0x73] = GREY;
	BG_PALETTE_SUB[0x74] = BLACK;

	BG_PALETTE_SUB[0x81] = GREY;
	BG_PALETTE_SUB[0x82] = GREY;
	BG_PALETTE_SUB[0x83] = GREY;
	BG_PALETTE_SUB[0x84] = GREY;

	// Put whole screen in grey 
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W + x] = jankenpon_handMap[0] | (GREYPAL << 12);
		}
	}

	// Initialize global variables
	shape = SCISSOR;
	color = B;
	U = SCISSOR;
	M = PAPER;
	D = ROCK;

	score = 0;
	level = EASY;

	wrong = 0;
	
	occupied = false;

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &jankenpon_timer_ISR1);
	irqEnable(IRQ_TIMER1);

	// Launch first configuration
	jankenpon_next();	
	
	// Activate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;
}

// Find next configuration
void jankenpon_next(){
	// Random numbers for direction and color
	int nb1, nb2, nb3;

	while((nb1 = rand()%3) == shape);

	if((level == MEDIUM) || (level == HARD)) nb2 = rand()%2;
	else nb2 = 0;

	if(level == HARD) nb3 = rand()%6;
	else nb3 = 0;

	shape = nb1;
	color = nb2;

	switch(nb3){
	case SPR:
		U = SCISSOR; M = PAPER; D = ROCK;
		break;
	case RSP:
		U = ROCK; M = SCISSOR; D = PAPER;
		break;
	case PRS:
		U = PAPER; M = ROCK; D = SCISSOR;
		break;
	case PSR:
		U = PAPER; M = SCISSOR; D = ROCK;
		break;
	case RPS:
		U = ROCK; M = PAPER; D = SCISSOR;
		break;
	case SRP:
		U = ROCK; M = PAPER; D = SCISSOR;
		break;
	}

	// Draw hands
	jankenpon_draw(color + 6);
}


// Draw hands
void jankenpon_draw(int pal){
	// Draw big hand and small hands
	int x, y;
	int length = 22; 			// of the big hands
	int L = 76;					// length of the whole image
	int height = 8;	

	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			// Big hand and mini hands
			if(x < length){
				switch(shape){
				case PAPER:
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[y*L+x] | (pal << 12);
					break;
				case ROCK:
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[y*L+length+x] | (pal << 12);
					break;
				case SCISSOR:
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[y*L+2*length+x] | (pal << 12);
					break;
				default:
					break;
				}
			}
			else if(y < height)
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[(U*height + y)*L+3*length+(x-length)] | (BLUEPAL << 12);
			else if(y < 2*height)
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[(M*height + (y-height))*L+3*length+(x-length)] | (BLUEPAL << 12);
			else
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[(D*height + (y-2*height))*L+3*length+(x-length)] | (BLUEPAL << 12);
		}
	}
}

// Main function
int jankenpon_game(){
	// Scan keys only if game not occupied by wrong
	if(!occupied){
		// Scan
		u16 keys = (u16) keysDown();

		// If touchscreen was touched, check if correct
		if(keys & KEY_TOUCH){
			// Find position touched on touchscreen
			touchPosition touch;
			touchRead(&touch);

			// Define circle center and radius in pixels
			// 1, 2 ,3 corresponds to scissor, paper, rock (like on the image)
			double r = 25;
			double cx = 208;
			double cy1 = 34;
			double cy2 = 98;
			double cy3 = 162;

			// Check if touched correct symbol
			switch(color){
			case B:
				if((pow(cx - touch.px, 2) + pow(cy1 - touch.py,2)) < pow(r,2)){
					if((U+1)%3 == shape) jankenpon_correct();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy2 - touch.py,2)) < pow(r,2)){
					if((M+1)%3 == shape) jankenpon_correct();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy3 - touch.py,2)) < pow(r,2)){
					if((D+1)%3 == shape) jankenpon_correct();
					else jankenpon_wrong();
				}
				break;
			case R:
				if((pow(cx - touch.px, 2) + pow(cy1 - touch.py,2)) < pow(r,2)){
					if(U == (shape+1)%3) jankenpon_correct();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy2 - touch.py,2)) < pow(r,2)){
					if(M == (shape+1)%3) jankenpon_correct();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy3 - touch.py,2)) < pow(r,2)){
					if(D == (shape+1)%3) jankenpon_correct();
					else jankenpon_wrong();
				}
				break;
			default: break;
			}
		}
	}

	// Return score
	return score;
}

// Correct function
void jankenpon_correct(){
	// Play sound
	mmEffect(SFX_BON);

	// Increment score
	score++;

	// Check level
	if(score == JANKENPONMEDIUM) level = MEDIUM;
	if(score == JANKENPONHARD) level = HARD;

	// Launch next configuration
	jankenpon_next();
}

// Wrong function
void jankenpon_wrong(){
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
void jankenpon_reset(){
	// Deactivate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Reset timer 1
	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	shape = SCISSOR;
	color = B;
	U = SCISSOR;
	M = PAPER;
	D = ROCK;

	score = 0;
	level = EASY;

	wrong = 0;
	
	occupied = false;
}