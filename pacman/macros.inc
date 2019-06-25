
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

.macro moviment (%name, %valid, %x, %y)
.data
%name:
.align 2
	.word %valid #1 é válido e 0 inválido
	.word %x
	.word %y
	
.end_macro
#entrada texto %str
# $a0-> ponteiro string   $v0-> syscall
# usa $t8  $t9
.macro macro_print_string(%str)
.data

my_str: .asciiz %str


.text
  move $t8,$a0
  move $t9,$v0 
  li $v0,4
  la $a0, my_str
  syscall
  move $a0, $t8
  move $v0, $t9

.end_macro
