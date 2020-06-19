#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct _grafo GRAPH;

//Cria um grafo sem arestas, de num_vertices de vertices
//Create a graph with num_vertex of vertexs and without edges
GRAPH *graph_create(int num_vertex);
//Insere uma aresta direcionada do vertice1 para o vertice2
//Insert a directed edge from vertex1 to vertex2
void graph_insert_directed_edge(GRAPH *graph,int vertex1,int vertex2);
//Cria tabuleiro sudoku
//Create a sudoku board
void graph_sudoku(GRAPH *graph);
//Colore o grafo para completar o sudoku, retorna true se obteve sucesso
//Color the graph to fill the sudoku, returns true with sucess
int graph_color(GRAPH *graph,int *colors,int vertex);
//Apaga todo o grafo
//Delete the graph
void graph_delete(GRAPH *graph);


#endif