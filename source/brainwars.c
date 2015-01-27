/*
 * brainwars.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati & Nawaaz GS
 *
 */

#include "general.h"
#include "brainwars.h"
#include "info.h"

#include "brainwars_main.h"
#include "brainwars_train.h"
#include "start.h"

#include "title.h"

#include "score.h"
#include "exp_leader.h"
#include "exp_eatit.h"
#include "exp_path.h"
#include "exp_jankenpon.h"
#include "exp_musical.h"
#include "exp_addition.h"
#include "exp_plusminus.h"
#include "exp_onep.h"
#include "exp_twop.h"

#include "oneplayer.h"

#include "leader.h"
#include "eatit.h"
#include "musical.h"
#include "path.h"
#include "addition.h"
#include "plusminus.h"
#include "jankenpon.h"

#include "bestscores.h"

#include "credits.h"

STATE state;
STATE selectMain;
bool stateChange;

static volatile int gameCounter;
static volatile int timeCounter;

static volatile bool twoPlayers;
static volatile bool gamePlayer;

GAME game;
GAME selectTrain;
bool gameChange;

int scores[7];

void brainwars_timer_ISR(){
	timeCounter--;
}

void brainwars_init(){
	// Init score saving
	fatInitDefault();

	// Read initial best scores
	scores[0] = info_get_score("leader");
	scores[1] = info_get_score("eatit");
	scores[2] = info_get_score("musical");
	scores[3] = info_get_score("path");
	scores[4] = info_get_score("addition");
	scores[5] = info_get_score("plusminus");
	scores[6] = info_get_score("jankenpon");

	// Initialize game state
	state = MAIN;
	stateChange = false;

	// Configure main and sub engines for graphics
	brainwars_configMain();
	brainwars_configSub();

	// Initialize main menu
	brainwars_main_init();
}

void brainwars_start_draw(){
	int x, y;
	int L = 32;	// length of the image

	swiCopy(startTiles, BG_TILE_RAM_SUB(1), startTilesLen/2);
	swiCopy(startPal, BG_PALETTE_SUB, startPalLen/2);


	// Draw start screen
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*L+x] = startMap[y*L+x];
		}
	}

	touchPosition touch;
	x = 1;
	scanKeys();
	u16 keys = keysDown();
	if(keys & KEY_TOUCH) {	touchRead(&touch); }

	while(x){

		if(keys & KEY_TOUCH) {	touchRead(&touch); }

		if((keys & KEY_TOUCH) &&
		   (touch.px > 0) &&
		   (touch.py > 0)) {
			// Initialize random number generation
			srand(touch.px + touch.py);
			x = 0;
		}
		else {
			scanKeys();
			keys = keysDown();
		}
	}

	swiCopy(brainwars_mainTiles, BG_TILE_RAM_SUB(1), brainwars_mainTilesLen/2);

	swiCopy(brainwars_mainPal, BG_PALETTE_SUB, brainwars_mainPalLen/2);
	swiCopy(brainwars_mainPal, &BG_PALETTE_SUB[16], brainwars_mainPalLen);

	// Set up palette colors
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[5] = BLACKVAL;
	BG_PALETTE_SUB[6] = GREYVAL;

	BG_PALETTE_SUB[17] = YELLOWVAL;
	BG_PALETTE_SUB[21] = BLACKVAL;
	BG_PALETTE_SUB[22] = GREYVAL;

	brainwars_main_draw();
}

void brainwars_configMain(){
	// General
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE;

	// Background 0 will always be used with same image
	BGCTRL[0] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(5) | BG_MAP_BASE(25);
	swiCopy(scoreTiles, BG_TILE_RAM(5), scoreTilesLen/2);
	swiCopy(scorePal, BG_PALETTE, scorePalLen/2);

	int x, y;
	for(x=0;x<32;x++){
		for(y=0;y<24;y++){
			BG_MAP_RAM(25)[y*32 + x] = 0;
		}
	}

	// Background 2 mode
	BGCTRL[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;

	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;
}

void brainwars_configSub(){
	// Memory, mode and active background
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE;

	// Background 0 configuration
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;
}

void brainwars_main_init(){
	// Copy bitmap and its palette for BG2 in main
	swiCopy(titleBitmap, BG_GFX, titleBitmapLen/2);
	swiCopy(titlePal, BG_PALETTE, titlePalLen/2);

	// Copy tiles and palette for BG0 in sub
	swiCopy(brainwars_mainTiles, BG_TILE_RAM_SUB(1), brainwars_mainTilesLen/2);
	swiCopy(brainwars_mainPal, BG_PALETTE_SUB, brainwars_mainPalLen/2);
	swiCopy(brainwars_mainPal, &BG_PALETTE_SUB[16], brainwars_mainPalLen/2);

	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[5] = BLACKVAL;
	BG_PALETTE_SUB[6] = GREYVAL;

	BG_PALETTE_SUB[17] = YELLOWVAL;
	BG_PALETTE_SUB[21] = BLACKVAL;
	BG_PALETTE_SUB[22] = GREYVAL;

	// Initialize selection variable
	selectMain = TRAIN;

	// Draw main menu
	brainwars_main_draw();
}

void brainwars_main(){
	// Check in which state the game is
	switch(state){
	case MAIN:
		// Check if state just changed
		if(stateChange){
			stateChange = false;
			brainwars_main_init();
		}

		// Execute action of the state
		brainwars_main_select();

		break;
	case TRAIN:
		// Check if state just changed
		if(stateChange){
			stateChange = false;
			brainwars_train_init();
		}

		// Execute action of state
		brainwars_train();

		break;
	case ONEP:
		// Check if state just changed
		if(stateChange){
			stateChange = false;
			brainwars_1p_init();
		}

		// Execute action of state
		brainwars_play();

		break;
	case TWOP:
		if(stateChange){
			stateChange = false;
			brainwars_2p_init();
		}

		brainwars_play();

		break;
	case SCORE:
		// Check if state just changed
		if(stateChange){
			stateChange = false;
			brainwars_score_init();
		}

		// Execute action of state
		brainwars_score();

		break;
	case CREDITS:
		// Check if state just changed
		if(stateChange){
			stateChange = false;
			brainwars_credits_init();
		}

		// Execute action of state
		brainwars_credits();
		break;
	default:
		break;
	}
}

void brainwars_main_select(){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Check if up key pressed
	if(keys & KEY_UP){
		// Update selected button
		if(selectMain==TRAIN) selectMain = CREDITS;
		else selectMain--;
	}

	// Check if down key pressed
	if(keys & KEY_DOWN){
		// Update selected button
		if(selectMain==CREDITS) selectMain = TRAIN;
		else selectMain++;
	}

	// Check if start key pressed
	if(keys & KEY_A){
		// Update game state
		state = selectMain;
		stateChange = true;
	}

	// Check if touchscreen was touched
	STATE touched = -1;
	touchPosition touch;
	touchRead(&touch);

	if(keys&KEY_TOUCH){
		if((touch.px>=39)&&(touch.px<=215)){
			int ystart = 21;
			int inter = 11;
			int h = 21;

			if((touch.py>=ystart)&&(touch.py<=ystart+h)) touched = TRAIN;
			if((touch.py>=ystart+inter+h)&&(touch.py<=ystart+inter+2*h)) touched = ONEP;
			if((touch.py>=ystart+2*inter+2*h)&&(touch.py<=ystart+2*inter+3*h)) touched = TWOP;
			if((touch.py>=ystart+3*inter+3*h)&&(touch.py<=ystart+3*inter+4*h)) touched = SCORE;
			if((touch.py>=ystart+4*inter+4*h)&&(touch.py<=ystart+4*inter+5*h)) touched = CREDITS;

			if(touched!=-1){
				if(touched==selectMain){
					// Update game state
					state = selectMain;
					stateChange = true;
				}
				else selectMain = touched;
			}
		}
	}

	// Draw updates
	brainwars_main_draw();
}

void brainwars_main_draw(){
	// Put mode instructions on MAIN screen
	switch(selectMain){
	case ONEP:
		swiCopy(exp_onepBitmap, BG_GFX, exp_onepBitmapLen/2);
		swiCopy(exp_onepPal, BG_PALETTE, exp_onepPalLen/2);
		break;
	case TWOP:
		swiCopy(exp_twopBitmap, BG_GFX, exp_twopBitmapLen/2);
		swiCopy(exp_twopPal, BG_PALETTE, exp_twopPalLen/2);
		break;
	default:
		swiCopy(titleBitmap, BG_GFX, titleBitmapLen/2);
		swiCopy(titlePal, BG_PALETTE, titlePalLen/2);
		break;
	}

	// Draw menu
	int x, y;
	int ystart = 2;
	int height = 4;
	int L = 32;			// length of the image

	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*L+x] = brainwars_mainMap[y*L+x];
		}
	}

	// Change color of the selected button
	for(x=0; x<32; x++){
		for(y=(selectMain-1)*height+ystart; y<selectMain*height+ystart; y++){
			BG_MAP_RAM_SUB(0)[y*L+x] = BG_MAP_RAM_SUB(0)[y*L+x]|(1<<12);
		}
	}
}

void brainwars_train_init(){
	// Copy bitmap and palette for BG2 in main
	swiCopy(exp_leaderBitmap, BG_GFX, exp_leaderBitmapLen/2);
	swiCopy(exp_leaderPal, BG_PALETTE, exp_leaderPalLen/2);

	// Copy tiles and palette for BG0 in sub
	swiCopy(brainwars_trainTiles, BG_TILE_RAM_SUB(1), brainwars_trainTilesLen/2);
	swiCopy(brainwars_trainPal, BG_PALETTE_SUB, brainwars_trainPalLen/2);
	swiCopy(brainwars_trainPal, &BG_PALETTE_SUB[16], brainwars_trainPalLen/2);

	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[5] = REDVAL;
	BG_PALETTE_SUB[6] = BLUEVAL;
	BG_PALETTE_SUB[7] = GREENVAL;
	BG_PALETTE_SUB[8] = BLACKVAL;
	BG_PALETTE_SUB[9] = GREYVAL;

	BG_PALETTE_SUB[17] = YELLOWVAL;
	BG_PALETTE_SUB[21] = REDVAL;
	BG_PALETTE_SUB[22] = BLUEVAL;
	BG_PALETTE_SUB[23] = GREENVAL;
	BG_PALETTE_SUB[24] = BLACKVAL;
	BG_PALETTE_SUB[25] = GREYVAL;

	// Initialize variables
	game = NOGAME;
	selectTrain = NOGAME;
	gameChange = false;

	// Draw training menu
	brainwars_train_draw();

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

	if(keys&KEY_TOUCH){
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

	// Draw updates
	brainwars_train_draw();
}

void brainwars_train_draw(){
	// Draw instructions on main
	switch(selectTrain){
	case LEADER:
		swiCopy(exp_leaderBitmap, BG_GFX, exp_leaderBitmapLen/2);
		swiCopy(exp_leaderPal, BG_PALETTE, exp_leaderPalLen/2);
		break;
	case EATIT:
		swiCopy(exp_eatitBitmap, BG_GFX, exp_eatitBitmapLen/2);
		swiCopy(exp_eatitPal, BG_PALETTE, exp_eatitPalLen/2);
		break;
	case MUSICAL:
		swiCopy(exp_musicalBitmap, BG_GFX, exp_musicalBitmapLen/2);
		swiCopy(exp_musicalPal, BG_PALETTE, exp_musicalPalLen/2);
		break;
	case PATH:
		swiCopy(exp_pathBitmap, BG_GFX, exp_pathBitmapLen/2);
		swiCopy(exp_pathPal, BG_PALETTE, exp_pathPalLen/2);
		break;
	case ADDITION:
		swiCopy(exp_additionBitmap, BG_GFX, exp_additionBitmapLen/2);
		swiCopy(exp_additionPal, BG_PALETTE, exp_additionPalLen/2);
		break;
	case PLUSMINUS:
		swiCopy(exp_plusminusBitmap, BG_GFX, exp_plusminusBitmapLen/2);
		swiCopy(exp_plusminusPal, BG_PALETTE, exp_plusminusPalLen/2);
		break;
	case JANKENPON:
		swiCopy(exp_jankenponBitmap, BG_GFX, exp_jankenponBitmapLen/2);
		swiCopy(exp_jankenponPal, BG_PALETTE, exp_jankenponPalLen/2);
		break;
	case NOGAME:
		swiCopy(titleBitmap, BG_GFX, titleBitmapLen/2);
		swiCopy(titlePal, BG_PALETTE, titlePalLen/2);
		break;
	}

	// Draw training menu
	int x, y;

	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*32+x] = brainwars_trainMap[y*32+x];
		}
	}

	// Change color of the selected button
	int xstart = 6;
	int ystart = 2;
	int inter = 1;
	int side = 6;

	int row, col;
	int x1, x2, y1, y2;

	row = selectTrain/3;
	col = selectTrain%3;

	x1 = xstart + col*side + col*inter;
	x2 = x1 + side;
	y1 = ystart + row*side + row*inter;
	y2 = y1 + side;

	for(x=x1; x<x2; x++){
		for(y=y1; y<y2; y++){
			BG_MAP_RAM_SUB(0)[y*32+x] = BG_MAP_RAM_SUB(0)[y*32+x]|(1<<12);
		}
	}
}

void brainwars_1p_init(){
	// Initialize global variables
	game = NOGAME;
	gameCounter = 2;
	gameChange = true;
	twoPlayers = false;
	gamePlayer = 0;
}

void brainwars_2p_init(){
	// Initialize global variables
	game = NOGAME;
	gameCounter = 0;
	gameChange = true;
	twoPlayers = true;
	gamePlayer = 0;

}

void brainwars_next_game(){
	// Find next game randomly
	int next_game;

	next_game = rand()%7;
	while(game == next_game) {	next_game = rand()%7; }

	game = next_game;

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
	timeCounter = 1;

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
			swiCopy(exp_leaderBitmap, BG_GFX, exp_leaderBitmapLen/2);
			swiCopy(exp_leaderPal, BG_PALETTE, exp_leaderPalLen/2);
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
			swiCopy(exp_eatitBitmap, BG_GFX, exp_eatitBitmapLen/2);
			swiCopy(exp_eatitPal, BG_PALETTE, exp_eatitPalLen/2);
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
			swiCopy(exp_musicalBitmap, BG_GFX, exp_musicalBitmapLen/2);
			swiCopy(exp_musicalPal, BG_PALETTE, exp_musicalPalLen/2);
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
			swiCopy(exp_pathBitmap, BG_GFX, exp_pathBitmapLen/2);
			swiCopy(exp_pathPal, BG_PALETTE, exp_pathPalLen/2);
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
			swiCopy(exp_additionBitmap, BG_GFX, exp_additionBitmapLen/2);
			swiCopy(exp_additionPal, BG_PALETTE, exp_additionPalLen/2);
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
			swiCopy(exp_plusminusBitmap, BG_GFX, exp_plusminusBitmapLen/2);
			swiCopy(exp_plusminusPal, BG_PALETTE, exp_plusminusPalLen/2);
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
			swiCopy(exp_jankenponBitmap, BG_GFX, exp_jankenponBitmapLen/2);
			swiCopy(exp_jankenponPal, BG_PALETTE, exp_jankenponPalLen/2);
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

void brainwars_score_init(void){
	// Copy map
	swiCopy(bestscoresMap, BG_MAP_RAM_SUB(0), bestscoresMapLen/2);

	// Copy tiles
	swiCopy(bestscoresTiles, BG_TILE_RAM_SUB(1), bestscoresTilesLen/2);

	// Copy palette
	swiCopy(bestscoresPal, BG_PALETTE_SUB, bestscoresPalLen/2);

	// Put correct colors in palettes
	BG_PALETTE_SUB[5] = REDVAL;
	BG_PALETTE_SUB[6] = BLUEVAL;
	BG_PALETTE_SUB[7] = GREENVAL;
	BG_PALETTE_SUB[8] = BLACKVAL;
	BG_PALETTE_SUB[9] = GREYVAL;
	BG_PALETTE_SUB[11] = GREENVAL;

	BG_PALETTE_SUB[21] = REDVAL;
	BG_PALETTE_SUB[22] = BLUEVAL;
	BG_PALETTE_SUB[23] = GREENVAL;
	BG_PALETTE_SUB[24] = BLACKVAL;
	BG_PALETTE_SUB[25] = GREYVAL;
	BG_PALETTE_SUB[27] = YELLOWVAL;

	// Put correct colors in palettes
	BG_PALETTE_SUB[5] = REDVAL;
	BG_PALETTE_SUB[6] = BLUEVAL;
	BG_PALETTE_SUB[7] = GREENVAL;
	BG_PALETTE_SUB[8] = BLACKVAL;
	BG_PALETTE_SUB[9] = GREYVAL;
	BG_PALETTE_SUB[11] = GREENVAL;

	BG_PALETTE_SUB[21] = REDVAL;
	BG_PALETTE_SUB[22] = BLUEVAL;
	BG_PALETTE_SUB[23] = GREENVAL;
	BG_PALETTE_SUB[24] = BLACKVAL;
	BG_PALETTE_SUB[25] = GREYVAL;
	BG_PALETTE_SUB[27] = YELLOWVAL;

	// Draw score of each game
	int i, j;

	int score;
	int color = YELLOW;

	int digit[4];

	int x, y;
	int row, col;
	int xstart = 7;		// x start on screen
	int ystart = 2;		// y start on screen
	int ystim = 24;		// y start in image
	int D = 15;			// distance between scores of the two columns
	int l = 2;			// length of one number
	int h = 5;			// height of one number

	int xinit, yinit;

	for(i=0; i<7; i++){
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

		scores[0] = info_get_score("leader");
		scores[1] = info_get_score("eatit");
		scores[2] = info_get_score("musical");
		scores[3] = info_get_score("path");
		scores[4] = info_get_score("addition");
		scores[5] = info_get_score("plusminus");
		scores[6] = info_get_score("jankenpon");

		// Check if higher then old score
		if(score>scores[i]){
			scores[i] = score;
			color = GREEN;
		}
		else color = YELLOW;

		// Compute digits of number
		digit[0] = score/1000;
		digit[1] = (score-1000*digit[0])/100;
		digit[2] = (score-1000*digit[0]-100*digit[1])/10;
		digit[3] = (score-1000*digit[0]-100*digit[1]-10*digit[2]);

		// Display digits
		yinit = ystart+row*h;

		for(j=0;j<4;j++){
			xinit = xstart+col*D+j*l;

			for(x=xinit; x<xinit+l; x++){
				for(y=yinit; y<yinit+1*h; y++){
					BG_MAP_RAM_SUB(0)[y*32 + x] = bestscoresMap[(y-yinit+ystim)*32+(x-xinit)+digit[j]*l]|((color-2)<<12);
				}
			}
		}
	}
}

void brainwars_score(void){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if((keys & KEY_TOUCH) | (keys & KEY_A) | (keys & KEY_START)){
		state = MAIN;
		stateChange = true;
	}
}

void brainwars_credits_init(){
	// Copy map
	swiCopy(creditsMap, BG_MAP_RAM_SUB(0), creditsMapLen/2);

	// Copy tiles
	swiCopy(creditsTiles, BG_TILE_RAM_SUB(1), creditsTilesLen/2);

	// Copy palette
	swiCopy(creditsPal, BG_PALETTE_SUB, creditsPalLen/2);
}

void brainwars_credits(){
	// Scan keys
	scanKeys();
	u16 keys = (u16) keysDown();

	// Scan if exit asked
	if((keys & KEY_TOUCH) | (keys & KEY_A) | (keys & KEY_START)){
		state = MAIN;
		stateChange = true;
	}
}
