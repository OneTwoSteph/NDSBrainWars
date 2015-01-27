/*
 * info.c
 *
 *  Created on: Jan 23, 2015
 *      Author: Stephanie Amati
 *
 */

#include "general.h"
#include "info.h"
#include "score.h"

int sec, min;

void info_time_ISR(){
	// Update sec
	sec++;

	// Check for minutes
	if(sec>59){
		sec = 0;
		min++;
	}
}

void info_init(state){
	// Put correct colors in end of bitmap palette for the tiles
	swiCopy(scorePal, &BG_PALETTE[16*15], scorePalLen/2);

	// Draw score and time titles
	int x, y;
	int ystart = 17;
	int ymid = 20;
	int H = 3;			// Height at which the titles are in image

	for(x=0; x<32;x++){
		for(y=ystart; y<ymid;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+(state-1)*H)*32+x]|(15<<12);
		}
	}

	// Initialize the timer only if state is not TRAIN
	if(state!=TRAIN){
		sec = 0;
		min = 0;

		TIMER2_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
		TIMER2_DATA = TIMER_FREQ_1024(1);

		irqSet(IRQ_TIMER2, &info_time_ISR);
		irqEnable(IRQ_TIMER2);
	}

	// Draw empty initial values
	info_update(0, state);
}

void info_update(int score, int state){
	int x, y;
	int xstart = 1;
	int ystart = 20;
	int length = 2;
	int H = 9;		// height above numbers in image score

	// Draw score
	int dig1, dig2, dig3, dig4;

	dig1 = score/1000;
	dig2 = (score-1000*dig1)/100;
	dig3 = (score-1000*dig1-100*dig2)/10;
	dig4 = (score-1000*dig1-100*dig2-10*dig3);

	for(x=xstart; x<xstart+length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig1*length+x]|(15<<12);
		}
	}

	for(x=xstart+length; x<xstart+2*length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig2*length+(x-length)]|(15<<12);
		}
	}

	for(x=xstart+2*length; x<xstart+3*length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig3*length+(x-2*length)]|(15<<12);
		}
	}

	for(x=xstart+3*length; x<xstart+4*length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig4*length+(x-3*length)]|(15<<12);
		}
	}

	// Draw time only if state not TRAIN
	if(state!=TRAIN){
		int dot = 1;
		int xstart = 22;

		dig1 = min/10;
		dig2 = min-10*dig1;
		dig3 = sec/10;
		dig4 = sec-10*dig3;

		for(x=xstart; x<xstart+length;x++){
			for(y=ystart; y<24;y++){
				BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig1*length+(x-xstart+1)]|(15<<12);
			}
		}

		for(x=xstart+length; x<xstart+2*length;x++){
			for(y=ystart; y<24;y++){
				BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig2*length+(x-length-xstart+1)]|(15<<12);
			}
		}

		for(x=xstart+2*length; x<xstart+2*length+dot;x++){
			for(y=ystart; y<24;y++){
				BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+10*length+(x-2*length-xstart+1)]|(15<<12);
			}
		}

		for(x=xstart+2*length+dot; x<xstart+3*length+dot;x++){
			for(y=ystart; y<24;y++){
				BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig3*length+(x-2*length-xstart-dot+1)]|(15<<12);
			}
		}

		for(x=xstart+3*length+dot; x<xstart+4*length+dot;x++){
			for(y=ystart; y<24;y++){
				BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig4*length+(x-3*length-xstart-dot+1)]|(15<<12);
			}
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
