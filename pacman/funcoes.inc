.text
j main
                                     
# draw_grid(cols, rows, *grid_table)
# $A0 - cols  $A1->rows   $A2->GRID
.globl draw_grid
draw_grid:

# |-----------|
# | $a0       | 0 ($sp)
# | $a1       | 4 ($sp)
# | $a2       | 8 ($sp)
# | $s0       | 12 ($sp)
# | $s1       | 16 ($sp)
# | $s2       | 20  ($sp)
# | $s3       | 24
# | $ra       | 28 ($sp)
# |===========|
# | $a0       | 32 ($sp) (quadro anterior)
# | $a1       | 36($sp)
# | $a2       | 40($p)
# |-----------|	
addi $sp, $sp, -32
sw $s0, 12($sp)
sw $s1, 16($sp)
sw $s2, 20($sp)
sw $s3, 24($sp)
sw $ra, 28($sp)

		
mul  $s0,$a0,$a1    # tamanho da grid
move $s1, $zero     # passo grid 
move $s2, $a2      # carrega ponteiro gride[0]
	
draw_grid_loop:	
   beq $s1, $s0, draw_grid_end    #if (i<49) 
   lbu $a2, 0($s2)    # carrega byte do grid[i] (cor)
   add $a2, $a2, -64  # $a2-> posicao do sprite
   div $t6, $s1, GRID_1_ROWS    # $t6 y  alcula posicao y
   mfhi $t7 #t6 X     # $t7 resto e posicao x
   
   mul $a0, $t7, X_SCALE   # x[]  
   mul $a1, $t6, Y_SCALE   # y[]
	
   jal draw_sprite
   addi $s1, $s1, 1  # i--
   addi $s2, $s2, 1  # gride[id[++]]
   b draw_grid_loop


draw_grid_end:
lw $s0, 12($sp)
lw $s1, 16($sp)
lw $s2, 20($sp)
lw $s3, 24($sp)
lw $ra, 28($sp)       #restaura valores
addi $sp, $sp, 32     #destroi pilha
jr   $ra
    





# draw_sprite(int x, int y, int sprite_id)  posicao em pixel 
#$a0-> x   $a1-> y   $a2->sprite_id [0.. n sprite]
# draw_sprite(X, Y, sprite_id)
.globl draw_sprite
draw_sprite:
# |-----------|
# | $a0       | 0 ($sp)
# | $a1       | 4 ($sp)
# | $a2       | 8 ($sp)
# | $ra       | 12 ($sp)
# |===========|
# | $a0       | 8 ($sp) (quadro anterior)
# | $a1       | 12($sp)
# | $a2       | 16($p)
# |-----------|	
addi $sp, $sp, -16
sw $ra, 12($sp)

		
move $t0, $a0     # $t0 pos x
move $t1, $a1     # $t1 pos y
	
la  $t2, sprites    # carrega ponteiro sprite[0]
mul $t8, $a2, 49   
add $t2, $t8, $t2  # ponteiro sprite[id[0]]

	
la $t4, colors     # carrega ponteiro colors[0]	
li $t5, 0          # ponteiro varredura sprite i=0 
draw_sprite_loop:	
   bge $t5, SPRITE_SIZE, draw_sprite_end    #if (i<49) 
   lbu $t3, 0($t2)   # carrega pixel do sprite[id][i] (cor)
   sll $t3, $t3, 2   
   add $t3, $t3, $t4  # ponteiro cor[sprite[id][i]] carregada do sprite
   lw  $a2, 0($t3)    # $a2->carrega cor[sprite[id][i]]
   div $t6, $t5, 7    # $t5 y  alcula posicao y
   mfhi $t7            # $t6 resto e posicao x
   add $a0, $t0, $t7  # x[]  
   add $a1, $t1, $t6  # y[]
	
   jal set_pixel
   addi $t5, $t5, 1  # i++
   addi $t2, $t2, 1  # prite[id[++]]
   b draw_sprite_loop


draw_sprite_end:
lw $ra, 12($sp)       #restaura valores
addi $sp, $sp, 16     #destroi pilha
jr   $ra
    


    
# set_pixel(X, Y, color)
# obrigatorio ter quadro de pilha anterior
.globl set_pixel

set_pixel:

la  $t9, FB_PTR
mul $a1, $a1, FB_XRES
add $a0, $a0, $a1
sll $a0, $a0, 2
add $a0, $a0, $t9
sw  $a2, 0($a0)

jr  $ra


#pacman movement
# void movement_pacman();

.globl movement_pacman
movement_pacman:
# |-----------|
# | $a0       | 0 ($sp)
# | $a1       | 4 ($sp)
# | $a2       | 8 ($sp)
# | $s0       | 12 ($sp)
# | $s1       | 16($sp)
# | $s2       | 20 ($sp)
# | $s3       | 24 ($sp)
# | $ra       | 28 ($sp)
# |===========|
# | $a0       | 32 ($sp) (quadro anterior)
# | $a1       | 36($sp)
# | $a2       | 40($p)
# |-----------|	
addi $sp, $sp, -32
sw $s0,12($sp)
sw $s1,16($sp)
sw $s2,20($sp)
sw $s3,24($sp)
sw $ra,28($sp)    
 
    li $a2,3    #sprite
    la $t0, pacman
    lw $s0, 4($t0)      # posicao x  pacman
    lw $s1, 8($t0)      # posicao y  pacman   
    la $t3,  mov_pacman # carrega estrutura movimento pacman
    lw $s2, 0($t3)      # carrega validade movimento
    lw $s3, 4($t3)      # carrega se ha movimento x x=1-> mov(+)   x=0-> mov(0)   x=-1-> mov(-)
    lw $s4, 8($t3)      # carrega se ha movimento y y=1-> mov(+)   y=0-> mov(0)   y=-1-> mov(-)
          
    beq $s2, $zero, movement_pacman_end
    beq $s3, 1, movement_pacman_x_mais
    beq $s3, -1,movement_pacman_x_menos
    beq $s4, 1, movement_pacman_y_mais
    beq $s4, -1, movement_pacman_y_menos
    j movement_pacman_end
  
movement_pacman_x_mais:
    addi  $a0,$s0, 1   # x
    move  $a1, $s1       # y
    sw    $a0, 4($t0)      # salva posicao x  pacman
    jal   draw_sprite
    j movement_pacman_end    
movement_pacman_x_menos:
    addi  $a0, $s0, -1   # x
    move  $a1, $s1       # y
    sw    $a0, 4($t0)      # salva posicao x  pacman
    jal  draw_sprite
    j movement_pacman_end
movement_pacman_y_mais:
    move  $a0,$s0          # x
    addi  $a1,$s1, -1       # y
    sw    $a1, 8($t0)      # salva posicao y  pacman
    jal  draw_sprite
    j movement_pacman_end
movement_pacman_y_menos:    
    move  $a0,$s0          # x
    addi  $a1,$s1, +1       # y
    sw    $a1, 8($t0)      # salva posicao y  pacman
    jal  draw_sprite
    j movement_pacman_end
 

movement_pacman_end:
lw $s0, 12($sp)
lw $s1, 16($sp)
lw $s2, 20($sp)
lw $s3, 24($sp)
lw $ra, 28($sp)       #restaura valores
addi $sp, $sp, 32     #destroi pilha
jr   $ra
    

