/*
 * brainwars.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati & Nawaaz S. Gujja Shaik
 *
 */

#include "general.h"
#include "brainwars.h"
#include "path.h"
#include "jankenpon.h"
#include "leader.h"
#include "eatit.h"

STATE state;
GAME game;

void brainwars_init(){
	// Initialize game state
	state = TRAIN;
	game = NOGAME;

	// Initialize random number generation
	srand(time(NULL));

	// Configure main and sub engines for graphics
	brainwars_configMain();
	brainwars_configSub();
}

void brainwars_configMain(){
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;
}

void brainwars_configSub(){
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE;
}

void brainwars_main(){
	// Check in which state the game is
	switch(state){
	case MAIN:
		break;
	case TRAIN:
		brainwars_train();
		break;
	case ONEP:
		break;
	default:
		break;
	}
}

void brainwars_1p(){

}
void brainwars_train(){
	// Game stop variable
	bool gamestate;

	// Check in which game we are training
	switch(game){
	case NOGAME:
		// Scan keys
		scanKeys();
		u16 keys = (u16) keysDown();

		if(keys & KEY_START){
			path_init();
			game = PATH;
			//jankenpon_init();
			//game = JANKENPON;
			//leader_init();
			//game = LEADER;
			//eatit_init();
			//game = EATIT;
		}
		break;
	case PATH:
		gamestate = path_game();
		if(!gamestate){
			game = NOGAME;
			path_reset();
		}
		break;
	case JANKENPON:
		gamestate = jankenpon_game();
		if(!gamestate){
			game = NOGAME;
			jankenpon_reset();
		}
		break;
	case LEADER:
		/*gamestate = leader_game();
		if(!gamestate){
			game = NOGAME;
			leader_reset();
		}
		break;*/
	case EATIT:
		gamestate = eatit_game();
		if(!gamestate){
			game = NOGAME;
			eatit_reset();
		}
		break;
	default:
		break;
	}
}
