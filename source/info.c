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
#include "info_im.h"

/****************************************************************** Constants */
// Palettes
#define NORMALPAL			6

// Display
#define XSTART1 			4
#define XSTART2				23
#define YSTART 				20
#define NBW					1
#define NBH					2
#define YM 					3
#define NBDIG 				4

// Game names
const char *names[7] = {"leader", "eatit", "musical", "path", "addition", "plusminus", "jankenpon"};

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
	info_update_time();
}


/***************************************************************** Functions */
// Initialization
void info_init(state){
	// Fill with gray
	int x, y;

	for(x = 0; x < W; x++){
		for(y = YSTART; y < H; y++){
			BG_MAP_RAM(BG0MAP)[y*W + x] = info_imMap[32] | (NORMALPAL << 12);
		}
	}

	// Draw score and time titles
	int ystart = 17;
	int h = 3;
	int ym = ((state == TWOP) ? h : 0);

	for(x = 0; x < W; x++){
		for(y = ystart; y < ystart + h; y++){
			BG_MAP_RAM(BG0MAP)[y*W + x] = info_imMap[ym*W + x] | (NORMALPAL << 12);
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

	// Print initial null score and time
	info_update_score(0, 0);
	info_update_time();

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

	swiWaitForVBlank();
	for(i = 0; i < NBDIG; i++){
		xm = dig[i]*NBW;
		ym = YM;
		for(x = XSTART1 + i*NBW; x < XSTART1 + (i+1)*NBW; x++){
			for(y = YSTART; y < YSTART + NBH; y++){
				BG_MAP_RAM(BG0MAP)[y*W + x] = info_imMap[ym*W + xm] | (NORMALPAL << 12);
				ym++;
			}
			ym = YM;
			xm++;
		}
	}
}

void info_update_time(){
	// Compute time digits
	int dig[NBDIG+1];

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
	for(i = 0; i < NBDIG+1; i++){
		xm = dig[i]*NBW;
		ym = YM;
		for(x = XSTART2 + i*NBW; x < XSTART2 + (i+1)*NBW; x++){
			for(y = YSTART; y < YSTART + NBH; y++){
				BG_MAP_RAM(BG0MAP)[y*W + x] = info_imMap[ym*W + xm] | (NORMALPAL << 12);
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

void info_finish(int score, int game, int state){
	// Disable BG0
	REG_DISPCNT &= ~DISPLAY_BG0_ACTIVE;

	// Disable timer
	irqDisable(IRQ_TIMER3);
	irqClear(IRQ_TIMER3);
	TIMER3_CR = 0;

	// Read into file to find if best score beated only if state not TRAIN
	if(state != TRAIN) info_save_score(score, game);
}

void info_save_score(int score, int game){
	FILE* file;
	char name[20] = "/";
	int max_score;
	bool write = false;

	// Open file
	strcat(name, names[game]);
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