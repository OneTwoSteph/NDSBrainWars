/*
 * brainwars.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie amati
 */

#include "general.h"
#include "brainwars.h"

void brainwars_init(void){
	// Configure sub engine to tile mode
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE;
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;
}
