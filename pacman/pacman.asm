.include "graphics.inc"
.include "funcoes.inc"
.include "macros.inc"
.include "interrupt.inc"


.data

animed_sprite(pacman, 3, 0,0, 0,0)#struct animed
moviment(mov_pacman,0,0,0)#struct leitura do movimento do pacman

.text 
.globl main
main:
  
     li $t0, 2
     sw $t0, 0xffff0000   #habilita interrupção pelo teclado. 
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

    
        
            
                
 
