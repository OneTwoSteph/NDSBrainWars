/*
 * path.c
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 */

#include "path.h"
#include "path_arrow.h"

COLOR color = GREEN;
DIRECTION direction = LEFT;

void path_init(){
	// Configure sub engine to tile mode
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE;
	BGCTRL_SUB[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_32x32 | BG_COLOR_16;

	// Copy tiles to memory
	swiCopy(path_arrowTiles, BG_TILE_RAM_SUB(1), path_arrowTilesLen/2);

	// Copy palette
	swiCopy(path_arrowPal, BG_PALETTE_SUB, path_arrowPalLen/2);
	swiCopy(path_arrowPal, &BG_PALETTE_SUB[16], path_arrowPalLen);
	swiCopy(path_arrowPal, &BG_PALETTE_SUB[16*2], path_arrowPalLen);
	swiCopy(path_arrowPal, &BG_PALETTE_SUB[16*3], path_arrowPalLen);

	// Set up palette colors (palette contains back, arrow, circle in this order)
	BG_PALETTE_SUB[2] = BLUEVAL;
	BG_PALETTE_SUB[18] = REDVAL;
	BG_PALETTE_SUB[34] = GREENVAL;
	BG_PALETTE_SUB[50] = YELLOWVAL;

	// Set draw on screen
	path_draw();

}

void path_draw(){
	int x, y;

	for(x=0; x<32; x++){
		for(y=0; y<24; y++){
			// Direction
			switch(direction){
				case UP:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(y+4)*32+x];
					break;
				case DOWN:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(31-4-y)*32+x]^(1<<11);
					break;
				case RIGHT:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(y+32+4)*32+x];
					break;
				case LEFT:
					BG_MAP_RAM_SUB(0)[y*32+x] = path_arrowMap[(y+32+4)*32+(31-x)]^(1<<10);
					break;
			}

			// Color
			BG_MAP_RAM_SUB(0)[y*32+x] = BG_MAP_RAM_SUB(0)[y*32+x]|(color<<12);
		}
	}
}
