/*
 * musical.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Stephanie Amati
 *
 */


/******************************************************************** Modules */
// General
#include "general.h"
#include "musical.h"

// Image
#include "musical_im.h"


/****************************************************************** Constants */
// Palettes
#define NORMALPAL	6
#define GREYPAL		7

// Image infos
#define XSTART 		4
#define WT 			6

// Game constants
typedef enum MUSIC MUSIC;
enum MUSIC
{
	DO = 0,
	RE = 1,
	MI = 2,
	FA = 3
};


/*********************************************************** Global variables */
// Sound variable for playing music tones
mm_sound_effect sound;

// Game variables
MUSIC music[4];				// tones order

// Game state
int score;
LEVEL level;
int answer;					// current tone to find
MUSIC wrongTone;			// last wrong tone touched

// Timer variables
int tonenb;					// draw notes and play music
MUSIC wrong;				// wrong blinking effect

// Drawing status
bool occupied;				// block actions while drawing


/***************************************************************** Timer ISRs */
// Music playing ISR
void musical_timer_ISR0(){
	// Play current tone only if not first time (to let a small pause)
	if(tonenb == 1){
		musical_draw_tones();
	}
	if(tonenb > 1) musical_play_tone();

	// Increase tone
	tonenb++;

	// Disable timer when last tone reached
	if(tonenb > (level+2)){
		TIMER0_CR &= ~(TIMER_ENABLE);
		occupied = false;
	}
}

// Wrong blinking ISR
void musical_timer_ISR1(){
	// Draw for blinking effect
	musical_draw_tone(wrongTone, ((wrong%2) == 0) ? GREYPAL : NORMALPAL);

	// Increment wrong
	wrong++;

	// When already blinked 3 times, update status, disable timer and launch new
	// configuration
	if(wrong == 6){
		TIMER1_CR &= ~(TIMER_ENABLE);
		occupied = false;
		musical_next();
	}
}


/****************************************************************** Functions */
// Initialization
void musical_init(){
	// Deactivate BG1 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles in BG0 of SUB and put correct colors in palette
	swiCopy(musical_imTiles, BG_TILE_RAM_SUB(BG0TILE), musical_imTilesLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[0x61] = GREY;
	BG_PALETTE_SUB[0x62] = BLACKGREY;
	BG_PALETTE_SUB[0x63] = BLUE;

	BG_PALETTE_SUB[0x71] = GREY;
	BG_PALETTE_SUB[0x72] = GREY;
	BG_PALETTE_SUB[0x73] = GREY;

	// Put whole screen in grey 
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W + x] = musical_imMap[0] | (NORMALPAL << 12);
		}
	}

	// Configure music timer 0
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER0_DATA = TIMER_FREQ_1024(4);
	irqSet(IRQ_TIMER0, &musical_timer_ISR0);
	irqEnable(IRQ_TIMER0);

	// Configure wrong blinking timer 1
	TIMER1_CR = TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER1_DATA = TIMER_FREQ_256(15);
	irqSet(IRQ_TIMER1, &musical_timer_ISR1);
	irqEnable(IRQ_TIMER1);

	// Initialize sound parameters
	sound.id = SFX_DO;
	sound.rate    =	(int)(1.0f * (1<<10));		// rate
	sound.handle  = 0;           				// 0 = allocate new handle
	sound.volume  = 255;         				// Max volumen
	sound.panning = 128;         				// centered panning

	// Set global variables
	int i;

	for(i = 0; i < 4; i++){
		music[i] = i;
	}

	score = 0;
	level = EASY;
	answer = 0;
	wrongTone = DO;

	tonenb = 0;
	wrong = 0;

	occupied = false;

	// Activate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG0_ACTIVE;

	// Launch first music
	musical_next();
}

// Create next music
void musical_next(){
	// Save previous first tone
	int prevTone = music[0];

	// Random numbers for the tone sequence (music) depending on the level
	switch(level){
	case VERYEASY:
		break;
	case EASY:
		while((music[0] = rand()%2) == prevTone);
		while((music[1] = rand()%2) == music[0]);

		break;
	case MEDIUM:
		while((music[0] = rand()%3) == prevTone);
		while((music[1] = rand()%3) == music[0])
		music[2] = music[0];
		while((music[2] == music[0]) || (music[2] == music[1])) music[2] = rand()%3;

		break;
	case HARD:
		while((music[0] = rand()%4) == prevTone);
		while((music[1] = rand()%4) == music[0]);
		music[2] = music[0];
		while((music[2] == music[0]) || (music[2] == music[1])) music[2] = rand()%4;
		music[3] = music[0];
		while((music[3] == music[0]) || (music[3] == music[1]) || (music[3] == music[2])) music[3] = rand()%4;

		break;
	default:
		break;
	}

	// Reinitialize answer
	answer = 0;

	// Play music
	musical_draw_play();
}

// Draw and play next music
void musical_draw_play(){
	// Change status
	occupied = true;

	// Reset variable
	tonenb = 0;

	// Enable timer
	TIMER0_CR |= TIMER_ENABLE;
}

// Play one tone of the music
void musical_play_tone(){
	// Play current tone
	MUSIC tone = music[tonenb-2];

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
}

// Draw all tones
void musical_draw_tones(){
	// Draw the number of tones depending on level
	int x, y;

	swiWaitForVBlank();
	for(x = XSTART; x < XSTART + (level+1)*WT; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W + x] = musical_imMap[y*W + x] | (NORMALPAL << 12);
		}
	}
}

// Draw one tone
void musical_draw_tone(int tone, int palette){
	// Draw tone with palette
	int x, y;

	swiWaitForVBlank();
	for(x = XSTART + tone*WT; x < XSTART + (tone+1)*WT; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG0MAP)[y*W + x] = (BG_MAP_RAM_SUB(BG0MAP)[y*W + x] & (0x0fff)) | (palette << 12);
		}
	}
}

// Main function
int musical_game(){
	// Scan the keys only the game is not in drawing
	// mode or in error blinking mode
	if(!occupied){
		// Scan keys
		u16 keys = (u16) keysDown();

		// Check which key was pressed or where the touchscreen was touched
		if(keys & KEY_TOUCH){
				// Find position touched on touchscreen
				touchPosition touch;
				touchRead(&touch);

				// Check which tone was touched
				MUSIC touched = -1;
				sound.rate = 0;
				if(((touch.px>=179)&&(touch.px<=205)&&(touch.py>=79)&&(touch.py<=100)) && (level >= HARD)) touched = FA;
				else if(((touch.px>=131)&&(touch.px<=157)&&(touch.py>=102)&&(touch.py<=123)) && (level >= MEDIUM)) touched = MI;
				else if((touch.px>=83)&&(touch.px<=109)&&(touch.py>=126)&&(touch.py<=147)) touched = RE;
				else if((touch.px>=35)&&(touch.px<=61)&&(touch.py>=150)&&(touch.py<=171)) touched = DO;

				// If a tone was touched, play it and check if correct
				if(touched != -1){
					switch(touched){
					case DO: sound.rate = (int)(1.0f * 1024); break;
					case RE: sound.rate = (int)(1.122f * 1024); break;
					case MI: sound.rate = (int)(1.26f * 1024); break; 
					case FA: sound.rate = (int)(1.335f * 1024); break;
					}
					mmEffectEx(&sound);

					if(touched == music[answer]) musical_correct();
					else{
						wrongTone = touched;
						musical_wrong();
					}
				}
		}
	}

	// Return score
	return score;
}

// Correct function
void musical_correct(){
	// Make the tone touched vanish
	musical_draw_tone(music[answer], GREYPAL);

	// Increment answer
	answer++;

	// Check if last not or not
	if(answer > level){
		// Increment score
		score++;

		// Check level
		if(score > MUSICALHARD) level = HARD;
		else{
			if(score > MUSICALMEDIUM) level = MEDIUM;
			else level = EASY;
		}

		// Launch next music
		musical_next();
	}
}

// Wrong function
void musical_wrong(){
	// Update status
	occupied = true;

	// Reset wrong variable
	wrong = 0;

	// Launch wrong timer
	TIMER1_CR |= TIMER_ENABLE;
}

// Reset function
void musical_reset(){
	// Deactivate BG0 SUB
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG0_ACTIVE;

	// Disable timer 0
	irqDisable(IRQ_TIMER0);
	irqClear(IRQ_TIMER0);
	TIMER0_CR = 0;

	// Disable timer 1
	irqDisable(IRQ_TIMER1);
	irqClear(IRQ_TIMER1);
	TIMER1_CR = 0;

	// Reset all global variables
	int i;

	for(i = 0; i < 4; i++){
		music[i] = i;
	}

	score = 0;
	level = EASY;
	answer = 0;

	tonenb = 0;
	wrong = 0;

	occupied = false;
}