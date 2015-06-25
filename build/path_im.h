
//{{BLOCK(path_im)

//======================================================================
//
//	path_im, 256x384@4, 
//	+ palette 16 entries, not compressed
//	+ 104 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x48 
//	Total size: 32 + 3328 + 3072 = 6432
//
//	Time-stamp: 2015-06-25, 12:23:27
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PATH_IM_H
#define GRIT_PATH_IM_H

#define path_imTilesLen 3328
extern const unsigned int path_imTiles[832];

#define path_imMapLen 3072
extern const unsigned short path_imMap[1536];

#define path_imPalLen 32
extern const unsigned short path_imPal[16];

#endif // GRIT_PATH_IM_H

//}}BLOCK(path_im)
