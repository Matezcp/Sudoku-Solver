#include <stdio.h>
#include "grafo.h"

int main(){
    char value;
    int *colors = (int *) calloc(sizeof(int),81);

    GRAPH *graph;

    graph = graph_create(81);

    graph_sudoku(graph);
    
    for(int i=0;i<81;i++){
        scanf("%c",&value);
        value -= 48;
        colors[i] = value;
    }

    if(graph_color(graph,colors,0)){
        printf("-------------------\n");
        for(int i=0;i<9;i++){
            printf("|");
            for(int j=0;j<9;j++){
                printf("%d|",colors[(i*9)+j]);
            }  
        printf("\n-------------------\n");
        }
    }
    else{
        printf("Solução não encontrada :( \n");
        printf("Solution not found :( \n");
    }

    free(colors);

    return 0;
}