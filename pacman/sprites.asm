.include "graphics.inc"
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
    li   $a2,8
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

#pilha
#|  a0  | 0(sp)
#|  a1  | 4(sp)
#|  a2  | 8(sp)
#|  s0  | 12(sp)
#|  s1  | 16(sp)
#|  s2  | 20(sp)
#|  ra  | 24(sp)
#|empty | 28(sp)

addi $sp, $sp, -32
sw $ra, 24($sp)

   
    la $s0, colors      # cor[0]
    la $s1, sprites     # sprite[0]
    mul $t2, $a2, 49    # calcula 0ff_set sprite, sprite_id*49
    add $s1, $s1, $t2   # x[i]
    addi $t3, $a0, 7 #X+7
    addi $t4, $a1, 7 #Y+7
    li $s2, 0

draw_sprite_for_i:

bge $a0, $t3, draw_sprite_for_i_end
add $s2, $s2, $a0
draw_sprite_for_j:
bge $a1, $t4, draw_sprite_for_j_end
add $s2, $s2, $a1
add $s1, $s1, $s2

   
    lb $a2, 0($s1) #carrega byte do sprite
    mul $a2, $a2, 4 #converte byte pra int 
    add $a2, $a2, $s0
    lw $a2, 0($a2)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    
    jal set_pixel  
   
    addi $a1, $a1, 1
  
j draw_sprite_for_j
    addi $a0, $a0, 1
draw_sprite_for_j_end:
j draw_sprite_for_i

draw_sprite_for_i_end:
    lw $ra, 24($sp)
    addi $sp, $sp, 32
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
   lw $a0, 0($sp)
   lw $a1, 4($sp)
   jr  $ra
