.include "graphics.inc"
.include "funcoes2.inc"
.include "pacman.inc"
.include "ghost.inc"
.include "macros.inc"
.include "interrupt.inc"


.data

animed_sprite(pacman, 3, 119, 147, 0, 0, 0) #struct animed
animed_sprite(ghost_1, 2, 105, 126, 0, 0, 0) #struct animed
moviment(mov_pacman, 0 ,0 ,0)#struct leitura do movimento do pacman
moviment(mov_ghost,0 ,0 ,0)#struct leitura do movimento do pacman

.text 
.globl main
main:
     #configuracoes
     li $t0, 2
     sw $t0, 0xffff0000   # habilita interrupção pelo teclado. 
  
     
    # CHAMA DRAW GRID (imprime grid)
    li $a0, GRID_1_COLS  
    li $a1, GRID_1_ROWS 
    la $a2, grid_1
    jal draw_grid  


main_loop_1:
    
   
    jal movement_pacman  #pacman.inc
    jal movement_ghost	 #ghost.inc 
    jal print_score      #pacman.inc		
	
    	
	
    macro_delay(20)   #delay 50ms
    j main_loop_1
    
main_end:      
jr $ra

    
        
            
                
 
