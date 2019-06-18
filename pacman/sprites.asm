.include "graphics.inc"
.include "bitmap.inc"   #setpixel
.include "init.inc"




.text 0x00410000
.globl main
main:
	# CHAMA DRAW GRID
    #$li $a0, 35
    #li $a1, 35
    #la $a2, grid
    #jal draw_grid    
    #hlt: b hlt

	# TESTE DRAW SPRITE
    li   $t8,0
    li   $t9,0
    main2:
    move $a0,$t8
    move $a1,$t9
    li   $a2,14
    jal  draw_sprite
    addi $t8, $t8, 1
	
	## DELAY(50)
    li $v0, 32
    li $a0, 50
    syscall
	
	##=========
    b main2
    
    
# draw_grid(width, height, grid_table)
.globl draw_grid
draw_grid:

	jr   $ra


# draw_sprite(int x, int y, int sprite_id)  posicao em pixel 
#$a0-> x   $a1-> y   $a2->sprite_id [0.. n sprite]
.globl draw_sprite
draw_sprite:
    la $t3, $zero       # ponteiro i
    la $t4, $zero       # ponteiro j
    la $t0, colors      # cor[0]
    la $t1, sprites     # sprite[0]
    mul $t1, $a2, 49    # calcula 0ff_set sprite
    add $t3, $t3, $t1   # x[i]

        
    lb $a2, 0($t3)
    mul $a2, $a2, 4
    jal set_pixel
    add $t3, $t3, 1
    add $t4, $t4, 1
    


    jr   $ra

# set_pixel(int X, int Y, int color)  
# $a0-> x   $a1-> y $a2-> color 
.globl set_pixel
set_pixel:
   la  $t0, FB_PTR
   mul $a1, $a1, FB_XRES
   add $a0, $a0, $a1
   sll $a0, $a0, 2
   add $a0, $a0, $t0
   sw  $a2, 0($a0)
   jr  $ra
