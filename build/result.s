
@{{BLOCK(result)

@=======================================================================
@
@	result, 256x160@4, 
@	+ palette 16 entries, not compressed
@	+ 164 tiles (t|f reduced) not compressed
@	+ regular map (flat), not compressed, 32x20 
@	Total size: 32 + 5248 + 1280 = 6560
@
@	Time-stamp: 2015-06-11, 19:15:12
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global resultTiles		@ 5248 unsigned chars
resultTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x77777777,0x77777777,0x77777777,0x77777777
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x67777777,0x67777777,0x67777777,0x67777777
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x76666666,0x76666666,0x76666666,0x76666666
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x67776666,0x67776666,0x67776666,0x67776666
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x66777666,0x66777666,0x66777666,0x66776666
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x66677776,0x66677776,0x66677776,0x66677776
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x77776666,0x77776666,0x77776666,0x77776667

	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x77766667,0x77766667,0x77766667,0x77766667
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x67777777,0x66777777,0x66677777,0x66677777
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x77766666,0x77666666,0x76666666,0x76666776
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x66677777,0x66666777,0x66666777,0x77666677
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x77777776,0x77777666,0x77776666,0x77776666
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x76666777,0x66666667,0x66666667,0x66776666
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x66677777,0x66677776,0x66677776,0x66677766
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x66666677,0x66666677,0x66666677,0x66666677

	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x66677776,0x66667776,0x66666776,0x76666776
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x77777666,0x77776666,0x77766666,0x77766667
	.word 0x67777777,0x67777777,0x67777777,0x67777777,0x67777777,0x67777777,0x67777777,0x67777777
	.word 0x77777666,0x77777666,0x77777666,0x76666666,0x76666666,0x76666666,0x76666666,0x77777666
	.word 0x67776666,0x67776666,0x67776666,0x67776666,0x67776666,0x67776666,0x67776666,0x67776666
	.word 0x66776666,0x66776666,0x66766666,0x66766666,0x66766666,0x66666666,0x66666766,0x66666766
	.word 0x66677776,0x66677776,0x66667776,0x66667776,0x66667776,0x66667776,0x76667776,0x76667776
	.word 0x77776667,0x77776667,0x77766667,0x77766667,0x77766667,0x77766667,0x77766677,0x77766677

	.word 0x77766667,0x77766667,0x77766667,0x77766667,0x77766667,0x77766667,0x77766667,0x77766667
	.word 0x66677777,0x66677777,0x66677777,0x66677777,0x66777777,0x67777777,0x77777777,0x77777777
	.word 0x76666776,0x76666776,0x77777766,0x77776666,0x77766666,0x76666666,0x76666667,0x66666777
	.word 0x77666677,0x77666677,0x77666677,0x77666677,0x77666677,0x77666677,0x77666677,0x77666677
	.word 0x77776666,0x77776666,0x77776666,0x77776666,0x77777777,0x77777777,0x77777777,0x77776666
	.word 0x66776666,0x66776666,0x66776666,0x66776666,0x66776666,0x66776666,0x66776666,0x66776666
	.word 0x66677766,0x66677766,0x66677766,0x66677766,0x66677766,0x66677766,0x66677766,0x66677766
	.word 0x76666776,0x76666776,0x76666666,0x77666666,0x77766666,0x77666666,0x76666776,0x76666776

	.word 0x77666677,0x77666677,0x77666677,0x66666677,0x66666677,0x66666677,0x66666677,0x77666677
	.word 0x76666777,0x76666777,0x66666777,0x66666776,0x66667776,0x66677776,0x67777776,0x77777777
	.word 0x77766667,0x77766667,0x77777777,0x77777766,0x77777666,0x77766666,0x77766666,0x77666667
	.word 0x67777777,0x67777777,0x67777777,0x67777777,0x67777777,0x67777777,0x67777777,0x77777777
	.word 0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777777
	.word 0x67776666,0x67776666,0x67776666,0x67776666,0x67776666,0x67776666,0x67776666,0x77777777
	.word 0x66666766,0x66667766,0x66667766,0x66667766,0x66677766,0x66677766,0x66677766,0x77777777
	.word 0x76667776,0x66667776,0x66667776,0x66666776,0x76666776,0x76666776,0x76666776,0x77777777

	.word 0x77766677,0x77766666,0x77766666,0x77666666,0x77666677,0x77666677,0x77666677,0x77777777
	.word 0x77766667,0x77766667,0x77766667,0x66666667,0x66666667,0x66666667,0x66666667,0x77777777
	.word 0x66677777,0x66677777,0x66677777,0x66677777,0x66677777,0x66777777,0x77777777,0x77777777
	.word 0x66667776,0x66667776,0x66667776,0x66667776,0x66666666,0x76666666,0x77766666,0x77777777
	.word 0x77666677,0x77666677,0x77666677,0x77666677,0x66666777,0x66666777,0x66677777,0x77777777
	.word 0x77776666,0x77776666,0x77776666,0x77776666,0x77777666,0x77777666,0x77777776,0x77777777
	.word 0x66776666,0x66776666,0x66776666,0x66776666,0x66666667,0x66666667,0x76666777,0x77777777
	.word 0x66677766,0x66677766,0x66677766,0x66677766,0x66677776,0x66677776,0x66677777,0x77777777

	.word 0x76666776,0x76666776,0x76666776,0x76666776,0x76666776,0x76666776,0x76666776,0x77777777
	.word 0x77666677,0x77666677,0x77666677,0x66666677,0x66666677,0x66666677,0x66666677,0x77777777
	.word 0x76666777,0x76666777,0x76666777,0x76666766,0x66666766,0x66667766,0x66777766,0x77777777
	.word 0x77666677,0x77666677,0x77666677,0x77666677,0x77666666,0x77766666,0x77777666,0x77777777
	.word 0x77777777,0x77777777,0x77777777,0x55555577,0x55555557,0x55555555,0x55775555,0x55775555
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x55777775,0x55777755,0x55577755,0x55577755
	.word 0x77777777,0x77777777,0x77777777,0x77775555,0x77555555,0x75555555,0x75555775,0x75555775
	.word 0x77777777,0x77777777,0x77777777,0x55577777,0x55555777,0x55555777,0x77555577,0x77555577

	.word 0x77777777,0x77777777,0x77777777,0x77777775,0x77777555,0x77777555,0x77775555,0x77775555
	.word 0x77777777,0x77777777,0x77777777,0x55555555,0x55555555,0x55555555,0x55775555,0x55775555
	.word 0x77777777,0x77777777,0x77777777,0x55557777,0x55557775,0x55557755,0x55557755,0x55557755
	.word 0x77777777,0x77777777,0x77777777,0x77777555,0x77777555,0x77777555,0x77777555,0x77777777
	.word 0x55775555,0x77755555,0x75555555,0x55555557,0x55555577,0x55557777,0x55777777,0x57775555
	.word 0x55577755,0x55577777,0x55577777,0x55577777,0x55577755,0x55577755,0x55577555,0x55577555
	.word 0x75555775,0x75555775,0x75555775,0x77777775,0x77777775,0x77777775,0x75555775,0x75555775
	.word 0x77555577,0x77555577,0x77555577,0x77555577,0x77555577,0x77555577,0x77555577,0x77555577

	.word 0x77775555,0x77775555,0x77775555,0x77775555,0x77775555,0x77775555,0x77775555,0x77775555
	.word 0x55775555,0x55555555,0x55555555,0x55555555,0x55555555,0x55775555,0x55775555,0x55775555
	.word 0x55557755,0x55557755,0x55557775,0x55557777,0x55557775,0x55557755,0x55557755,0x55557755
	.word 0x77777777,0x77777777,0x77777555,0x77777555,0x77777555,0x77777555,0x77777777,0x77777777
	.word 0x57775555,0x57775555,0x57775555,0x55555555,0x55555557,0x55555777,0x77777777,0x77777777
	.word 0x55577555,0x55577555,0x55577555,0x55777555,0x55777755,0x77777777,0x77777777,0x77777777
	.word 0x75555775,0x75555775,0x75555775,0x77555555,0x77555555,0x77775555,0x77777777,0x77777777
	.word 0x77555577,0x77555577,0x77555577,0x55555777,0x55555777,0x55577777,0x77777777,0x77777777

	.word 0x77775555,0x77775555,0x77775555,0x77777555,0x77777555,0x77777775,0x77777777,0x77777777
	.word 0x55775555,0x55775555,0x55775555,0x55775555,0x55775555,0x55775555,0x77777777,0x77777777
	.word 0x77777777,0x77777777,0x77775555,0x77775555,0x77775555,0x77775555,0x77777777,0x77777777
	.word 0x77777777,0x77777777,0x66666777,0x66666777,0x66666777,0x76666777,0x76666777,0x76666777
	.word 0x77777777,0x77777777,0x67777666,0x67776666,0x67766666,0x67766667,0x67766667,0x67766667
	.word 0x77777777,0x77777777,0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777666
	.word 0x77777777,0x77777777,0x66666667,0x66666667,0x66666667,0x66676667,0x66676667,0x66676667
	.word 0x77777777,0x77777777,0x66667777,0x66667777,0x66677777,0x66677777,0x66677777,0x66677777

	.word 0x77777777,0x77777777,0x77666677,0x77666677,0x77766677,0x77766677,0x77766677,0x77766677
	.word 0x77777777,0x77777777,0x76666666,0x76666666,0x76666666,0x76666666,0x77776666,0x77776666
	.word 0x77777777,0x77777777,0x66666677,0x66666677,0x66666677,0x77666677,0x77666677,0x77666677
	.word 0x77777777,0x77777777,0x77777766,0x77777666,0x77776666,0x77776666,0x77776666,0x77776666
	.word 0x77777777,0x77777777,0x76666777,0x76666777,0x76666777,0x76666777,0x76667777,0x76667777
	.word 0x77777777,0x77777777,0x77766677,0x77766677,0x77666667,0x77666667,0x77666667,0x77666667
	.word 0x77777777,0x77777777,0x67776666,0x67776666,0x67776666,0x67776666,0x67777666,0x67777666
	.word 0x77777777,0x77777777,0x66777666,0x66777666,0x66777666,0x66777666,0x66777666,0x66777666

	.word 0x77777777,0x77777777,0x66677766,0x66677766,0x66677766,0x66677666,0x66677666,0x66677666
	.word 0x77777777,0x77777777,0x66667777,0x66666777,0x66666677,0x77666677,0x77666677,0x77666677
	.word 0x77777777,0x77777777,0x66667777,0x66667777,0x66667777,0x66667777,0x66667777,0x66667777
	.word 0x76666777,0x76666777,0x66666777,0x66666777,0x66666777,0x76666777,0x76666777,0x76666777
	.word 0x67766667,0x67766667,0x67766666,0x67776666,0x67777666,0x67777777,0x67777777,0x67777777
	.word 0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777666
	.word 0x66676666,0x66676666,0x66676666,0x66676666,0x66777666,0x66777666,0x66777666,0x66666666
	.word 0x66777776,0x66777776,0x66777776,0x66777776,0x67777776,0x67777776,0x67777776,0x67777776

	.word 0x77776677,0x77776666,0x77776666,0x77776666,0x77777666,0x77777666,0x77777666,0x77777666
	.word 0x77776666,0x76666666,0x76666666,0x76666666,0x76666666,0x77776666,0x77776666,0x77776666
	.word 0x66666677,0x66666677,0x66666677,0x66666677,0x77666677,0x77666677,0x77666677,0x77666677
	.word 0x77776666,0x77777666,0x77777766,0x77777666,0x77776666,0x77776666,0x77776666,0x77776666
	.word 0x76667777,0x76667777,0x76667777,0x76667777,0x76667777,0x76667777,0x76667777,0x76677777
	.word 0x77666667,0x77666667,0x76667666,0x76667666,0x76667666,0x76667666,0x76667666,0x76667666
	.word 0x67777666,0x67777666,0x67777666,0x67777666,0x67777666,0x67777666,0x67777666,0x67777766
	.word 0x66676666,0x66676666,0x66676666,0x66666666,0x66666676,0x66666676,0x66666676,0x66666776

	.word 0x76666677,0x66666677,0x66666777,0x66667777,0x66777777,0x77777777,0x77666677,0x77666677
	.word 0x77777777,0x77777776,0x77777766,0x77776666,0x77776666,0x77766666,0x77766667,0x77766667
	.word 0x66667777,0x66667777,0x66667777,0x66667777,0x66667777,0x76667777,0x76677777,0x76677777
	.word 0x76666777,0x76666777,0x76666777,0x76666777,0x76666777,0x77777777,0x77777777,0x77777777
	.word 0x67777777,0x67777777,0x67777777,0x67777777,0x67777777,0x77777777,0x77777777,0x77777777
	.word 0x77777666,0x67666666,0x67666666,0x67666666,0x67666666,0x77777777,0x77777777,0x77777777
	.word 0x66666666,0x66666666,0x66777666,0x66777666,0x66777666,0x77777777,0x77777777,0x77777777
	.word 0x67777776,0x67777766,0x67777766,0x67777766,0x67777766,0x77777777,0x77777777,0x77777777

	.word 0x77777666,0x77777666,0x77777666,0x77777666,0x77777666,0x77777777,0x77777777,0x77777777
	.word 0x77776666,0x66666666,0x66666666,0x66666666,0x66666666,0x77777777,0x77777777,0x77777777
	.word 0x77666677,0x77666677,0x77666677,0x77666677,0x77666677,0x77777777,0x77777777,0x77777777
	.word 0x77776666,0x77776666,0x77776666,0x77776666,0x77776666,0x77777777,0x77777777,0x77777777
	.word 0x66667666,0x66677766,0x66677766,0x66677766,0x66677766,0x77777777,0x77777777,0x77777777
	.word 0x67777766,0x67777766,0x67777766,0x67777766,0x67777766,0x77777777,0x77777777,0x77777777
	.word 0x66777666,0x66777666,0x66777666,0x66777666,0x66777666,0x77777777,0x77777777,0x77777777
	.word 0x66666776,0x66666776,0x66667776,0x66667776,0x66667776,0x77777777,0x77777777,0x77777777

	.word 0x77666677,0x77666677,0x66666677,0x66666777,0x66677777,0x77777777,0x77777777,0x77777777
	.word 0x77766667,0x77766667,0x77766666,0x77776666,0x77777766,0x77777777,0x77777777,0x77777777
	.word 0x77777777,0x66667777,0x66667777,0x66667777,0x66667777,0x77777777,0x77777777,0x77777777
	.word 0x77777777,0x77777777,0x77777777,0x88877777,0x88887777,0x88887777,0x78888777,0x78888777
	.word 0x77777777,0x77777777,0x77777777,0x77777788,0x77778888,0x77778888,0x77788887,0x77788887
	.word 0x77777777,0x77777777,0x77777777,0x77777777,0x77777777,0x88777777,0x88887777,0x88887777
	.word 0x77777777,0x77777777,0x77777777,0x77777887,0x77777888,0x77777888,0x77777888,0x77777888
	.word 0x77777777,0x77777777,0x77777777,0x88877777,0x88887777,0x88887777,0x77888777,0x77888777

	.word 0x77777777,0x77777777,0x77777777,0x77777788,0x77777888,0x77777888,0x77778888,0x77778888
	.word 0x77777777,0x77777777,0x77777777,0x88877777,0x88887777,0x88888777,0x78888777,0x78888777
	.word 0x77777777,0x77777777,0x77777777,0x88777777,0x88777777,0x88877777,0x88877777,0x88877777
	.word 0x77777777,0x77777777,0x77777777,0x77778888,0x77778888,0x77778888,0x77778888,0x77778888
	.word 0x77777777,0x77777777,0x77777777,0x88888777,0x88888777,0x88888777,0x78888777,0x78888777
	.word 0x77777777,0x77777777,0x77777777,0x77788888,0x77788888,0x77788888,0x77777777,0x77777777
	.word 0x77777777,0x77777777,0x77777777,0x88887777,0x88887777,0x88887777,0x77777777,0x77777777
	.word 0x78888777,0x78888777,0x78888777,0x78888777,0x78888777,0x78888777,0x78888777,0x78888777

	.word 0x87777777,0x87777777,0x87777777,0x87777777,0x87777777,0x87777777,0x87777777,0x87777777
	.word 0x77777888,0x77777888,0x77777888,0x77777888,0x77777888,0x77777888,0x77777888,0x77777888
	.word 0x77888777,0x77888777,0x87777777,0x87777777,0x88777777,0x88777777,0x88777777,0x88877777
	.word 0x77778888,0x77778888,0x77778888,0x77777888,0x77777888,0x77777788,0x77777788,0x77777778
	.word 0x78888777,0x77777777,0x88777777,0x88777777,0x88777777,0x77777777,0x78888777,0x78888777
	.word 0x77788887,0x77788887,0x77778888,0x77777888,0x77778888,0x77788887,0x77788887,0x77788887
	.word 0x78887777,0x78887777,0x78887777,0x77888777,0x77888777,0x77888777,0x77788877,0x88888877
	.word 0x77778888,0x77778888,0x77778888,0x77778888,0x77778888,0x77778888,0x77778888,0x77788888

	.word 0x78888777,0x88888777,0x88888777,0x78888777,0x78888777,0x77777777,0x77777777,0x78888777
	.word 0x77777888,0x77778888,0x77788888,0x77788887,0x77788887,0x77788887,0x77788887,0x77788887
	.word 0x78888777,0x78888777,0x88888777,0x88888777,0x78888777,0x78888777,0x78888777,0x78888777
	.word 0x77777777,0x77777888,0x77778888,0x77788888,0x77788887,0x77788887,0x77788887,0x77788887
	.word 0x77777777,0x77777777,0x77777777,0x87777777,0x87777777,0x87777777,0x87777777,0x88777777
	.word 0x77778888,0x77777888,0x77777888,0x77777888,0x77777888,0x77777888,0x77777788,0x77777788
	.word 0x77788887,0x77788887,0x77788887,0x77788887,0x77788887,0x77788888,0x77788888,0x77788887
	.word 0x78888777,0x78888777,0x78888777,0x88887777,0x88887777,0x88877777,0x77777777,0x77777777

	.word 0x77788887,0x77788887,0x77788887,0x77788888,0x77778888,0x77777888,0x77777777,0x77777777
	.word 0x87777777,0x87777777,0x87777777,0x87777777,0x87777777,0x87777777,0x77777777,0x77777777
	.word 0x77777888,0x77777888,0x77777888,0x77777888,0x77777888,0x77777888,0x77777777,0x77777777
	.word 0x88877777,0x88887777,0x88887777,0x88888777,0x88888777,0x88888777,0x77777777,0x77777777
	.word 0x77777778,0x77777777,0x77777777,0x77778888,0x77778888,0x77778888,0x77777777,0x77777777
	.word 0x88888877,0x88888877,0x88888877,0x77777777,0x77777777,0x77777777,0x77777777,0x77777777
	.word 0x77788888,0x77788888,0x77788888,0x77778888,0x77778888,0x77778888,0x77777777,0x77777777
	.word 0x78888777,0x78888777,0x78888777,0x88888777,0x88887777,0x88777777,0x77777777,0x77777777

	.word 0x88777777,0x88777777,0x88777777,0x88777777,0x88877777,0x88877777,0x77777777,0x77777777
	.word 0x77777788,0x77777788,0x77777788,0x77777778,0x77777778,0x77777778,0x77777777,0x77777777
	.word 0x77777777,0x78888777,0x78888777,0x88888777,0x88887777,0x88877777,0x77777777,0x77777777
	.word 0x77788887,0x77788887,0x77788887,0x77778888,0x77778888,0x77777788,0x77777777,0x77777777

	.section .rodata
	.align	2
	.global resultMap		@ 1280 unsigned chars
resultMap:
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002
	.hword 0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x000A
	.hword 0x000B,0x000C,0x000D,0x000E,0x000A,0x000F,0x0010,0x0011
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0012
	.hword 0x0013,0x0014,0x0015,0x0016,0x0017,0x0018,0x0019,0x001A
	.hword 0x001B,0x001C,0x001D,0x001E,0x001F,0x0020,0x0021,0x0022
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0023
	.hword 0x0024,0x0025,0x0026,0x0027,0x0028,0x0029,0x002A,0x002B
	.hword 0x002C,0x002D,0x002E,0x002F,0x0030,0x0031,0x0032,0x0033
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0034,0x0035
	.hword 0x0036,0x0037,0x0038,0x0039,0x003A,0x003B,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x003C,0x003D
	.hword 0x003E,0x003F,0x0040,0x0041,0x0042,0x0043,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0044,0x0045
	.hword 0x0046,0x0047,0x0048,0x0049,0x0449,0x004A,0x0001,0x0001
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
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x004B,0x004C
	.hword 0x004D,0x004E,0x004F,0x0050,0x0051,0x0052,0x0053,0x0001
	.hword 0x0001,0x0054,0x0055,0x0056,0x0057,0x0058,0x0059,0x0053
	.hword 0x005A,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x005B,0x005C
	.hword 0x005D,0x005E,0x005F,0x0060,0x0061,0x0062,0x0063,0x0001
	.hword 0x0001,0x0064,0x0065,0x0066,0x041E,0x0067,0x0068,0x0069
	.hword 0x006A,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x006B,0x006C
	.hword 0x006D,0x006E,0x006F,0x0070,0x0071,0x0072,0x0073,0x0001
	.hword 0x0001,0x0470,0x0074,0x0075,0x0076,0x0077,0x0078,0x0079
	.hword 0x007A,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x007B,0x007C,0x007D,0x007E,0x007F,0x0080,0x0081,0x0481
	.hword 0x0082,0x0083,0x0084,0x0085,0x047C,0x0481,0x0086,0x0083
	.hword 0x0081,0x0481,0x0081,0x047B,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0087,0x0487,0x0088,0x0089,0x008A,0x008B,0x008C,0x008D
	.hword 0x008E,0x008F,0x0090,0x0091,0x0092,0x0093,0x0094,0x0095
	.hword 0x048D,0x008D,0x0C91,0x0096,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.hword 0x0097,0x0098,0x0099,0x009A,0x009B,0x009C,0x0498,0x0098
	.hword 0x009D,0x009E,0x009F,0x0098,0x0097,0x0098,0x00A0,0x00A1
	.hword 0x0498,0x0098,0x00A2,0x00A3,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001
	.hword 0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001

	.section .rodata
	.align	2
	.global resultPal		@ 32 unsigned chars
resultPal:
	.hword 0x0000,0x7FFF,0x413C,0x77BE,0x2D6B,0x7E44,0x3AC7,0x739C
	.hword 0x2D6B,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(result)