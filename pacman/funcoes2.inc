.text
j main

#--------------------------------------------#                                                                          
# draw_grid(cols, rows, *grid_table)
#ari
#--------------------------------------------#
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
    




#--------------------------------------------#
# draw_sprite(int x, int y, int sprite_id)  posicao em pixel 
# draw_sprite(X, Y, sprite_id)
#--------------------------------------------#
#$a0-> x   $a1-> y   $a2->sprite_id [0.. n sprite]

.globl draw_sprite
draw_sprite:
# |-----------|
# | $a0       | 0 ($sp)
# | $a1       | 4 ($sp)
# | $a2       | 8 ($sp)
# | $ra       | 12 ($sp)
# |===========|
# | $a0       | 16 ($sp) (quadro anterior)
# | $a1       | 20($sp)
# | $a2       | 24($p)
# |-----------|	
addi $sp, $sp, -16
sw   $ra, 12($sp)
sw   $a0, 16($sp)  #quadro pilha anterior
sw   $a0, 20($sp)
sw   $a0, 24($sp)

		
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
   add $a0, $a0, X_OFFSET
   add $a1, $t1, $t6  # y[]
   add $a1, $a1, Y_OFFSET	
   jal set_pixel
   addi $t5, $t5, 1  # i++
   addi $t2, $t2, 1  # prite[id[++]]
   b draw_sprite_loop


draw_sprite_end:
lw $ra, 12($sp)       #restaura valores
lw  $a0, 16($sp)      #quadro pilha anterior
lw  $a0, 20($sp)
lw  $a0, 24($sp)

addi $sp, $sp, 16     #destroi pilha
jr   $ra
    


#--------------------------------------------#   
# set_pixel(X, Y, color)
# obrigatorio ter quadro de pilha anterior
#--------------------------------------------#
.globl set_pixel

set_pixel:
addi $sp, $sp, -8
sw  $s0,0($sp)

la  $s0, FB_PTR
mul $a1, $a1, FB_XRES
add $a0, $a0, $a1
sll $a0, $a0, 2
add $a0, $a0, $s0
sw  $a2, 0($a0)

lw $s0, 0($sp)
addi $sp, $sp, 8     #destroi pilha
jr  $ra



#--------------------------------------------#
# check_wall
# int check_wall(int x,int y, *grid);
#--------------------------------------------#
# $a0-> posi��o no grid X $a1-> posi��o no grid Y  $a2-> ponteiro do grid      
# $v0 = retorna 1 tem parede e 0 n�o tem parede
.globl check_wall
# |-----------|
# | $a0       | 0 ($sp)
# | $a1       | 4 ($sp)
# | $a2       | 8 ($sp)
# | $s0       | 12 ($sp)
# | $s1       | 16 ($sp)
# | $s2       | 20 ($sp)
# | $s3       | 24 ($sp)
# | $ra       | 28 ($sp)
# |===========|
# | $a0       | 32 ($sp) (quadro anterior)
# | $a1       | 36($sp)
# | $a2       | 40($p)
# |-----------|	
check_wall:
addi $sp, $sp, -32
sw $s0, 12($sp)
sw $s1, 16($sp)
sw $s2, 20($sp)
sw $s3, 24($sp)
sw $ra, 28($sp)



mul $s0, $a1, GRID_1_ROWS   #calcula posicao do grid          
add $s1, $a0, $s0   #posi��o final no grid   
add $s1, $s1, $a2 #posi��o do vetor grid
lb $s0, 0($s1) #carrega o id do sprite

move $v0, $zero #caso n�o tenha parede

beq $s0, 64, check_wall_end    #verifica se � comida
beq $s0, 65, check_wall_end    #verifica se � a p�lula
beq $s0, 68, check_wall_end    #verifica se � a cereja
beq $s0, 67, check_wall_end    #verifica se � a pacman  
  
addi $v0, $v0, 1 #tem parede
  
check_wall_end:
lw $s0, 12($sp)
lw $s1, 16($sp)
lw $s2, 20($sp)
lw $s3, 24($sp)
lw $ra, 28($sp)
addi $sp, $sp, 32     #destroi pilha
jr   $ra
    



#--------------------------------------------#
# reset
# coid reset();
#--------------------------------------------#
reset:
 la $t0, pacman
 li $t1, 119
 sw $t1, 4($t0)  # pos_x
 li $t1, 147
 sw $t1, 8($t0)  # pos_y
 sw $zero, 12($t0) # mov_x
 sw $zero, 16($t0) # mov_y
 la $t0, pontuacao
 sw $zero, 0($t0)  #pontuacao
 la $t0, mov_pacman
 sw $zero, 0($t0)  #        

    
jr   $ra        
                
