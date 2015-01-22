/*
 * brainwars.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati & Nawaaz GS
 *
 */

#include "general.h"
#include "brainwars.h"

#include "title.h"
#include "brainwars_main.h"
#include "brainwars_train.h"
#include "exp_leader.h"
#include "exp_eatit.h"
#include "exp_path.h"
#include "exp_jankenpon.h"

#include "leader.h"
#include "eatit.h"
#include "pairs.h"
#include "musical.h"
#include "path.h"
//#include "addition.h"
#include "plusminus.h"
#include "jankenpon.h"

STATE state;
STATE selectMain;
bool stateChange;

GAME game;
GAME selectTrain;
bool gameChange;

void brainwars_init(){
	// Initialize game state
	state = MAIN;
	stateChange = false;

	// Initialize random number generation
	srand(time(NULL));

	// Configure main and sub engines for graphics
	brainwars_configMain();
	brainwars_configSub();

	// Initialize main menu
	brainwars_main_init();
}

void brainwars_configMain(){
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE ;
}

void brainwars_configSub(){
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE;
}

void brainwars_main_init(){
	// Configure background
	BGCTRL[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;

	// Main affine matrix
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	// Copy bitmap and tiles to memory
	swiCopy(titleBitmap, BG_GFX, titleBitmapLen);
	swiCopy(brainwars_mainTiles, BG_TILE_RAM_SUB(1), brainwars_mainTilesLen/2);

	// Copy palettes
	swiCopy(titlePal, BG_PALETTE, titlePalLen);
	swiCopy(brainwars_mainPal, BG_PALETTE_SUB, brainwars_mainPalLen/2);
	swiCopy(brainwars_mainPal, &BG_PALETTE_SUB[16], brainwars_mainPalLen);

	// Set up palette colors
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[3] = BLUEVAL;
	BG_PALETTE_SUB[5] = GREENVAL;
	BG_PALETTE_SUB[6] = REDVAL;
	BG_PALETTE_SUB[7] = BLACKVAL;
	BG_PALETTE_SUB[8] = GREYVAL;

	BG_PALETTE_SUB[17] = YELLOWVAL;
	BG_PALETTE_SUB[19] = BLUEVAL;
	BG_PALETTE_SUB[21] = GREENVAL;
	BG_PALETTE_SUB[22] = REDVAL;
	BG_PALETTE_SUB[23] = BLACKVAL;
	BG_PALETTE_SUB[24] = GREYVAL;

	// Initialize selection variable
	selectMain = ONEP;

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
		if(selectMain==TRAIN)
			selectMain = CREDITS;
		else
			selectMain--;

		// Draw updates
		brainwars_main_draw();
	}

	// Check if down key pressed
	if(keys & KEY_DOWN){
		// Update selected button
		if(selectMain==CREDITS)
			selectMain = TRAIN;
		else
			selectMain++;

		// Draw updates
		brainwars_main_draw();
	}

	// Check if start key pressed
	if(keys & KEY_START){
		// Update game state
		state = selectMain;
		stateChange = true;
	}
}

void brainwars_main_draw(){
	int x, y;
	int height = 4;
	int L = 32;	// length of the image

	// Draw main menu
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*L+x] = brainwars_mainMap[y*L+x];
		}
	}

	// Change color of the selected button
	for(x=0; x<32; x++){
		for(y=selectMain*height; y<(selectMain+1)*height; y++){
			BG_MAP_RAM_SUB(0)[y*L+x] = BG_MAP_RAM_SUB(0)[y*L+x]|(1<<12);
		}
	}
}

void brainwars_1p(){

}

void brainwars_train_init(){
	// Configure backgrounds
	BGCTRL[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;

	// Main affine matrix
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	// Copy bitmap and tiles to memory
	swiCopy(exp_leaderBitmap, BG_GFX, exp_leaderBitmapLen/2);
	swiCopy(brainwars_trainTiles, BG_TILE_RAM_SUB(1), brainwars_trainTilesLen/2);

	// Copy palettes
	swiCopy(exp_leaderPal, BG_PALETTE, exp_leaderPalLen/2);
	swiCopy(brainwars_trainPal, BG_PALETTE_SUB, brainwars_trainPalLen/2);
	swiCopy(brainwars_trainPal, &BG_PALETTE_SUB[16], brainwars_trainPalLen);

	// Set up sub palette colors
	BG_PALETTE_SUB[1] = WHITEVAL;
	BG_PALETTE_SUB[3] = BLUEVAL;
	BG_PALETTE_SUB[5] = GREENVAL;
	BG_PALETTE_SUB[6] = REDVAL;
	BG_PALETTE_SUB[7] = BLACKVAL;
	BG_PALETTE_SUB[8] = GREYVAL;

	BG_PALETTE_SUB[17] = YELLOWVAL;
	BG_PALETTE_SUB[19] = BLUEVAL;
	BG_PALETTE_SUB[21] = GREENVAL;
	BG_PALETTE_SUB[22] = REDVAL;
	BG_PALETTE_SUB[23] = BLACKVAL;
	BG_PALETTE_SUB[24] = GREYVAL;

	// Initialize variable
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
			leader_init();
		}

		// Execute action of game
		gameChange = leader_game();

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
			eatit_init();
		}

		// Execute action of game
		gameChange = eatit_game();

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			eatit_reset();
		}

		break;
	case PAIRS:
		/*// Check if game just changed
		if(gameChange){
			gameChange = false;
			pairs_init();
		}

		// Execute action of game
		gameChange = pairs_game();

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			pairs_reset();
		}*/

		break;
	case MUSICAL:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			musical_init();
		}

		/*// Execute action of game
		gameChange = musical_game();

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			musical_reset();
		}*/

		break;
	case PATH:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			path_init();
		}

		// Execute action of game
		gameChange = path_game();

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			path_reset();
		}

		break;
	case ADDITION:
		/*// Check if game just changed
		if(gameChange){
			gameChange = false;
			addition_init();
		}

		// Execute action of game
		gameChange = addition_game();

		// Check if game ended
		if(gameChange){
			game = NOGAME;
			addition_reset();
		}*/

		break;
	case PLUSMINUS:
		// Check if game just changed
		if(gameChange){
			gameChange = false;
			plusminus_init();
		}

		// Execute action of game
		gameChange = plusminus_game();

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
			jankenpon_init();
		}

		// Execute action of game
		gameChange = jankenpon_game();

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
	if(keys & KEY_RIGHT){
		// Update selected button
		selectTrain = (selectTrain+1)%9;

		// Draw updates
		brainwars_train_draw();
	}

	// Check if left key pressed
	if(keys & KEY_LEFT){
		// Update selected button
		selectTrain = (selectTrain+8)%9;

		// Draw updates
		brainwars_train_draw();
	}

	// Check if down key pressed
	if(keys & KEY_DOWN){
		// Update selected button
		selectTrain = (selectTrain+3)%9;

		// Draw updates
		brainwars_train_draw();
	}

	// Check if up key pressed
	if(keys & KEY_UP){
		// Update selected button
		selectTrain = (selectTrain+6)%9;

		// Draw updates
		brainwars_train_draw();
	}

	// Check if start key pressed
	if(keys & KEY_START){
		// Update game state
		game = selectTrain;
		gameChange = true;

		// Exit case
		if(game == NOGAME){
			state = MAIN;
			stateChange = true;
		}
	}
}

void brainwars_train_draw(){
	int x, y;
	int xstart = 4;
	int ystart = 3;
	int length = 8;
	int height = 6;
	int L = 32;			// length of the image

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
	case PAIRS:
		swiCopy(titleBitmap, BG_GFX, titleBitmapLen/2);
		swiCopy(titlePal, BG_PALETTE, titlePalLen/2);
		break;
	case MUSICAL:
		swiCopy(titleBitmap, BG_GFX, titleBitmapLen/2);
		swiCopy(titlePal, BG_PALETTE, titlePalLen/2);
		break;
	case PATH:
		swiCopy(exp_pathBitmap, BG_GFX, exp_pathBitmapLen/2);
		swiCopy(exp_pathPal, BG_PALETTE, exp_pathPalLen/2);
		break;
	case ADDITION:
		swiCopy(titleBitmap, BG_GFX, titleBitmapLen/2);
		swiCopy(titlePal, BG_PALETTE, titlePalLen/2);
		break;
	case PLUSMINUS:
		swiCopy(titleBitmap, BG_GFX, titleBitmapLen/2);
		swiCopy(titlePal, BG_PALETTE, titlePalLen/2);
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
	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			BG_MAP_RAM_SUB(0)[y*L+x] = brainwars_trainMap[y*L+x];
		}
	}

	// Change color of the selected button
	int row, col;
	row = selectTrain/3;
	col = selectTrain%3;

	for(x=xstart+col*length; x<xstart+(col+1)*length; x++){
		for(y=ystart+row*height; y<ystart+(row+1)*height; y++){
			BG_MAP_RAM_SUB(0)[y*L+x] = BG_MAP_RAM_SUB(0)[y*L+x]|(1<<12);
		}
	}
}
