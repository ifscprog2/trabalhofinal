#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "grafo/grafo.h"

grafo_t* le_vertices_arquivo(const char* filename)
{
    setlocale(LC_CTYPE, "");

    if (filename == NULL)
    {
        fprintf(stderr, "le_vertices_arquivo: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "le_vertices_arquivo: Arquivo não encontrado\n");
        exit(EXIT_FAILURE);
    }

    char buffer_temp[12]; //buffer para comparar com buffer_compara
    char buffer[100]; //buffer pra ler o arquivo para fazer o while
    char num_no[4]; //string com o id do vértice que está sendo lido
    char peso[5];
    int id_vertice_destino, id_vertice_fonte, dist,peso_aresta; //vetor com os ids de todos vertices

    grafo_t* grafo = cria_grafo(1);

    rewind(fp);
    //obter os ids dos vertices
    while (fgets(buffer, 100, fp) != NULL)
    {
        memcpy(buffer_temp, buffer, 12);

        //se for a linha com o numero do no o if é executado
        if (memcmp("Número do Nó", buffer_temp, 12) == 0)
        {

            memset(num_no, '\0', 4); //seta a string com o numero do no(vertice) com null em todas posições
            strncpy(num_no, &buffer[41], 3); //copia do buffer o trecho que tem o numero do no
            id_vertice_fonte = atoi(num_no); //converte de char para int

            grafo_adicionar_vertice(grafo, id_vertice_fonte);

        }

    }

    rewind(fp);
    //obter as arestas
    while (fgets(buffer, 100, fp) != NULL)
    {
        memcpy(buffer_temp, buffer, 12);

        //se for a linha com o numero do no o if é executado
        if (memcmp("Número do Nó", buffer_temp, 12) == 0)
        {

            memset(num_no, '\0', 4); //seta a string com o numero do no(vertice) com null em todas posições
            strncpy(num_no, &buffer[41], 3); //copia do buffer o trecho que tem o numero do no
            id_vertice_fonte = atoi(num_no); //converte de char para int

            while (fgets(buffer, 100, fp) != NULL)
            {

                memcpy(buffer_temp, buffer, 12);
                if (memcmp("------------", buffer_temp, 12) == 0)
                    break;

                //se for aresta
                if (memcmp("Índice......", buffer_temp, 12) == 0)
                {

                    memset(num_no, '\0', 4); //seta a string com o numero do no(vertice) com null em todas posições
                    strncpy(num_no, &buffer[35], 3); //copia do buffer o trecho que tem o numero do no
                    id_vertice_destino = atoi(num_no); //converte de char para int

                    memset(peso, '\0', 5); //seta a string com o peso da aresta com null em todas posições
                    strncpy(peso, &buffer[64], 4); //copia do buffer o trecho que tem o peso da aresta
                    peso_aresta = atoi(peso); //converte de char para int

                    if (!procurar_adjacente(procura_vertice(grafo, id_vertice_fonte),procura_vertice(grafo, id_vertice_destino)))
                    {
                         adiciona_adjacentes(grafo,procura_vertice(grafo, id_vertice_fonte), 2,id_vertice_destino, peso_aresta);

                    }


                }

            }



        }

    }
    imprime_vertices(grafo);

    return grafo;

}
