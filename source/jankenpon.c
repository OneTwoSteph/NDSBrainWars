/*
 * jankenpon.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati
 */

#include "general.h"
#include "jankenpon.h"
#include "jankenpon_hand.h"

SHAPE shape;
COLOR color;
SHAPE U, M, D;

int score;
int wrong;
LEVEL level;

void jankenpon_init(){
	// Copy tiles to memory
	swiCopy(jankenpon_handTiles, BG_TILE_RAM_SUB(1), jankenpon_handTilesLen/2);

	// Copy palette
	swiCopy(jankenpon_handPal, BG_PALETTE_SUB, jankenpon_handPalLen/2);
	swiCopy(jankenpon_handPal, &BG_PALETTE_SUB[16], jankenpon_handPalLen);
	swiCopy(jankenpon_handPal, &BG_PALETTE_SUB[16*2], jankenpon_handPalLen);
	swiCopy(jankenpon_handPal, &BG_PALETTE_SUB[16*3], jankenpon_handPalLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[2] = BLUEVAL;
	BG_PALETTE_SUB[3] = GREYVAL;
	BG_PALETTE_SUB[4] = BLACKVAL;

	BG_PALETTE_SUB[17] = WHITEVAL;
	BG_PALETTE_SUB[18] = REDVAL;
	BG_PALETTE_SUB[19] = GREYVAL;
	BG_PALETTE_SUB[20] = BLACKVAL;

	BG_PALETTE_SUB[65] = GREYVAL;
	BG_PALETTE_SUB[66] = GREYVAL;
	BG_PALETTE_SUB[67] = GREYVAL;
	BG_PALETTE_SUB[68] = GREYVAL;

	// Set draw on screen
	shape = rand()%3;
	color = BLUE;
	U = SCISSOR;
	M = PAPER;
	D = ROCK;
	jankenpon_draw(shape, color, U, M, D);

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
}

void jankenpon_draw(shape, color, U, M, D){
	int x, y;
	int length = 22; // of the big hands
	int W = 76;	// of the whole image containing the 3 big and small hands
	int height = 8;

	// Draw
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			// Big hand and mini hands
			if(x<length){
				switch(shape){
				case PAPER:
					BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[y*W+x];
					break;
				case ROCK:
					BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[y*W+length+x];
					break;
				case SCISSOR:
					BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[y*W+2*length+x];
					break;
				default:
					break;
				}
			}
			else{
				// First little hand
				if(y<height)
					BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[(U*height + y)*W+3*length+(x-length)];
				else{
					if(y<2*height)
						BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[(M*height + (y-height))*W+3*length+(x-length)];
					else
						BG_MAP_RAM_SUB(0)[y*32+x] = jankenpon_handMap[(D*height + (y-2*height))*W+3*length+(x-length)];
				}
			}

			// Color
			BG_MAP_RAM_SUB(0)[y*32+x] = BG_MAP_RAM_SUB(0)[y*32+x]|(color<<12);
		}
	}
}

bool jankenpon_game(void){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed
	if(keys & KEY_START) return false;
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
			case BLUE:
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
			case RED:
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
			case GREEN: break;
			case YELLOW: break;
			default: break;
			}
		}

		// Return true for the game to continue
		return true;
	}
}

void jankenpon_next(void){
	// Increment score
	score++;

	// Check level
	if(score == PATHMEDIUM) level = MEDIUM;
	if(score == PATHHARD) level = HARD;

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
	jankenpon_draw(shape, color, U, M, D);
}
void jankenpon_wrong(void){
	// Check what to do in function of wrong variable
	switch(wrong){
		case 0:
			TIMER1_CR |= TIMER_ENABLE;
			jankenpon_draw(shape, GREY, U, M, D);
			wrong++;
			break;
		case 1:
			jankenpon_draw(shape, color, U, M, D);
			wrong++;
			break;
		case 2:
			jankenpon_draw(shape, GREY, U, M, D);
			wrong++;
			break;
		case 3:
			TIMER1_CR &= ~(TIMER_ENABLE);
			jankenpon_draw(shape, color, U, M, D);
			wrong=0;
			break;
		default:
			break;
	}
}

void jankenpon_reset(){
	// Draw nothing
	jankenpon_draw(shape, GREY, U, M, D);
}
