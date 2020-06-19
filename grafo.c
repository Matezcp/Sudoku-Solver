#include "grafo.h"

//A estrutura do grafo eh composta por um vetor de listas e um indicados do numero de vertices
struct _grafo{
    LISTA** lista_de_adjacencia;
    int num_vertices;
};

int whitchQuadrant(int linha,int coluna);
void insertQuadrantNeighbor(int vertice,int *vizinhos);
int verificaCor(GRAFO *grafo, int vertice,int *cores,int cor);


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

//insere uma aresta direcionada do vertice1 para o vertice2
void grafo_inserir_aresta_direcionado(GRAFO *grafo,int vertice1,int vertice2){
    if(lista_verificar_existencia(grafo->lista_de_adjacencia[vertice1],vertice2)==FALSE){ //Verifica se a aresta já existe
        //Insere a aresta, colocando-a na lista dos vertices desejados
        lista_inserir(grafo->lista_de_adjacencia[vertice1],vertice2); 
    }
}


void grafo_sudoku(GRAFO *grafo){
    int matriz[9][9];
    int value = 0;
    int linha,coluna;
    int vizinhos[20];
    int i,j,k;

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++,value++){
            matriz[i][j] = value;
        }
    }

    for(i=0,k=0;i<grafo->num_vertices;i++,k=0){
        linha = i / 9;
        coluna = i % 9;

        //Anda toda coluna para baixo
        for(j=coluna+1;j<9;j++,k++)
            vizinhos[k] = matriz[linha][j];
        //Anda toda coluna para cima
        for(j=coluna-1;j>=0;j--,k++)
            vizinhos[k] = matriz[linha][j];
        //Anda toda linha para direita
        for(j=linha+1;j<9;j++,k++)
            vizinhos[k] = matriz[j][coluna];
        //Anda toda linha para esquerda
        for(j=linha-1;j>=0;j--,k++)
            vizinhos[k] = matriz[j][coluna];

        //Insere
        insertQuadrantNeighbor(i,vizinhos);

        //Insere as arestas
        for(j=0;j<20;j++){
            grafo_inserir_aresta_direcionado(grafo,i,vizinhos[j]);
        }


    }
    

}

//Colore o Grafo
int grafo_colorido(GRAFO *grafo,int *cores,int vertice){
    //Se chegou no ultimo vertice retorna true
    if(vertice == 81)
        return 1;
    
    //Se já estiver colorido
    if(cores[vertice]){
        //Chama para o próximo vertice, se retornar true retorna true
        if(grafo_colorido(grafo,cores,vertice+1))
            return 1;
        //Se retornar false retorna false
        else
            return 0;
    }

    //Se não tiver colorido ve cor a cor
    for(int i=1;i<=9;i++){
        //Se a cor pode ser colocada naquela posição
        if(verificaCor(grafo,vertice,cores,i)){
            //Coloca a cor naquela posição
            cores[vertice] = i;
            //Chama a função para o proximo vertice se retornar true, retorna true
            if(grafo_colorido(grafo,cores,vertice+1))
                return 1;
            //Se não retornar true marca o vertice como não colorido e tenta outra cor
            cores[vertice] = 0;
        }
    }

    //Se no final não conseguir retorna false
    return 0;
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

int whitchQuadrant(int linha,int coluna){
    int mult;
    if(linha <= 2){
        mult = 0;
    }
    else if(linha <= 5){
        mult = 3;
    }
    else{
        mult = 6;
    }

    if(coluna <= 2){
        return mult;
    }
    else if(coluna <= 5){
        return mult + 1;
    }
    else{
        return mult + 2;
    }

}

void insertQuadrantNeighbor(int vertice,int *vizinhos){
    int linha,coluna;
    int modLinha,modColuna;

    linha = vertice/9;
    coluna = vertice % 9;

    int quadrant = whitchQuadrant(linha,coluna);

    modLinha = linha % 3;
    modColuna = coluna % 3;

    if(modLinha == 0){
        if(modColuna == 0){
            vizinhos[16] = vertice + 10;
            vizinhos[17] = vertice + 11;
            vizinhos[18] = vertice + 19;
            vizinhos[19] = vertice + 20;
        }
        else if(modColuna == 1){
            vizinhos[16] = vertice + 8;
            vizinhos[17] = vertice + 10;
            vizinhos[18] = vertice + 17;
            vizinhos[19] = vertice + 19;
        }
        else{
            vizinhos[16] = vertice + 7;
            vizinhos[17] = vertice + 8;
            vizinhos[18] = vertice + 16;
            vizinhos[19] = vertice + 17;
        }
    }
    else if(modLinha == 1){
        if(modColuna == 0){
            vizinhos[16] = vertice - 8;
            vizinhos[17] = vertice - 7;
            vizinhos[18] = vertice + 10;
            vizinhos[19] = vertice + 11;
        }
        else if(modColuna == 1){
            vizinhos[16] = vertice - 10;
            vizinhos[17] = vertice - 8;
            vizinhos[18] = vertice + 8;
            vizinhos[19] = vertice + 10;
        }
        else{
            vizinhos[16] = vertice - 11;
            vizinhos[17] = vertice - 10;
            vizinhos[18] = vertice + 7;
            vizinhos[19] = vertice + 8;
        }
    }
    else{
        if(modColuna == 0){
            vizinhos[16] = vertice - 17;
            vizinhos[17] = vertice - 16;
            vizinhos[18] = vertice - 8;
            vizinhos[19] = vertice - 7;
        }
        else if(modColuna == 1){
            vizinhos[16] = vertice - 19;
            vizinhos[17] = vertice - 17;
            vizinhos[18] = vertice - 10;
            vizinhos[19] = vertice - 8;
        }
        else{
            vizinhos[16] = vertice - 20;
            vizinhos[17] = vertice - 19;
            vizinhos[18] = vertice - 11;
            vizinhos[19] = vertice - 10;
        }
    }

}

int verificaCor(GRAFO *grafo, int vertice,int *cores,int cor){
    int vizinho;
    for(int i=0;i<lista_get_tam(grafo->lista_de_adjacencia[vertice]);i++){
        vizinho = lista_buscar_nVizinho(grafo->lista_de_adjacencia[vertice],i);
        if(cores[vizinho] == cor)
            return 0;
    }

    return 1;
}
