.include "graphics.inc"
.include "funcoes2.inc"
.include "pacman.inc"
.include "ghost.inc"
.include "macros.inc"
.include "interrupt.inc"


.data

animed_sprite(pacman, 3, 0, 0, 0, 0, 0) #struct animed
animed_sprite(ghost_1, 2, 0, 0, 0, 0, 0) #struct animed
moviment(mov_pacman, 0 ,0 ,0)#struct leitura do movimento do pacman
moviment(mov_ghost,0 ,0 ,0)#struct leitura do movimento do pacman

.text 
.globl main
main:
     #configuracoes
     li $t0, 2
     sw $t0, 0xffff0000   # habilita interrupção pelo teclado. 
     la $t0, pacman
     li $t1, 119         # posicao x inicial pacman 119
     sw $t1, 4($t0)      # guarda estrurura pacman posicao x
     li $t1, 147        # posicao y inicial pacman   140   
     sw $t1, 8($t0)      # guarda estrurura pacman posicao x
     
    # CHAMA DRAW GRID (imprime grid)
    li $a0, GRID_1_COLS  
    li $a1, GRID_1_ROWS 
    la $a2, grid_1
     jal draw_grid  


main_loop_1:
    
   
    jal movement_pacman
    jal movement_ghost	
	
	
	
	
    macro_delay(40)   #delay 50ms
    j main_loop_1
    
main_end:      
jr $ra

    
        
            
                
 
