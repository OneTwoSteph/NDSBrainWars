/*
 * plusminus.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS
 */

#include "general.h"
#include "plusminus.h"
#include "plusminus_im.h"
#include "numbers.h"

static volatile int pm_score;
static volatile int numbers[3];
static volatile int new_num[3];
static volatile int compare;

static volatile int draw_timer;

void plusminus_timer_ISR(){
	draw_timer++;
}

void plusminus_init() {

	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;
	BGCTRL_SUB[1] = BG_TILE_BASE(3) | BG_MAP_BASE(16) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory. Number tiles in BG0 and game BG in BG1
	swiCopy(numbersTiles, BG_TILE_RAM_SUB(1), numbersTilesLen/2);
	swiCopy(plusminus_imTiles, BG_TILE_RAM_SUB(3), plusminus_imTilesLen/2);

	// Copy palette for both images
	swiCopy(numbersPal, BG_PALETTE_SUB, numbersPalLen/2);
	swiCopy(plusminus_imPal, &BG_PALETTE_SUB[16], plusminus_imPalLen/2);

	// Same background color in both images
	BG_PALETTE_SUB[1] = BG_PALETTE_SUB[27];
	
	// Init. Timer for interrupt
	TIMER0_DATA = TIMER_FREQ_1024(4);
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	irqSet(IRQ_TIMER0, &plusminus_timer_ISR);

	int row, col;

	// Draw Initial Field
	for(row=0; row<32; row++){
		for(col=0; col<32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0;
			BG_MAP_RAM_SUB(16)[row*32+col] = plusminus_imMap[row*32+col] | (1<<12);
		}
	}

	int i;

	for(i = 0; i < 3; i++) 	{
		numbers[i] = rand()%10;
		new_num[i] = 0;
	}

	pm_score = 0;
	compare = GREATER;

	plusminus_draw();



}

void plusminus_new_number() {
	int i, j, k;

	for(i = 0; i < 3; i++) { new_num[i] = rand()%10; }

	j = rand()%4;
	// Determine if new number will be a multiple, or factor of 2
	// If yes, compute the necessary value ( * 2 or /2 )
	if(j == 3) {

		k = rand()%2;

		if((k == 1) && (numbers[0] < 5)) { // if we can multiply by 2

			for(i = 0; i < 3; i++) 	{ new_num[i] = 2*numbers[i]; }

			if(new_num[2] > 9) {
				new_num[2] = new_num[2]%10;
				new_num[1]++;
			}
			if(new_num[1] > 9) {
				new_num[1] = new_num[1]%10;
				new_num[0]++;
			}

			compare = MULTIPLY;

		}
		else if((numbers[0] >= 5) && !(numbers[2]%2)) { // if divide by 2

			new_num[2] = numbers[2]/2;

			if(new_num[1]%2) {
				new_num[1] = (numbers[1]-1)/2;
				new_num[2] = new_num[2] + 5;
			}
			else { new_num[1] = numbers[1]/2; }

			if(new_num[0]%2) {
				new_num[0] = (numbers[0]-1)/2;
				new_num[1] = new_num[1] + 5;
			}
			else { new_num[0] = numbers[0]/2; }

			compare = DIVIDED;

		}
	}
	// Or else load random number and check that it's not the same number
	else {

		if     (new_num[0] > numbers[0]) 	{ compare = GREATER; }
		else if(new_num[0] < numbers[0])	{ compare = SMALLER; }
		else if(new_num[1] > numbers[1])	{ compare = GREATER; }
		else if(new_num[1] < numbers[1])	{ compare = SMALLER; }
		else if(new_num[2] > numbers[2])	{ compare = GREATER; }
		else 								{ compare = SMALLER; }


	}
	
	//Load generated new number into number array
	for(i = 0; i < 3; i++) 	{ numbers[i] = new_num[i]; }


}

void plusminus_draw(void) {

	int row, col;
	
	// Draw the proper number at the proper position

	//First number
	for(row = 7; row < 17; row++) {
		for(col = 7; col < 13; col++) {
			BG_MAP_RAM_SUB(0)[row*32+col] = numbersMap[((row-7)*60) + ((col-7)+numbers[0]*6)];
		}
	}

	//Second number
	for(row = 7; row < 17; row++) {
		for(col = 13; col < 19; col++) {
			BG_MAP_RAM_SUB(0)[row*32+col] = numbersMap[((row-7)*60) + ((col-13)+numbers[1]*6)];
		}
	}

	//Third number
	for(row = 7; row < 17; row++) {
		for(col = 19; col < 25; col++) {
			BG_MAP_RAM_SUB(0)[row*32+col] = numbersMap[((row-7)*60) + ((col-19)+numbers[2]*6)];
		}
	}
}

bool plusminus_game(void) {

	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed
	// Else check where pressed, and if correct
	if(keys & KEY_START) { return true; }
	else if(keys & KEY_TOUCH) {

		touchPosition touch;
		touchRead(&touch);

		switch(compare){

		case 1:
			if((touch.px < 60) && (touch.py < 96)) 	{ plusminus_correct();	}
			else									{ plusminus_wrong(); 	}
			break;
		case 2:
			if((touch.px < 60) && (touch.py >= 96)) { plusminus_correct();	}
			else									{ plusminus_wrong(); 	}
			break;
		case 3:
			if((touch.px >= 200) && (touch.py < 96)) { plusminus_correct();	}
			else if((touch.px < 60) && (touch.py < 96))
													{ plusminus_correct();
													  compare = GREATER;	}
			else									{ plusminus_wrong(); 	}
			break;
		case 4:
			if((touch.px >= 200) && (touch.py >= 96)) { plusminus_correct();}
			else if((touch.px < 60) && (touch.py >= 96))
													{ plusminus_correct();
													  compare = SMALLER;	}
			else									{ plusminus_wrong(); 	}
			break;
		default:
			break;

		}

	return false;
	}
	return false;
}

void plusminus_correct(void) {

	pm_score++;
	// If correct, increment score,
	// If correctly found multiple or factor, more points!
	if(compare > 2) { pm_score = pm_score + 2; }
	
	// Generate CORRECT condition

	int old_color = BG_PALETTE_SUB[1];

	BG_PALETTE_SUB[1] = TRUEGREEN;
	BG_PALETTE_SUB[27] = TRUEGREEN;

	draw_timer = 0;
	irqEnable(IRQ_TIMER0);
	while(draw_timer <= 2);
	irqDisable(IRQ_TIMER0);

	BG_PALETTE_SUB[1] = old_color;
	BG_PALETTE_SUB[27] = old_color;

	plusminus_new_number();
	plusminus_draw();

}
void plusminus_wrong(void) {

	if(pm_score > 0)	{ pm_score--; }
	// Remove points
	
	// Generate WRONG condition
	int old_color = BG_PALETTE_SUB[1];

	BG_PALETTE_SUB[1] = TRUERED;
	BG_PALETTE_SUB[27] = TRUERED;

	draw_timer = 0;
	irqEnable(IRQ_TIMER0);
	while(draw_timer <= 2);
	irqDisable(IRQ_TIMER0);

	BG_PALETTE_SUB[1] = old_color;
	BG_PALETTE_SUB[27] = old_color;

	plusminus_new_number();
	plusminus_draw();
}

void plusminus_reset(void) {

	draw_timer = 0;
	pm_score = 0;
	compare = 1;

}
