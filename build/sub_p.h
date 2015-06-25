
//{{BLOCK(sub_p)

//======================================================================
//
//	sub_p, 336x160@4, 
//	+ palette 16 entries, not compressed
//	+ 250 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 42x20 
//	Total size: 32 + 8000 + 1680 = 9712
//
//	Time-stamp: 2015-06-25, 12:23:28
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SUB_P_H
#define GRIT_SUB_P_H

#define sub_pTilesLen 8000
extern const unsigned int sub_pTiles[2000];

#define sub_pMapLen 1680
extern const unsigned short sub_pMap[840];

#define sub_pPalLen 32
extern const unsigned short sub_pPal[16];

#endif // GRIT_SUB_P_H

//}}BLOCK(sub_p)
