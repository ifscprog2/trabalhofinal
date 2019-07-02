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

#include "importa_dados.h"
#include "grafo/grafo.h"

int main(void) {

	grafo_t *grafo1;

	grafo1 = le_vertices_arquivo("vertices.txt");


	bellman_ford(grafo1,1);  //menor caminho  para no
	imprimir_caminho(grafo1, 1, 68 );

	exportar_grafo_dot("grafo1.dot", grafo1);

	libera_grafo(grafo1);

	printf("\nfim progr v_003\n");

	return EXIT_SUCCESS;
}

