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

void info_finish(int score, int game){
	// Put transparent tiles on BGO of sub since no score has to be shown for now
	int x, y;
	for(x=0;x<32;x++){
		for(y=0;y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = 0;
		}
	}

	// Disable timer
	TIMER2_CR &= ~(TIMER_ENABLE);

	// Read into file to find if best score beated
	FILE* file;
	int max_score;

	switch(game){
	case LEADER:
		file = fopen("/leader.txt", "r");
		if(file==NULL){
			file = fopen("/leader.txt","w+");
			fprintf(file,"%i\n", score);
		}
		else{
			fscanf(file,"%i\n",&max_score);

			if(score > max_score){
				fclose(file);
				file = fopen("/leader.txt","w+");
				fprintf(file,"%i\n", score);
			}
		}

		break;
	case EATIT:
		file = fopen("/eatit.txt", "r");
		if(file==NULL){
			file = fopen("/eatit.txt","w+");
			fprintf(file,"%i\n", score);
		}
		else{
			fscanf(file,"%i\n",&max_score);

			if(score > max_score){
				fclose(file);
				file = fopen("/eatit.txt","w+");
				fprintf(file,"%i\n", score);
			}
		}
		break;
	case MUSICAL:
		file = fopen("/musical.txt", "r");
		if(file==NULL){
			file = fopen("/musical.txt","w+");
			fprintf(file,"%i\n", score);
		}
		else{
			fscanf(file,"%i\n",&max_score);

			if(score > max_score){
				fclose(file);
				file = fopen("/musical.txt","w+");
				fprintf(file,"%i\n", score);
			}
		}
		break;
	case PATH:
		file = fopen("/path.txt", "r");
		if(file==NULL){
			file = fopen("/path.txt","w+");
			fprintf(file,"%i\n", score);
		}
		else{
			fscanf(file,"%i\n",&max_score);

			if(score > max_score){
				fclose(file);
				file = fopen("/path.txt","w+");
				fprintf(file,"%i\n", score);
			}
		}
		break;
	case ADDITION:
		file = fopen("/addition.txt", "r");
		if(file==NULL){
			file = fopen("/addition.txt","w+");
			fprintf(file,"%i\n", score);
		}
		else{
			fscanf(file,"%i\n",&max_score);

			if(score > max_score){
				fclose(file);
				file = fopen("/addition.txt","w+");
				fprintf(file,"%i\n", score);
			}
		}
		break;
	case PLUSMINUS:
		file = fopen("/plusminus.txt", "r");
		if(file==NULL){
			file = fopen("/plusminus.txt","w+");
			fprintf(file,"%i\n", score);
		}
		else{
			fscanf(file,"%i\n",&max_score);

			if(score > max_score){
				fclose(file);
				file = fopen("/plusminus.txt","w+");
				fprintf(file,"%i\n", score);
			}
		}
		break;
	case JANKENPON:
		file = fopen("/jankenpon.txt", "r");
		if(file==NULL){
			file = fopen("/jankenpon.txt","w+");
			fprintf(file,"%i\n", score);
		}
		else{
			fscanf(file,"%i\n",&max_score);

			if(score > max_score){
				fclose(file);
				file = fopen("/jankenpon.txt","w+");
				fprintf(file,"%i\n", score);
			}
		}
	case NOGAME:
		break;
	}

	fclose(file);
}

void info_init(){
	// Put correct colors in end of bitmap palette for the tiles
	swiCopy(scorePal, &BG_PALETTE[16*15], scorePalLen/2);

	// Draw score and time titles
	int x, y;
	int ystart = 17;
	int ymid = 20;
	int H = 3;			// Height at which the titles are in image

	for(x=0; x<32;x++){
		for(y=ystart; y<ymid;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+x]|(15<<12);
		}
	}

	// Initialize the timer
	sec = 0;
	min = 0;

	TIMER2_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	TIMER2_DATA = TIMER_FREQ_1024(1);

	irqSet(IRQ_TIMER2, &info_time_ISR);
	irqEnable(IRQ_TIMER2);

	// Draw empty initial values
	info_update(0);
}

void info_update(int score){
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

	// Draw time
	int dot = 1;
	int W = 20;

	dig1 = min/10;
	dig2 = min-10*dig1;
	dig3 = sec/10;
	dig4 = sec-10*dig3;

	for(x=xstart+W; x<xstart+length+W;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig1*length+(x-W)]|(15<<12);
		}
	}

	for(x=xstart+length+W; x<xstart+2*length+W;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig2*length+(x-length-W)]|(15<<12);
		}
	}

	for(x=xstart+2*length+W+dot; x<xstart+3*length+W+dot;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig3*length+(x-2*length-W-dot)]|(15<<12);
		}
	}

	for(x=xstart+3*length+W+dot; x<xstart+4*length+W+dot;x++){
		for(y=ystart; y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = scoreMap[(y-ystart+H)*32+dig4*length+(x-3*length-W-dot)]|(15<<12);
		}
	}
}
