/*
 * grafo.h
 *
 *  Created on: 29 de abr de 2019
 *      Author: ednei.freiberger
 */

/*
 * grafo.h
 *
 *  Created on: Jul 5, 2016
 *      Author: Renan Augusto Starke
 */

#ifndef GRAFO_GRAFO_H_
#define GRAFO_GRAFO_H_

#include "vertice.h"
#include "../pilha/pilha.h"

typedef struct grafos grafo_t;

/* Cria um novo grafo com id */
grafo_t *cria_grafo(int id);

/* Adiciona um vertice ao grafo */
vertice_t* grafo_adicionar_vertice(grafo_t *grafo, int id);

/* Cria arestas:
 * grafo: grafo que pertence a aresta
 * vertice: ponteiro do vertice que se deseja adicionar arestas
 * n: numero total dos proximos parametros
 * proximos parametros: par ordenado composto por: <vert. destino> , <peso da aresta>
 * Ex: adicionar uma aresta para o vertice 2 e 3 com respectivos pesos 9 e 15
 * adiciona_adjacentes(grafo, vertice, 4, 2, 9, 3, 15);  */
void adiciona_adjacentes(grafo_t *grafo, vertice_t *vertice, int n, ...);

/* Procura um vertice no grafo com id numerico */
vertice_t* procura_vertice(grafo_t *grafo, int id);

/* Exporta o grafo utilizando a linguagem dot */
void exportar_grafo_dot(const char *filename, grafo_t *grafo);

/* Libera memoria utilizada pelo grafo */
void libera_grafo (grafo_t *grafo);


void bfs(grafo_t *grafo, vertice_t* inicial);

void dfs(grafo_t *grafo, vertice_t* inicial);

void delay(unsigned int milliseconds);

void imprime_vertices(grafo_t* grafo);

int bellman_ford(grafo_t *grafo, int fonte);

void imprimir_caminho(grafo_t *grafo, int destino, int fonte);

#endif /* GRAFO_GRAFO_H_ */
