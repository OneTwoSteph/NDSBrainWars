
//{{BLOCK(result)

//======================================================================
//
//	result, 256x160@4, 
//	+ palette 16 entries, not compressed
//	+ 164 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x20 
//	Total size: 32 + 5248 + 1280 = 6560
//
//	Time-stamp: 2015-06-11, 19:15:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_RESULT_H
#define GRIT_RESULT_H

#define resultTilesLen 5248
extern const unsigned int resultTiles[1312];

#define resultMapLen 1280
extern const unsigned short resultMap[640];

#define resultPalLen 32
extern const unsigned short resultPal[16];

#endif // GRIT_RESULT_H

//}}BLOCK(result)
