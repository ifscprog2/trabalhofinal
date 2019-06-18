/*
 * grafo.c
 *
 *  Created on: Nov 18, 2016
 *      Author: Renan Augusto Starke
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "grafo.h"

#define INFINITO 65535

struct vertices {
	int id; /*!< Identificação numérica do vértice  */

	/* Mais informações, se necessário */
	int distancia;
	int predecessor;

};

struct arestas {
	int adj; /*!< Valor booleando. Verdadeiro representa uma adjacência entre dois vértices  */

	/* Mais informações, se necessário */
	int peso;
};

struct grafos {
	int n_vertices; /*!< Número de vértices do grafo  */
	vertice_t *vertices; /*!< Vetor de ponteiros: conjunto V */
	aresta_t **matriz_adj; /*!< Matriz de adjacência: conjunto E */
};

/**
 * @brief  Imprime os dados de cada vértice
 * @param	grafo: um grafo representado por matriz de adjacência
 *
 * @retval Nenhum. Dados são exibidos na saída padrão
 */
void imprime_dados_vertice(grafo_t *g) {
	int i;

	for (i = 0; i < g->n_vertices; i++) {
		printf("g->vertices[%d].distancia = %d  |  pred: %d \n", i,
				g->vertices[i].distancia, g->vertices[i].predecessor);
	}
}

/**
 * @brief  Implementação de Bellman-Ford para um grafo representado por matriz de adjacência
 * @param	grafo: um grafo
 * @param  fonte: vértice fonte utilizando em Bellman-Ford
 *
 * @retval Nenhum. Predecessor e distância são adicionados em cada vértice
 */

void bellman_ford(grafo_t *grafo, int fonte) {

	puts("Inicio de Bellman-Ford");

	int v, w, nova_distancia, i;

	for (v = 0; v < grafo->n_vertices; v++) {
		grafo->vertices[v].distancia = INFINITO;
		grafo->vertices[v].predecessor = -1;

	}

	grafo->vertices[fonte].distancia = 0;

	for (i = 0; i <= grafo->n_vertices - 1; i++) {

		for (v = 0; v <= grafo->n_vertices - 1; v++) {
			for (w = 0; w <= grafo->n_vertices - 1; w++) {

				if (adjacente(grafo, v, w)) {
					nova_distancia = obter_peso(grafo, v, w)
							+ obter_distancia(grafo, w);

					if (obter_distancia(grafo, v) > nova_distancia) {
						grafo->vertices[v].distancia = nova_distancia;
						grafo->vertices[v].predecessor = w;
					}
				}
			}

		}

	}

	imprime_dados_vertice(grafo);

}

/**
 * @brief  Imprime o caminho de menor distância. Execute Bellman-Ford previamente.
 * @param	grafo: um grafo
 * @param  fonte: vértice fonte utilizando em Bellman-Ford
 * @param  destino: vértice destino. Deve haver pelo menos um caminho entre fonte e destino
 *
 * @retval Nenhum
 */
void imprimir_caminho(grafo_t *grafo, int fonte, int destino) {


	puts("Inicio imprimir caminho\n");
	printf("caminho entre %d e %d\n ", fonte, destino);

    printf("%d  ", destino);
	while (fonte != destino) {
		printf(" %d \t ", grafo->vertices[destino].predecessor);
		destino = grafo->vertices[destino].predecessor;
	}


}

/**
 * @brief  Libera a memória utilizada pelo grafo
 * @param	Nenhum
 *
 * @retval Nenhum
 */
void libera_grafo(grafo_t *g) {

	int i;

	for (i=0; i < g->n_vertices; i++)
			free(g->matriz_adj[i]);


	free(g->matriz_adj);
	free(g->vertices);
	free(g);

}

/**
 * @brief  Cria uma novo grafo estático
 * @param	vertices: quantidade de vértices
 *
 * @retval grafo_t: ponteiro para um novo grafo
 */
grafo_t *cria_grafo(int vertices) {
	int i;
	aresta_t **matriz_adj;
	/* Aloca estrutura do grafo */
	grafo_t *g = malloc(sizeof(grafo_t));

	if (g == NULL) {
		perror("cria_grafo (g)");
		exit(EXIT_FAILURE);
	}

	/* Guarda número total de vértices */
	g->n_vertices = vertices;
	/* Aloca vértices */
	g->vertices = malloc(vertices * sizeof(vertice_t));

	if (g->vertices == NULL) {
		perror("cria_grafo (vertices)");
		exit(EXIT_FAILURE);
	}

	/* Zera vetor de vértices */
	memset(g->vertices, 0, vertices * sizeof(vertice_t));

	/* Aloca 1a dimensão da matriz de adjacência */
	matriz_adj = malloc(vertices * sizeof(aresta_t *));

	if (matriz_adj == NULL) {
		perror("cria_grafo (matriz_adj)");
		exit(EXIT_FAILURE);
	}

	/* Aloca 2a dimensão da matriz de adjacência */
	for (i = 0; i < vertices; i++) {
		matriz_adj[i] = calloc(vertices, sizeof(aresta_t));

		if (matriz_adj[i] == NULL) {
			perror("cria_grafo (matriz_adj[i])");
			exit(EXIT_FAILURE);
		}
	}

	g->matriz_adj = matriz_adj;

	/* Inicializa id dos vértices como índice do vetor */
	for (i = 0; i < g->n_vertices; i++)
		g->vertices[i].id = i;

	return g;
}

/**
 * @brief  Cria adjacência entre vértices u e v
 * @param	u: índice do vértice u
 * @param  v: índice do vértice v
 *
 * @retval int: verdadeiro se adjacência for criada
 */
int cria_adjacencia(grafo_t *g, int u, int v) {

	if (g == NULL) {
		return FALSE;
	}

	if (u > g->n_vertices || v > g->n_vertices)
		return FALSE;

	g->matriz_adj[u][v].adj = TRUE;

	return TRUE;
}

/**
 * @brief  Remove adjacência entre vértices u e v
 * @param	u: índice do vértice u
 * @param  v: índice do vértice v
 *
 * @retval int: verdadeiro se adjacência for removida
 */
int rem_adjacencia(grafo_t *g, int u, int v) {

	if (g == NULL) {
		return FALSE;
	}

	if (u > g->n_vertices || v > g->n_vertices)
		return FALSE;

	g->matriz_adj[u][v].adj = FALSE;

	return TRUE;
}

/**
 * @brief  Retorna adjacência entre vértices u e v
 * @param	u: índice do vértice u
 * @param  v: índice do vértice v
 *
 * @retval int: verdadeiro se u for adjacente a v
 */
int adjacente(grafo_t *g, int u, int v) {

	if (u > g->n_vertices || v > g->n_vertices)
		return FALSE;

	return ((g->matriz_adj[u][v].adj));
}

/**
 * @brief  Cria adjacência entre vértices u e v com um peso numérico na aresta
 * @param	u: índice do vértice u
 * @param  v: índice do vértice v
 * @param  peso: peso atribuído na aresta entre u e v
 *
 * @retval int: verdadeiro se adjacência for criada
 */
int cria_adjacencia_nao_dir(grafo_t *g, int u, int v, int peso) {

	if (g == NULL) {
		return FALSE;
	}

	if (u > g->n_vertices || v > g->n_vertices)
		return FALSE;

	g->matriz_adj[u][v].adj = TRUE;
	g->matriz_adj[v][u].adj = TRUE;
	g->matriz_adj[v][u].peso = peso;
	g->matriz_adj[u][v].peso = peso;

	return TRUE;
}

/**
 * @brief  Retorna o peso de uma aresta entre os vertices u e v
 * @param	u: índice do vértice u
 * @param  v: índice do vértice v
 *
 * @retval int: -1 se algum dos vertices não existir, o peso atual
 */
int obter_peso(grafo_t *g, int u, int v) {

	if (u > g->n_vertices || v > g->n_vertices)
		return -1;

	return g->matriz_adj[v][u].peso;
}

/**
 * @brief  Retorna a distancia associada ao vértice (Bellman Ford)
 * @param	g: grafo
 * @param  u: índice do vértice u
 *
 * @retval int: -1 se vertice não existir, a distância atual
 */
int obter_distancia(grafo_t *g, int u) {

	if (u > g->n_vertices)
		return -1;

	return g->vertices[u].distancia;
}

/**
 * @brief  Exporta para o formato dot um grafo representado por matriz de adjacência
 * @param	filename: nome do arquivo
 * @param  grafo: grafo para ser exportado
 *
 * @retval Nenhum
 */
void exportar_grafo_dot(const char *filename, grafo_t *grafo) {
	FILE* file;
	int i, j;

	if (filename == NULL || grafo == NULL) {
		fprintf(stderr, "exportar_grafp_dot: ponteiros invalidos\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(filename, "w");
	if (file == NULL) {
		perror("exportar_grafp_dot:");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "graph {\n");

	/* Exporta as strings dos vértices */
	for (i = 0; i < grafo->n_vertices; i++) {
		fprintf(file, "\t%d;\n", i);
	}

	for (i = 0; i < grafo->n_vertices; i++)
		for (j = i; j < grafo->n_vertices; j++)	// Exporta adjacencia na diagonal superior
			if ((grafo->matriz_adj[i][j].adj) == TRUE)
				fprintf(file, "\t%d -- %d [label=%d];\n", i, j,
						grafo->matriz_adj[i][j].peso); //[label="d0_1=1*27(4)"style=solid]

	fprintf(file, "}\n");
	fclose(file);
}
