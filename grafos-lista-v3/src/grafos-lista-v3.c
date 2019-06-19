/*
 ============================================================================
 Name        : grafos-lista-v0.c
 Author      : ednei
 Version     :
 Copyright   : Your copyright notice: ariane
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

	grafo_t *grafo, *grafo1;

	printf("Hello world!\n");
	grafo1 = le_vertices_arquivo("vertices.txt");

	exportar_grafo_dot("grafo1.dot", grafo1);



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



	// constrói grafo
	while (!fila_vazia(fila)) {
		vertice = dequeue(fila);
		id = vertice_get_id(vertice);

		switch (id) {
		case 1:
			//adiciona_adjacentes(grafo, vertice, 4, 2, 1, 3, 1);
			adiciona_adjacentes(grafo, vertice, 2, 2, 7);
			adiciona_adjacentes(grafo, vertice, 2, 3, 9);
			adiciona_adjacentes(grafo, vertice, 2, 6, 14);

			break;
		case 2:
			adiciona_adjacentes(grafo, vertice, 6, 1, 7, 4, 15, 3, 10);
			break;
		case 3:
			adiciona_adjacentes(grafo, vertice, 8, 1, 9, 2, 10, 4, 11, 6, 2);
			break;
		case 4:
			adiciona_adjacentes(grafo, vertice, 6, 2, 15, 3, 11, 5, 6);
			break;
		case 5:
			adiciona_adjacentes(grafo, vertice, 4, 4, 6, 6, 9);
			break;
		case 6:
			adiciona_adjacentes(grafo, vertice, 6, 5, 9, 3, 2, 1, 14);
			break;


		default:
			break;
		}
	}



	bfs(grafo, vertice_inicial);
	dfs(grafo, vertice_inicial);

	bellman_ford(grafo,1);

	//fflush(stdout);
	exportar_grafo_dot("grafo.dot", grafo);

	libera_fila(fila);
	libera_grafo(grafo);

	printf("\nfim progr v_03\n");

	return EXIT_SUCCESS;
}

