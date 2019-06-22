.include "graphics.inc"
.include "funcoes.inc"


.text 
.globl main
main:
	# CHAMA DRAW GRID
    li $a0, GRID_1_COLS  
    li $a1, GRID_1_ROWS 
    la $a2, grid_1
    jal draw_grid  

	# TESTE DRAW SPRITE
    li   $s0,0
    li   $s1,0
main2:
    move $a0,$s0  # x
    move $a1,$s1  # y
    li   $a2,3    #sprite
    jal  draw_sprite
    add $s0, $s0, 1
	
	## DELAY(50)
    li $v0, 32
    li $a0, 10
    syscall
	
	##=========
    b main2
  
    
main_end:      
jr $ra

    
        
            
                
 