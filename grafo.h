#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct _grafo GRAFO;

//Cria um grafo sem arestas, de num_vertices de vertices
GRAFO *grafo_criar(int num_vertices);
//Insere uma aresta entre os vertices: vertice1 e vertice2 no grafo
void grafo_inserir_aresta(GRAFO *grafo,int vertice1,int vertice2);
//Retira uma aresta entre os vertices: vertice1 e vertice2 no grafo
void grafo_remover_aresta(GRAFO *grafo,int vertice1,int vertice2);
//Impriem o grafo
void grafo_imprimir(GRAFO *grafo);
//Apaga todo o grafo
void grafo_apagar(GRAFO *grafo);

#endif