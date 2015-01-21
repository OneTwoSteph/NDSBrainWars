/*
 * eatit.c
 *
 *  Created on: Jan 21, 2015
 *      Author: Stephanie Amati
 *
 */

#include "general.h"
#include "eatit.h"
#include "eatit_pacman.h"

ROW row;
FOOD up[4];
FOOD down[4];

int score;
int wrong;

void eatit_init(){
	// Configure Background
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory
	swiCopy(eatit_pacmanTiles, BG_TILE_RAM_SUB(1), eatit_pacmanTilesLen/2);

	// Copy palette
	swiCopy(eatit_pacmanPal, BG_PALETTE_SUB, eatit_pacmanPalLen/2);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[3] = REDVAL;
	BG_PALETTE_SUB[4] = BLACKVAL;
	BG_PALETTE_SUB[5] = GREENVAL;
	BG_PALETTE_SUB[6] = BLUEVAL;
	BG_PALETTE_SUB[7] = GREYVAL;

	// Set draw on screen
	up[0] = EMPTY;
	up[1] = CHERRY;
	up[2] = CHERRY;
	up[3] = MONSTER;

	down[0] = EMPTY;
	down[1] = CHERRY;
	down[2] = CHERRY;
	down[3] = MONSTER;

	row = FIRST;

	eatit_draw();

	// Configure interrupts and timer for false blinking effect
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);

	//irqSet(IRQ_TIMER1, &eatit_wrong);
	//irqEnable(IRQ_TIMER1);

	// Set global variables
	score = 0;
	wrong = 0;
}

void eatit_draw(){
	int x, y;

	int lPac = 8; 			// length of pacman
	int lFood = 6; 			// length of food
	int height = 12; 		// height of one raw

	int L = 34;				// length of the whole image

	// Draw on screen
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			// Up and down
			if(y<height){
				// 0, 1, 2, 3 position (0 = left)
				if(x<lFood)
					BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+x+up[0]*lFood];
				else{
					if(x<2*lFood)
						BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-lFood)+up[1]*lFood];
					else{
						if(x<3*lFood)
							BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-2*lFood)+up[2]*lFood];
						else{
							if(x<4*lFood)
								BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-3*lFood)+up[3]*lFood];
							else
								BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[y*L+(x-4*lFood)+3*lFood+row*lPac];
						}

					}
				}

			}
			else{
				if(x<lFood)
					BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+x+down[0]*lFood];
				else{
					if(x<2*lFood)
						BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-lFood)+down[1]*lFood];
					else{
						if(x<3*lFood)
							BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-2*lFood)+down[2]*lFood];
						else{
							if(x<4*lFood)
								BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-3*lFood)+down[3]*lFood];
							else
								BG_MAP_RAM_SUB(0)[y*32+x] = eatit_pacmanMap[(y-height)*L+(x-4*lFood)+3*lFood+(row+1)%2*lPac];
						}
					}
				}
			}
		}
	}
}

/*
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
*/
