
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
    lw $t1, 4($s2)       # x pacman 
    add $a0, $t0, $t1    # posicao x de pesquisa
    lw $t2, 8($s1)       # y mov_pacman
    lw $t3, 8($s2)       # y pacman 
    add $a1, $t2, $t3    # posicao x de pesquisa
    jal check_wall       # retorna $v0->1 se é parede
    bnez $v0, mov_pacman_0  #if (parede=0)
       sw $t0, 12($s2)  # guarda novo movimento x
       sw $t2, 16($s2)  # gurada novo movimento y  
    
mov_pacman_0:       
    lw $t0, 4($s2)       # pos_x pacman
    lw $t1, 12($s2)      # mov_x pacman 
    add $a0, $t0, $t1    # posicao x de pesquisa
    lw $t2, 8($s2)       # pos_y pacman
    lw $t3, 16($s2)      # mov_y pacman 
    add $a1, $t2, $t3    # posicao x de pesquisa
    jal check_wall       # retorna $v0->1 se é parede    
 
    bnez $v0, movement_pacman_end  #if (parede=0)
       sw $a0, 4($s2)
       sw $a1, 8($s2)
       mul $a0, $a0, 7
       mul $a1, $a1, 7
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
    
