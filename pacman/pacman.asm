.include "graphics.inc"
.include "funcoes.inc"
.include "macros.inc"
.include "interrupt.inc"


.data

animed_sprite(pacman, 3,0,0,0,0,0,0) #struct animed
moviment(mov_pacman,0,0,0)#struct leitura do movimento do pacman

.text 
.globl main
main:
     #configuracoes
     li $t0, 2
     sw $t0, 0xffff0000   # habilita interrupção pelo teclado. 
     la $t0, pacman
     li $t1, 119         # posicao x inicial pacman
     sw $t1, 4($t0)      # guarda estrurura pacman posicao x
     li $t1, 140         # posicao y inicial pacman      
     sw $t1, 8($t0)      # guarda estrurura pacman posicao x
     
    # CHAMA DRAW GRID (imprime grid)
    li $a0, GRID_1_COLS  
    li $a1, GRID_1_ROWS 
    la $a2, grid_1
    jal draw_grid  


main_loop_1:
    
   
    jal movement_pacman
	
	
	
	
	
    macro_delay(50)   #delay 50ms
    j main_loop_1
    
main_end:      
jr $ra

    
        
            
                
 
