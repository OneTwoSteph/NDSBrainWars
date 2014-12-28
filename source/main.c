/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "path.h"
#include "general.h"

int main(void) {

    consoleDemoInit();

    srand(time(NULL));

    STATE state;
    state = TRAIN;

    GAME game;
    game = NOGAME;

    bool path;

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
    				path_init();
    				game = PATH;
    			}
    			break;
    		case PATH:
    			path = path_game();
    			if(!path){
    				game = NOGAME;
    				path_reset();
    			}
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
