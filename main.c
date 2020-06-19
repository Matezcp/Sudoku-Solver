#include <stdio.h>
#include "grafo.h"

int main(){
    char entrada;
    int *cores = (int *) calloc(sizeof(int),81);

    GRAFO *grafo;

    grafo = grafo_criar(81);

    grafo_sudoku(grafo);
    
    for(int i=0;i<81;i++){
        scanf("%c",&entrada);
        entrada -= 48;
        cores[i] = entrada;
    }

    if(grafo_colorido(grafo,cores,0)){
        printf("-------------------\n");
        for(int i=0;i<9;i++){
            printf("|");
            for(int j=0;j<9;j++){
                printf("%d|",cores[(i*9)+j]);
            }  
        printf("\n-------------------\n");
        }
    }
    else{
        printf("Solução não encontrada :( \n");
    }

    free(cores);

    return 0;
}