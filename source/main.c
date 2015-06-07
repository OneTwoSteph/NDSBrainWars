/*
 * main.c
 *
 *  Created on: Dec 27, 2014
 *    Original: Template Nintendo DS (May 2011)
 * Modified by: Stephanie Amati & Nawaaz Gujja Shaik
 *
 */

#include "general.h"
#include "brainwars.h"

int main(void) {
    // Initialize game
    brainwars_init();
    brainwars_start_draw();

    // Game infinite loop
    while(1){
    	// Game
    	brainwars_main();

    	// Usual end of loop call
        swiWaitForVBlank();	
    }
}
