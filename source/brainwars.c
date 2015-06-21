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
#include "oneplayer.h"
#include "sub_score.h"
#include "sub_credits.h"

// Other
#include "score.h"


/****************************************************************** Constants */


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

// Training state
GAME oldgame;
GAME game;
GAME selectTrain;
bool gameChange;

// 1p and 2p state
int gameCounter;
int timeCounter;
bool twoPlayers;
bool gamePlayer;

// Score
int scores[7];


/***************************************************************** Timer ISRs */
// Display timer
void brainwars_timer_ISR3(){
	display++;
}

// 1p and 2p ISR
void brainwars_timer_ISR(){
	timeCounter--;
}


/********************************************************************** Start */
// Initialize NDS
void brainwars_start_init(){
	// Initialize score saving in text files
	fatInitDefault();

	// Read saved best scores in files to initialize scores array
	scores[0] = info_get_score("leader");
	scores[1] = info_get_score("eatit");
	scores[2] = info_get_score("musical");
	scores[3] = info_get_score("path");
	scores[4] = info_get_score("addition");
	scores[5] = info_get_score("plusminus");
	scores[6] = info_get_score("jankenpon");

	// Initialize sound
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad(MOD_AURORA);
	mmLoadEffect(SFX_DO);
	mmLoadEffect(SFX_BOING);
	mmLoadEffect(SFX_DUM_DUM);
	mmLoadEffect(SFX_OULALA);

	// Initialize timer for background change
	TIMER3_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ;
	TIMER3_DATA = TIMER_FREQ_1024(TIMER3F);

	irqSet(IRQ_TIMER3, &brainwars_timer_ISR3);
	irqEnable(IRQ_TIMER3);

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
	BGCTRL[0] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(MAINBG0TILE) | BG_MAP_BASE(MAINBG0MAP);

	// BG1 will be used to display main graphics
	BGCTRL[1] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(MAINBG1TILE) | BG_MAP_BASE(MAINBG1MAP);

	// BG2 will be used to display grey background for inter panel pause
	BGCTRL[2] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(MAINBG2TILE) | BG_MAP_BASE(MAINBG2MAP);

	// Load image in BG2 which will never change (just grey background) and use
	// palette 15 to put grey in it
	swiCopy(loadT, (u8*)BG_TILE_RAM(MAINBG2TILE), 8*8*4/8/2);

	BG_PALETTE[0xf1] = GREY;

	int row, col;
	for(row = 0; row < H; row++){
		for(col = 0; col < W; col++){
			BG_MAP_RAM(MAINBG2MAP)[row*W+col] = 0 | (15<<12);
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
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(SUBBG0TILE) | BG_MAP_BASE(SUBBG0MAP);

	// BG1 will be used to display main graphics
	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(SUBBG1TILE) | BG_MAP_BASE(SUBBG1MAP);

	// BG2 will be used to display grey background for inter panel pause
	BGCTRL_SUB[2] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(SUBBG2TILE) | BG_MAP_BASE(SUBBG2MAP);

	// Load image in BG2 which will never change (just grey background) and use
	// palette 15 to put grey in it
	swiCopy(loadT, (u8*)BG_TILE_RAM_SUB(SUBBG2TILE), 8*8*4/8/2);

	BG_PALETTE_SUB[0xf1] = GREY;

	int row, col;
	for(row = 0; row < H; row++){
		for(col = 0; col < W; col++){
			BG_MAP_RAM_SUB(SUBBG2MAP)[row*W+col] = 0 | (15<<12);
		}
	}
}

// Start
void brainwars_start(){
	// Launch timer for panel change pause
	display = 0;
	TIMER3_CR |= TIMER_ENABLE;

	// Activate BG2 for grey background
	swiWaitForVBlank();
	REG_DISPCNT |= DISPLAY_BG2_ACTIVE;
	REG_DISPCNT_SUB |= DISPLAY_BG2_ACTIVE;

	// Copy start image for MAIN screen in BG1 and put correct colors in palette
	swiCopy(main_startTiles, BG_TILE_RAM(MAINBG1TILE), main_startTilesLen/2);
	swiCopy(main_startMap, BG_MAP_RAM(MAINBG1MAP), main_startMapLen);

	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = GREY;
	BG_PALETTE[0x05] = BLACK;

	// Copy start image for SUB screen in BG1 and put correct colors in palette
	swiCopy(sub_startTiles, BG_TILE_RAM_SUB(SUBBG1TILE), sub_startTilesLen/2);
	swiCopy(sub_startMap, BG_MAP_RAM_SUB(SUBBG1MAP), sub_startMapLen);

	BG_PALETTE_SUB[0x01] = GREY;
	BG_PALETTE_SUB[0x02] = BLACK;

	// Display title on MAIN after 0.6 seconds
	while(display < 0.6*TIMER3F);
	swiWaitForVBlank();
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;
	mmEffect(SFX_DUM_DUM);

	// Wait more 0.6s before continuing
	while(display < 1.2*TIMER3F);

	// Scan touch screen to see if it was taped and if yes, use x and y to
	// initialize the random seed
	bool wait = true;
	bool instr = true;
	display = 0;

	while(wait){
		// Create instructions blinking effect (0.8s)
		if((display % (int)(0.8*TIMER3F)) == 0){
			swiWaitForVBlank();
			if(instr) REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;
			else REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

			instr = !instr;
		}

		// Scan touch screen and if touch screen was touched, check for position
		touchPosition touch;
		scanKeys();
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

	// Stop timer
	TIMER3_CR &= ~(TIMER_ENABLE);

	// Initialize game music that will play all the time
	//mmStart(MOD_AURORA, MM_PLAY_LOOP);
	//mmSetModuleVolume(350);

	// Launch main menu
	brainwars_main_init();
}


/****************************************************************** Main menu */
// Initialization
void brainwars_main_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER3_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to memory
	swiWaitForVBlank();
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy main menu image in BG1 for MAIN screen and put correct colors in
	// palette
	swiCopy(main_menuTiles, BG_TILE_RAM(MAINBG1TILE), main_menuTilesLen/2);

	// Put correct colors in palette (see color index in Photoshop)
	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = GREY;
	BG_PALETTE[0x05] = BLACK;

	// Copy main menu image in BG1 for SUB screen and put correct colors in
	// palette
	swiCopy(sub_menuTiles, BG_TILE_RAM_SUB(SUBBG1TILE), sub_menuTilesLen/2);

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
	while(display < PAUSE*TIMER3F)
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER3_CR &= ~(TIMER_ENABLE);
}

// Main function
void brainwars_main(){
	// Check if state changed an initialize module in function of new state
	if(stateChange){
		switch(state){
		case MAIN: brainwars_main_init(); break;
		case TRAIN: brainwars_train_init(); break;
		case ONEP: brainwars_1p_init(); break;
		case TWOP: brainwars_2p_init(); break;
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
	case ONEP: brainwars_play(); break;
	case TWOP: brainwars_play(); break;
	case SCORE: brainwars_score(); break;
	case CREDITS: brainwars_credits(); break;
	default: break;
	}
}

// Selection in main menu
void brainwars_main_select(){
	// Scan keys and touchscreen
	scanKeys();
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
			int ystart = 21, inter = 11, h = 21;

			if((touch.py >= ystart) && (touch.py <= ystart+h)) option = TRAIN;
			if((touch.py >= ystart+inter+h) && (touch.py <= ystart+inter+2*h)) option = ONEP;
			if((touch.py >= ystart+2*inter+2*h) && (touch.py <= ystart+2*inter+3*h)) option = TWOP;
			if((touch.py >= ystart+3*inter+3*h) && (touch.py <= ystart+3*inter+4*h)) option = SCORE;
			if((touch.py >= ystart+4*inter+4*h) && (touch.py <= ystart+4*inter+5*h)) option = CREDITS;
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
			BG_MAP_RAM(MAINBG1MAP)[y*W + x] = main_menuMap[(y + (selectMain-1)*H)*W + x];
		}
	}

	// Draw menu on SUB screen BG1
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(SUBBG1MAP)[y*W+x] = sub_menuMap[y*W+x];
		}
	}

	// Change color of the selected button
	int YS = 2, BH = 4;

	for(x = 0; x < W; x++){
		for(y = (selectMain-1)*BH + YS; y < selectMain*BH + YS; y++){
			BG_MAP_RAM_SUB(SUBBG1MAP)[y*W+x] = BG_MAP_RAM_SUB(SUBBG1MAP)[y*W+x]|(1<<12);
		}
	}
}


/***************************************************************** Train menu */
void brainwars_train_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER3_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT &= ~DISPLAY_BG1_ACTIVE;
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy train menu tiles and palette for BG1 of MAIN screen
	swiCopy(main_expTiles, BG_TILE_RAM(MAINBG1TILE), main_expTilesLen/2);

	BG_PALETTE[0x01] = RED;
	BG_PALETTE[0x02] = BLUE;
	BG_PALETTE[0x03] = GREEN;
	BG_PALETTE[0x04] = YELLOW;
	BG_PALETTE[0x05] = WHITE;
	BG_PALETTE[0x06] = GREY;
	BG_PALETTE[0x07] = BLACKGREY;
	BG_PALETTE[0x08] = BLACK;

	// Copy tiles and palette for BG1 of SUB screen
	swiCopy(sub_trainTiles, BG_TILE_RAM_SUB(SUBBG1TILE), sub_trainTilesLen/2);

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
	game = NOGAME;
	selectTrain = LEADER;
	gameChange = false;

	// Draw training menu for the first time
	brainwars_train_draw();

	// Wait 1s before activating BG1
	while(display < PAUSE*TIMER3F)
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;
	REG_DISPCNT |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER3_CR &= ~(TIMER_ENABLE);
}

void brainwars_train(){
	// Check in which game we are training
	switch(game){
	case LEADER:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			leader_init(state);
		}

		// Execute action of game
		gameChange = leader_game(0,0);

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			leader_reset();
		}

		break;
	case EATIT:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			eatit_init(state);
		}

		// Execute action of game
		gameChange = eatit_game(0,0);

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			eatit_reset();
		}

		break;
	case MUSICAL:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			musical_init(state);
		}

		// Execute action of game
		gameChange = musical_game(0,0);

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			musical_reset();
		}

		break;
	case PATH:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			path_init(state);
		}

		// Execute action of game
		gameChange = path_game(0,0);

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			path_reset();
		}

		break;
	case ADDITION:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			addition_init(state);
		}

		// Execute action of game
		gameChange = addition_game(0,0);

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			addition_reset();
		}

		break;
	case PLUSMINUS:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			plusminus_init(state);
		}

		// Execute action of game
		gameChange = plusminus_game(0,0);

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			plusminus_reset();
		}

		break;
	case JANKENPON:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			jankenpon_init(state);
		}

		// Execute action of game
		gameChange = jankenpon_game(0,0);

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			jankenpon_reset();
		}

		break;
	case NOGAME:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			brainwars_train_init();
		}

		// Execute action of state
		brainwars_train_select();

		break;
	default:
		break;
	}
}

void brainwars_train_select(){
	// Save current selected button for drawing
	int prevSelect = selectTrain;

	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Check if right key pressed
	if(keys & KEY_RIGHT) selectTrain = (selectTrain+1)%8;

	// Check if left key pressed
	if(keys & KEY_LEFT) selectTrain = (selectTrain+7)%8;

	// Check if down key pressed
	if(keys & KEY_DOWN) selectTrain = (selectTrain+3)%8;

	// Check if up key pressed
	if(keys & KEY_UP) selectTrain = (selectTrain+5)%8;

	// Check if start key pressed
	if(keys & KEY_A){
		// Update game state
		game = selectTrain;
		gameChange = true;

		// Exit case
		if(game == NOGAME){
			state = MAIN;
			stateChange = true;
		}
	}

	// Check if touchscreen was touched
	GAME touched = -1;
	touchPosition touch;
	touchRead(&touch);

	if(keys & KEY_TOUCH){
		int xstart = 49;
		int ystart = 22;
		int interx = 18;
		int intery = 15;
		int side = 40;

		int i;
		int row, col;
		int x1, x2, y1, y2;

		// Loop on the games square position
		for(i=0;i<8;i++){
			row = i/3;
			col = i%3;

			x1 = xstart + col*side + col*interx;
			x2 = x1 + side;
			y1 = ystart + row*side + row*intery;
			y2 = y1 + side;

			if((touch.px>=x1)&&(touch.px<=x2)&&(touch.py>=y1)&&(touch.py<=y2))
				touched = i;
		}

		if(touched!=-1){
			if(touched==selectTrain){
				// Update game state
				game = selectTrain;
				gameChange = true;

				// Exit case
				if(game == NOGAME){
					state = MAIN;
					stateChange = true;
				}
			}
			else selectTrain = touched;
		}
	}

	// Check if start pressed
	if(keys & KEY_START){
		state = MAIN;
		stateChange = true;
	}

	// Draw updates only if something has changed
	if(prevSelect != selectTrain) brainwars_train_draw();
}

void brainwars_train_draw(){
	// Draw instructions on MAIN screen
	int x, y;

	swiWaitForVBlank();
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM(MAINBG1MAP)[y*W + x] = main_expMap[(y + selectTrain*H)*W + x];
		}
	}

	// Draw training menu on SUB screen
	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(SUBBG1MAP)[y*W+x] = sub_trainMap[y*W+x];
		}
	}

	// Change color of the selected button
	int XS = 6;
	int YS= 2;
	int INTER = 1;
	int SIDE = 6;

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
			BG_MAP_RAM_SUB(SUBBG1MAP)[y*W+x] = BG_MAP_RAM_SUB(SUBBG1MAP)[y*W+x]|(1<<12);
		}
	}
}

void brainwars_1p_init(){
	// Initialize global variables
	game = NOGAME;
	oldgame = NOGAME;
	gameCounter = 2;
	gameChange = true;
	twoPlayers = false;
	gamePlayer = 0;
}

void brainwars_2p_init(){
	// Initialize global variables
	game = NOGAME;
	oldgame = NOGAME;
	gameCounter = 0;
	gameChange = true;
	twoPlayers = true;
	gamePlayer = 0;

}

void brainwars_next_game(){
	// Find next game randomly
	int next_game;

	next_game = rand()%7;
	while(oldgame == next_game) {	next_game = rand()%7; }

	game = next_game;
	oldgame = next_game;

}

void brainwars_wait_next(){
	// Copy image to memory
	swiCopy(oneplayerTiles, BG_TILE_RAM_SUB(1), oneplayerTilesLen/2);
	swiCopy(oneplayerPal, BG_PALETTE_SUB, oneplayerPalLen/2);

	// Draw Initial Field
	int x,y;
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*32+x] = oneplayerMap[y*80+x];
		}
	}

	// Initiate timer for game start
	timeCounter = 5;

	TIMER3_DATA = TIMER_FREQ_1024(1);
	TIMER3_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;

	irqSet(IRQ_TIMER3, &brainwars_timer_ISR);
	irqEnable(IRQ_TIMER3);

	// Display number for game start counting
	while(timeCounter > 0) {
		for(x=12; x<20; x++){
			for(y=10; y<21; y++){
				BG_MAP_RAM_SUB(0)[y*32+x] = oneplayerMap[(y-10+24)*80+(x-12+(timeCounter*8))];
			}
		}
	}

	// Disable timers
	irqDisable(IRQ_TIMER3);
	irqClear(IRQ_TIMER3);
	TIMER3_CR = 0;
}

void brainwars_play(){
	// Check in which game we are playing
	switch(game){
	case LEADER:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			//swiCopy(exp_leaderBitmap, BG_GFX, exp_leaderBitmapLen/2);
			//swiCopy(exp_leaderPal, BG_PALETTE, exp_leaderPalLen/2);
			brainwars_wait_next();
			leader_init(state);
		}

		// Execute action of game
		gameChange = leader_game(gamePlayer, gameCounter);

		// Check if game ended
		if(gameChange){
			leader_reset();
			if(twoPlayers) {
				if(gamePlayer) 	{ game = NOGAME; }
				else			{ gamePlayer = PLAYERTWO;}
			}
			else				{ game = NOGAME; }
		}

		break;
	case EATIT:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			//swiCopy(exp_eatitBitmap, BG_GFX, exp_eatitBitmapLen/2);
			//swiCopy(exp_eatitPal, BG_PALETTE, exp_eatitPalLen/2);
			brainwars_wait_next();
			eatit_init(state);
		}

		// Execute action of game
		gameChange = eatit_game(gamePlayer, gameCounter);

		// Check if game ended
		if(gameChange){
			eatit_reset();
			if(twoPlayers) {
				if(gamePlayer) 	{ game = NOGAME; }
				else			{ gamePlayer = PLAYERTWO;}
			}
			else				{ game = NOGAME; }
		}

		break;
	case MUSICAL:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			//swiCopy(exp_musicalBitmap, BG_GFX, exp_musicalBitmapLen/2);
			//swiCopy(exp_musicalPal, BG_PALETTE, exp_musicalPalLen/2);
			brainwars_wait_next();
			musical_init(state);
		}

		// Execute action of game
		gameChange = musical_game(gamePlayer, gameCounter);

		// Check if game ended
		if(gameChange){
			musical_reset();
			if(twoPlayers) {
				if(gamePlayer) 	{ game = NOGAME; }
				else			{ gamePlayer = PLAYERTWO;}
			}
			else				{ game = NOGAME; }
		}

		break;
	case PATH:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			//swiCopy(exp_pathBitmap, BG_GFX, exp_pathBitmapLen/2);
			//swiCopy(exp_pathPal, BG_PALETTE, exp_pathPalLen/2);
			brainwars_wait_next();
			path_init(state);
		}

		// Execute action of game
		gameChange = path_game(gamePlayer, gameCounter);

		// Check if game ended
		if(gameChange){
			path_reset();
			if(twoPlayers) {
				if(gamePlayer) 	{ game = NOGAME; }
				else			{ gamePlayer = PLAYERTWO;}
			}
			else				{ game = NOGAME; }
		}

		break;
	case ADDITION:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			//swiCopy(exp_additionBitmap, BG_GFX, exp_additionBitmapLen/2);
			//swiCopy(exp_additionPal, BG_PALETTE, exp_additionPalLen/2);
			brainwars_wait_next();
			addition_init(state);
		}

		// Execute action of game
		gameChange = addition_game(gamePlayer, gameCounter);

		// Check if game ended
		if(gameChange){
			addition_reset();
			if(twoPlayers) {
				if(gamePlayer) 	{ game = NOGAME; }
				else			{ gamePlayer = PLAYERTWO;}
			}
			else				{ game = NOGAME; }
		}

		break;
	case PLUSMINUS:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			//swiCopy(exp_plusminusBitmap, BG_GFX, exp_plusminusBitmapLen/2);
			//swiCopy(exp_plusminusPal, BG_PALETTE, exp_plusminusPalLen/2);
			brainwars_wait_next();
			plusminus_init(state);
		}

		// Execute action of game
		gameChange = plusminus_game(gamePlayer, gameCounter);

		// Check if game ended
		if(gameChange){
			plusminus_reset();
			if(twoPlayers) {
				if(gamePlayer) 	{ game = NOGAME; }
				else			{ gamePlayer = PLAYERTWO;}
			}
			else				{ game = NOGAME; }
		}

		break;
	case JANKENPON:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			//swiCopy(exp_jankenponBitmap, BG_GFX, exp_jankenponBitmapLen/2);
			//swiCopy(exp_jankenponPal, BG_PALETTE, exp_jankenponPalLen/2);
			brainwars_wait_next();
			jankenpon_init(state);
		}

		// Execute action of game
		gameChange = jankenpon_game(gamePlayer, gameCounter);

		// Check if game ended
		if(gameChange){
			jankenpon_reset();
			if(twoPlayers) {
				if(gamePlayer) 	{ game = NOGAME; }
				else			{ gamePlayer = PLAYERTWO;}
			}
			else				{ game = NOGAME; }
		}

		break;
	case NOGAME:
		// Check if game just changed
		gamePlayer = PLAYERONE;

		if(gameCounter >= 3){

			info_draw_final_score(state);
			state = MAIN;
			stateChange = true;
		}
		else {
			gameCounter++;
			brainwars_next_game();
		}

		break;
	default:
		break;
	}
}

void brainwars_score_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER3_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy map
	swiCopy(sub_scoreTiles, BG_MAP_RAM_SUB(SUBBG1TILE), sub_scoreTilesLen/2);

	// Put correct colors in palettes
	BG_PALETTE_SUB[0x01] = RED;
	BG_PALETTE_SUB[0x02] = BLUE;
	BG_PALETTE_SUB[0x03] = GREEN;
	BG_PALETTE_SUB[0x04] = YELLOW;
	BG_PALETTE_SUB[0x05] = WHITE;
	BG_PALETTE_SUB[0x06] = GREY;
	BG_PALETTE_SUB[0x07] = BLACKGREY;
	BG_PALETTE_SUB[0x08] = BLACK;

	BG_PALETTE_SUB[0x11] = RED;
	BG_PALETTE_SUB[0x12] = BLUE;
	BG_PALETTE_SUB[0x13] = GREEN;
	BG_PALETTE_SUB[0x14] = GREEN;
	BG_PALETTE_SUB[0x15] = WHITE;
	BG_PALETTE_SUB[0x16] = GREY;
	BG_PALETTE_SUB[0x17] = BLACKGREY;
	BG_PALETTE_SUB[0x18] = BLACK;

	// Create map
	int x, y;

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			BG_MAP_RAM_SUB(SUBBG1MAP)[y*W + x] = sub_scoreMap[y*W + x];
		}
	}

	// Draw score of each game
	int i, j;

	int score;
	int palette = 0;

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
		case 0: score = info_get_score("leader"); break;
		case 1: score = info_get_score("eatit"); break;
		case 2: score = info_get_score("musical"); break;
		case 3: score = info_get_score("path"); break;
		case 4: score = info_get_score("addition"); break;
		case 5: score = info_get_score("plusminus"); break;
		case 6: score = info_get_score("jankenpon"); break;
		}

		// Check if higher then old score
		if(score > scores[i]){
			scores[i] = score;
			palette = 1;
		}
		else palette = 0;

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
					BG_MAP_RAM_SUB(SUBBG1MAP)[y*W + x] = sub_scoreMap[(y - yinit + ystim)*W + (x-xinit) + digit[j]*l] | (palette<<12);
				}
			}
		}
	}

	// Wait 1s before activating BG1
	while(display < PAUSE*TIMER3F)
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER3_CR &= ~(TIMER_ENABLE);
}

void brainwars_score(void){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if(keys & KEY_START){
		state = MAIN;
		stateChange = true;
	}
}

void brainwars_credits_init(){
	// Launch timer to create 1s pause
	display = 0;
	TIMER3_CR |= TIMER_ENABLE;

	// Inactivate BG1 while copying new images to  memory
	swiWaitForVBlank();
	REG_DISPCNT_SUB &= ~DISPLAY_BG1_ACTIVE;

	// Copy tiles
	swiCopy(sub_creditsTiles, BG_TILE_RAM_SUB(SUBBG1TILE), sub_creditsTilesLen/2);

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
			BG_MAP_RAM_SUB(SUBBG1MAP)[y*W + x] = sub_creditsMap[y*W + x];
		}
	}

	// Wait 1s before activating BG1
	while(display < PAUSE*TIMER3F)
	swiWaitForVBlank();
	REG_DISPCNT_SUB |= DISPLAY_BG1_ACTIVE;

	// Stop timer
	TIMER3_CR &= ~(TIMER_ENABLE);
}

void brainwars_credits(){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if(keys & KEY_START){
		state = MAIN;
		stateChange = true;
	}
}                                                           
