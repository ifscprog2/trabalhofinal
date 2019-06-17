#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "grafo/grafo.h"


grafo_t* le_vertices_arquivo(const char* filename)
{
    setlocale(LC_CTYPE, "");

    if(filename==NULL)
    {
        fprintf(stderr, "le_vertices_arquivo: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(filename, "r");

    if(fp==NULL)
        {
            fprintf(stderr, "le_vertices_arquivo: Arquivo n�o encontrado\n");
            exit(EXIT_FAILURE);
        }


    char buffer_compara[12]; //armazena a string N�mero do n� para fazer a busca
    char buffer_temp[12];//buffer para comparar com buffer_compara
    char buffer[100];//buffer pra ler o arquivo para fazer o while
    char num_no[4];//string com o id do v�rtice que est� sendo lido
    int id_vertice; //vetor com os ids de todos vertices


    grafo_t* grafo = cria_grafo(1);
    vertice_t* vertice;

    fread(buffer_compara,sizeof(char), 12, fp);

    rewind(fp);

    while(fgets(buffer,100,fp)!=NULL)
    {
        memcpy(buffer_temp,buffer,12);

        //se for a linha com o numero do no o if � executado
        if(memcmp(buffer_compara,buffer_temp,sizeof(buffer_compara))==0)
        {

            memset(num_no,'\0',4); //seta a string com o numero do no(vertice) com null em todas posi��es
            strncpy(num_no,&buffer[41],3); //copia do buffer o trecho que tem o numero do no
            id_vertice = atoi(num_no);//converte de char para int

            //  printf("\n id_vertice = %d  no= %s", id_vertice[k],num_no);

            vertice= grafo_adicionar_vertice(grafo,id_vertice);
            printf("\nAdcionando vertice:");
            printf("\nid= %d\n", vertice_get_id(vertice));


        }

    }
       //printf("k= %d",k); //numero de vertices
    fflush(stdout);
    imprime_vertices(grafo);

    return grafo ;

}