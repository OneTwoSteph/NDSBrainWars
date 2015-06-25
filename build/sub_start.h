
//{{BLOCK(sub_start)

//======================================================================
//
//	sub_start, 256x192@4, 
//	+ palette 16 entries, not compressed
//	+ 36 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 32 + 1152 + 1536 = 2720
//
//	Time-stamp: 2015-06-25, 12:23:29
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SUB_START_H
#define GRIT_SUB_START_H

#define sub_startTilesLen 1152
extern const unsigned int sub_startTiles[288];

#define sub_startMapLen 1536
extern const unsigned short sub_startMap[768];

#define sub_startPalLen 32
extern const unsigned short sub_startPal[16];

#endif // GRIT_SUB_START_H

//}}BLOCK(sub_start)
