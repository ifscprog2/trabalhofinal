/*
 * grafo.h
 *
 *  Created on: Nov 18, 2016
 *      Author: Renan Augusto Starke
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#define TRUE 1
#define FALSE 0

typedef struct vertices vertice_t;
typedef struct arestas aresta_t;
typedef struct grafos grafo_t;

grafo_t *cria_grafo(int vertices);
void libera_grafo (grafo_t *g);
int cria_adjacencia(grafo_t *g, int u, int v);
int cria_adjacencia_nao_dir(grafo_t *g, int u, int v, int peso);
int rem_adjacencia(grafo_t *g, int u, int v);
int adjacente(grafo_t *g, int u, int v);

int obter_peso(grafo_t *g, int u, int v);
int obter_distancia(grafo_t *g, int u);
void exportar_grafo_dot(const char *filename, grafo_t *grafo);

void bellman_ford (grafo_t *grafo, int fonte);
void imprimir_caminho(grafo_t *grafo, int fonte, int destino);
void imprime_dados_vertice(grafo_t *g);



#endif /* GRAFO_H_ */
