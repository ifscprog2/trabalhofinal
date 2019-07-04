
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
    jal check_score
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
    



#--------------------------------------------#
# checa pontuação
# void check_score(int x, int y, *grid);
#--------------------------------------------#
# $a0-> posição no grid X $a1-> posição no grid Y  $a2-> ponteiro do grid      

.globl check_score
check_score:
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
sw $a0,32($sp)  #salva pilha anterior

mul $s0, $a1, GRID_1_ROWS   # calcula posicao do grid          
add $s1, $a0, $s0           # posição final no grid   
la  $s2, grid_pontuacao     # endereco grid 


add $s1, $s1, $s2           #posição do vetor grid pontuacao
lb $s0, 0($s1)              #carrega o id do sprite


bne $s0, 64, check_score_cereja    #verifica se é comida
    li $s2, 84             # carrega asci code T (84) 0x54
    sb $s2, 0($s1)         # mata a comida no grid pontuacao
    la $s2, pontuacao
    lw $s3, 0($s2)
    add $s3, $s3, 10
    sw $s3, 0($s2)
    li $v0, 1
    move $a0, $s3
    syscall
    
check_score_cereja:    
bne $s0, 68, check_score_pilula    #verifica se é ccereja
    li $s2, 84             # carrega asci code T (84) 0x54
    sb $s2, 0($s1)         # mata a comida no grid pontuacao
    la $s2, pontuacao
    lw $s3, 0($s2)
    add $s3, $s3, 100
    sw $s3, 0($s2)
    li $v0, 1
    move $a0, $s3
    syscall


check_score_pilula:    
bne $s0, 65, check_score_end   #verifica se é pilula
    li $s2, 84             # carrega asci code T (84) 0x54
    sb $s2, 0($s1)         # mata a comida no grid pontuacao
    la $s2, pontuacao
    lw $s3, 0($s2)
    add $s3, $s3, 100
    sw $s3, 0($s2)
    li $v0, 1
    move $a0, $s3
    syscall
    




check_score_end:
lw $s0, 12($sp)
lw $s1, 16($sp)
lw $s2, 20($sp)
lw $s3, 24($sp)
lw $ra, 28($sp)       #restaura valores
lw $a0,32($sp)        #restaura da pilha anterior

addi $sp, $sp, 32     #destroi pilha
jr   $ra
    


#--------------------------------------------#
# print score
# void print_score();
#--------------------------------------------#
# $a0-> posição no grid X $a1-> posição no grid Y  $a2-> ponteiro do grid      

.globl print_score
print_score:
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
# | $ra       | 36 ($sp)
# |===========|
# | $a0       | 40 ($sp) (quadro anterior)
# | $a1       | 44($sp)
# | $a2       | 48($p)
# |-----------|	
addi $sp, $sp, -40
sw $s0, 12($sp)
sw $s1, 16($sp)
sw $s2, 20($sp)
sw $s3, 24($sp)
sw $s4, 28($sp)
sw $s5, 32($sp)
sw $ra, 36($sp)    

  lw $s1, pontuacao
  li $s5, 234  # posicao x inicio da casa menos significativa 
  
print_score_loop_1:      
 
   div  $s1, $s1, 10
   mfhi $s2               # primeira casa decimal
   add $a2, $s2, 21       # parametro id draw sprite 0 tem offset de 21 
   li $a1, Y_OFFSET       # parametro y draw sprite
   move $a0, $s5          # parametro x draw sprite
   jal draw_sprite
   add $s5, $s5, -7       #tamanho x do sprite
   add $s4, $s4, -1
   beqz $s1, print_score_end
   j print_score_loop_1    



print_score_end:
lw $s0, 12($sp)
lw $s1, 16($sp)
lw $s2, 20($sp)
lw $s3, 24($sp)
lw $s4, 28($sp)
lw $s5, 32($sp)
lw $ra, 36($sp)       #restaura valores

addi $sp, $sp, 40     #destroi pilha
jr   $ra
    



