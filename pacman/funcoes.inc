.text
j main
                                     
# draw_grid(width, height, grid_table)
.globl draw_grid
draw_grid:

jr   $ra




# draw_sprite(int x, int y, int sprite_id)  posicao em pixel 
#$a0-> x   $a1-> y   $a2->sprite_id [0.. n sprite]
# draw_sprite(X, Y, sprite_id)
.globl draw_sprite
draw_sprite:
#-------------------------------
# $ra       20($sp)
# #s4       16($sp)
# $s3       12($sp)
# $s2        8($sp)
# $s1        4($sp)
# $s0        0($sp)
#-------------------------------	
addi $sp, $sp, -24
sw $ra, 20($sp)
sw $s4, 16($sp)
sw $s3, 12($sp)
sw $s2,  8($sp)
sw $s1,  4($sp)
sw $s0,  0($sp)
	
move $s0, $a0     # necessario salvar $a0, $a1, set pixel altera
move $s1, $a1
	
la $s2, sprites    # carrega ponteiro sprite[0]
mul $t1, $a2, 49   
add $s2, $t1, $s2  # ponteiro sprint[id]

	
la $s4, colors     # carrega ponteiro colors[0]	
li $s3, 0          # ponteiro varredura sprite 
draw_sprite_loop:	
   bge $s3, SPRITE_SIZE, draw_sprite_end
   lbu $t3, 0($s2)   # carrega pixel do sprite (cor)
   sll $t3, $t3, 2   
   add $t3, $t3, $s4  # ponteiro cor[] carregada do sprite
   lw  $a2, 0($t3)    # carrega cor[]
   div $t5, $s3, 7 #t5 y  #calcula posicao y
   mfhi $t6 #t6 X         # posicao x
   add $a0, $s0, $t6
   add $a1, $s1, $t5
	
   jal set_pixel
   addi $s3, $s3, 1  #passo loop 
   addi $s2, $s2, 1  #proximo pixel sprite
   b draw_sprite_loop


draw_sprite_end:
lw $ra, 20($sp)       #restaura valores
lw $s4, 16($sp)
lw $s3, 12($sp)
lw $s2,  8($sp)
lw $s1,  4($sp)
lw $s0,  0($sp)
addi $sp, $sp, 24
jr   $ra
    


    
# set_pixel(X, Y, color)
.globl set_pixel


set_pixel:
   la  $t0, FB_PTR
   mul $a1, $a1, FB_XRES
   add $a0, $a0, $a1
   sll $a0, $a0, 2
   add $a0, $a0, $t0
   sw  $a2, 0($a0)
   jr  $ra
