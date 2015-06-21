/*
 * main.c
 *
 *  Created on: Dec 27, 2014
 *    Original: Template Nintendo DS (May 2011)
 * Modified by: Stephanie Amati & Nawaaz Gujja Shaik
 *
 */


/******************************************************************** Modules */
//General
#include "general.h"
#include "brainwars.h"


/*********************************************************************** Main */
int main(void) {
    // Initialize game
    brainwars_start_init();

    // Game infinite loop
    while(1){
    	brainwars_main();
    }
}
