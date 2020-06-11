#include "grafo.h"

//A estrutura do grafo eh composta por um vetor de listas e um indicados do numero de vertices
struct _grafo{
    LISTA** lista_de_adjacencia;
    int num_vertices;
};


GRAFO *grafo_criar(int num_vertices){
    GRAFO *grafo;
    if((grafo = (GRAFO *) malloc(sizeof(GRAFO)))==NULL) return NULL; //Verifica se a alocação foi bem sucedida

    grafo->num_vertices = num_vertices;
    if((grafo->lista_de_adjacencia = (LISTA**) malloc(sizeof(LISTA*)*num_vertices))==NULL) return NULL; //Verifica se a alocação foi bem sucedida

    for(int i=0;i<num_vertices;i++){
        grafo->lista_de_adjacencia[i] = lista_criar(); //Cria uma lista para cada vertice
    }

    return grafo;
}

void grafo_inserir_aresta(GRAFO *grafo,int vertice1,int vertice2){
    if(lista_verificar_existencia(grafo->lista_de_adjacencia[vertice1],vertice2)==FALSE){ //Verifica se a aresta já existe
        //Insere a aresta, colocando-a na lista dos vertices desejados
        lista_inserir(grafo->lista_de_adjacencia[vertice1],vertice2); 
        lista_inserir(grafo->lista_de_adjacencia[vertice2],vertice1);
    }
}

void grafo_remover_aresta(GRAFO *grafo,int vertice1,int vertice2){
    //Remove a aresta de cada lista, a verificação de existencia da aresta ocorre dentro da funcao lista_remover
    lista_remover(grafo->lista_de_adjacencia[vertice1],vertice2);
    lista_remover(grafo->lista_de_adjacencia[vertice2],vertice1);
}

void grafo_imprimir(GRAFO *grafo){
    for(int i=0; i<grafo->num_vertices;i++){    //Percorre a lista de cada vertice, imprimindo o numero do vertice e em seguida imprimindo a lista daquele vertice
        printf("%d: ",i);
        lista_imprime(grafo->lista_de_adjacencia[i]);
    }
    printf("\n"); //Apos imprimir o grafo inteiro, pular uma linha
}

void grafo_apagar(GRAFO *grafo){
    //Apaga a lista de cada vertice
    for(int i=0;i<grafo->num_vertices;i++){
        lista_apagar(&grafo->lista_de_adjacencia[i]);
    }
    //Por fim apaga o ponteiro duplo das listas e o grafo
    free(grafo->lista_de_adjacencia);
    free(grafo);
}

