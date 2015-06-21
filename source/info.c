/*
 * info.c
 *
 *  Created on: Jan 23, 2015
 *      Author: Stephanie Amati
 *
 */


/******************************************************************** Modules */
// General
#include "general.h"
#include "info.h"

// Images
#include "score.h"
#include "result.h"

/****************************************************************** Constants */
// Palettes
#define NORMALPAL			6

// Display
#define XSTART1 			4
#define XSTART2 			11
#define XSTART3				23
#define YSTART 				20
#define NBW					1
#define NBH					2
#define YM 					6
#define NBDIG 				4


/*********************************************************** Global variables */
STATE gameState;

int sec, min;

int score_p1[3];
int score_p2[3];

int counter;


/***************************************************************** Timer ISRs */
void info_time_ISR3(){
	// Update sec
	sec++;

	// Check for minutes
	if(sec>59){
		sec = 0;
		min++;
	}

	// Draw
	info_draw_time();
}


/***************************************************************** Functions */
// Initialization
void info_init(state){
	// Copy image in BG0 of MAIN screen
	swiCopy(scoreTiles, BG_TILE_RAM(BG0TILE), scoreTilesLen/2);

	// Put correct colors in palette
	BG_PALETTE[0x61] = RED;
	BG_PALETTE[0x62] = BLUE;
	BG_PALETTE[0x63] = GREEN;
	BG_PALETTE[0x64] = GREY;
	BG_PALETTE[0x65] = BLACKGREY;
	BG_PALETTE[0x66] = BLACK;

	// Fill with gray
	int x, y;

	for(x = 0; x < W; x++){
		for(y = YSTART; y < H; y++){
			BG_MAP_RAM(BG0MAP)[y*W + x] = scoreMap[32] | (NORMALPAL << 12);
		}
	}

	// Draw score and time titles
	int ystart = 17;
	int h = 3;
	int ym = ((state == TWOP) ? h : 0);

	for(x = 0; x < W; x++){
		for(y = ystart; y < ystart + h; y++){
			BG_MAP_RAM(BG0MAP)[y*W + x] = scoreMap[ym*W + x] | (NORMALPAL << 12);
			ym++;
		}
		ym = ((state == TWOP) ? h : 0);
	}

	// Initialize variables
	gameState = state;

	sec = 0;
	min = 0;

	counter = 0;

	// Initialize the timer
	TIMER3_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	TIMER3_DATA = TIMER_FREQ_1024(1);

	irqSet(IRQ_TIMER3, &info_time_ISR3);
	irqEnable(IRQ_TIMER3);

	// Activate BG0
	REG_DISPCNT |= DISPLAY_BG0_ACTIVE;

	// Update game counter if two player mode
	if(gameState == TWOP) counter++;
}

void info_update_score(int score, int player){
	// Update score
	if(player == 1) score_p2[0] = score;
	else score_p1[0] = score;

	// Compute score's digits
	int dig[NBDIG];

	dig[0] = score/1000;
	dig[1] = (score-1000*dig[0])/100;
	dig[2] = (score-1000*dig[0]-100*dig[1])/10;
	dig[3] = (score-1000*dig[0]-100*dig[1]-10*dig[2]);

	// Draw scores
	int i;
	int x, y;
	int xm, ym;
	int xstart = ((player == 1) ? XSTART2 : XSTART1);

	swiWaitForVBlank();
	for(i = 0; i < NBDIG; i++){
		xm = dig[i]*NBW;
		ym = YM;
		for(x = xstart + i*NBW; x < xstart + (i+1)*NBW; x++){
			for(y = YSTART; y < YSTART + NBH; y++){
				BG_MAP_RAM(BG0MAP)[y*W + x] = scoreMap[ym*W + xm] | (NORMALPAL << 12);
				ym++;
			}
			ym = YM;
			xm++;
		}
	}
}

void info_draw_time(){
	// Compute time digits
	int dig[NBDIG];

	dig[0] = min/10;
	dig[1] = min-10*dig[0];
	dig[2] = 10;
	dig[3] = sec/10;
	dig[4] = sec-10*dig[3];

	// Draw time
	int i;
	int x, y;
	int xm, ym;

	swiWaitForVBlank();	
	for(i = 0; i <= NBDIG; i++){
		xm = dig[i]*NBW;
		ym = YM;
		for(x = XSTART3 + i*NBW; x < XSTART3 + (i+1)*NBW; x++){
			for(y = YSTART; y < YSTART + NBH; y++){
				BG_MAP_RAM(BG0MAP)[y*W + x] = scoreMap[ym*W + xm] | (NORMALPAL << 12);
				ym++;
			}
			ym = YM;
			xm++;
		}
	}
}

int info_get_time(){
	return 60*min+sec;
}

void info_finish(int score, char* game, int state){
	// Put transparent tiles on BGO of sub since no score has to be shown for now
	int x, y;
	for(x=0;x<32;x++){
		for(y=0;y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = 0;
		}
	}

	// Disable timer
	irqDisable(IRQ_TIMER2);
	irqClear(IRQ_TIMER2);
	TIMER2_CR = 0;

	// Read into file to find if best score beated only if state not TRAIN
	if(state!=TRAIN) info_save_score(score, game);
}

void info_save_score(int score, char* game){
	FILE* file;
	char name[20] = "/";
	int max_score;
	bool write = false;

	// Open file
	strcat(name, game);
	strcat(name, ".txt");
	file = fopen(name, "r");

	// Read score and check if new score better or not to write new one
	if(file==NULL) write = true;
	else{
		fscanf(file,"%i\n",&max_score);

		if(score > max_score) write = true;
	}

	if(write){
		fclose(file);
		file = fopen(name, "w");
		fprintf(file,"%i\n", score);
		fclose(file);
	}
	else fclose(file);
}

int info_get_score(char* game){
	FILE* file;
	char name[20] = "/";
	int score;

	// Open correct file corresponding to the
	strcat(name, game);
	strcat(name, ".txt");
	file = fopen(name, "r");

	// Read score or put 0 if no file exists
	if(file==NULL) score = 0;
	else fscanf(file,"%i\n",&score);

	// Close file
	fclose(file);

	// Return score
	return score;
}

void info_store_temp_score(bool player, int counter, int score){

	if(player)	{ score_p2[counter-1] = score; }
	else 		{ score_p1[counter-1] = score; }

}

void info_draw_final_score(STATE state){
	int x,y,j;

	int digits[4];
	u16 keys;

	int final_p1 = 0;
	int final_p2 = 0;

	switch(state){

	case ONEP:
		final_p1 = score_p1[2];

		digits[0] = final_p1/1000;
		digits[1] = (final_p1-1000*digits[0])/100;
		digits[2] = (final_p1-1000*digits[0]-100*digits[1])/10;
		digits[3] = (final_p1-1000*digits[0]-100*digits[1]-10*digits[2]);

		// Copy image to memory
		swiCopy(resultTiles, BG_TILE_RAM_SUB(1), resultTilesLen/2);
		swiCopy(resultPal, BG_PALETTE_SUB, resultPalLen/2);

		// Draw Initial Field
		for(x=0; x<32; x++){
			for(y=0; y<24; y++){
				BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[1];
			}
		}

		for(x=0; x<32; x++){
			for(y=5; y<10; y++){
				BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[y*32+x];
			}
		}

		for(j=0;j<4;j++){
			for(x=18; x<20; x++){
				for(y=5; y<10; y++){
					BG_MAP_RAM_SUB(0)[y*32+(x+2*j)] = resultMap[(y-5+15)*32 + (x-18)+2*digits[j]];
				}
			}
		}
		scanKeys();
		keys = keysDown();

		while(!(keys & KEY_START)){
			scanKeys();
			keys = keysDown();
		}

		break;
	case TWOP:

		for(x=0; x<3; x++){
			final_p1 = final_p1 + score_p1[x];
			final_p2 = final_p2 + score_p2[x];
		}

		digits[0] = final_p1/1000;
		digits[1] = (final_p1-1000*digits[0])/100;
		digits[2] = (final_p1-1000*digits[0]-100*digits[1])/10;
		digits[3] = (final_p1-1000*digits[0]-100*digits[1]-10*digits[2]);

		// Copy image to memory
		swiCopy(resultTiles, BG_TILE_RAM_SUB(1), resultTilesLen/2);
		swiCopy(resultPal, BG_PALETTE_SUB, resultPalLen/2);
		swiCopy(resultPal, &BG_PALETTE_SUB[16], resultPalLen/2);
		swiCopy(resultPal, &BG_PALETTE_SUB[32], resultPalLen/2);

		BG_PALETTE_SUB[0x18] = BLUE;
		BG_PALETTE_SUB[0x28] = RED;

		// Draw Initial Field
		int l = 5;

		for(x=0; x<32; x++){
			for(y=0; y<24; y++){
				BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[1];
			}
		}

		for(x=0; x<32; x++){
			for(y=0; y<5; y++){
				BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[y*32+x];
			}
			for(y=10+l; y<15+l; y++){
				BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[(y-l)*32+x];
			}
		}

		for(j=0;j<4;j++){
			for(x=6; x<8; x++){
				for(y=5; y<10; y++){
					BG_MAP_RAM_SUB(0)[y*32+(x+2*j)] = resultMap[(y-5+15)*32 + (x-6)+2*digits[j]] | (1 << 12);
				}
			}
		}

		digits[0] = final_p2/1000;
		digits[1] = (final_p2-1000*digits[0])/100;
		digits[2] = (final_p2-1000*digits[0]-100*digits[1])/10;
		digits[3] = (final_p2-1000*digits[0]-100*digits[1]-10*digits[2]);


		for(j=0;j<4;j++){
			for(x=18; x<20; x++){
				for(y=5; y<10; y++){
					BG_MAP_RAM_SUB(0)[y*32+(x+2*j)] = resultMap[(y-5+15)*32 + (x-18)+2*digits[j]] | (2 << 12);
				}
			}
		}


		if(final_p1 > final_p2){
			for(x=15;x<17;x++){
				for(y=10+l; y<15+l; y++){
					BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[(y-10+15-l)*32 + (x-15)+2] | (1 << 12);
				}
			}
		}
		else if (final_p1 < final_p2){
			for(x=15;x<17;x++){
				for(y=10+l; y<15+l; y++){
					BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[(y-10+15-l)*32 + (x-15)+4] | (2 << 12);
				}
			}
		}
		else	{
			for(x=0; x<32; x++){
				for(y=10+l; y<15+l; y++){
					BG_MAP_RAM_SUB(0)[y*32+x] = resultMap[1];
				}
			}
		}



		scanKeys();
		keys = keysDown();

		while(!(keys & KEY_START)){
			scanKeys();
			keys = keysDown();
		}

		break;
	default:
		break;
	}

	counter = 0;
}
