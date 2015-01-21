/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include <time.h>
#include "general.h"
#include "brainwars.h"
#include "path.h"
#include "jankenpon.h"

int main(void) {

    consoleDemoInit();

    brainwars_init();

    srand(time(NULL));

    STATE state;
    state = TRAIN;

    GAME game;
    game = NOGAME;

    bool gamestate;

    while(1){

    	// Check in which state the game is
    	switch(state){
    	case INIT:
    		break;
    	case TRAIN:
    		// Check in which game we are training
    		switch(game){
    		case NOGAME:
    			scanKeys();
    			u16 keys = (u16) keysDown();

    			if(keys & KEY_START){
    				//path_init();
    				//game = PATH;
    				//jankenpon_init();
    				//game = JANKENPON;
    				leader_init();
    				//game = LEADER;
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
    			break;
    		case LEADER:
    			break;
    		default:
    			break;
    		}
    		break;
    	case ONEP:
    		break;
    	default:
    		break;
    	}

    	// Usual end of loop call
        swiWaitForVBlank();	
    }
}
