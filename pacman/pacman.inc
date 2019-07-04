
#--------------------------------------------#
# pacman movement
# void movement_pacman();
#--------------------------------------------#
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
 
   
    la $s2, pacman      # struct animed_sprite
    la $s1, mov_pacman  # struct moviment
    la $a2, grid_1
    
    lw $t0, 4($s1)       # x mov_pacman
    lw $t1, 4($s2)       # x pacman pixel
    div $t4, $t1, 7       # x pacman grid
    mfhi $t6
    add $a0, $t0, $t4    # posicao x de pesquisa
    lw $t2, 8($s1)       # y mov_pacman
    lw $t3, 8($s2)       # y pacman pixel
    div $t5, $t3, 7      # y pacman grid
    mfhi $t7
    add $a1, $t2, $t5    # posicao x de pesquisa
    add $t7, $t6, $t7    # se zero está na posicao (0,0) sprite
    bnez $t7, mov_pacman_0
     jal check_wall       # retorna $v0->1 se é parede
     bnez $v0, mov_pacman_0  #if (parede=0)
       sw $t0, 12($s2)  # guarda novo movimento x
       sw $t2, 16($s2)  # gurada novo movimento y  
    
mov_pacman_0:       
    lw $t0, 4($s2)       # pos_x pacman
    lw $t1, 12($s2)      # mov_x pacman 
    div $t4, $t0, 7       # x pacman grid
    mfhi $t6
    add $a0, $t1, $t4    # posicao x de pesquisa
    lw $t2, 8($s2)       # pos_y pacman
    lw $t3, 16($s2)      # mov_y pacman 
    div $t5, $t2, 7      # y pacman grid
    mfhi $t7
    add $a1, $t3, $t5    # posicao x de pesquisa
    add $t7, $t6, $t7    # se zero está na posicao (0,0) sprite
    bnez $t7, mov_pacman_1
    jal check_wall       # retorna $v0->1 se é parede    
    bnez $v0, movement_pacman_end  #if (parede=0)
mov_pacman_1:
       add $a0, $t1, $t0  # atualiza pos_x
       sw $a0, 4($s2)
       add $a1, $t2, $t3 # atualiza pox_y
       sw $a1, 8($s2)
       li $a2, 3          #sprite pacman
       jal   draw_sprite
              
               
                 

movement_pacman_end:
lw $s0, 12($sp)
lw $s1, 16($sp)
lw $s2, 20($sp)
lw $s3, 24($sp)
lw $ra, 28($sp)       #restaura valores
addi $sp, $sp, 32     #destroi pilha
jr   $ra
    




