
@{{BLOCK(credits)

@=======================================================================
@
@	credits, 256x192@4, 
@	+ palette 16 entries, not compressed
@	+ 218 tiles (t|f reduced) not compressed
@	+ regular map (flat), not compressed, 32x24 
@	Total size: 32 + 6976 + 1536 = 8544
@
@	Time-stamp: 2015-06-11, 19:15:05
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global creditsTiles		@ 6976 unsigned chars
creditsTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xA99AAAA9,0xA9AA9AA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xA9999AAA,0xAA99AA9A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x9AA999AA,0x9AA99AA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA99,0xA999AA99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAAA99AAA,0xA999AA9A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAA999AAA,0xAA99999A

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAA9999AA,0xAA999AA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAA9AA99A,0xAA9AA999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xA99AAA99,0xA999AA99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAAA9999A,0xA9AA999A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x9AAAA999,0xAA9AA99A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999AAA,0x9999AA9A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x9999AAAA,0x999AA9AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xA99AA9AA,0xA99AA9AA

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAA999AAA,0xAA99AA9A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99A99AA9,0x99A9AAA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA99,0x99AA9AA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x9AAAAAA9,0x999AA999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x999999AA,0xA999999A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAAAA99AA,0xA9AA99AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x9AAA9999,0xAA9AA99A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA99,0x9999AA99

	.word 0xA9AA9AA9,0xA9AA9AA9,0xA9AA9AA9,0xA99AAAA9,0xA9999AA9,0xA9999AA9,0xA9999AA9,0xA9999AA9
	.word 0xAA99AA9A,0xAA99AA9A,0xAA999AAA,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xA999AA9A
	.word 0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x99AA99AA
	.word 0xA999AA99,0xA999AA99,0xA99AAA99,0xA999AA99,0xA999AA99,0xA999AA99,0xA999AA99,0x99AAAA99
	.word 0xA999AA9A,0xA999AA9A,0xA999999A,0xA999AA9A,0xA999AA9A,0xA999AA9A,0xA999AA9A,0xA9999AAA
	.word 0xAA99999A,0xAA99999A,0xAA99999A,0xAA99999A,0xAA99999A,0xAA99999A,0xAA99999A,0xAA99999A
	.word 0xAA999AA9,0xAA999AA9,0xAA999AA9,0xAA999AA9,0xAA999AA9,0xAA999AA9,0xAA999AA9,0xAA999AAA
	.word 0xAA9AA999,0xAA9AA999,0xAA9AA99A,0xAA9AA999,0xAA9AA999,0xAA9AA999,0x9AAA9999,0x9AAA99AA

	.word 0xA999AA99,0xA999AA99,0xA99AAA99,0xA999AA99,0xA999AA99,0xA999AA99,0xA999AA99,0xA9AAAA99
	.word 0xA9AA999A,0xA9AA999A,0xA9AA999A,0xA9AA999A,0xA9AA999A,0xA9AA999A,0xA9AA999A,0xAAA99AAA
	.word 0xAA9AA99A,0xAA9AA99A,0xAA9AA99A,0x9AAAA99A,0x999AA99A,0x999AA99A,0x999AA99A,0x999AA999
	.word 0x9999AA9A,0x9999AA9A,0x9999AA9A,0x9999AA9A,0x9999AA9A,0x9999AA9A,0x9999AA9A,0x9999AAAA
	.word 0x999AA9AA,0x999AA9AA,0x999AA9AA,0x999AA9AA,0x999AA9AA,0x999AA9AA,0x999AA9AA,0x999AAAAA
	.word 0xA99AA9AA,0xA99AA9AA,0xA99AA9AA,0xA99AA9AA,0xA99AA9AA,0xA99AA9AA,0xA99AA9AA,0xA999AAA9
	.word 0xAA99AA9A,0xAA99AA9A,0xAA999AAA,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A
	.word 0x99A9AAA9,0x99A9AAA9,0x99AAAAA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99A99AA9,0x99A99AA9

	.word 0x99AA9AA9,0x99AA9AA9,0x99999AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99A9AA99
	.word 0x999AA999,0x999AA999,0x999AA999,0x999AA999,0x999AA999,0x999AA999,0x999AA999,0x999AA999
	.word 0xA99AA9AA,0xA99AA9AA,0xA99AA9AA,0xA99AAAAA,0xA99AA9AA,0xA99AA9AA,0xA99AA9AA,0xA99AA9AA
	.word 0xA999999A,0xA999999A,0xA99999AA,0xA999999A,0xA999999A,0xA999999A,0xA999999A,0x99999AAA
	.word 0xAA99AA9A,0xAA99AA9A,0xAA99999A,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xA9999AAA
	.word 0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0xAA9999AA
	.word 0xA9AA99AA,0xA9AA99AA,0xAAAA99AA,0xA9AA99AA,0xA9AA99AA,0xA9AA99AA,0xA9AA99AA,0xA9AA999A
	.word 0xAA9AA99A,0x999AA99A,0x9AAAA999,0xAAA9999A,0xAA99999A,0xAA9AA99A,0xAA9AA99A,0x9AAA999A

	.word 0x9999AA99,0x9999AA99,0x999AAA99,0x9999AA99,0x9999AA99,0x9999AA99,0x9999AA99,0x99AAAA99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77799999,0x7779A9A9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x79997779,0x79997779
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99777997,0x97797797
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99777799,0x97797799
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99977799,0x99779779
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77997777,0x77977977
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77999977,0x97799779

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77799997,0x79779977
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77779999,0x79779997
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x97779999,0x97779997
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77797779,0x77797779
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77977799,0x77977799
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x97779997,0x99779997
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99977779,0x99779779
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99777999,0x99977999

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77997779,0x77999779
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77799977,0x97799779
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x97779997,0x99779977
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x97779999,0x77977999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x97799779,0x97799779
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77997779,0x99977977
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77797777,0x97799977
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x77799997,0x79779997

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x999A9A97
	.word 0x7779A9A9,0x77799A9A,0x77799A9A,0x97799A9A,0x97799A9A,0x9779A9A9,0x9779A9A9,0x97799999
	.word 0x79997779,0x79997797,0x79997797,0x79997797,0x79997797,0x79997797,0x79997797,0x79997797
	.word 0x97797797,0x97797797,0x99997797,0x97797797,0x97797797,0x97797797,0x97797797,0x99777997
	.word 0x97797799,0x97797799,0x99777799,0x97797799,0x97797799,0x97797799,0x97797799,0x97797799
	.word 0x99779779,0x99779779,0x99779779,0x99779779,0x99779779,0x99779779,0x99779779,0x99977799
	.word 0x77977977,0x77977977,0x77977977,0x77997777,0x77999977,0x77999977,0x77999977,0x77999977
	.word 0x97799779,0x97799779,0x97799977,0x97799779,0x97799779,0x97799779,0x97799779,0x77999779

	.word 0x79779977,0x79779977,0x99779977,0x79779977,0x79779977,0x79779977,0x79779977,0x97799997
	.word 0x79779997,0x79779997,0x77779999,0x79779997,0x79779997,0x79779997,0x79779997,0x79779997
	.word 0x97979997,0x97979997,0x77977999,0x77977997,0x77977997,0x77777997,0x77977997,0x77977997
	.word 0x77797779,0x77977779,0x77977779,0x77979779,0x77979779,0x77979779,0x77979779,0x77979779
	.word 0x77977799,0x79777799,0x79777799,0x79797799,0x79797799,0x79797799,0x79797799,0x79797799
	.word 0x99779997,0x99779997,0x97779997,0x99779997,0x99779997,0x99779997,0x99779997,0x77779997
	.word 0x99779779,0x99779779,0x99779779,0x99779779,0x99779779,0x99779779,0x99779779,0x99777779
	.word 0x99977999,0x99977999,0x99777999,0x99977999,0x99977999,0x99977999,0x99977999,0x97777999

	.word 0x97779777,0x97797777,0x97797777,0x97797977,0x97797977,0x97797977,0x97797977,0x97797977
	.word 0x99779779,0x99779779,0x99977779,0x99779779,0x99779779,0x99779779,0x99779779,0x99777779
	.word 0x77999779,0x77999779,0x77997779,0x77999779,0x77999779,0x77999779,0x77999779,0x77977779
	.word 0x97799779,0x97799779,0x97799779,0x97799779,0x97799779,0x97799779,0x97799779,0x77799777
	.word 0x99779977,0x99779977,0x97779977,0x99779977,0x99779977,0x99779977,0x99779977,0x77779977
	.word 0x77977999,0x99977999,0x97777999,0x77799999,0x77999999,0x77977999,0x77977999,0x97779999
	.word 0x99799799,0x99799799,0x99777799,0x99977999,0x99977999,0x99977999,0x99977999,0x99977999
	.word 0x99977977,0x99999977,0x99997777,0x99977799,0x99977999,0x99977977,0x99977977,0x99997779

	.word 0x97799977,0x97799977,0x77799977,0x97799977,0x97799977,0x97799977,0x97799977,0x77799977
	.word 0x77977799,0x79777799,0x79777799,0x79797799,0x79797799,0x79797799,0x79797799,0x79797797
	.word 0x79779997,0x99779997,0x77779997,0x77999997,0x79999997,0x79779997,0x79779997,0x77799997
	.word 0x999A9A97,0x99A9A999,0x99A9A999,0x99A9A997,0x99A9A997,0x999A9A97,0x999A9A97,0x99999999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0xAAAAAA99,0xA99AAA99,0xA99A9A99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x69999AAA,0x6999999A,0x6999999A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x66669966,0x69669996,0x69669996
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x96666999,0x99966996,0x99966996

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999966,0x99999966,0x99999966
	.word 0xA99A9A99,0xA9AA9AA9,0xA9AA9AA9,0xA9AA9AA9,0xA9AAAAA9,0xA9AA9AA9,0xA9AA9AA9,0x99999999
	.word 0x6999999A,0x6999999A,0x6999999A,0x6999999A,0x6999999A,0x6999999A,0x6999999A,0x99999999
	.word 0x69669996,0x69669966,0x66669996,0x99669996,0x99669996,0x99669996,0x99669666,0x99999999
	.word 0x99966996,0x96666996,0x99966999,0x99966999,0x99966999,0x99966999,0x99966999,0x99999999
	.word 0x99999966,0x99999966,0x99999966,0x99999966,0x99999966,0x99999966,0x99996666,0x99999999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x999AAAA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xA999AAA9,0xAA99AAA9,0xAA99A9A9,0xAA99A9A9

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAAA999AA,0x9AA99AA9,0x9AA99AA9,0x9AA99999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99AAAA99,0x9AA9AA99,0x9AA9AA99,0x9AA9AA99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAAA99999,0xA9AA9999,0xA9AA9999,0xA9AA9999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xA99AA999,0xA9AAA99A,0xA9AAA99A,0xA9AAA99A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAAAAA999,0x9AA99999,0x9AA99999,0x9AA99999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9AA9AA9A,0x9AA9AA99,0x9AA9AA99,0x9AA9AA99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA99,0x9999AA99,0x9999AA99,0x9999AA99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA99,0x99AA9AA9,0x99AA9AA9,0x99999AA9

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9AAA9AAA,0x9AAA9AAA,0x9AAA9AAA,0x9AA9AAAA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA99,0x999AAA99,0x999A9A99,0x999A9A99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAA99AAAA,0x999AA9AA,0x999AA9AA,0x999AA9AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAAA9AAAA,0x9AA999AA,0x9AA999AA,0x9AA999AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAA9AA99A,0xAA9AA9AA,0xAA9AA9AA,0xAA9AA9AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9AAA9999,0xAA9AA999,0xAA9AA999,0xAA9AA999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9A99AA99,0x9A9AAA99,0x9A9AAA99,0x9A9AAA99
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9999AAA9,0x99999AA9,0x99999AA9,0x99999AA9

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA99,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAA99AAA9,0xAA99AAA9,0xAA99A9A9,0xAA99A9A9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x999AAA9A,0x999AAA9A,0x999AAA9A,0x999AA9AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999AAA,0x999999AA,0x999999AA,0x999999AA
	.word 0x999AAAA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AAAAA9,0x99999999,0x99999999
	.word 0xAA9AA9AA,0x999AA9AA,0x999AA9AA,0xAA9AAAAA,0xAA9AA9AA,0xA99AA9AA,0x99999999,0x99999999
	.word 0xAAA999AA,0x9AA99AAA,0x9AA99AA9,0x9AA99AA9,0x9AA99AA9,0xAAA999AA,0x99999999,0x99999999
	.word 0x9AA9AA99,0x9AA9AA99,0x9AA9AA99,0x9AA9AA99,0x9AA9AA99,0x9AAAAA9A,0x99999999,0x99999999

	.word 0xA9AA9999,0xA9AA9999,0xA9AA9999,0xA9AA9999,0xA9AA9999,0xAAA99999,0x99999999,0x99999999
	.word 0xAAAAA99A,0xAA9AA99A,0xAA9AA99A,0xAA9AA99A,0xA99AA99A,0xA99AA999,0x99999999,0x99999999
	.word 0x9AA99999,0x9AA99999,0x9AA99999,0x9AA99999,0x9AA99999,0x9AA99999,0x99999999,0x99999999
	.word 0x9AA9AA99,0x9AAAAA99,0x9AA9AA99,0x9AA9AA99,0x9AA9AA99,0x9AA9AA99,0x99999999,0x99999999
	.word 0x999AAA99,0x9999AA99,0x9999AA99,0x9999AA99,0x9999AA99,0x99AAAA99,0x99999999,0x99999999
	.word 0x999AAAA9,0x99AAA999,0x99AA9999,0x99AA9AA9,0x99AA9AA9,0x999AAA99,0x99999999,0x99999999
	.word 0x9AA9AAAA,0x9AA9A9AA,0x9AA9A9AA,0x9AA9A9AA,0x9AA9A9AA,0x9AA9A9AA,0x99999999,0x99999999
	.word 0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AAAAA9,0x99AA9AA9,0x99AA9AA9,0x99999999,0x99999999

	.word 0x9999AAAA,0x999AA9AA,0x999AA9AA,0x999AA9AA,0x999AA9AA,0x999AA9AA,0x99999999,0x99999999
	.word 0x9AA999AA,0xAAA999AA,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x99999999,0x99999999
	.word 0xAA9AA9AA,0xAAAAA99A,0xAA9AA999,0xAA9AA999,0xAA9AA999,0xAA9AA999,0x99999999,0x99999999
	.word 0xAA9AA999,0xAA9AA999,0xAA9AA999,0xAA9AA999,0xAA9AA999,0x9AAA9999,0x99999999,0x99999999
	.word 0x9AAAAA99,0x9AA9AA99,0x9AA9AA99,0x9AA9AA99,0x9A99AA99,0x9A99AA99,0x99999999,0x99999999
	.word 0x9999AAA9,0x99999AA9,0x99999AA9,0x99999AA9,0x99999AA9,0x999AAAA9,0x99999999,0x99999999
	.word 0x99999AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99A9AA99,0x99999999,0x99999999
	.word 0xAA9AA9AA,0xAA9AA9AA,0xAA9AA9AA,0xAA9AAAAA,0xAA9AA9AA,0xAA9AA9AA,0x99999999,0x99999999

	.word 0x999AA9AA,0x999AA9A9,0x999AA9A9,0x999AA9A9,0x999AA9A9,0x999AA9A9,0x99999999,0x99999999
	.word 0x99999AAA,0x999999AA,0x999999AA,0x999999AA,0x999999AA,0x9999AAAA,0x99999999,0x99999999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x55599999,0x9559A9A9,0x9559A9A9,0x95599A9A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x55599995,0x95599955,0x95599955,0x95599955
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x55599995,0x55599955,0x59599955,0x59599955
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x55995599,0x55995599,0x55995599,0x55995599
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x95599599,0x95599595,0x95599595,0x95599595
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99559959,0x99559959,0x99559555,0x99559555

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x55999555,0x55999555,0x55999595,0x55999595
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x55999955,0x95599559,0x95599559,0x95599559
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999995,0x9A9A9955,0x9A9A9955,0xA9A99999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9AAAA999,0xAA9AA999,0xAA9AA999,0xAA9AA999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x9AA999AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xA999AAA9,0xA99AA9AA,0xA99AA9AA,0xA99999AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAAAA999A,0xA9AA9999,0xA9AA9999,0xA9AA9999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xAAA99999,0x9AA9999A,0x9AA9999A,0x9AA9999A
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0xA99AA99A,0xA99AA9AA,0xA99A99AA,0xA99A99AA
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x9999999A,0xA9A9999A,0xA9A99999,0x9A9A9999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x98888889,0x99988999,0x99988999,0x99988999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99998888,0x99988988,0x99988988,0x99988988
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x98899888,0x88899888,0x88899898,0x88899898
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x88899989,0x89889989,0x89889989,0x99889989

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99988999,0x99988998,0x99988998,0x99988999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x98889988,0x98889988,0x98889988,0x88889988
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x98899888,0x98899888,0x98899888,0x98899889
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99888888,0x99998899,0x99998899,0x99998899
	.word 0x55599A9A,0x95599A9A,0x95599A9A,0x9559A9A9,0x9559A9A9,0x55599999,0x99999999,0x99999999
	.word 0x55599995,0x95599955,0x95599955,0x95599955,0x95599955,0x95599955,0x99999999,0x99999999
	.word 0x59559995,0x59559955,0x59559955,0x55559955,0x59559955,0x59559955,0x99999999,0x99999999
	.word 0x55995595,0x55995595,0x55995595,0x55995595,0x55995595,0x55995595,0x99999999,0x99999999

	.word 0x95999555,0x95999559,0x95999559,0x95999559,0x55999599,0x55999599,0x99999999,0x99999999
	.word 0x59959595,0x59959595,0x59959595,0x59959595,0x59955595,0x59955595,0x99999999,0x99999999
	.word 0x55995595,0x55995595,0x55995595,0x55995555,0x55995595,0x55995595,0x99999999,0x99999999
	.word 0x55599955,0x59999559,0x99999559,0x95599559,0x95599559,0x55999559,0x99999999,0x99999999
	.word 0xA9A99995,0xA9A99955,0xA9A99955,0x9A9A9955,0x9A9A9955,0x99999995,0x99999999,0x99999999
	.word 0xAA9AA999,0x9AAAA999,0x999AA999,0x999AA999,0x999AA999,0x999AA999,0x99999999,0x99999999
	.word 0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x99AA9AA9,0x999AAA99,0x99999999,0x99999999
	.word 0x9AA999AA,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x9AA9AAAA,0x99999999,0x99999999

	.word 0xA999AAAA,0xA99AAA99,0xA99AA999,0xA99AA9AA,0xA99AA9AA,0xA999AAA9,0x99999999,0x99999999
	.word 0xAA99AA9A,0xAA99AAAA,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0xAA99AA9A,0x99999999,0x99999999
	.word 0xA9AA999A,0xA9AA9999,0xA9AA9999,0xA9AA9999,0xA9AA9999,0xAAAA99AA,0x99999999,0x99999999
	.word 0xAAA9999A,0x9AA9999A,0x9AA9999A,0x9AA9999A,0x9AA9999A,0xAAA9999A,0x99999999,0x99999999
	.word 0xAAAA999A,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x9AA999AA,0x99999999,0x99999999
	.word 0x9A9A9999,0x9A9A9999,0x9A9A9999,0xA9A99999,0xA9A99999,0x99999999,0x99999999,0x99999999
	.word 0x99988999,0x99988999,0x99988999,0x99988999,0x99988999,0x99988999,0x99999999,0x99999999
	.word 0x89998888,0x89988988,0x89988988,0x89988988,0x89988988,0x89988988,0x99999999,0x99999999

	.word 0x88898898,0x98898898,0x98898898,0x98898888,0x98898898,0x98898898,0x99999999,0x99999999
	.word 0x88889988,0x88999988,0x89999988,0x89889988,0x89889989,0x88899989,0x99999999,0x99999999
	.word 0x99988999,0x99988998,0x99988998,0x99988998,0x99988998,0x98888999,0x99999999,0x99999999
	.word 0x88889988,0x89889988,0x89889988,0x89889988,0x89889988,0x89889988,0x99999999,0x99999999
	.word 0x98899889,0x98899889,0x98899889,0x98899889,0x98899889,0x98899889,0x99999999,0x99999999
	.word 0x99998899,0x99998899,0x99998899,0x99998899,0x98898899,0x98898899,0x99899999,0x99999999
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99889889,0x98889889,0x98889889,0x98889889
	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x98889998,0x88988998,0x88988998,0x88988998

	.word 0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99A9A999,0x99A9A999,0x9A9A9999
	.word 0x88889889,0x89889889,0x89889889,0x89889889,0x99889889,0x99889889,0x99999999,0x99999999
	.word 0x99988998,0x88988998,0x88988998,0x88988998,0x88988998,0x98889998,0x99999999,0x99999999
	.word 0x9A9A9999,0x9A9A9999,0x9A9A9999,0x99A9A999,0x99A9A999,0x99999999,0x99999999,0x99999999
	.word 0x99999999,0x99999999,0x99999999,0x999AAA99,0xA9AA9AA9,0xA9AA9AA9,0xA9AA9999,0xA9AAA999
	.word 0x99999999,0x99999999,0x99999999,0x99999AAA,0xA999AA9A,0xAAA9AA9A,0xA999AA9A,0xA999AA9A
	.word 0x99999999,0x99999999,0x99999999,0xAAAAA99A,0x999AA99A,0x999AA99A,0xAAAAA99A,0xAA9AA99A
	.word 0xA99AA999,0xA99AAA99,0xA999AA99,0xA999AAA9,0x99AAAAA9,0x99999999,0x99999999,0x99999999

	.word 0xA999AA9A,0xA999AA9A,0xA999AA9A,0xA999AA9A,0xA9999AAA,0x99999999,0x99999999,0x99999999
	.word 0xAA99999A,0xAA9AA99A,0xAA9AA99A,0xAA9AA99A,0x9AAA999A,0x99999999,0x99999999,0x99999999

	.section .rodata
	.align	2
	.global creditsMap		@ 1536 unsigned chars
creditsMap:
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007
	.hword 0x0008,0x0009,0x000A,0x000B,0x000C,0x000A,0x000D,0x000E
	.hword 0x000F,0x0010,0x0011,0x0012,0x0013,0x000F,0x0014,0x0003
	.hword 0x0004,0x0015,0x0016,0x0017,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0018,0x0019,0x001A,0x001B,0x001C,0x001D
	.hword 0x001E,0x001F,0x0020,0x0021,0x0022,0x0020,0x0023,0x0024
	.hword 0x0025,0x0026,0x0027,0x0028,0x0029,0x002A,0x002B,0x002C
	.hword 0x002D,0x002E,0x002F,0x0030,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0031,0x0032,0x0033,0x0034,0x0035,0x0036
	.hword 0x0037,0x0038,0x0039,0x003A,0x003B,0x003C,0x003D,0x003E
	.hword 0x003F,0x043B,0x003E,0x0040,0x0041,0x0042,0x0034,0x0043
	.hword 0x0044,0x0045,0x0046,0x003C,0x0047,0x0048,0x0001,0x0001

	.hword 0x0001,0x0001,0x0049,0x004A,0x004B,0x004C,0x004D,0x004E
	.hword 0x004F,0x0050,0x0051,0x0052,0x0053,0x0054,0x0055,0x0056
	.hword 0x0057,0x0058,0x0059,0x005A,0x005B,0x005C,0x0456,0x005D
	.hword 0x005E,0x005F,0x0060,0x0061,0x0062,0x0063,0x0001,0x0001
	.hword 0x0001,0x0001,0x0064,0x0065,0x0066,0x0067,0x0068,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0069,0x006A,0x006B,0x006C,0x006D,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x006E,0x006F,0x0070,0x0071,0x0072,0x0073
	.hword 0x0074,0x0075,0x0076,0x0077,0x0078,0x0079,0x007A,0x007B
	.hword 0x007C,0x007D,0x007E,0x007F,0x0080,0x0081,0x0082,0x0083
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0084,0x0085,0x0086,0x0087,0x0088,0x0089
	.hword 0x008A,0x008B,0x008C,0x008D,0x008E,0x008F,0x0090,0x0091
	.hword 0x0092,0x0093,0x0094,0x0095,0x0096,0x0097,0x0098,0x0099
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x009A,0x009B,0x009C,0x009D,0x009E,0x009F
	.hword 0x00A0,0x00A1,0x00A2,0x00A3,0x00A4,0x006E,0x00A5,0x00A6
	.hword 0x00A7,0x00A8,0x00A9,0x00AA,0x00AB,0x00AC,0x00AD,0x00AE
	.hword 0x00AF,0x00B0,0x00B1,0x00B2,0x00B3,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x00B4,0x00B5,0x00B6,0x00B7,0x00B8,0x00B9
	.hword 0x00BA,0x00BB,0x00BC,0x00BD,0x00BE,0x0084,0x00BF,0x00C0
	.hword 0x00C1,0x00C2,0x00C3,0x00C4,0x00C5,0x00C6,0x00C7,0x00C8
	.hword 0x00C9,0x00CA,0x00CB,0x00CC,0x00CD,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x00CE,0x00CF,0x00D0,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x00D1,0x00D2,0x00D3,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x00D4,0x00D5,0x00D6,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x00D7,0x00D8,0x00D9,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.section .rodata
	.align	2
	.global creditsPal		@ 32 unsigned chars
creditsPal:
	.hword 0x0000,0x7FFF,0x413C,0x77BE,0x2D6B,0x59BF,0x7E44,0x3AC7
	.hword 0x035F,0x739C,0x2D6B,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(credits)