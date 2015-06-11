
//{{BLOCK(start)

//======================================================================
//
//	start, 256x192@4, 
//	+ palette 16 entries, not compressed
//	+ 35 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 32 + 1120 + 1536 = 2688
//
//	Time-stamp: 2015-06-11, 19:15:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_START_H
#define GRIT_START_H

#define startTilesLen 1120
extern const unsigned int startTiles[280];

#define startMapLen 1536
extern const unsigned short startMap[768];

#define startPalLen 32
extern const unsigned short startPal[16];

#endif // GRIT_START_H

//}}BLOCK(start)
