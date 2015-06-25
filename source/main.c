/*
 * main.c
 *
 *  Created on: Dec 27, 2014
 *    Original: Template Nintendo DS (May 2011)
 * Modified by: Stephanie Amati & Nawaaz Gujja Shaik
 *
 */


/******************************************************************** Modules */
// General
#include "general.h"
#include "brainwars.h"


/****************************************************************** Functions */
// Main function of the game (main loop)
int main(void) {
    // Initialize game
    brainwars_start_init();

    // Game infinite loop
    while(1){
    	// Execute game
    	brainwars_main();

    	// Scan keys one time per loop to avoid over-reading
    	scanKeys();
    }
}