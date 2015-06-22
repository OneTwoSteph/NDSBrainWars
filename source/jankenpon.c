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
#include "info.h"
#include "jankenpon.h"

// Image
#include "jankenpon_hand.h"

#define BLUEPAL		6
#define	REDPAL		7


/****************************************************************** Constants */
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

SHAPE shape;
COLOR color;
SHAPE U, M, D;

int score;
int wrong;
LEVEL level;

STATE state;

void jankenpon_wrong(void){
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
	jankenpon_draw();
}

void jankenpon_init(int gameState){
	// Desactivate BG1
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to memory
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

	// Set draw on screen
	shape = rand()%3;
	color = B;
	U = SCISSOR;
	M = PAPER;
	D = ROCK;
	jankenpon_draw();

	// Activate BG0
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	//irqInit();
	irqSet(IRQ_TIMER1, &jankenpon_wrong);
	irqEnable(IRQ_TIMER1);

	// Set global variables
	score = 0;
	wrong = 0;
	level = EASY;
	state = gameState;

	// Draw infos
	info_init(state);
}

void jankenpon_draw(){
	int x, y;
	int length = 22; // of the big hands
	int L = 76;	// length of the whole image
	int height = 8;

	// Draw first background with grey
	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[0] | (BLUEPAL << 12);
		}
	}

	// If we are not in the wrong case, draw figures
	if((wrong%2) == 0){
		for(x = 0; x < W; x++){
			for(y = 0; y < H; y++){
				// Big hand and mini hands
				if(x < length){
					switch(shape){
					case PAPER:
						BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[y*L+x];
						break;
					case ROCK:
						BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[y*L+length+x];
						break;
					case SCISSOR:
						BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[y*L+2*length+x];
						break;
					default:
						break;
					}
				}
				else{
					// First little hand
					if(y<height)
						BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[(U*height + y)*L+3*length+(x-length)];
					else{
						if(y<2*height)
							BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[(M*height + (y-height))*L+3*length+(x-length)];
						else
							BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = jankenpon_handMap[(D*height + (y-2*height))*L+3*length+(x-length)];
					}
				}

				// Color
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = BG_MAP_RAM_SUB(0)[y*32+x] | (((color == B) ? BLUEPAL : REDPAL) << 12);
			}
		}
	}
}

bool jankenpon_game(bool player, int gameCounter){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed or time crossed 15 sec
	int time;
	time = info_get_time();

	if(state != TRAIN) { info_store_temp_score(player, gameCounter, score); }

	if((keys & KEY_START) || (time > GAMETIME)) { return true; }
	else{
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
					if((U+1)%3 == shape) jankenpon_next();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy2 - touch.py,2)) < pow(r,2)){
					if((M+1)%3 == shape) jankenpon_next();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy3 - touch.py,2)) < pow(r,2)){
					if((D+1)%3 == shape) jankenpon_next();
					else jankenpon_wrong();
				}
				break;
			case R:
				if((pow(cx - touch.px, 2) + pow(cy1 - touch.py,2)) < pow(r,2)){
					if(U == (shape+1)%3) jankenpon_next();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy2 - touch.py,2)) < pow(r,2)){
					if(M == (shape+1)%3) jankenpon_next();
					else jankenpon_wrong();
				}

				if((pow(cx - touch.px, 2) + pow(cy3 - touch.py,2)) < pow(r,2)){
					if(D == (shape+1)%3) jankenpon_next();
					else jankenpon_wrong();
				}
				break;
			default: break;
			}
		}
	}

	// Return true for the game to continue
	return false;
}

void jankenpon_next(){
	// Increment score
	score++;

	// Update infos
	info_update_score(score, 0);

	// Check level
	if(score == JANKENPONMEDIUM) level = MEDIUM;
	if(score == JANKENPONHARD) level = HARD;

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

	// Redraw screen
	jankenpon_draw();
}

void jankenpon_reset(){
	// Suppress infos
	info_finish(score, "jankenpon", state);

	// Draw nothing
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Reset all global variables
	score = 0;
	wrong = 0;

	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;
}
