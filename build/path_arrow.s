
@{{BLOCK(path_arrow)

@=======================================================================
@
@	path_arrow, 256x512@4, 
@	+ palette 16 entries, not compressed
@	+ 59 tiles (t|f reduced) not compressed
@	+ regular map (flat), not compressed, 32x64 
@	Total size: 32 + 1888 + 4096 = 6016
@
@	Time-stamp: 2014-12-27, 23:42:25
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global path_arrowTiles		@ 1888 unsigned chars
path_arrowTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x22200000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x22222222
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x22000000,0x22220000,0x22222200
	.word 0x00000000,0x00000000,0x22000000,0x22222000,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x22000000,0x22222200,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000022,0x00022222,0x02222222

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x20000000,0x22200000,0x22220000
	.word 0x20000000,0x22000000,0x22220000,0x22222200,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x00000002,0x00000222,0x00002222,0x00222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x00000000,0x00000000,0x00000000,0x20000000,0x22000000,0x22220000,0x22222000,0x22222200
	.word 0x22222000,0x22222220,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x00000000,0x00000000,0x20000000,0x22000000,0x22200000,0x22200000,0x22220000,0x22222000
	.word 0x22222220,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x12222222,0x11222222,0x11122222

	.word 0x22222222,0x11122222,0x11111222,0x11111112,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x20000000,0x22000000,0x22000000,0x22200000
	.word 0x22222200,0x22222220,0x22222220,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x11112222,0x11111222,0x11111122,0x11111112,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00222222,0x02222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x22220000,0x22220000,0x22222000,0x22222000,0x22222200,0x22222200,0x22222220,0x22222222
	.word 0x00000000,0x00000000,0x20000000,0x22000000,0x22000000,0x22000000,0x22200000,0x22200000

	.word 0x00000000,0x00000002,0x00000002,0x00000022,0x00000022,0x00000022,0x00000222,0x00000222
	.word 0x22220000,0x22220000,0x22220000,0x22222000,0x22222000,0x22222000,0x22222200,0x22222200
	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x12222222,0x12222222,0x11222222
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11221111,0x11222111,0x11222211,0x11222221
	.word 0x22222200,0x22222200,0x22222220,0x22222220,0x22222220,0x22222220,0x22222222,0x22222222
	.word 0x11222222,0x11122222,0x11122222,0x11122222,0x11122222,0x11122222,0x11122222,0x11222222
	.word 0x11111111,0x21111111,0x22111111,0x22211111,0x22221111,0x22222111,0x22222211,0x22222221
	.word 0x11222222,0x11222222,0x11222222,0x11222222,0x11222222,0x11222222,0x11222222,0x11222222

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x20000000,0x20000000,0x20000000
	.word 0x11222222,0x12222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x11111111,0x11111111,0x11111111,0x11111112,0x11111122,0x11122222,0x22222222,0x22222222
	.word 0x11111111,0x21111111,0x22111111,0x22211111,0x22221111,0x22222221,0x22222222,0x22222222
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000002,0x00000002,0x00000002,0x00000002
	.word 0x20000000,0x20000000,0x20000000,0x20000000,0x20000000,0x20000000,0x20000000,0x20000000
	.word 0x00000222,0x00000222,0x00000022,0x00000022,0x00000002,0x00000002,0x00000002,0x00000000
	.word 0x22222222,0x22222220,0x22222220,0x22222200,0x22222000,0x22222000,0x22220000,0x22220000

	.word 0x22222222,0x02222222,0x02222222,0x00222222,0x00222222,0x00022222,0x00002222,0x00002222
	.word 0x22222000,0x22220000,0x22220000,0x22200000,0x22000000,0x20000000,0x00000000,0x00000000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111112,0x11111122,0x11112222,0x22222222
	.word 0x22222221,0x22222221,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x22222200,0x22222000,0x22220000,0x22200000,0x20000000,0x00000000,0x00000000,0x00000000
	.word 0x02222222,0x00002222,0x00000022,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x22220000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000022,0x00022222,0x00222222

	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x21111112,0x11111111,0x11111111
	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222221,0x22222111
	.word 0x11122222,0x11112222,0x11111222,0x11111222,0x11111222,0x11111122,0x11111122,0x11111122
	.word 0x00000000,0x00000000,0x00000002,0x00000002,0x00000022,0x00000022,0x00000222,0x00000222
	.word 0x11111122,0x11111222,0x11111222,0x11111222,0x11112222,0x11122222,0x11222222,0x12222222
	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x11111111,0x11111111
	.word 0x11111111,0x11111112,0x11111122,0x11111222,0x11112222,0x11112222,0x11111111,0x11111111
	.word 0x11112222,0x11111222,0x11111122,0x11111122,0x11111112,0x11111112,0x11111112,0x11111112

	.word 0x22221111,0x22211111,0x22211111,0x22111111,0x22111111,0x21111111,0x21111111,0x21111111
	.word 0x11222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222200,0x22222000,0x22200000,0x20000000

	.section .rodata
	.align	2
	.global path_arrowMap		@ 4096 unsigned chars
path_arrowMap:
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0002
	.hword 0x0002,0x0401,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0003,0x0004,0x0005,0x0006,0x0006
	.hword 0x0006,0x0006,0x0405,0x0404,0x0007,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0008,0x0009,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x000A,0x0408,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x000B,0x000C,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x040C,0x040B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x000D
	.hword 0x000E,0x0006,0x0006,0x0006,0x0006,0x0006,0x000F,0x0010
	.hword 0x0410,0x040F,0x0006,0x0006,0x0006,0x0006,0x0006,0x040E
	.hword 0x040D,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0011,0x0012
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x000F,0x0013,0x0014
	.hword 0x0014,0x0413,0x040F,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0015,0x0411,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0016,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x000F,0x0013,0x0014,0x0014
	.hword 0x0014,0x0014,0x0413,0x040F,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0416,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0017,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x000F,0x0013,0x0014,0x0014,0x0014
	.hword 0x0014,0x0014,0x0014,0x0413,0x040F,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0018,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0019,0x0006,0x0006
	.hword 0x0006,0x0006,0x001A,0x0013,0x0014,0x0014,0x001B,0x0014
	.hword 0x0014,0x041B,0x0014,0x0014,0x0413,0x041A,0x0006,0x0006
	.hword 0x0006,0x0006,0x0419,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x001C,0x0006,0x0006
	.hword 0x0006,0x0006,0x001D,0x0014,0x0014,0x001E,0x001F,0x0014
	.hword 0x0014,0x041F,0x041E,0x0014,0x0014,0x041D,0x0006,0x0006
	.hword 0x0006,0x0006,0x041C,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0020,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0021,0x0022,0x0023,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0423,0x0422,0x0421,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0024,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0025,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0425,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0025,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0425,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0820,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0C20,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x081C,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0C1C,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0819,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0C19,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0C18,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0026,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0027,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0028,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0811,0x0812
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x001F,0x0014
	.hword 0x0014,0x041F,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0815,0x0C11,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0029
	.hword 0x080E,0x0006,0x0006,0x0006,0x0006,0x0006,0x081A,0x002A
	.hword 0x042A,0x002B,0x0006,0x0006,0x0006,0x0006,0x0006,0x0C0E
	.hword 0x0429,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x002C,0x0C15,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0815,0x042C
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0808,0x0C0A,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x080A,0x0C08,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0C07,0x0804,0x0805,0x0006,0x0006
	.hword 0x0006,0x0006,0x0C05,0x0C04,0x002D,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x002E,0x0802
	.hword 0x0802,0x0C01,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0002
	.hword 0x0002,0x0401,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0407,0x0004,0x0005,0x0006,0x0006
	.hword 0x0006,0x0006,0x0405,0x0404,0x002F,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0008,0x040A,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0409,0x0408,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x082C,0x000C,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x040C,0x040B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0829
	.hword 0x000E,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x040E
	.hword 0x040D,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0011,0x0415
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0412,0x0411,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0827,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0821,0x0030,0x0031,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0416,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0418,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0032,0x0014,0x0413,0x040F,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0033,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0019,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0034,0x0014,0x0014,0x0413,0x040F,0x0006,0x0006
	.hword 0x0006,0x0006,0x0419,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x001C,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x041E,0x0014,0x0014,0x0413,0x040F,0x0006
	.hword 0x0006,0x0006,0x041C,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0424,0x0006,0x0006,0x0006
	.hword 0x0431,0x0035,0x0035,0x0035,0x0035,0x0035,0x0035,0x0035
	.hword 0x0035,0x0035,0x0035,0x0036,0x0014,0x0014,0x0413,0x040F
	.hword 0x0006,0x0006,0x0006,0x0420,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0025,0x0006,0x0006,0x0006
	.hword 0x0037,0x0014,0x0014,0x0014,0x0014,0x0014,0x0014,0x0014
	.hword 0x0014,0x0014,0x0014,0x0014,0x0014,0x0014,0x0014,0x0038
	.hword 0x0006,0x0006,0x0006,0x0425,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0025,0x0006,0x0006,0x0006
	.hword 0x0837,0x0014,0x0014,0x0014,0x0014,0x0014,0x0014,0x0014
	.hword 0x0014,0x0014,0x0014,0x0014,0x0014,0x0014,0x0014,0x0838
	.hword 0x0006,0x0006,0x0006,0x0425,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0820,0x0006,0x0006,0x0006
	.hword 0x0039,0x0835,0x0835,0x0835,0x0835,0x0835,0x0835,0x0835
	.hword 0x0835,0x0835,0x0835,0x0836,0x0014,0x0014,0x0C13,0x0C0F
	.hword 0x0006,0x0006,0x0006,0x0C20,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x081C,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0C1E,0x0014,0x0014,0x0C13,0x0C0F,0x0006
	.hword 0x0006,0x0006,0x0C1C,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0819,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0834,0x0014,0x0014,0x0C13,0x0C0F,0x0006,0x0006
	.hword 0x0006,0x0006,0x0C19,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0426,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0832,0x0014,0x0C13,0x0C0F,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0818,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0027,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0021,0x0830,0x0831,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0427,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0811,0x0C15
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0C12,0x0C11,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0029
	.hword 0x080E,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0C0E
	.hword 0x0C0D,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x002C,0x0C15,0x0006,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0815,0x0C0B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0808,0x003A,0x0006,0x0006,0x0006,0x0006,0x0006
	.hword 0x0006,0x0006,0x0006,0x0006,0x0006,0x0C09,0x0C08,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x042D,0x0804,0x0805,0x0006,0x0006
	.hword 0x0006,0x0006,0x0C05,0x0C04,0x0807,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0801,0x0802
	.hword 0x0802,0x042E,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.section .rodata
	.align	2
	.global path_arrowPal		@ 32 unsigned chars
path_arrowPal:
	.hword 0x77BD,0x7FDE,0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(path_arrow)
