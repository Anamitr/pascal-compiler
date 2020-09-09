	jump.i	#lab0
lab0:
	add.i	0,4,24
	inttoreal.i	24,28
	mov.r	28,8
	write.r	8
	exit
