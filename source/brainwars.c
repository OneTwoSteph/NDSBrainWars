/*
 * brainwars.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati & Nawaaz GS
 *
 */


/******************************************************************** Modules */
// General
#include "brainwars.h"
#include "general.h"
#include "info.h"

// Games
#include "leader.h"
#include "eatit.h"
#include "musical.h"
#include "path.h"
#include "addition.h"
#include "plusminus.h"
#include "jankenpon.h"


/********************************************************************* Images */
// MAIN screen
#include "main_start.h"
#include "main_menu.h"
#include "main_exp.h"

// SUB screen
#include "sub_start.h"
#include "sub_menu.h"
#include "sub_train.h"
#include "sub_p.h"
#include "sub_score.h"
#include "sub_credits.h"

// Other
#include "info_im.h"


/****************************************************************** Constants */
// Palettes IDs
#define NORMALPAL		0
#define YELLOWPAL		1
#define GREENPAL		2
#define BLUEPAL			3
#define REDPAL			4
#define GREYPAL			5

// 1p and 2p display infos
#define PWIM		42
#define PSIDE		6
#define PSTARTX		5
#define PSTARTY		3
#define PINT 		2

typedef enum PSTATE PSTATE;
enum PSTATE
{
	SEL = 0,
	SHOW = 1,
	PLAY = 2,
	RESULT = 3,
	FINAL = 4
};


/*********************************************************** Global variables */
// Display
int display;

u8 loadT[] = {
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11,
	0x11,0x11,0x11,0x11
};

// Game state
STATE state;
bool stateChange;
STATE selectMain;

// Train state
GAME trainGame;
GAME selectTrain;
bool trainGameChange;

// 1p and 2p state
PSTATE pState;
bool pStateChange;
GAME pGames[3];
int onepCurrent;
int twopCurrent;
int onepScores[3];
int twopScores[6];

// Score
int scores[7];


/***************************************************************** Timer ISRs */
// Display timer
void brainwars_timer_ISR2(){
	display++;
}


/********************************************************************** Start */
// Initialize NDS
void brainwars_start_init(){
	// Initialize score saving in text files
	fatInitDefault();

	// Read saved best scores in files to initialize scores array
	scores[0] = info_get_score(LEADER);
	scores[1] = info_get_score(EATIT);
	scores[2] = info_get_score(MUSICAL);
	scores[3] = info_get_score(PATH);
	scores[4] = info_get_score(ADDITION);
	scores[5] = info_get_score(PLUSMINUS);
	scores[6] = info_get_score(JANKENPON);

	// Initialize sound
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad(MOD_REGGAEBANANA);
	mmLoadEffect(SFX_DO);
	mmLoadEffect(SFX_DUM_DUM);
	mmLoadEffect(SFX_BON);
	mmLoadEffect(SFX_NUL);

	// Initialize timer for background change
	TIMER2_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER2_DATA = TIMER_FREQ_1024(TIMERF);

	irqSet(IRQ_TIMER2, &brainwars_timer_ISR2);
	irqEnable(IRQ_TIMER2);

	// Configure MAIN and SUB screens
	brainwars_start_configMain();
	brainwars_start_configSub();

	// Launch the start screen before game starts
	brainwars_start();
}

// MAIN screen configuration
void brainwars_start_configMain(){
	// Use VRAM A
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	// Activate mode 0 for mode tiles on all backgrounds
	REG_DISPCNT = MODE_0_2D;

	// BG0 will be used to display game infos (score and timer)
	BGCTRL[0] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(BG0TILE) | BG_MAP_BASE(BG0MAP);

	// BG1 will be used to display main graphics
	BGCTRL[1] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(BG1TILE) | BG_MAP_BASE(BG1MAP);

	// BG2 will be used to display grey background for inter panel pause
	BGCTRL[2] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(BG2TILE) | BG_MAP_BASE(BG2MAP);

	// Load image in BG0 which will never changer (score and timer) and put
	// correct colors in palette
	swiCopy(info_imTiles, BG_TILE_RAM(BG0TILE), info_imTilesLen/2);

	BG_PALETTE[0x61] = GREY;
	BG_PALETTE[0x62] = BLACKGREY;
	BG_PALETTE[0x63] = BLACK;

	BG_PALETTE[0x71] = GREY;
	BG_PALETTE[0x72] = BLACKGREY;
	BG_PALETTE[0x73] = RED;

	// Load image in BG2 which will never change (just grey background) and use
	// palette 15 to put grey in it
	swiCopy(loadT, (u8*)BG_TILE_RAM(BG2TILE), 8*8*4/8/2);

	BG_PALETTE[0xf1] = GREY;

	int row, col;
	for(row = 0; row < H; row++){
		for(col = 0; col < W; col++){
			BG_MAP_RAM(BG2MAP)[row*W+col] = 0 | (15<<12);
		}
	}
}

// SUB screen configuration
void brainwars_start_configSub(){
	// Use VRAM C
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;

	// Activate mode 0 to use all backgrounds in tiles mode
	REG_DISPCNT_SUB = MODE_0_2D;

	// BG0 will be used for the games graphics
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(BG0TILE) | BG_MAP_BASE(BG0MAP);

	// BG1 will be used to display main graphics
	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(BG1TILE) | BG_MAP_BASE(BG1MAP);

	// BG2 will be used to display grey background for inter panel pause
	BGCTRL_SUB[2] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(BG2TILE) | BG_MAP_BASE(BG2MAP);

	// Load image in BG2 which will never change (just grey background) and use
	// palette 15 to put grey in it
	swiCopy(loadT, (u8*)BG_TILE_RAM_SUB(BG2TILE), 8*8*4/8/2);

	BG_PALETTE_SUB[0xf1] = GREY;

	int row, col;
	for(row = 0; row < H; row++){
		for(col = 0; col < W; col++){
			BG_MAP_RAM_SUB(BG2MAP)[row*W+col] = 0 | (15<<12);
		}
	}
}

// Start
void brainwars_start(){
	// Launch timer for panel change pause
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;

	// Activate BG2 for grey background
	swiWaitForVBlank();
	REG_DISPCNT |= DISPLAY_BG2_ACTIVE;
	REG_DISPCNT_SUB |= DISPLAY_BG2_ACTIVE;

	// Copy start image for MAIN screen in BG1 and put correct colors in palette
	swiCopy(main_startTiles, BG_TILE_RAM(BG1TILE), main_startTilesLen/2);
	swiCopy(main_startMap, BG_MAP_RAM(BG1MAP), main_startMapLen);

	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = GREY;
	BG_PALETTE[0x05] = BLACK;

	// Copy start image for SUB screen in BG1 and put correct colors in palette
	swiCopy(sub_startTiles, BG_TILE_RAM_SUB(BG1TILE), sub_startTilesLen/2);
	swiCopy(sub_startMap, BG_MAP_RAM_SUB(BG1MAP), sub_startMapLen);

	BG_PALETTE_SUB[0x01] = GREY;
	BG_PALETTE_SUB[0x02] = BLACK;

	// Display title on MAIN after 0.6 seconds
	while(display < PAUSE*TIMERF);
	swiWaitForVBlank();
	mmEffect(SFX_DUM_DUM);
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;

	// Wait more 0.6s before continuing
	while(display < 1.2*TIMERF);
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER2_CR &= ~(TIMER_ENABLE);

	// Scan touch screen to see if it was taped and if yes, use x and y to
	// initialize the random seed
	bool wait = true;

	while(wait){
		// Scan touch screen and if touch screen was touched, check for position
		scanKeys();
		touchPosition touch;
		u16 keys = keysDown();

		if(keys & KEY_TOUCH) {
			touchRead(&touch);

			// Use position touched to initialize random number seed
			if((touch.px > 0) && (touch.py > 0)){
				srand(touch.px + touch.py);
				wait = false;
			}
		}
	}

	// Initialize game music that will play all the time
	mmStart(MOD_REGGAEBANANA, MM_PLAY_LOOP);
	mmSetModuleVolume(350);

	// Launch main menu
	brainwars_main_init();
}


/****************************************************************** Main menu */
// Initialization
void brainwars_main_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to memory
	swiWaitForVBlank();
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy main menu image in BG1 for MAIN screen and put correct colors in
	// palette
	swiCopy(main_menuTiles, BG_TILE_RAM(BG1TILE), main_menuTilesLen/2);

	// Put correct colors in palette
	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = YELLOW;
	BG_PALETTE[0x05] = GREY;
	BG_PALETTE[0x06] = BLACK;

	// Copy main menu image in BG1 for SUB screen and put correct colors in
	// palette
	swiCopy(sub_menuTiles, BG_TILE_RAM_SUB(BG1TILE), sub_menuTilesLen/2);

	BG_PALETTE_SUB[0x01] = WHITE;
	BG_PALETTE_SUB[0x02] = GREY;
	BG_PALETTE_SUB[0x03] = BLACKGREY;
	BG_PALETTE_SUB[0x04] = BLACK;

	BG_PALETTE_SUB[0x11] = YELLOW;
	BG_PALETTE_SUB[0x12] = GREY;
	BG_PALETTE_SUB[0x13] = BLACKGREY;
	BG_PALETTE_SUB[0x14] = BLACK;

	// Initialize menu variable
	state = MAIN;
	selectMain = TRAIN;
	stateChange = false;

	// Draw main menu
	brainwars_main_draw();

	// Wait 1s before activating BG1
	while(display < PAUSE*TIMERF);
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER2_CR &= ~(TIMER_ENABLE);
}

// Main function
void brainwars_main(){
	// Check if state changed an initialize module in function of new state
	if(stateChange){
		switch(state){
		case MAIN: brainwars_main_init(); break;
		case TRAIN: brainwars_train_init(); break;
		case ONEP: brainwars_p_init(); break;
		case TWOP: brainwars_p_init(); break;
		case SCORE: brainwars_score_init(); break;
		case CREDITS: brainwars_credits_init(); break;
		default: break;
		}

		stateChange = false;
	}

	// Execute correct module in function of state
	switch(state){
	case MAIN: brainwars_main_select(); break;
	case TRAIN: brainwars_train(); break;
	case ONEP: brainwars_p(); break;
	case TWOP: brainwars_p(); break;
	case SCORE: brainwars_score(); break;
	case CREDITS: brainwars_credits(); break;
	default: break;
	}
}

// Selection in main menu
void brainwars_main_select(){
	// Scan keys and touchscreen
	u16 keys = (u16) keysDown();
	touchPosition touch;
	touchRead(&touch);

	// Check if up or down was pressed or if touchscreen was touched
	int option = -1;

	if(keys & KEY_UP){
		if(selectMain == TRAIN) option = CREDITS;
		else option = selectMain - 1;
	}
	else if(keys & KEY_DOWN) option = (((selectMain-1) + 1) % 5) + 1;
	else if(keys & KEY_A) option = selectMain;
	else if(keys & KEY_TOUCH){
		if((touch.px>=39)&&(touch.px<=215)){
			int i;
			int ystart = 21, inter = 11, h = 21;

			// Loop to see which option was touched
			for(i = 0; i < 5; i++){
				if((touch.py >= ystart+i*inter+i*h) && (touch.py <= ystart+i*inter+(i+1)*h)){
					option = i + 1;
					break;
				}
			}
		}
	}

	// Check if an option in menu was chosen or changed
	if(option == selectMain){
		state = selectMain;
		stateChange = true;
	}
	else if(option != -1){
		selectMain = option;
		brainwars_main_draw();
	}
}

// Draw
void brainwars_main_draw(){
	// Put correct information on MAIN screen BG1
	int x, y;

	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM(BG1MAP)[y*W + x] = main_menuMap[(y + (selectMain-1)*H)*W + x];
		}
	}

	// Draw menu on SUB screen BG1
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W+x] = sub_menuMap[y*W+x];
		}
	}

	// Change color of the selected button
	int YS = 2, BH = 4;

	for(x = 0; x < W; x++){
		for(y = (selectMain-1)*BH + YS; y < selectMain*BH + YS; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W+x] = BG_MAP_RAM_SUB(BG1MAP)[y*W+x]|(YELLOWPAL<<12);
		}
	}
}


/******************************************************************* Training */
// Initialization
void brainwars_train_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy train menu tiles and palette for BG1 of MAIN screen
	swiCopy(main_expTiles, BG_TILE_RAM(BG1TILE), main_expTilesLen/2);

	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = YELLOW;
	BG_PALETTE[0x05] = WHITE;
	BG_PALETTE[0x06] = GREY;
	BG_PALETTE[0x07] = BLACKGREY;
	BG_PALETTE[0x08] = BLACK;

	// Copy tiles and palette for BG1 of SUB screen
	swiCopy(sub_trainTiles, BG_TILE_RAM_SUB(BG1TILE), sub_trainTilesLen/2);

	BG_PALETTE_SUB[0x01] = RED;
	BG_PALETTE_SUB[0x02] = BLUE;
	BG_PALETTE_SUB[0x03] = GREEN;
	BG_PALETTE_SUB[0x04] = WHITE;
	BG_PALETTE_SUB[0x05] = GREY;
	BG_PALETTE_SUB[0x06] = BLACKGREY;
	BG_PALETTE_SUB[0x07] = BLACK;

	BG_PALETTE_SUB[0x11] = RED;
	BG_PALETTE_SUB[0x12] = BLUE;
	BG_PALETTE_SUB[0x13] = GREEN;
	BG_PALETTE_SUB[0x14] = YELLOW;
	BG_PALETTE_SUB[0x15] = GREY;
	BG_PALETTE_SUB[0x16] = BLACKGREY;
	BG_PALETTE_SUB[0x17] = BLACK;

	// Initialize variables
	trainGame = NOGAME;
	selectTrain = LEADER;
	trainGameChange = false;

	// Draw training menu for the first time
	brainwars_train_draw();

	// Wait 1s before activating BG1
	while(display < PAUSE*TIMERF);
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER2_CR &= ~(TIMER_ENABLE);
}

// Main function
void brainwars_train(){
	// Check if game has changed and initialize correct module
	if(trainGameChange){
		if(trainGame != NOGAME) {
			info_init();
			mmStop();
		}

		switch(trainGame){
		case LEADER: leader_init(); break;
		case EATIT: eatit_init(); break;
		case MUSICAL: musical_init(); break;
		case PATH: path_init(); break;
		case ADDITION: addition_init(); break;
		case PLUSMINUS: plusminus_init(); break;
		case JANKENPON: jankenpon_init(); break;
		case NOGAME: brainwars_train_init(); break;
		default: break;
		}

		trainGameChange = false;
	}

	// Execute current game
	int score;
	switch(trainGame){
	case LEADER: score = leader_game(); break;
	case EATIT: score = eatit_game(); break;
	case MUSICAL: score = musical_game(); break;
	case PATH: score = path_game(); break;
	case ADDITION: score = addition_game(); break;
	case PLUSMINUS: score = plusminus_game(); break;
	case JANKENPON: score = jankenpon_game(); break;
	case NOGAME: brainwars_train_select(); break;
	default: break;
	}

	// Check if game has to end
	if(trainGame != NOGAME){
		// Update infos
		info_update_score(score);

		// Scan keys
		u16 keys = (u16) keysDown();

		// Check if start was pressed and stop current game if yes
		if(keys & KEY_START){
			// Restart music
			mmStart(MOD_REGGAEBANANA, MM_PLAY_LOOP);

			// Reset infos
			info_finish(-1, trainGame);

			// Stop games
			switch(trainGame){
			case LEADER: leader_reset(); break;
			case EATIT: eatit_reset(); break;
			case MUSICAL: musical_reset(); break;
			case PATH: path_reset(); break;
			case ADDITION: addition_reset(); break;
			case PLUSMINUS: plusminus_reset(); break;
			case JANKENPON: jankenpon_reset(); break;
			case NOGAME: break;
			default: break;
			}

			// Reset train state
			trainGame = NOGAME;
			trainGameChange = true;
		}
	}
}

// Select menu
void brainwars_train_select(){
	// Scan keys and touchscreen
	u16 keys = (u16) keysDown();
	touchPosition touch;
	touchRead(&touch);

	// Check if an option was selected with buttons or touching the screen
	int option = -1;

	if(keys & KEY_RIGHT) option = (selectTrain+1) % 7;
	else if(keys & KEY_LEFT) option = (selectTrain+6) % 7;
	else if(keys & KEY_DOWN) option  = (selectTrain+3) % 7;
	else if(keys & KEY_UP) option = (selectTrain+4) % 7;
	else if(keys & KEY_A) option = selectTrain;
	else if(keys & KEY_TOUCH){
		int i;
		int row, col;
		int xstart = 49, ystart = 22, interx = 18, intery = 15, side = 40;
		int x1, x2, y1, y2;

		// Loop on the options square to see which one was touched
		for(i = 0; i < 7; i++){
			row = i/3;
			col = i%3;

			x1 = xstart + col*side + col*interx;
			x2 = x1 + side;
			y1 = ystart + row*side + row*intery;
			y2 = y1 + side;

			if((touch.px >= x1) && (touch.px <= x2) && (touch.py >= y1) && (touch.py <= y2)){
				option = i;
				break;
			}
		}
	}
	else if(keys & KEY_START){
		state = MAIN;
		stateChange = true;
	}

	// Check if an option was selected or chosen
	if(option == selectTrain){	
		trainGame = selectTrain;
		trainGameChange = true;
	}
	else if(option != -1){
		selectTrain = option;
		brainwars_train_draw();
	}
}

// Draw
void brainwars_train_draw(){
	// Draw instructions on MAIN screen
	int x, y;

	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM(BG1MAP)[y*W + x] = main_expMap[(y + selectTrain*H)*W + x];
		}
	}

	// Draw training menu on SUB screen
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W+x] = sub_trainMap[y*W+x];
		}
	}

	// Change color of the selected button
	int XS = 6, YS = 2, INTER = 1, SIDE = 6;
	int row, col;
	int x1, x2, y1, y2;

	row = selectTrain/3;
	col = selectTrain%3;

	x1 = XS + col*SIDE + col*INTER;
	x2 = x1 + SIDE;
	y1 = YS + row*SIDE + row*INTER;
	y2 = y1 + SIDE;

	for(x = x1; x < x2; x++){
		for(y = y1; y < y2; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W+x] = BG_MAP_RAM_SUB(BG1MAP)[y*W+x] | (YELLOWPAL<<12);
		}
	}
}


/***************************************************************** One player */
// Initialization
void brainwars_p_init(){
	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles in MAIN BG1 and put correct colors in palettes
	swiCopy(main_expTiles, BG_TILE_RAM(BG1TILE), main_expTilesLen/2);

	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = YELLOW;
	BG_PALETTE[0x05] = WHITE;
	BG_PALETTE[0x06] = GREY;
	BG_PALETTE[0x07] = BLACKGREY;
	BG_PALETTE[0x08] = BLACK;

	// Copy tiles in SUB BG1 and put correct colors in palette
	swiCopy(sub_pTiles, BG_TILE_RAM_SUB(BG1TILE), sub_pTilesLen/2);

	BG_PALETTE_SUB[0x01] = RED;
	BG_PALETTE_SUB[0x02] = BLUE;
	BG_PALETTE_SUB[0x03] = GREEN;
	BG_PALETTE_SUB[0x04] = WHITE;
	BG_PALETTE_SUB[0x05] = GREY;
	BG_PALETTE_SUB[0x06] = BLACKGREY;
	BG_PALETTE_SUB[0x07] = BLACK;

	BG_PALETTE_SUB[0x11] = RED;
	BG_PALETTE_SUB[0x12] = BLUE;
	BG_PALETTE_SUB[0x13] = GREEN;
	BG_PALETTE_SUB[0x14] = YELLOW;
	BG_PALETTE_SUB[0x15] = GREY;
	BG_PALETTE_SUB[0x16] = BLACKGREY;
	BG_PALETTE_SUB[0x17] = BLACK;

	BG_PALETTE_SUB[0x31] = RED;
	BG_PALETTE_SUB[0x32] = BLUE;
	BG_PALETTE_SUB[0x33] = GREEN;
	BG_PALETTE_SUB[0x34] = WHITE;
	BG_PALETTE_SUB[0x35] = GREY;
	BG_PALETTE_SUB[0x36] = BLACKGREY;
	BG_PALETTE_SUB[0x37] = BLUE;

	BG_PALETTE_SUB[0x41] = RED;
	BG_PALETTE_SUB[0x42] = BLUE;
	BG_PALETTE_SUB[0x43] = GREEN;
	BG_PALETTE_SUB[0x44] = WHITE;
	BG_PALETTE_SUB[0x45] = GREY;
	BG_PALETTE_SUB[0x46] = BLACKGREY;
	BG_PALETTE_SUB[0x47] = RED;

	BG_PALETTE_SUB[0x51] = GREY;
	BG_PALETTE_SUB[0x52] = GREY;
	BG_PALETTE_SUB[0x53] = GREY;
	BG_PALETTE_SUB[0x54] = GREY;
	BG_PALETTE_SUB[0x55] = GREY;
	BG_PALETTE_SUB[0x56] = GREY;
	BG_PALETTE_SUB[0x57] = GREY;

	// Fill screen with grey
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = sub_pMap[(PSIDE+1)*PWIM - 1] | (NORMALPAL << 12);
		}
	}

	// Initialize global variables
	pState = SEL;
	pStateChange = true;

	onepCurrent = 0;
	twopCurrent = 0;

	// Choose the 3 games
	int tab[7];
	int i, j;
	int max, maxi;

	for(i = 0; i < 7; i++) tab[i] = rand();

	for(i = 0; i < 3; i++){
		max = 0;
		for(j = 0; j < 7; j++){
			if(tab[j] > max){
				max = tab[j];
				maxi = j;
			}
		}
		pGames[i] = maxi;
		tab[maxi] = -1;
	}

	// Activate BG1
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;	
}

// Main function
void brainwars_p(){
	// Check if state changed an initialize module in function of new state
	if(pStateChange){
		switch(pState){
		case SEL: brainwars_p_sel_init(); break;
		case SHOW: brainwars_p_show_init(); break;
		case PLAY: brainwars_p_play_init(); break;
		case RESULT: brainwars_p_result_init(); break;
		case FINAL: brainwars_p_final_init(); break;
		default: break;
		}

		pStateChange = false;
	}

	// Execute correct module in function of state
	switch(pState){
	case SEL: brainwars_p_sel(); break;
	case SHOW: brainwars_p_show(); break;
	case PLAY: brainwars_p_play(); break;
	case RESULT: brainwars_p_result(); break;
	case FINAL: brainwars_p_final(); break;
	default: break;
	}

	// Check if user wants to end mode
	u16 keys = (u16) keysDown();

	if(keys & KEY_START){
		if(pState == PLAY){
			// Restart music
			mmStart(MOD_REGGAEBANANA, MM_PLAY_LOOP);

			// Check the game
			int game = (state == ONEP) ? onepCurrent : (int)twopCurrent/2;

			// Reset infos
			info_finish(-1, game);

			// Stop game
			switch(pGames[game]){
			case LEADER: leader_reset(); break;
			case EATIT: eatit_reset(); break;
			case MUSICAL: musical_reset(); break;
			case PATH: path_reset(); break;
			case ADDITION: addition_reset(); break;
			case PLUSMINUS: plusminus_reset(); break;
			case JANKENPON: jankenpon_reset(); break;
			case NOGAME: break;
			default: break;
			}
		}
		state = MAIN;
		stateChange = true;
	}
}

// Selected games animation initialization
void brainwars_p_sel_init(){
	// Start timer
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;
}

// Selected games animation main function
void brainwars_p_sel(){
	// Draw games one by one and stop mode after a while
	swiWaitForVBlank();
	if(display > 20){
		// Disable time
		TIMER2_CR &= ~(TIMER_ENABLE);

		// Go to next state
		pState = SHOW;
		pStateChange = true;
	}
	else if(display > 15) brainwars_p_draw_block(pGames[2], 2);
	else if(display > 10) brainwars_p_draw_block(pGames[1], 1);
	else if(display > 5) brainwars_p_draw_block(pGames[0], 0);
}

// Show game instructions initialization
void brainwars_p_show_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;

	// See in what game we are
	int game = (state == ONEP) ? onepCurrent : twopCurrent/2;

	// Put correct explanation in MAIN screen
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM(BG1MAP)[y*W + x] = main_expMap[(y + pGames[game]*H)*W + x];
		}
	}

	// Wait a moment
	while(display < 3);

	// Activate BG1 of MAIN
	swiWaitForVBlank();
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;

	// Disable time
	TIMER2_CR &= ~(TIMER_ENABLE);

	// Draw the 3 blocks again with the right one selected
	brainwars_p_draw_block(pGames[0], 0);
	brainwars_p_draw_block(pGames[1], 1);
	brainwars_p_draw_block(pGames[2], 2);
	brainwars_p_draw_block_sel(game);

	// Draw game
	brainwars_p_draw(0, 6, 5, 2, 4, 11,  NORMALPAL);
	brainwars_p_draw(game+1, 14, 1, 2, 27, 11, NORMALPAL);

	// Draw player
	if(state == TWOP){
		brainwars_p_draw(0, 8, 8, 2, 4, 14, NORMALPAL);
		if((twopCurrent%2) == 0) brainwars_p_draw(1, 14, 1, 2, 27, 14, NORMALPAL);
		else brainwars_p_draw(2, 14, 1, 2, 27, 14, NORMALPAL);
	}

	// Draw "press A"
	brainwars_p_draw(0, 12, 23, 2, 0, 19, NORMALPAL);
}

// Show game instructions main function
void brainwars_p_show(){
	// Scan keys
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if(keys & KEY_A){
		pState = PLAY;
		pStateChange = true;
	}
}

// Play game initialization
void brainwars_p_play_init(){
	// Check which game we are playing
	int game = game = (state == ONEP) ? onepCurrent : twopCurrent/2;

	// Initialize infos
	info_init();

	// Stop music
	mmStop();

	// Initialize game
	switch(pGames[game]){
	case LEADER: leader_init(); break;
	case EATIT: eatit_init(); break;
	case MUSICAL: musical_init(); break;
	case PATH: path_init(); break;
	case ADDITION: addition_init(); break;
	case PLUSMINUS: plusminus_init(); break;
	case JANKENPON: jankenpon_init(); break;
	case NOGAME: brainwars_train_init(); break;
	default: break;
	}

	// Reinitialize display
	display = 0;
}

// Play game main function
void brainwars_p_play(){
	// Check which game
	int game = (state == ONEP) ? onepCurrent : (int)twopCurrent/2;

	// Check if game has to end otherwise execute game
	if(info_get_time() <= GAMETIME){
		int score = 0;

		switch(pGames[game]){
		case LEADER: score = leader_game(); break;
		case EATIT: score = eatit_game(); break;
		case MUSICAL: score = musical_game(); break;
		case PATH: score = path_game(); break;
		case ADDITION: score = addition_game(); break;
		case PLUSMINUS: score = plusminus_game(); break;
		case JANKENPON: score = jankenpon_game(); break;
		case NOGAME: brainwars_train_select(); break;
		default: break;
		}

		// Update infos
		info_update_score(score);

		// Check if game just ended
		if(info_get_time() == GAMETIME){
			// Stop game time
			info_stop_time();

			// Store score
			if(state == ONEP) onepScores[onepCurrent] = score;
			else twopScores[twopCurrent] = score; 

			// Start timer
			display = 0;
			TIMER2_CR |= TIMER_ENABLE;
		}
	}

	// Finish game but keep a pause on it before
	if(display > 10){
		// Restart music
		mmStart(MOD_REGGAEBANANA, MM_PLAY_LOOP);

		// Stop timer
		TIMER2_CR &= ~(TIMER_ENABLE);

		// Reset infos
		info_finish((state == ONEP) ? onepScores[onepCurrent] : -1, pGames[game]);

		// Stop game
		switch(pGames[game]){
		case LEADER: leader_reset(); break;
		case EATIT: eatit_reset(); break;
		case MUSICAL: musical_reset(); break;
		case PATH: path_reset(); break;
		case ADDITION: addition_reset(); break;
		case PLUSMINUS: plusminus_reset(); break;
		case JANKENPON: jankenpon_reset(); break;
		case NOGAME: break;
		default: break;
		}

		// Go to next state
		pState = RESULT;
		pStateChange = true;
	}
}

// Show game results initialization
void brainwars_p_result_init(){
	// Check which game
	int currentGame = (state == ONEP) ? onepCurrent : (int)twopCurrent/2;

	// Launch timer to create 1s pause
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;

	// Fill screen with grey
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = sub_pMap[(PSIDE+1)*PWIM - 1] | (NORMALPAL << 12);
		}
	}

	// Print scores of all the games played until now
	int s;

	for(s = 0; s < currentGame + 1; s++){
		// Draw game
		brainwars_p_draw(0, 6, 5, 2, 4, 4 + s*3,  NORMALPAL);
		brainwars_p_draw(s+1, 14, 1, 2, 4 + 5 + 1, 4 + s*3, NORMALPAL);

		// Draw score
		if(state == ONEP){
			// Compute score digits
			int dig[4];

			dig[0] = onepScores[s]/1000;
			dig[1] = (onepScores[s]-1000*dig[0])/100;
			dig[2] = (onepScores[s]-1000*dig[0]-100*dig[1])/10;
			dig[3] = (onepScores[s]-1000*dig[0]-100*dig[1]-10*dig[2]);

			// Draw result
			int i;
			for(i = 0; i < 4; i++){
				brainwars_p_draw(dig[i], 14, 1, 2, 24+i, 4 + s*3, BLUEPAL);
			}
		}
		else{
			// Check at what player we are
			if((2*s + 1) <= twopCurrent){
				int j;
				int pal[2] = {BLUEPAL, BLUEPAL};

				if(twopScores[2*s] > twopScores[2*s+1]) pal[1] = REDPAL;
				else if(twopScores[2*s] < twopScores[2*s+1]) pal[0] = REDPAL;

				for(j = 0; j < 2; j++){
					// Compute score digits
					int dig[4];

					dig[0] = twopScores[2*s + j]/1000;
					dig[1] = (twopScores[2*s + j]-1000*dig[0])/100;
					dig[2] = (twopScores[2*s + j]-1000*dig[0]-100*dig[1])/10;
					dig[3] = (twopScores[2*s + j]-1000*dig[0]-100*dig[1]-10*dig[2]);

					// Draw result
					int i;
					for(i = 0; i < 4; i++){
						brainwars_p_draw(dig[i], 14, 1, 2, 17 + j*7 + i, 4 + s*3, pal[j]);
					}
				}
			}
			else{
				// Compute score digits
				int dig[4];

				dig[0] = twopScores[2*s]/1000;
				dig[1] = (twopScores[2*s]-1000*dig[0])/100;
				dig[2] = (twopScores[2*s]-1000*dig[0]-100*dig[1])/10;
				dig[3] = (twopScores[2*s]-1000*dig[0]-100*dig[1]-10*dig[2]);

				// Draw result
				int i;
				for(i = 0; i < 4; i++){
					brainwars_p_draw(dig[i], 14, 1, 2, 17 + (twopCurrent%2)*7 + i, 4 + s*3, BLUEPAL);
				}
			}

		}
	}

	if(!((state == ONEP) && (onepCurrent == 2)))brainwars_p_draw(0, 12, 23, 2, 0, 19, NORMALPAL);

	// Activate BG1 of SUB
	while(display < 3);
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER2_CR &= ~(TIMER_ENABLE);
}

// Show game results main function
void brainwars_p_result(){
	// Scan keys
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if(keys & KEY_A){
		// Update state for next step
		if(state == ONEP) onepCurrent++;
		else twopCurrent++;

		// Go to next state in function of current game
		if((state == TWOP) && (twopCurrent > 5)){
			pState = FINAL;
			pStateChange = true;
		} 
		else if((state == ONEP) && (onepCurrent > 2));
		else{
			// Fill screen with grey
			int x, y;

			for(x = 0; x < W; x++){
				for(y = 0; y < H; y++){
					BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = sub_pMap[(PSIDE+1)*PWIM - 1] | (NORMALPAL << 12);
				}
			}

			// Change state
			pState = SHOW;
			pStateChange = true;
		} 
	}
}

// Final screen initialization
void brainwars_p_final_init(){
	// Erase press A
	brainwars_p_draw(0, 12, 23, 2, 0, 19, GREYPAL);

	// Draw total title
	brainwars_p_draw(0, 10, 5, 2, 4, 15, NORMALPAL);

	// Compute totals
	int total[2] = {0, 0};
	int i;

	for(i = 0; i < 2*4; i++) total[i%2] += twopScores[i];

	// Draw totals
	int j;
	int pal[2] = {BLUEPAL, BLUEPAL};

	if(total[0] > total[1]) pal[1] = REDPAL;
	else if(total[0] < total[1]) pal[0] = REDPAL;

	for(j = 0; j < 2; j++){
		// Compute score digits
		int dig[4];

		dig[0] = total[j]/1000;
		dig[1] = (total[j]-1000*dig[0])/100;
		dig[2] = (total[j]-1000*dig[0]-100*dig[1])/10;
		dig[3] = (total[j]-1000*dig[0]-100*dig[1]-10*dig[2]);

		// Draw result
		int i;
		for(i = 0; i < 4; i++){
			brainwars_p_draw(dig[i], 14, 1, 2, 17 + j*7 + i, 15, pal[j]);
		}
	}
}

// Final screen main function
void brainwars_p_final(){
	// Scan keys
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if(keys & KEY_A){
		state = MAIN;
		stateChange = true;
	}
}

// Draw game blocks
void brainwars_p_draw_block(int game, int pos){
	// Draw block
	int x, y;
	int xm, ym;

	xm = game*PSIDE;
	ym = 0;
	for(x = PSTARTX + pos*(PSIDE + PINT); x < PSTARTX + pos*(PSIDE + PINT) + PSIDE; x++){
		for(y = PSTARTY; y < PSTARTY + PSIDE; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = sub_pMap[ym*PWIM + xm] | (NORMALPAL<< 12);
			ym++;
		}
		ym = 0;
		xm++;
	}
}

// Draw selected block in yellow
void brainwars_p_draw_block_sel(int pos){
	// Change the palette of the selected game
	int x, y;

	for(x = PSTARTX + pos*(PSIDE + PINT); x < PSTARTX + pos*(PSIDE + PINT) + PSIDE; x++){
		for(y = PSTARTY; y < PSTARTY + PSIDE; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = BG_MAP_RAM_SUB(BG1MAP)[y*W + x] | (YELLOWPAL<< 12);
		}
	}
}

// Draw results and other infos
void brainwars_p_draw(int xim, int yim, int w, int h, int x, int y, int pal){
	// Change the palette of the selected game
	int col, row;
	int xm, ym;

	xm = xim;
	ym = yim;
	for(col = x; col < x + w; col++){
		for(row = y; row < y + h; row++){
			BG_MAP_RAM_SUB(BG1MAP)[row*W + col] = sub_pMap[ym*PWIM + xm] | (pal << 12);
			ym++;
		}
		ym = yim;
		xm++;
	}
}


/********************************************************************* Scores */
// Initialization
void brainwars_score_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;

	// Copy start image for MAIN screen in BG1 and put correct colors in palette
	swiCopy(main_startTiles, BG_TILE_RAM(BG1TILE), main_startTilesLen/2);
	swiCopy(main_startMap, BG_MAP_RAM(BG1MAP), main_startMapLen);

	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = GREY;
	BG_PALETTE[0x05] = BLACK;

	// Copy tiles
	swiCopy(sub_scoreTiles, BG_TILE_RAM_SUB(BG1TILE), sub_scoreTilesLen/2);

	// Put correct colors in palettes
	BG_PALETTE_SUB[0x11] = RED;
	BG_PALETTE_SUB[0x12] = BLUE;
	BG_PALETTE_SUB[0x13] = GREEN;
	BG_PALETTE_SUB[0x14] = YELLOW;
	BG_PALETTE_SUB[0x15] = WHITE;
	BG_PALETTE_SUB[0x16] = GREY;
	BG_PALETTE_SUB[0x17] = BLACKGREY;
	BG_PALETTE_SUB[0x18] = BLACK;

	BG_PALETTE_SUB[0x21] = RED;
	BG_PALETTE_SUB[0x22] = BLUE;
	BG_PALETTE_SUB[0x23] = GREEN;
	BG_PALETTE_SUB[0x24] = GREEN;
	BG_PALETTE_SUB[0x25] = WHITE;
	BG_PALETTE_SUB[0x26] = GREY;
	BG_PALETTE_SUB[0x27] = BLACKGREY;
	BG_PALETTE_SUB[0x28] = BLACK;

	// Create map
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = sub_scoreMap[y*W + x] | (YELLOWPAL << 12);
		}
	}

	// Draw score of each game
	int i, j;

	int score;
	int palette = GREENPAL;

	int digit[4];

	int row, col;
	int xstart = 7;		// x start on screen
	int ystart = 2;		// y start on screen
	int ystim = 24;		// y start in image
	int D = 15;			// distance between scores of the two columns
	int l = 2;			// length of one number
	int h = 5;			// height of one number

	int xinit, yinit;

	for(i = 0; i < 7; i++){
		row = i/2;
		col = i%2;

		// Get new score
		switch(i){
		case 0: score = info_get_score(LEADER); break;
		case 1: score = info_get_score(EATIT); break;
		case 2: score = info_get_score(MUSICAL); break;
		case 3: score = info_get_score(PATH); break;
		case 4: score = info_get_score(ADDITION); break;
		case 5: score = info_get_score(PLUSMINUS); break;
		case 6: score = info_get_score(JANKENPON); break;
		}

		// Check if higher then old score
		if(score > scores[i]){
			scores[i] = score;
			palette = GREENPAL;
		}
		else palette = YELLOWPAL;

		// Compute digits of number
		digit[0] = score/1000;
		digit[1] = (score-1000*digit[0])/100;
		digit[2] = (score-1000*digit[0]-100*digit[1])/10;
		digit[3] = (score-1000*digit[0]-100*digit[1]-10*digit[2]);

		// Display digits
		yinit = ystart+row*h;

		for(j= 0;j < 4;j++){
			xinit = xstart+col*D+j*l;

			for(x = xinit; x < xinit + l; x++){
				for(y = yinit; y < yinit + 1*h; y++){
					BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = sub_scoreMap[(y - yinit + ystim)*W + (x-xinit) + digit[j]*l] | (palette<<12);
				}
			}
		}
	}

	// Wait 1s before activating BG1
	while(display < PAUSE*TIMERF);
	swiWaitForVBlank();
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER2_CR &= ~(TIMER_ENABLE);
}

// Wait for exit
void brainwars_score(void){
	// Scan keys
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if(keys & KEY_START){
		state = MAIN;
		stateChange = true;
	}
}


/******************************************************************** Credits */
// Initialization
void brainwars_credits_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER2_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;

	// Copy start image for MAIN screen in BG1 and put correct colors in palette
	swiCopy(main_startTiles, BG_TILE_RAM(BG1TILE), main_startTilesLen/2);
	swiCopy(main_startMap, BG_MAP_RAM(BG1MAP), main_startMapLen);

	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = GREY;
	BG_PALETTE[0x05] = BLACK;

	// Copy tiles
	swiCopy(sub_creditsTiles, BG_TILE_RAM_SUB(BG1TILE), sub_creditsTilesLen/2);

	// Set palette colors
	BG_PALETTE_SUB[0x01] = RED;
	BG_PALETTE_SUB[0x02] = BLUE;
	BG_PALETTE_SUB[0x03] = GREEN;
	BG_PALETTE_SUB[0x04] = YELLOW;
	BG_PALETTE_SUB[0x05] = GREY;
	BG_PALETTE_SUB[0x06] = BLACK;

	// Create map
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(BG1MAP)[y*W + x] = sub_creditsMap[y*W + x];
		}
	}

	// Wait 1s before activating BG1
	while(display < PAUSE*TIMERF);
	swiWaitForVBlank();
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER2_CR &= ~(TIMER_ENABLE);
}

// Wait for exit
void brainwars_credits(){
	// Scan keys
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if(keys & KEY_START){
		state = MAIN;
		stateChange = true;
	}
}