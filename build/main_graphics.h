
//{{BLOCK(main_graphics)

//======================================================================
//
//	main_graphics, 256x2496@4, 
//	+ palette 16 entries, not compressed
//	+ 1288 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x312 
//	Total size: 32 + 41216 + 19968 = 61216
//
//	Time-stamp: 2015-06-11, 19:15:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAIN_GRAPHICS_H
#define GRIT_MAIN_GRAPHICS_H

#define main_graphicsTilesLen 41216
extern const unsigned int main_graphicsTiles[10304];

#define main_graphicsMapLen 19968
extern const unsigned short main_graphicsMap[9984];

#define main_graphicsPalLen 32
extern const unsigned short main_graphicsPal[16];

#endif // GRIT_MAIN_GRAPHICS_H

//}}BLOCK(main_graphics)
