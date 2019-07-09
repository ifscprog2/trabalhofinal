	

#--------------------------------------------#
# ghost_1 movement
# void movement_ghost_1();
#--------------------------------------------#
.globl movement_ghost
movement_ghost:
# |-----------|
# | $a0       | 0 ($sp)
# | $a1       | 4 ($sp)
# | $a2       | 8 ($sp)
# | $s0       | 12 ($sp)
# | $s1       | 16($sp)
# | $s2       | 20 ($sp)
# | $s3       | 24 ($sp)
# | $s4       | 28 ($sp)
# | $s5       | 32 ($sp)
# | $s6       | 36 ($sp)
# | $ra       | 40 ($sp)
# | $empty    | 44 ($sp)
# |===========|
# | $a0       | 32 ($sp) (quadro anterior)
# | $a1       | 36($sp)
# | $a2       | 40($sp)
# |-----------|	
addi $sp, $sp, -48
sw $s0,12($sp)
sw $s1,16($sp)
sw $s2,20($sp)
sw $s3,24($sp)
sw $s4,28($sp)
sw $s5,32($sp)
sw $s6,36($sp)
sw $ra,40($sp)    
 

   
   la $s2, ghost_1      # struct animed_sprite
    la $s1, mov_pacman  # struct moviment
    la $a2, grid_1

    lw $t0, 4($s1)       # x mov_pacman temporario ate fazer a logica do ghost_1
    lw $t1, 4($s2)       # x ghost_1 pixel
    div $t4, $t1, 7       # x ghost_1 em  grid
    
 
    mfhi $t6             #resto, será usado para ver se está no ponto 0,0 do sprite
    add $a0, $t0, $t4    # posicao x de pesquisa (para verificar parede)
    lw $t2, 8($s1)       # y mov_pacman
    lw $t3, 8($s2)       # y ghost_1 pixel
    div $t5, $t3, 7      # y ghost_1 em grid
    
    
    mfhi $t7
    add $a1, $t2, $t5    # posicao x de pesquisa
    add $t7, $t6, $t7    # se zero está na posicao (0,0) do sprite
    bnez $t7, mov_ghost_1_0
     jal check_wall       # retorna $v0->1 se é parede
     
     
     
     bnez $v0, mov_ghost_1_0  #if (parede=0)
     
    
  
       sw $t0, 12($s2)  # guarda novo movimento x
       sw $t2, 16($s2)  # guarda novo movimento y  
        
    
      
mov_ghost_1_0: 
   
  
    
    lw $t0, 4($s2)       # pos_x ghost_1   
    lw $t1, 12($s2)      # mov_x pacman 
    div $t4, $t0, 7       # x ghost_1 grid      
    mfhi $t6
    add $a0, $t1, $t4    # posicao x de pesquisa
    
    lw $t2, 8($s2)       # pos_y ghost_1
    lw $t3, 16($s2)      # mov_y pacman 
    div $t5, $t2, 7      # y ghost_1 grid   
    mfhi $t7
    add $a1, $t3, $t5    # posicao x de pesquisa
    
    add $t7, $t6, $t7    # se zero está na posicao (0,0) sprite
    bnez $t7, mov_ghost_1_1
     
    
    
    jal check_wall       # retorna $v0->1 se é parede 
    
    bnez $v0, movement_ghost_1_end  #if (parede=0)
    
     
 
mov_ghost_1_1: 

  
  add $a0, $t1, $t0  # atualiza pos_x
  sw $a0, 4($s2)
  add $a1, $t2, $t3 # atualiza pos_y
  sw $a1, 8($s2)

    lw $t0 , 12 ($s2)
     beq $t0, 1, baixo_ou_direita
     beq $t0, -1, esquerda
     lw $t0 , 16 ($s2)
     beq $t0, 1,baixo_ou_direita
     beq $t0, -1, subir
     
     
     baixo_ou_direita:
   
     div $s6, $a1, 7 
     mfhi $t0
     sub $s6, $a1, $t0
     
     div $s5, $a0, 7 
     mfhi $t0
     sub $s5, $a0, $t0
     
      
   j mov_ghost_1_2
   
   
    esquerda:
  
     li $t1, 7
     div $s5, $a0, 7 
     mfhi $t0
     sub $s5, $t1, $t0
     add $s5, $s5, $a0
     
     add $s6, $a1, $zero
  j mov_ghost_1_2
  
  subir:
  
     li $t1, 7
     div $s6, $a1, 7 
     mfhi $t0
     sub $s6, $t1, $t0
     add $s6, $s6, $a1
     
     add $s5, $a0, $zero
  
  
 mov_ghost_1_2:
      
  add $s3, $a0, $zero
  add $s4, $a1, $zero
 
  
     
  add $a0, $s5, $zero
  add $a1, $s6, $zero
  
  div $t4, $s5, 7       # x ghost_1 em  grid

  div $t5, $s6, 7       # y ghost_1 em  grid
 
  
  mul $t5, $t5, GRID_1_ROWS
  add $t4, $t5, $t4
   la $a2, grid_1
   add $t4, $t4, $a2
 
  
 lbu $a2, 0($t4)
 subi $a2, $a2, 64

  jal draw_sprite


 add $a0, $s3, $zero
 add $a1, $s4, $zero
  
  li $a2, 2
    
     jal draw_sprite

              
movement_ghost_1_end:
lw $s0,12($sp)  #restaura valores
lw $s1,16($sp)
lw $s2,20($sp)
lw $s3,24($sp)
lw $s4,28($sp)
lw $s5,32($sp)
lw $s6,36($sp)
lw $ra,40($sp)    
  
addi $sp, $sp, 48     #destroi pilha
jr   $ra
    




