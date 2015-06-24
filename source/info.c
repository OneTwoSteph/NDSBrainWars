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
#define REDPAL				7

// Display
#define XSTART1 			4
#define XSTART2				23
#define YSTART 				20
#define NBW					1
#define NBH					2
#define YM 					3
#define NBDIG 				4

// Game names
const char* names[7] = {"leader", "eatit", "musical", "path", "addition",
					    "plusminus", "jankenpon"};

/*********************************************************** Global variables */
// Time variables
int sec, min;

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
void info_init(){
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

	for(x = 0; x < W; x++){
		for(y = ystart; y < ystart + h; y++){
			BG_MAP_RAM(BG0MAP)[y*W + x] = info_imMap[(y-ystart)*W + x] | (NORMALPAL << 12);
		}
	}

	// Initialize variables
	sec = 0;
	min = 0;

	// Initialize the timer
	TIMER3_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	TIMER3_DATA = TIMER_FREQ_1024(1);
	irqSet(IRQ_TIMER3, &info_time_ISR3);
	irqEnable(IRQ_TIMER3);

	// Print initial null score and time
	info_update_score(0);
	info_update_time();

	// Activate BG0
	swiWaitForVBlank();
	REG_DISPCNT |= DISPLAY_BG0_ACTIVE;
}

// Update score display
void info_update_score(int score){
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

// Update time display
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
	int pal = ((60*min+sec) == 20) ? REDPAL : NORMALPAL;

	swiWaitForVBlank();	
	for(i = 0; i < NBDIG+1; i++){
		xm = dig[i]*NBW;
		ym = YM;
		for(x = XSTART2 + i*NBW; x < XSTART2 + (i+1)*NBW; x++){
			for(y = YSTART; y < YSTART + NBH; y++){
				BG_MAP_RAM(BG0MAP)[y*W + x] = info_imMap[ym*W + xm] | (pal << 12);
				ym++;
			}
			ym = YM;
			xm++;
		}
	}
}

// Return current time
int info_get_time(){
	return 60*min + sec;
}

void info_stop_time(){
	TIMER3_CR &= ~(TIMER_ENABLE);
	min = 60;
	sec = 60;
}

// Finish score and time displaying
void info_finish(int score, int game){
	// Disable BG0
	swiWaitForVBlank();
	REG_DISPCNT &= ~DISPLAY_BG0_ACTIVE;

	// Disable timer
	// Disable timer
	irqDisable(IRQ_TIMER3);
	irqClear(IRQ_TIMER3);
	TIMER3_CR = 0;

	// Reinitialize variables
	min = 0;
	sec = 0;

	// See if score needs to be saved only if in 1p mode and if game was
	// not abruptly stopped (score = -1)
	if(score != -1) info_save_score(score, game);
}

// Save best scores
void info_save_score(int score, int game){
	// Open file
	FILE* file;
	char name[20] = "/";

	strcat(name, names[game]);
	strcat(name, ".txt");
	file = fopen(name, "r");

	// Read score and check if new score better or not
	int max_score;
	bool write = false;

	if(file==NULL) write = true;
	else{
		fscanf(file,"%i\n", &max_score);

		if(score > max_score) write = true;
	}

	// Write new best score if previous beaten
	if(write){
		fclose(file);
		file = fopen(name, "w");
		fprintf(file,"%i\n", score);
		fclose(file);
	}
	else fclose(file);
}

// Returns the score of a specific game
int info_get_score(int game){
	// Open correct file corresponding to the asked game
	FILE* file;
	char name[20] = "/";

	strcat(name, names[game]);
	strcat(name, ".txt");
	file = fopen(name, "r");

	// Read score or put 0 if no file exists
	int score;

	if(file==NULL) score = 0;
	else fscanf(file,"%i\n",&score);

	// Close file
	fclose(file);

	// Return score
	return score;
}