
@{{BLOCK(main_start)

@=======================================================================
@
@	main_start, 256x192@4, 
@	+ palette 16 entries, not compressed
@	+ 141 tiles (t|f reduced) not compressed
@	+ regular map (flat), not compressed, 32x24 
@	Total size: 32 + 4512 + 1536 = 6080
@
@	Time-stamp: 2015-06-25, 12:23:26
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global main_startTiles		@ 4512 unsigned chars
main_startTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x54444444,0x54444444,0x54444444,0x54444444
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x45555555,0x55555555,0x55555555,0x55555555
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444445,0x44444455,0x44444455
	.word 0x44444444,0x44444444,0x44444444,0x44555554,0x44555554,0x44555554,0x44555554,0x44555554
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x55555544,0x55555544,0x55555544,0x55555544
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x54455554,0x54455554,0x54455554,0x54555554

	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44455555,0x44455555,0x44445555,0x44445555
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x22244444,0x22244444,0x22244444,0x22244444
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x22244222,0x22244222,0x22244222,0x22244222
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x11111422,0x11111422,0x11111422,0x11111422
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444111,0x44411111,0x44111111,0x41111111
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x33444444,0x33334444,0x33333444,0x33333444
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444443,0x44444333,0x44443333,0x44433333
	.word 0x54444444,0x54444444,0x54444444,0x54444444,0x54444444,0x54444444,0x54444444,0x54444444

	.word 0x55555555,0x55545555,0x55545555,0x55545555,0x55545555,0x55555555,0x55555555,0x55555555
	.word 0x44444555,0x55554555,0x55554555,0x55554555,0x55554555,0x55554455,0x55554445,0x55554444
	.word 0x44444444,0x54444555,0x55544555,0x55544555,0x55554555,0x55554555,0x55554445,0x44444445
	.word 0x44444444,0x44445555,0x44555555,0x44555555,0x45555555,0x45555555,0x45555545,0x45555544
	.word 0x44444444,0x54555554,0x54555554,0x54555554,0x54555554,0x54555554,0x54555554,0x54555554
	.word 0x44444444,0x55544555,0x55555555,0x55555555,0x55555555,0x55555555,0x55545555,0x55545555
	.word 0x55555444,0x55555444,0x55555445,0x55555455,0x55555455,0x55555455,0x55555455,0x55555455
	.word 0x54555554,0x54555554,0x54555554,0x54555554,0x55555555,0x55555555,0x55555555,0x55555555

	.word 0x44445555,0x44445555,0x55445555,0x55445555,0x55545555,0x55545555,0x55544555,0x44444555
	.word 0x44444444,0x44455555,0x45555555,0x45555555,0x55555555,0x55555555,0x55555455,0x55555444
	.word 0x44444444,0x55555544,0x55555544,0x55555544,0x55555544,0x55555544,0x45555544,0x45555544
	.word 0x44444444,0x55554445,0x55555545,0x55555545,0x55555555,0x55555555,0x54555554,0x45555544
	.word 0x22244444,0x22244444,0x22244445,0x22244455,0x22244555,0x22244555,0x22244555,0x22244444
	.word 0x22242222,0x22242222,0x22242222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222
	.word 0x11111422,0x11111422,0x11111422,0x11111422,0x11111422,0x11111422,0x11111422,0x11111422
	.word 0x41111111,0x41111111,0x11111141,0x11111141,0x11111141,0x11111141,0x11111141,0x11111141

	.word 0x33333344,0x33333344,0x33333344,0x33333344,0x33333444,0x33333444,0x33333444,0x33334444
	.word 0x44333333,0x44333333,0x44333334,0x44444444,0x44444443,0x44444433,0x44444333,0x44443333
	.word 0x55555555,0x55555555,0x55545555,0x55545555,0x55545555,0x55545555,0x55555555,0x55555555
	.word 0x55554445,0x55554455,0x55554555,0x55554555,0x55554555,0x55554555,0x55554555,0x55554455
	.word 0x44444445,0x55444445,0x55544445,0x55554445,0x55554445,0x55554445,0x55554445,0x55554445
	.word 0x45555555,0x45555555,0x45555555,0x45555545,0x45555545,0x45555545,0x55555545,0x55555555
	.word 0x54555554,0x54555554,0x54555554,0x54555554,0x54555554,0x54555554,0x54555554,0x54555554
	.word 0x55545555,0x55545555,0x55545555,0x55545555,0x55545555,0x55545555,0x55545555,0x55545555

	.word 0x55554455,0x55554455,0x55554455,0x55554455,0x55554455,0x55554455,0x55554455,0x55554455
	.word 0x55555555,0x55555555,0x55555555,0x55554555,0x55554555,0x55554555,0x55554555,0x55554555
	.word 0x44444555,0x54444555,0x55444555,0x55544555,0x55544555,0x55544555,0x55544455,0x55544455
	.word 0x55555554,0x55555555,0x55555555,0x55555455,0x55555455,0x55555455,0x55555455,0x55555555
	.word 0x45555544,0x45555544,0x45555544,0x45555544,0x45555544,0x45555544,0x45555545,0x45555545
	.word 0x55555544,0x55555444,0x55555444,0x55544444,0x55455544,0x55455554,0x55555544,0x55555544
	.word 0x22244444,0x22244445,0x22244455,0x22244455,0x22244555,0x22244555,0x22244555,0x22244555
	.word 0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222422,0x22222422,0x22222422

	.word 0x11111141,0x11111141,0x11111141,0x11111141,0x11111141,0x11111111,0x41111111,0x41111111
	.word 0x33344444,0x33444444,0x34333444,0x44333334,0x44333334,0x33333334,0x33333344,0x33333344
	.word 0x44433333,0x44433333,0x44333333,0x44333333,0x44333333,0x44333333,0x44333333,0x44433333
	.word 0x54444444,0x54444444,0x54444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55555555,0x55555555,0x45555555,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55554455,0x55554445,0x55554444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55554445,0x55544445,0x55444445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55555555,0x45555555,0x44555445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444

	.word 0x54555554,0x54555554,0x54555554,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55545555,0x55545555,0x55545555,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55544455,0x55544455,0x55544455,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55554455,0x55544455,0x55544455,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55544455,0x55444455,0x54444455,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55555555,0x55555555,0x45554455,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x45555545,0x45555544,0x45555544,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55555544,0x55555444,0x55554444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444

	.word 0x22244455,0x22244455,0x22244444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x22222422,0x22224422,0x22224422,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x11111422,0x11111422,0x11111422,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44111111,0x44411111,0x44444411,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x33333444,0x33334444,0x33344444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44433333,0x44443333,0x44444433,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x45555544,0x55555544,0x55445544
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x45544554,0x45544554,0x44544544

	.word 0x55445544,0x45555544,0x55555544,0x55445544,0x55445544,0x55445544,0x55555544,0x45555544
	.word 0x44544544,0x44555544,0x44455444,0x44455444,0x44455444,0x44455444,0x44455444,0x44455444
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44455544,0x44555554
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x54555555,0x54555555
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x55544555,0x55544555
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44554445,0x44554455
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x55544455,0x55544455
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x54455444,0x54455444

	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x55445545,0x55445545
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444455,0x44444455
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44555455,0x44555455
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x55545554,0x55545554
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x45544555,0x45544555
	.word 0x44554554,0x44554554,0x44445554,0x44455544,0x44554444,0x44554554,0x44554554,0x44555554
	.word 0x54445544,0x54445544,0x54445544,0x54445544,0x54445544,0x54445544,0x54445544,0x54445544
	.word 0x45544445,0x45544445,0x45544555,0x55544555,0x55544445,0x45544445,0x45544445,0x45545555

	.word 0x44554455,0x44554455,0x55554455,0x55554455,0x44554445,0x44554444,0x44554444,0x44554444
	.word 0x54544455,0x54554455,0x54554455,0x54554455,0x44454455,0x55554455,0x55555455,0x44455455
	.word 0x54555444,0x54555445,0x54555445,0x55555445,0x55455445,0x55455445,0x55455455,0x54455455
	.word 0x55445545,0x55445545,0x55445545,0x55445545,0x55445545,0x55445545,0x55445545,0x55445545
	.word 0x44444444,0x54444444,0x54444455,0x54444455,0x54444444,0x54444444,0x55444444,0x55444555
	.word 0x44555455,0x44555455,0x44554554,0x44554554,0x44554554,0x44554554,0x54554554,0x54554554
	.word 0x54445454,0x54455455,0x54455455,0x54455455,0x54454445,0x54455555,0x54555555,0x54554445
	.word 0x45544445,0x45544445,0x45544445,0x45544445,0x45544445,0x45544445,0x45544445,0x45544445

	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x54444444,0x54444444
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x54455445,0x54455445
	.word 0x44455544,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x45544455,0x45544455
	.word 0x54445544,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44554454,0x44554454
	.word 0x45545555,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44445554,0x44445554
	.word 0x44554444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x55445554,0x55445554
	.word 0x44455455,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44445555,0x54445555
	.word 0x54455455,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x54445555,0x54455555

	.word 0x55445545,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44455445,0x44455445
	.word 0x55444555,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44554455,0x44554455
	.word 0x55455444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44445554,0x44445554
	.word 0x54554554,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44555444,0x45555544
	.word 0x54554445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x45544554,0x45544554
	.word 0x45544445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44455544,0x44455544
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44554455,0x44554455
	.word 0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444554,0x44444455

	.word 0x54455455,0x55455455,0x55455455,0x55455555,0x45455545,0x55455545,0x55555545,0x45555445
	.word 0x45544454,0x45544554,0x45444554,0x45444554,0x45444544,0x45444555,0x45445555,0x55445544
	.word 0x44554555,0x44554555,0x44454545,0x44454545,0x44454545,0x44454545,0x54454545,0x54455545
	.word 0x44445454,0x44455455,0x44455455,0x44455455,0x44454445,0x44455555,0x54555555,0x54554445
	.word 0x44445454,0x44455455,0x44455455,0x44455455,0x44454445,0x54455555,0x54555555,0x55554445
	.word 0x54445544,0x54444554,0x54444554,0x54444455,0x54444455,0x54444445,0x54444445,0x54445555
	.word 0x54455445,0x54455445,0x54444445,0x54455545,0x54455545,0x54455445,0x54455445,0x54455555
	.word 0x44455445,0x44455445,0x44455445,0x44455445,0x44455445,0x44455445,0x44455445,0x55455555

	.word 0x44554455,0x44554455,0x44554455,0x44554455,0x44554455,0x44554455,0x54554455,0x54555555
	.word 0x44445454,0x44455455,0x44455455,0x44455455,0x44454445,0x44455555,0x44555555,0x44554445
	.word 0x45545544,0x45545544,0x44455544,0x44555444,0x45544444,0x45545544,0x45545544,0x45555544
	.word 0x45544554,0x45544554,0x45555554,0x45555554,0x45544554,0x45544554,0x45544554,0x45544554
	.word 0x44454544,0x44554554,0x44554554,0x44554554,0x44544454,0x44555554,0x45555555,0x45544455
	.word 0x54554455,0x54554455,0x55554455,0x45554455,0x55554455,0x54554455,0x44554455,0x44554455
	.word 0x44444445,0x44444445,0x44444444,0x44444444,0x44444444,0x44444445,0x44444455,0x44444455
	.word 0x54444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444

	.word 0x45555445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55445544,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x54455545,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x54554445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55554445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44445555,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44454555,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x55445555,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444

	.word 0x44554445,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44555444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x45544554,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x45544455,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444
	.word 0x44444554,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444,0x44444444

	.section .rodata
	.align	2
	.global main_startMap		@ 1536 unsigned chars
main_startMap:
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
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0003
	.hword 0x0004,0x0001,0x0001,0x0005,0x0001,0x0006,0x0007,0x0008
	.hword 0x0001,0x0001,0x0001,0x0009,0x000A,0x000B,0x000C,0x000D
	.hword 0x000E,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x000F,0x0010
	.hword 0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,0x0017,0x0018
	.hword 0x0019,0x001A,0x001B,0x001C,0x001D,0x001E,0x001F,0x0020
	.hword 0x0021,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x000F,0x0022
	.hword 0x0023,0x0024,0x0025,0x0026,0x0027,0x0028,0x0029,0x002A
	.hword 0x002B,0x002C,0x002D,0x002E,0x002F,0x001E,0x0030,0x0031
	.hword 0x0032,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0033,0x0034
	.hword 0x0035,0x0036,0x0037,0x0038,0x0039,0x003A,0x003B,0x003C
	.hword 0x003D,0x003E,0x003F,0x0040,0x0041,0x0042,0x0043,0x0044
	.hword 0x0045,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0046
	.hword 0x0047,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0048
	.hword 0x0049,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x004A,0x004B,0x004C,0x004D,0x004E,0x004F
	.hword 0x0050,0x0051,0x044E,0x0052,0x0053,0x0054,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0055,0x0056,0x0057,0x0058,0x0059,0x005A
	.hword 0x005B,0x005C,0x0459,0x005D,0x005E,0x005F,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0060,0x0061,0x0062,0x0063,0x0064,0x0065,0x0066,0x0067
	.hword 0x0068,0x0069,0x006A,0x006B,0x006C,0x006D,0x006E,0x006F
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x000F,0x0070,0x0071,0x0072,0x0073,0x0074,0x0075,0x0076
	.hword 0x0077,0x0078,0x0079,0x007A,0x007B,0x007C,0x007D,0x007E
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x007F,0x0080,0x0081,0x0082,0x0083,0x0084,0x0085,0x0086
	.hword 0x0087,0x0082,0x0088,0x0089,0x008A,0x008B,0x0481,0x008C
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
	.global main_startPal		@ 32 unsigned chars
main_startPal:
	.hword 0x0000,0x59BF,0x7E44,0x3AC7,0x739C,0x2D6B,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(main_start)
