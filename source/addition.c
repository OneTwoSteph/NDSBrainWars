/*
 * addition.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS
 *
 */

#include "general.h"
#include "info.h"
#include "addition.h"
#include "addition_im.h"
#include "numbers.h"

static volatile int draw_timer;
static volatile int counter;
static volatile int total_number[3];
static volatile int final_number;
static volatile int numbers[2];
static volatile int add_score;

void addition_timer_ISR(){
	draw_timer++;
}

void addition_init() {
	// Add BG1 and configure
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;
	BGCTRL_SUB[1] = BG_TILE_BASE(4) | BG_MAP_BASE(17) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory
	swiCopy(numbersTiles, BG_TILE_RAM_SUB(1), numbersTilesLen/2);
	swiCopy(addition_imTiles, BG_TILE_RAM_SUB(4), addition_imTilesLen/2);

	// Copy palette
	swiCopy(numbersPal, BG_PALETTE_SUB, numbersPalLen/2);
	swiCopy(addition_imPal, &BG_PALETTE_SUB[16], addition_imPalLen/2);

	BG_PALETTE_SUB[1] = GREYVAL;
	BG_PALETTE_SUB[5] = BLACKVAL;

	BG_PALETTE_SUB[21] = GREYVAL;
	BG_PALETTE_SUB[22] = GREYVAL;
	BG_PALETTE_SUB[24] = BLUEVAL;

	TIMER0_DATA = TIMER_FREQ_1024(4);
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
	irqSet(IRQ_TIMER0, &addition_timer_ISR);

	int row, col;

	// Draw Initial Field
	for(row=0; row<32; row++){
		for(col=0; col<32; col++){
			BG_MAP_RAM_SUB(0)[row*32+col] = 0;
			BG_MAP_RAM_SUB(17)[row*32+col] = addition_imMap[row*32+col] | (1<<12);
		}
	}

	add_score = 0;
	counter = 0;

	addition_new_number();
	addition_draw();

	// Draw infos
	info_init();
}

void addition_new_number() {

	int i;
	int temp_number[3];
	final_number = 0;

	for(i = 0; i < 3; i++) { temp_number[i] = rand()%10; }

	while(temp_number[1]  == temp_number[0])  { temp_number[1] = rand()%10; }

	while((temp_number[2] == temp_number[1]) ||
		  (temp_number[2] == temp_number[0])) { temp_number[2] = rand()%10; }

	for(i = 0; i < 3; i++) { final_number = final_number + temp_number[i]; }

	numbers[0] = final_number%10;
	numbers[1] = (final_number - numbers[0])/10;

	counter = 0;

}

void addition_draw() {

	int row, col;

	//First number
	for(row = 2; row < 12; row++) {
		for(col = 25; col < 31; col++) {
			BG_MAP_RAM_SUB(0)[row*32+col] = numbersMap[((row-3)*60) + ((col-25)+numbers[0]*6)];
		}
	}

	//Second number
	for(row = 2; row < 12; row++) {
		for(col = 19; col < 25; col++) {
			BG_MAP_RAM_SUB(0)[row*32+col] = numbersMap[((row-3)*60) + ((col-19)+numbers[1]*6)];
		}
	}

}

bool addition_game() {

	scanKeys();
	u16 keys = (u16) keysDown();

	// Stop game if START button pressed
	if(keys & KEY_START) { return true; }
	else if(keys & KEY_TOUCH) {

		touchPosition touch;
		touchRead(&touch);

		if		(touch.px < 48)   {
			if		(touch.py < 64)	  { addition_add_num(1); }
			else if	((touch.py >= 64) &&
					 (touch.py < 128)){ addition_add_num(4); }
			else 					  { addition_add_num(7); }
		}
		else if	((touch.px >= 48) &&
				 (touch.px < 96)) {
			if		(touch.py < 64)	 { addition_add_num(2); }
			else if	((touch.py >= 64) &&
					 (touch.py < 128)){ addition_add_num(5); }
			else 					 { addition_add_num(8); }
		}
		else if ((touch.px >=96) &&
				 (touch.px < 144 )){
			if		(touch.py < 64)	 { addition_add_num(3); }
			else if	((touch.py >= 64) &&
					 (touch.py < 128)){ addition_add_num(6); }
			else 					 { addition_add_num(9); }
		}
		else {
			if(touch.py > 128) 		 { addition_add_num(0); }
		}
	}

	// Update infos
	info_update(add_score);

	// Return false because game did not end
	return false;

}

void addition_add_num(int num) {

	if (counter == 0) 					{ total_number[0] = num; }
	else if ((counter == 1) &&
			 (num != total_number[0])) 	{ total_number[1] = num; }
	else if ((counter == 2) &&
			 (num != total_number[0]) &&
			 (num != total_number[1]))  { total_number[2] = num; }
    else 								{ counter--; }

	counter++;

	if (counter >= 3) {

		int i, total;
		total = 0;

		for(i = 0; i < 3; i++) { total = total + total_number[i]; }

		if(total == final_number) { addition_correct(); }
		else					  { addition_wrong();   }
	}



}

void addition_correct() {
	add_score++;

	int old_color = BG_PALETTE_SUB[1];

	BG_PALETTE_SUB[1] = GREENVAL;
	BG_PALETTE_SUB[22] = GREENVAL;

	draw_timer = 0;
	irqEnable(IRQ_TIMER0);
	while(draw_timer <= 2);
	irqDisable(IRQ_TIMER0);

	BG_PALETTE_SUB[1] = old_color;
	BG_PALETTE_SUB[22] = old_color;

	addition_new_number();
	addition_draw();
}

void addition_wrong() {
	if(add_score > 0)	{ add_score--; }

	int old_color = BG_PALETTE_SUB[1];

	BG_PALETTE_SUB[1] = REDVAL;
	BG_PALETTE_SUB[22] = REDVAL;

	draw_timer = 0;
	irqEnable(IRQ_TIMER0);
	while(draw_timer <= 2);
	irqDisable(IRQ_TIMER0);

	BG_PALETTE_SUB[1] = old_color;
	BG_PALETTE_SUB[22] = old_color;

	addition_new_number();
	addition_draw();

}

void addition_reset() {
	// Suppress infos
	info_finish(add_score, "addition");

	draw_timer = 0;
	add_score = 0;
	counter = 0;

	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;
}
