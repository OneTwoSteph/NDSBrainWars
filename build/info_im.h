
//{{BLOCK(info_im)

//======================================================================
//
//	info_im, 256x40@4, 
//	+ palette 16 entries, not compressed
//	+ 37 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x5 
//	Total size: 32 + 1184 + 320 = 1536
//
//	Time-stamp: 2015-06-25, 02:39:11
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_INFO_IM_H
#define GRIT_INFO_IM_H

#define info_imTilesLen 1184
extern const unsigned int info_imTiles[296];

#define info_imMapLen 320
extern const unsigned short info_imMap[160];

#define info_imPalLen 32
extern const unsigned short info_imPal[16];

#endif // GRIT_INFO_IM_H

//}}BLOCK(info_im)
