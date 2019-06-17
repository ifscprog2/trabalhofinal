/*
 ============================================================================
 Name        : grafos-lista-v0.c
 Author      : ednei
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 ============================================================================
 Name        : grafos.c
 Author      :
 Version     :
 Copyright   : Renan Augusto Starke, todos os direitos reservados
 Description : grafos com lista encadeadas, Ansi-style
 : estruturas disponiveis:
 : pilha e fila
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pilha/pilha.h"
#include "fila/fila.h"
#include "grafo/grafo.h"

int main(void) {

	printf("Hello world!\n");
	le_vertices_arquivo("vertices.txt");


	printf("fim prog v0");
	return 0;

}

/*
 grafo_t *grafo;

 vertice_t* vertice;
 vertice_t* vertice_inicial;

 fila_t *fila;
 int id;

 grafo = cria_grafo(0);

 fila = cria_fila();



 //Adiciona todos os vertices no grafo
 vertice_inicial = grafo_adicionar_vertice(grafo, 1);
 enqueue(vertice_inicial, fila);

 vertice = grafo_adicionar_vertice(grafo, 2);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo, 3);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo, 4);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo, 5);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo, 6);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo,7);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo,8);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo,9);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo,10);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo,11);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo,12);
 enqueue(vertice, fila);

 vertice = grafo_adicionar_vertice(grafo,13);
 enqueue(vertice, fila);



 // constrói grafo
 while (!fila_vazia(fila))	{
 vertice = dequeue(fila);
 id = vertice_get_id(vertice);

 switch(id){
 case 1:
 //adiciona_adjacentes(grafo, vertice, 4, 2, 1, 3, 1);
 adiciona_adjacentes(grafo, vertice, 2, 2, 1);
 adiciona_adjacentes(grafo, vertice, 2, 3, 1);
 break;
 case 2:
 adiciona_adjacentes(grafo, vertice, 8, 4, 1, 5, 1, 3, 1, 1, 1);
 break;
 case 3:
 adiciona_adjacentes(grafo, vertice, 10, 1, 1 , 2, 1 , 5, 1, 8, 1, 7, 1);
 break;
 case 4:
 adiciona_adjacentes(grafo, vertice, 4, 2, 1, 5, 1);
 break;
 case 5:
 adiciona_adjacentes(grafo, vertice, 8, 2, 1, 3, 1, 4, 1, 6, 1);
 break;
 case 6:
 adiciona_adjacentes(grafo, vertice, 2, 5, 1);
 break;
 case 7:
 adiciona_adjacentes(grafo, vertice, 4, 3, 1, 8, 1);
 break;
 case 8:
 adiciona_adjacentes(grafo, vertice, 4, 3, 1, 7, 1);
 break;
 case 9:
 adiciona_adjacentes(grafo, vertice, 2, 10, 1);
 break;
 case 10:
 adiciona_adjacentes(grafo, vertice, 2, 9, 1);
 break;
 case 11:
 adiciona_adjacentes(grafo, vertice, 2, 12, 1);
 break;
 case 12:
 adiciona_adjacentes(grafo, vertice, 4, 11, 1, 13, 1);
 break;
 case 13:
 adiciona_adjacentes(grafo, vertice, 2, 12, 1);
 break;


 default:
 break;
 }
 }





 bfs(grafo, vertice_inicial);
 dfs(grafo, vertice_inicial);

 //fflush(stdout);
 exportar_grafo_dot("grafo.dot", grafo);


 libera_fila(fila);
 libera_grafo(grafo);



 printf ("fim progr v03");

 return EXIT_SUCCESS;
 }
 */
