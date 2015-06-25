
//{{BLOCK(main_start)

//======================================================================
//
//	main_start, 256x192@4, 
//	+ palette 16 entries, not compressed
//	+ 141 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 32 + 4512 + 1536 = 6080
//
//	Time-stamp: 2015-06-25, 12:23:26
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAIN_START_H
#define GRIT_MAIN_START_H

#define main_startTilesLen 4512
extern const unsigned int main_startTiles[1128];

#define main_startMapLen 1536
extern const unsigned short main_startMap[768];

#define main_startPalLen 32
extern const unsigned short main_startPal[16];

#endif // GRIT_MAIN_START_H

//}}BLOCK(main_start)
