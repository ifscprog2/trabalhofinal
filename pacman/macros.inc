
#struct animed sprite
.macro animed_sprite (%name, %id, %pos_x, %pos_y, %mov_x, %mov_y)
.data
%name:
.align 2
	.word %id
	.word %pos_x
	.word %pos_y
	.word %mov_x
	.word %mov_y
.end_macro