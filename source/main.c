/*
 * main.c
 *
 *  Created on: Dec 27, 2014
 *    Original: Template Nintendo DS (May 2011)
 * Modified by: Stephanie Amati & Nawaaz S. Gujja Shaik
 *
 */

#include <nds.h>
#include "brainwars.h"

int main(void) {
	// Initialize console
    consoleDemoInit();

    // Initialize game
    brainwars_init();

    // Game infinite loop
    while(1){
    	// Game
    	brainwars_main();

    	// Usual end of loop call
        swiWaitForVBlank();	
    }
}
