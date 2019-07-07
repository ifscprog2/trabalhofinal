.eqv FB_PTR 0x10040000
.eqv FB_XRES 256
.eqv FB_YRES 256

.eqv X_OFFSET  5
.eqv Y_OFFSET  1
.eqv X_SCALE   7
.eqv Y_SCALE   7

.eqv GRID_1_ROWS 35       
.eqv GRID_1_COLS 36  #36
  

.data
pontuacao: .word 0
pause: .word 0


# 35x35 Pacman Arena - Sprites 7x7
grid_1:
.ascii "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"
.ascii "ENNNNNNGNNNGNNNGF@EGNNNGNNNGNNNNNNF"
.ascii "IA@@@@@I@@@I@@@LK@JM@@@I@@@I@@@@@AI"
.ascii "I@ONNP@I@Q@I@Q@I@@@I@Q@I@Q@I@ONNP@I"
.ascii "I@@@@@@I@I@I@I@R@Q@R@I@I@I@I@@@@@@I"
.ascii "LNNNNP@R@I@I@I@@@I@@@I@I@I@R@ONNNNM"
.ascii "I@@@@@@@@I@R@LNNNSNNNM@R@I@@@@@@@@I"
.ascii "I@ENNF@Q@I@D@I@D@I@D@I@D@I@Q@ENNF@I"
.ascii "I@JNNK@I@LNGNM@I@I@I@LNGNM@I@JNNK@I"
.ascii "I@@@@@@I@IDIDI@I@I@I@IDIDI@I@@@@@@I"
.ascii "I@ONNNNM@I@I@I@I@I@I@I@I@I@LNNNNP@I"
.ascii "I@@@@@@I@I@R@R@I@R@I@R@R@I@I@@@@@@I"
.ascii "I@ENNF@I@I@@@@@I@@@I@@@@@I@I@ENNF@I"
.ascii "I@JNNK@I@JP@Q@OHP@OHP@Q@OK@I@JNNK@I"
.ascii "I@@@@@@I@@@@I@@@@@@@@@I@@@@I@@@@@@I"
.ascii "LNNNNP@I@EF@R@ENP@ONF@R@EF@I@ONNNNM"
.ascii "IA@@@@@I@JK@@@IB@@@BI@@@JK@I@@@@@AI"
.ascii "JNNNNNNK@@@@Q@IABABAI@Q@@@@JNNNNNNK"
.ascii "@@@@@@@@@OP@I@IB@@@BI@I@OP@@@@@@@@@"
.ascii "ENNNNNNF@@@@R@JNNNNNK@R@@@@ENNNNNNF"
.ascii "IA@@@@@I@EF@@@@@@@@@@@@@EF@I@@@@@AI"
.ascii "LNNNNP@I@JK@ENNNPCONNNF@JK@I@ONNNNM"
.ascii "I@@@@@@I@@@@I@@@@@@@@@I@@@@I@@@@@@I"
.ascii "I@ENNF@I@EP@R@OGP@OGP@R@OF@I@ENNF@I"
.ascii "I@JNNK@I@I@@@@@I@@@I@@@@@I@I@JNNK@I"
.ascii "I@@@@@@I@I@Q@Q@I@Q@I@Q@Q@I@I@@@@@@I"
.ascii "I@ONNNNM@I@I@I@I@I@I@I@I@I@LNNNNP@I"
.ascii "I@@@@@@I@IDIDI@I@I@I@IDIDI@I@@@@@@I"
.ascii "I@ENNF@I@LNHNM@R@I@R@LNHNM@I@ENNF@I"
.ascii "I@JNNK@R@I@D@I@D@I@D@I@D@I@R@JNNK@I"
.ascii "I@@@@@@@@I@Q@LNNNSNNNM@Q@I@@@@@@@@I"
.ascii "LNNNNP@Q@I@I@I@@@I@@@I@I@I@Q@ONNNNM"
.ascii "I@@@@@@I@I@I@I@Q@R@Q@I@I@I@I@@@@@@I"
.ascii "I@ONNP@I@R@I@R@I@@@I@R@I@R@I@ONNP@I"
.ascii "IA@@@@@I@@@I@@@LF@EM@@@I@@@I@@@@@AI"
.ascii "JNNNNNNHNNNHNNNHK@JHNNNHNNNHNNNNNNK"

.eqv BLACK  0x00000000
.eqv BLUE   0x001111ff
.eqv PURPLE 0x00b711ff
.eqv YELLOW 0x00fffc60
.eqv RED    0x00ff0000
.eqv GREEN  0x00007000
.eqv GRAY   0x00a0a0a0
.eqv WHITE  0x00ffffff

colors: .word BLACK, BLUE, PURPLE, YELLOW 
        .word RED, GREEN, GRAY, WHITE

.eqv SPRITE_SIZE 49
sprites:
#Comida 0 (@) (0x40) (64)
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
.byte 0,0,0,6,0,0,0
.byte 0,0,6,6,6,0,0
.byte 0,0,0,6,0,0,0
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
#Invenc. 1 (A)
.byte 0,0,0,0,0,0,0
.byte 0,0,0,1,0,0,0
.byte 0,0,1,1,1,0,0
.byte 0,1,1,1,1,1,0
.byte 0,0,1,1,1,0,0
.byte 0,0,0,1,0,0,0
.byte 0,0,0,0,0,0,0
#Inimigo 2(B)
.byte 0,0,0,0,0,0,0
.byte 0,0,2,2,2,0,0
.byte 0,2,0,2,0,2,0
.byte 0,2,2,2,2,2,0
.byte 0,2,2,2,2,2,0
.byte 0,2,0,2,0,2,0
.byte 0,0,0,0,0,0,0
#PACMAN 3 (C)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,3,3,3,3,3,0
.byte 0,3,3,3,3,3,0
.byte 0,3,3,3,3,3,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,0,0,0
#Cereja 4 (D)
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,5,5,0
.byte 0,0,0,5,5,0,0
.byte 0,4,4,4,0,0,0
.byte 0,4,4,4,0,0,0
.byte 0,4,4,4,0,0,0
.byte 0,0,0,0,0,0,0
#Canto Sup. Esq. (E)
.byte 0,0,0,0,0,0,0
.byte 0,0,0,6,6,6,6
.byte 0,0,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,0
#Canto Sup. Dir. (F)
.byte 0,0,0,0,0,0,0
.byte 6,6,6,6,0,0,0
.byte 6,6,6,6,6,0,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
#Tee Inferior   (G)
.byte 0,0,0,0,0,0,0
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 0,6,6,6,6,6,0
#Tee Superior   (H)
.byte 0,6,6,6,6,6,0
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 0,0,0,0,0,0,0
#Parede Vertical  (I)
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
#Canto Inf. Esq.
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,0,6,6,6,6,6
.byte 0,0,0,6,6,6,6
.byte 0,0,0,0,0,0,0
#Canto Inf. Dir.
.byte 0,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,0,0
.byte 6,6,6,6,0,0,0
.byte 0,0,0,0,0,0,0
#Tee Direita
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,0
#Tee Esquerda
.byte 0,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
#Parede Horizontal
.byte 0,0,0,0,0,0,0
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 0,0,0,0,0,0,0
#Ponta Esq.
.byte 0,0,0,0,0,0,0
.byte 0,0,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,6,6,6,6,6,6
.byte 0,0,6,6,6,6,6
.byte 0,0,0,0,0,0,0
#Ponta Dir.
.byte 0,0,0,0,0,0,0
.byte 6,6,6,6,6,0,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,6,0
.byte 6,6,6,6,6,0,0
.byte 0,0,0,0,0,0,0
#Ponta Sup.
.byte 0,0,0,0,0,0,0
.byte 0,0,6,6,6,0,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
#Ponta Inf.
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,6,6,6,6,6,0
.byte 0,0,6,6,6,0,0
.byte 0,0,0,0,0,0,0
#Cruz
.byte 0,6,6,6,6,6,0
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 6,6,6,6,6,6,6
.byte 0,6,6,6,6,6,0
#Preto  (T)
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,0
numbers:
#0  21 (U)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,0,0,0
#1  (V)
.byte 0,0,0,0,0,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,0,0,0
#2  (W)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,3,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,0,0,0
#3  (X)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,0,0,0
#4  (Y)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,0,0,0
#5  (Z)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,3,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,0,0,0
#6  ([)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,0,0,0,0
.byte 0,0,3,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,0,0,0
#7  (\)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,0,0,0
#8  ([)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,0,0,0
#9  (^)
.byte 0,0,0,0,0,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,3,0,3,0,0
.byte 0,0,3,3,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,3,0,0
.byte 0,0,0,0,0,0,0


grid_pontuacao:
.ascii "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"
.ascii "ENNNNNNGNNNGNNNGF@EGNNNGNNNGNNNNNNF"
.ascii "IA@@@@@I@@@I@@@LK@JM@@@I@@@I@@@@@AI"
.ascii "I@ONNP@I@Q@I@Q@I@@@I@Q@I@Q@I@ONNP@I"
.ascii "I@@@@@@I@I@I@I@R@Q@R@I@I@I@I@@@@@@I"
.ascii "LNNNNP@R@I@I@I@@@I@@@I@I@I@R@ONNNNM"
.ascii "I@@@@@@@@I@R@LNNNSNNNM@R@I@@@@@@@@I"
.ascii "I@ENNF@Q@I@D@I@D@I@D@I@D@I@Q@ENNF@I"
.ascii "I@JNNK@I@LNGNM@I@I@I@LNGNM@I@JNNK@I"
.ascii "I@@@@@@I@IDIDI@I@I@I@IDIDI@I@@@@@@I"
.ascii "I@ONNNNM@I@I@I@I@I@I@I@I@I@LNNNNP@I"
.ascii "I@@@@@@I@I@R@R@I@R@I@R@R@I@I@@@@@@I"
.ascii "I@ENNF@I@I@@@@@I@@@I@@@@@I@I@ENNF@I"
.ascii "I@JNNK@I@JP@Q@OHP@OHP@Q@OK@I@JNNK@I"
.ascii "I@@@@@@I@@@@I@@@@@@@@@I@@@@I@@@@@@I"
.ascii "LNNNNP@I@EF@R@ENP@ONF@R@EF@I@ONNNNM"
.ascii "IA@@@@@I@JK@@@IB@@@BI@@@JK@I@@@@@AI"
.ascii "JNNNNNNK@@@@Q@IABABAI@Q@@@@JNNNNNNK"
.ascii "@@@@@@@@@OP@I@IB@@@BI@I@OP@@@@@@@@@"
.ascii "ENNNNNNF@@@@R@JNNNNNK@R@@@@ENNNNNNF"
.ascii "IA@@@@@I@EF@@@@@@@@@@@@@EF@I@@@@@AI"
.ascii "LNNNNP@I@JK@ENNNPCONNNF@JK@I@ONNNNM"
.ascii "I@@@@@@I@@@@I@@@@@@@@@I@@@@I@@@@@@I"
.ascii "I@ENNF@I@EP@R@OGP@OGP@R@OF@I@ENNF@I"
.ascii "I@JNNK@I@I@@@@@I@@@I@@@@@I@I@JNNK@I"
.ascii "I@@@@@@I@I@Q@Q@I@Q@I@Q@Q@I@I@@@@@@I"
.ascii "I@ONNNNM@I@I@I@I@I@I@I@I@I@LNNNNP@I"
.ascii "I@@@@@@I@IDIDI@I@I@I@IDIDI@I@@@@@@I"
.ascii "I@ENNF@I@LNHNM@R@I@R@LNHNM@I@ENNF@I"
.ascii "I@JNNK@R@I@D@I@D@I@D@I@D@I@R@JNNK@I"
.ascii "I@@@@@@@@I@Q@LNNNSNNNM@Q@I@@@@@@@@I"
.ascii "LNNNNP@Q@I@I@I@@@I@@@I@I@I@Q@ONNNNM"
.ascii "I@@@@@@I@I@I@I@Q@R@Q@I@I@I@I@@@@@@I"
.ascii "I@ONNP@I@R@I@R@I@@@I@R@I@R@I@ONNP@I"
.ascii "IA@@@@@I@@@I@@@LF@EM@@@I@@@I@@@@@AI"
.ascii "JNNNNNNHNNNHNNNHK@JHNNNHNNNHNNNNNNK"
