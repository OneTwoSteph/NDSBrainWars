/*
 * musical.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Stephanie Amati
 *
 */

#include "general.h"
#include "info.h"
#include "musical.h"
#include "musical_tone.h"

#define BLUEPAL		6
#define	REDPAL		7
#define GREYPAL	8

mm_sound_effect sound;

MUSIC music[4];
int answer;
int tonenb;

bool ready;
MUSIC wrong;
int score;
LEVEL level;

STATE state;

void musical_play(){
	//Disable Timer
	TIMER0_CR &= ~(TIMER_ENABLE);

	// Play current tone
	MUSIC tone = music[tonenb];

	switch(tone){
	case DO:
		sound.rate = (int)(1.0f * 1024);
		break;
	case RE:
		sound.rate = (int)(1.122f * 1024);
		break;
	case MI:
		sound.rate = (int)(1.26f * 1024);
		break;
	case FA:
		 sound.rate = (int)(1.335f * 1024);
		 break;
	}

	mmEffectEx(&sound);

	// Increase tone
	tonenb++;

	// Enable time only if last tone not reached
	if(tonenb>level){
		tonenb = 0;
		ready = true;
	}
	else TIMER0_CR |= TIMER_ENABLE;
}

void musical_wait_ISR(){
	// Disable timer
	TIMER1_CR &= ~(TIMER_ENABLE);

	// Launch next challenge or play new music depending on game state
	if((answer==(level+1)) || (wrong<=FA)) musical_next();
	else musical_play();
}

void musical_init(int gameState){
	// Desactivate BG1
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles to memory
	swiCopy(musical_toneTiles, BG_TILE_RAM_SUB(BG0TILE), musical_toneTilesLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[0x61] = GREY;
	BG_PALETTE_SUB[0x62] = BLACKGREY;
	BG_PALETTE_SUB[0x63] = BLUE;

	BG_PALETTE_SUB[0x71] = GREY;
	BG_PALETTE_SUB[0x72] = BLACKGREY;
	BG_PALETTE_SUB[0x73] = RED;

	BG_PALETTE_SUB[0x81] = GREY;
	BG_PALETTE_SUB[0x82] = GREY;
	BG_PALETTE_SUB[0x83] = GREY;

	// Set whole BG0 in grey
	int row, col;

	swiWaitForVBlank();
	for(row = 0; row < H; row++){
		for(col = 0; col < W; col++){
			BG_MAP_RAM_SUB(BG0MAP)[row*W+col] = musical_toneMap[0] | (BLUEPAL << 12);
		}
	}

	// Activate BG0
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Configure interrupts and timers, timer 0 for music and timer 1 for waiting
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER0_DATA = TIMER_FREQ_1024(4);

	irqSet(IRQ_TIMER0, &musical_play);
	irqEnable(IRQ_TIMER0);

	TIMER1_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_1024(2);

	irqSet(IRQ_TIMER1, &musical_wait_ISR);
	irqEnable(IRQ_TIMER1);

	// Initialize sound parameters
	sound.id = SFX_DO;
	sound.rate    =	(int)(1.0f * (1<<10));		// rate
	sound.handle  = 0;           				// 0 = allocate new handle
	sound.volume  = 255;         				// Max volumen
	sound.panning = 128;         				// centered panning

	// Set global variables
	ready = false;
	wrong = 4;
	score = -1;
	level = EASY;
	tonenb = 0;
	state = gameState;

	// Launch first music
	musical_next();

	// Draw infos
	info_init(state);
}

bool musical_game(bool player, int gameCounter){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed or time crossed 15 sec
	int time;
	time = info_get_time();

	if(state != TRAIN) { info_store_temp_score(player, gameCounter, score); }

	if((keys & KEY_START) || (time > GAMETIME)) { return true; }
	else{
		// If game ready and touchscreen was touched, check if correct
		if(ready && (keys & KEY_TOUCH)){
			// Set sound rate to 0
			sound.rate = 0;

			// Find position touched on touchscreen
			touchPosition touch;
			touchRead(&touch);

			// Check if touched correct symbol
			switch(level){
			case HARD:
				// Check if in fourth tone
				if((touch.px>=179)&&(touch.px<=205)&&(touch.py>=79)&&(touch.py<=100)){
					sound.rate = (int)(1.335f * 1024);

					if(music[answer]==FA) answer++;
					else wrong = FA;

					// Draw correct or wrong tone
					musical_draw();
				}

			case MEDIUM:
				// Check if in third tone
				if((touch.px>=131)&&(touch.px<=157)&&(touch.py>=102)&&(touch.py<=123)){
					sound.rate = (int)(1.26f * 1024);

					if(music[answer]==MI) answer++;
					else wrong = MI;

					// Draw correct or wrong tone
					musical_draw();
				}

			case EASY:
				// Check if in second tone
				if((touch.px>=83)&&(touch.px<=109)&&(touch.py>=126)&&(touch.py<=147)){
					sound.rate = (int)(1.122f * 1024);

					if(music[answer]==RE) answer++;
					else wrong = RE;

					// Draw correct or wrong tone
					musical_draw();
				}

				// Check if in first tone
				if((touch.px>=35)&&(touch.px<=61)&&(touch.py>=150)&&(touch.py<=171)){
					sound.rate = (int)(1.0f * 1024);

					if(music[answer]==DO) answer++;
					else wrong = DO;

					// Draw correct or wrong tone
					musical_draw();
				}

				break;
			default:
				break;
			}

			// Play sound if a tone was touched
			if(sound.rate >= 0) mmEffectEx(&sound);

			// If last ton or wrong, wait a few seconds and launch new music
			if((answer==(level+1)) || (wrong<=FA)){
				ready = false;
				TIMER1_CR |= TIMER_ENABLE;
			}
		}
	}

	// Play effect if tone was false
	//if(wrong<=FA) mmEffect(SFX_BOING);

	// Update infos
	info_update(score, state, player);

	// Return false (the game is note finished)
	return false;
}

void musical_next(){
	// Increment score only if precedent game wasn't wrong
	if(wrong>FA) score++;
	else wrong = FA+1;

	// Check level
	if(score > MUSICALHARD) level = HARD;
	else{
		if(score > MUSICALMEDIUM) level = MEDIUM;
		else level = EASY;
	}

	// If first time, initiate third and fourth tone
	if(score==0){
		music[2] = MI;
		music[3] = FA;
	}

	// Random numbers for the tone sequence (music) depending on the level
	switch(level){
	case VERYEASY:
		break;
	case EASY:
		music[0] = rand()%2;
		while((music[1]=rand()%2)==music[0]);

		break;
	case MEDIUM:
		music[0] = rand()%3;
		while((music[1]=rand()%3)==music[0])
		music[2] = music[0];
		while((music[2]==music[0])||(music[2]==music[1])) music[2] = rand()%3;

		break;
	case HARD:
		music[0] = rand()%4;
		while((music[1]=rand()%4)==music[0]);
		music[2] = music[0];
		while((music[2]==music[0])||(music[2]==music[1])) music[2] = rand()%4;
		music[3] = music[0];
		while((music[3]==music[0])||(music[3]==music[1])||(music[3]==music[2])) music[3] = rand()%4;

		break;
	default:
		break;
	}

	// Reinitialize answer
	answer = 0;

	// Redraw screen
	musical_draw();

	// Wait a moment and launch music
	TIMER1_CR |= TIMER_ENABLE;
}

void musical_draw(){
	int x, y;
	int xstart = 4;
	int length = 6; 	// of the tones

	// Draw first background with grey
	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = musical_toneMap[0] | (BLUEPAL << 12);
		}
	}

	// Draw tones in function of the level
	for(x = 0; x < xstart + (level+1)*length; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = musical_toneMap[y*W+x] | (BLUEPAL << 12);
		}
	}

	// Undraw correct tones
	int i;

	for(i = 0; i < answer; i++){
		if(music[i] != wrong){
			for(x = xstart + music[i]*length; x < xstart + (music[i]+1)*length; x++){
				for(y = 0; y < H; y++){
					BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = (BG_MAP_RAM_SUB(BG0MAP)[y*W+x] & 0x0fff) | (GREYPAL << 12);
				}
			}
		}
	}

	// Draw false tone in red
	if(wrong <= FA){
		for(x = xstart + wrong*length; x < xstart + (wrong+1)*length; x++){
			for(y = 0; y < H; y++){
				BG_MAP_RAM_SUB(BG0MAP)[y*W+x] = (BG_MAP_RAM_SUB(BG0MAP)[y*W+x] & 0x0fff) | (REDPAL << 12);
			}
		}
	}
}

void musical_reset(){
	// Suppress infos display
	info_finish(score, "musical", state);

	// Disable timers
	TIMER0_CR = 0;
	TIMER1_CR = 0;
	irqDisable(IRQ_TIMER0);
	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER0);
	irqClear(IRQ_TIMER1);

	// Desactivate BG0
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Reset all global variables (just to be sure)
	score = 0;
	wrong = 0;
	level = EASY;
}
