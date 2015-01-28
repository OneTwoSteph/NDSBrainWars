
//{{BLOCK(credits)

//======================================================================
//
//	credits, 256x192@4, 
//	+ palette 16 entries, not compressed
//	+ 218 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 32 + 6976 + 1536 = 8544
//
//	Time-stamp: 2015-01-28, 11:27:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CREDITS_H
#define GRIT_CREDITS_H

#define creditsTilesLen 6976
extern const unsigned int creditsTiles[1744];

#define creditsMapLen 1536
extern const unsigned short creditsMap[768];

#define creditsPalLen 32
extern const unsigned short creditsPal[16];

#endif // GRIT_CREDITS_H

//}}BLOCK(credits)
