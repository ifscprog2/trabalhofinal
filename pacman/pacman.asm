.include "graphics.inc"
.include "funcoes.inc"


.text 
.globl main
main:
	# CHAMA DRAW GRID
    #$li $a0, 35
    #li $a1, 35
    #la $a2, grid
    #jal draw_grid    
    #hlt: b hlt

	# TESTE DRAW SPRITE
    li   $t8,21
    li   $t9,0
main2:
    move $a0,$t8
    move $a1,$t9
    li   $a2,3
    jal  draw_sprite
    add $t8, $t8, 1
	
	## DELAY(50)
    li $v0, 32
    li $a0, 10
    syscall
	
	##=========
    b main2
  
    
main_end:      
jr $ra

    
        
            
                
 