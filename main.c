#include <stdio.h>
#include "grafo.h"

int main(){
    int *cores;

    GRAFO *grafo;

    grafo = grafo_criar(81);

   /* grafo_inserir_aresta(grafo,0,1);
    grafo_inserir_aresta(grafo,0,7);
    grafo_inserir_aresta(grafo,1,3);
    grafo_inserir_aresta(grafo,2,3);
    grafo_inserir_aresta(grafo,3,8);
    grafo_inserir_aresta(grafo,3,10);
    grafo_inserir_aresta(grafo,4,5);
    grafo_inserir_aresta(grafo,4,10);
    grafo_inserir_aresta(grafo,5,6);
    grafo_inserir_aresta(grafo,6,10);
    grafo_inserir_aresta(grafo,6,7);
    grafo_inserir_aresta(grafo,7,8);
    grafo_inserir_aresta(grafo,7,9);
    grafo_inserir_aresta(grafo,7,10);
    grafo_inserir_aresta(grafo,8,9);
    grafo_inserir_aresta(grafo,9,10);*/



    //cores = grafo_colorido(grafo);

    //grafo_imprimir(grafo);

   /* for(int i=0;i<11;i++){
        printf("GRAFO: %d COR: %d\n",i,cores[i]);
    }*/

    return 0;
}