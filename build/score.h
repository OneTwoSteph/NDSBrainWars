
//{{BLOCK(score)

//======================================================================
//
//	score, 256x104@4, 
//	+ palette 16 entries, not compressed
//	+ 104 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x13 
//	Total size: 32 + 3328 + 832 = 4192
//
//	Time-stamp: 2015-01-23, 23:35:38
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SCORE_H
#define GRIT_SCORE_H

#define scoreTilesLen 3328
extern const unsigned int scoreTiles[832];

#define scoreMapLen 832
extern const unsigned short scoreMap[416];

#define scorePalLen 32
extern const unsigned short scorePal[16];

#endif // GRIT_SCORE_H

//}}BLOCK(score)
