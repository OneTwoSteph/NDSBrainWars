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

#include "result.h"

int sec, min;

static volatile int score_p1[3];
static volatile int score_p2[3];

int counter = 0;

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

	sec = 0;
	min = 0;

	// Initialize the timer only if state is not TRAIN
	if(state!=TRAIN){

		TIMER2_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
		TIMER2_DATA = TIMER_FREQ_1024(1);

		irqSet(IRQ_TIMER2, &info_time_ISR);
		irqEnable(IRQ_TIMER2);
	}

	// Draw empty initial values
	int player;
	if(state==TWOP){
		player = counter%2;
		if(player==0){
			info_update(score_p1[counter/2], state, false);
			info_update(0, state, true);
		}
		else{
			info_update(score_p1[counter/2], state, false);
			info_update(0, state, true);
		}
	}
	else info_update(0, state, false);

	// Update game counter if two player mode
	if(state==TWOP) counter++;
}

void info_update(int score, int state, bool player){
	int x, y;
	int xstart = 1;
	int ystart = 20;
	int length = 2;
	int H = 9;		// height above numbers in image score
	if(player) xstart = 11;

	// Draw score
	int dig1, dig2, dig3, dig4;

	dig1 = score/1000;
	dig2 = (score-1000*dig1)/100;
	dig3 = (score-1000*dig1-100*dig2)/10;
	dig4 = (score-1000*dig1-100*dig2-10*dig3);

	for(x=xstart; x<xstart+length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig1*length+x-xstart+1]|(15<<12);
		}
	}

	for(x=xstart+length; x<xstart+2*length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig2*length+(x-xstart-length+1)]|(15<<12);
		}
	}

	for(x=xstart+2*length; x<xstart+3*length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig3*length+(x-xstart-2*length+1)]|(15<<12);
		}
	}

	for(x=xstart+3*length; x<xstart+4*length;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig4*length+(x-xstart-3*length+1)]|(15<<12);
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

		BG_PALETTE_SUB[0x18] = BLUEVAL;
		BG_PALETTE_SUB[0x28] = REDVAL;

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
