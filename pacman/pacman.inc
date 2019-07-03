
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
 
   
    la $s2, pacman      # strut animed_sprite
    move $a2, $s2       # parametro para check_all 
    lw $s0, 4($s2)      # posicao atual x  pacman
    move $a0, $s0       # parametro para check_all / draw sprite
    lw $s1, 8($s2)      # posicao atual y  pacman   
    move $a1, $s1       # parametro para check_all / draw sprite
    jal check_wall
    li $a2,3            # parametro draw sprite
    
    la $t1,  mov_pacman # estrutura movimento pacman  (teclado)
    lw $t2, 0($t1)      # carrega validade movimento
    beq $t2, $zero, movement_pacman_end
      lw $t3, 4($t1)      # carrega se ha movimento x x=1-> mov(+)   x=0-> mov(0)   x=-1-> mov(-)
      lw $t4, 8($t1)      # carrega se ha movimento y y=1-> mov(+)   y=0-> mov(0)   y=-1-> mov(-)
        
    
      beq $t3, 1, movement_pacman_x_mais
      beq $t3, -1,movement_pacman_x_menos
      beq $t4, 1, movement_pacman_y_mais
      beq $t4, -1, movement_pacman_y_menos
    j movement_pacman_end
  
movement_pacman_x_mais:     #direita
    lw $t0, 12($s2)         #carrega move x animed_sprite
    andi $t0, $t0, 8        #bitwase #1000
    beqz $t0, movement_pacman_cont  #se zero e parede
      addi  $a0, $s0, 1      # x
      move  $a1, $s1         # y
      sw    $a0, 4($s2)      # salva nova posicao x  pacman
      sw $t3, 20($s2)      # salva movimento animed_sprite x x=1-> mov(+)   x=0-> mov(0)   x=-1-> mov(-)
      sw $t4, 24($s2)      # salva movimento animed_sprite y y=1-> mov(+)   y=0-> mov(0)   y=-1-> mov(-)
      jal   draw_sprite
      j movement_pacman_end    
movement_pacman_x_menos:   #esquerda
    lw $t0, 12($s2)       #carrega move x
    andi $t0, $t0, 4       #bitwase #0100
    beqz $t0, movement_pacman_cont   #se zero e parede
      addi  $a0, $s0, -1   # x
      move  $a1, $s1       # y
      sw    $a0, 4($s2)      # salva nova posicao x  pacman
      sw $t3, 20($s2)      # salva movimento animed_sprite x x=1-> mov(+)   x=0-> mov(0)   x=-1-> mov(-)
      sw $t4, 24($s2)      # salva movimento animed_sprite y y=1-> mov(+)   y=0-> mov(0)   y=-1-> mov(-)
      jal  draw_sprite
      j movement_pacman_end
movement_pacman_y_mais:    #desce
    lw $t0, 16($s2)       #carrega move y
    andi $t0, $t0, 2       #bitwase #0010
    beqz $t0, movement_pacman_cont  #se zero e parede
     move  $a0,$s0          # x
     addi  $a1,$s1, 1      # y
     sw    $a1, 8($s2)      # salva nova posicao y  pacman
     sw $t3, 20($s2)      # salva movimento animed_sprite x x=1-> mov(+)   x=0-> mov(0)   x=-1-> mov(-)
     sw $t4, 24($s2)      # salva movimento animed_sprite y y=1-> mov(+)   y=0-> mov(0)   y=-1-> mov(-)
     jal  draw_sprite
     j movement_pacman_end
movement_pacman_y_menos:    #sobe
    lw $t0, 16($s2)       #carrega move y
    andi $t0, $t0, 1      #bitwase #0001
    beqz $t0, movement_pacman_cont    #se zero e parede
      move  $a0,$s0          # x
      addi  $a1,$s1, -1      # y
      sw    $a1, 8($s2)      # salva nova posicao y  pacman
      sw $t3, 20($s2)      # salva movimento animed_sprite x x=1-> mov(+)   x=0-> mov(0)   x=-1-> mov(-)
      sw $t4, 24($s2)      # salva movimento animed_sprite y y=1-> mov(+)   y=0-> mov(0)   y=-1-> mov(-)
      jal  draw_sprite
      j movement_pacman_end

movement_pacman_cont:     # tenta movimetar o pacman no movimento anterior
       
      lw $t3, 20($s2)      # carrega se ha movimento x x=1-> mov(+)   x=0-> mov(0)   x=-1-> mov(-)
      lw $t4, 24($s2)      # carrega se ha movimento y y=1-> mov(+)   y=0-> mov(0)   y=-1-> mov(-)
        
    
      beq $t3, 1, movement_pacman_cont_x_mais
      beq $t3, -1,movement_pacman_cont_x_menos
      beq $t4, 1, movement_pacman_cont_y_mais
      beq $t4, -1, movement_pacman_cont_y_menos
      j movement_pacman_end
  
movement_pacman_cont_x_mais:     #direita
    lw $t0, 12($s2)         #carrega move x animed_sprite
    andi $t0, $t0, 8        #bitwase #1000
    beqz $t0, movement_pacman_end  #se zero e parede
      addi  $a0, $s0, 1      # x
      move  $a1, $s1         # y
      sw    $a0, 4($s2)      # salva nova posicao x  pacman
      jal   draw_sprite
      j movement_pacman_end    
movement_pacman_cont_x_menos:   #esquerda
    lw $t0, 12($s2)       #carrega move x
    andi $t0, $t0, 4       #bitwase #0100
    beqz $t0, movement_pacman_end   #se zero e parede
      addi  $a0, $s0, -1   # x
      move  $a1, $s1       # y
      sw    $a0, 4($s2)      # salva nova posicao x  pacman
      jal  draw_sprite
      j movement_pacman_end
movement_pacman_cont_y_mais:    #desce
    lw $t0, 16($s2)       #carrega move y
    andi $t0, $t0, 2       #bitwase #0010
    beqz $t0, movement_pacman_end  #se zero e parede
     move  $a0,$s0          # x
     addi  $a1,$s1, 1      # y
     sw    $a1, 8($s2)      # salva nova posicao y  pacman
     jal  draw_sprite
     j movement_pacman_end
movement_pacman_cont_y_menos:    #sobe
    lw $t0, 16($s2)       #carrega move y
    andi $t0, $t0, 1      #bitwase #0001
    beqz $t0, movement_pacman_end    #se zero e parede
      move  $a0,$s0          # x
      addi  $a1,$s1, -1      # y
      sw    $a1, 8($s2)      # salva nova posicao y  pacman
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
    
