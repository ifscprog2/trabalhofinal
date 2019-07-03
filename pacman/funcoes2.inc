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
   add $a1, $t1, $t6  # y[]
	
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
# int check_wall(*grid, int x,int y);
#--------------------------------------------#
# $a0-> ponteiro do grid   $a1-> ponteiro do animed sprite       
# #$ao e $a1 posicao grid em pixel
# salva informacao strutura sprite mov_x mov_y
# $v0 = retorna 1 tem parede e 0 não tem parede
.globl check_wall
check_wall:
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
 

div $s0, $a0, 7   #calcula posicao x grid 0..34 GRID_1_ROWS
mfhi $t0          
div $s1, $a1, 7   #calula posicao y grid 0..34  GRID_1_COLS     
mfhi $t1
add $t0, $t0, $t1  #verifica se está posicao 0x0 do sprite do grid
bne $t0, $zero, check_wall_end    #$t0 tem valor, sprite nao esta posicao (0,0) 
  sw $zero, 12($a2) #reseta movimento x na struct sprite
  sw $zero, 16($a2) #reseta movimento y na struct sprite
 
aaaaaaaaaaaaa:   
  #verifica o sprite superior (-y) $v0 = 0001 se é parede
  addi $t0, $s1, -1       #posicao superior -y
  mul $t0, $t0,  GRID_1_ROWS        # calcula posicao do vetor grid
  add $t1, $t0, $s0      # pos = (y*35)+x
  la $t2, grid_1
  add $t2, $t2, $t1
  lb  $t3, 0($t2)
  bne $t3, 64, check_wall_ymais   #verifica se sprite superior é comida
     lw $t5, 16($a2)
     addi $t5,$t5, 1           # mov_y = xxx1 -> parede no sprite superior 
     sw $t5, 16($a2)           #  salva move_y	

check_wall_ymais: 
  #verifica o sprite inferior (+y) $v0 = xx1x se é parede
  addi $t0, $s1, 1       #posicao superior -y
  mul $t0, $t0,  GRID_1_ROWS        # calcula posicao do vetor grid
  add $t1, $t0, $s0      # pos = (y*35)+x
  la $t2, grid_1
  add $t2, $t2, $t1
  lb  $t3, 0($t2)
  bne $t3, 64, check_wall_xmais   #verifica se sprite inferior é comida
     lw $t5, 16($a2)
     addi $t5, $t5, 2            # mov_y = xx1x -> parede no sprite inferior 
     sw $t5, 16($a2)           #  salva move_y	
     

check_wall_xmais:
  #verifica o sprite direita (+x) $v0 = x1xx se é parede
  addi  $t0, $s0, 1       #posicao superior +x
  mul $t1, $s1,  GRID_1_ROWS        # calcula posicao do vetor grid
  add $t2, $t0, $t1      # pos = (y*35)+x
  la $t3, grid_1
  add $t3, $t3, $t2
  lb  $t4, 0($t3)
  bne $t4, 64, check_wall_xmenos   #verifica se sprite inferior é comida
   lw $t5, 12($a2)
   addi $t5, $t5, 8            # mov_y = 1xxx -> parede no sprite direita
   sw $t5, 12($a2)           #  salva move_x	
  
check_wall_xmenos:
 #verifica o sprite esquerda (-x) $v0 = 1xxx se é parede
  add $t0, $s0, -1       #posicao superior -x
  mul $t1, $s1,  GRID_1_ROWS        # calcula posicao do vetor grid
  add $t2, $t0, $t1      # pos = (y*7)+x
  la  $t3, grid_1
  add $t3, $t3, $t2
  lb  $t4, 0($t3)
  bne $t4, 64, check_wall_end   #verifica se sprite inferior é comida
     lw   $t5, 12($a2)
     addi $t5, $t5, 4            # mov_y = x1xx -> parede no sprite esquerda
     sw   $t5, 12($a2)           #  salva move_x	
  
check_wall_end:
lw $s0, 12($sp)
lw $s1, 16($sp)
lw $s2, 20($sp)
lw $s3, 24($sp)
lw $ra, 28($sp)       #restaura valores
addi $sp, $sp, 32     #destroi pilha
jr   $ra
    
