#--------------------------------------------#
#struct animed sprite
#--------------------------------------------#
.macro animed_sprite (%name, %id, %pos_x, %pos_y, %mov_pos_x, %mov_pos_y, %mov_x, %mov_y, %inven)
.data
%name:
.align 2
	.word %id            # 0
	.word %pos_x         # 4 posicao x atual
	.word %pos_y         # 8 posicao y atual
	.word %mov_pos_x     # 12 em movimento x possiveis 
	.word %mov_pos_y     # 16 em movimento y possiveis
	.word %mov_x         # 20 movimento atual x
	.word %mov_y         # 24 movimento atual y
        .word %inven         # 28 invencibilidade  0-> vencivel 
.end_macro

.macro moviment (%name, %valid, %x, %y)
.data
%name:
.align 2
	.word %valid #1 é válido e 0 inválido
	.word %x
	.word %y
	
.end_macro

#--------------------------------------------#
# entrada texto %str
# void macro_print_string(String)
#--------------------------------------------#
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


#--------------------------------------------#
## DELAY(50)
#void delay(ms)
#--------------------------------------------#
.macro macro_delay(%ms)
.data

.text

add $a0, $zero, %ms
li $v0, 32
syscall
 	
.end_macro





