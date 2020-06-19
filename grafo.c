#include "grafo.h"

//A estrutura do graph eh composta por um vetor de listas e um indicados do numero de vertices
//The graph's structure is composed of a vector of lists and a indicator of the vertex number
struct _grafo{
    LIST** list_of_adjacency;
    int num_vertex;
};

//Funções axuliares:
//Auxiliary functions:
void insertQuadrantNeighbor(int vertex,int *neighbors);
int verifyColor(GRAPH *graph, int vertex,int *colors,int color);

//Cria um grafo sem arestas, de num_vertex de vertices e retorna o grafo
//Create a graph with num_vertex of vertexs and without edges and returns it
GRAPH *graph_create(int num_vertex){
    GRAPH *graph;
    //Verifica se a alocação foi bem sucedida
    //Verify if the allocation was successful
    if((graph = (GRAPH *) malloc(sizeof(GRAPH)))==NULL) return NULL;

    graph->num_vertex = num_vertex;
    //Verifica se a alocação foi bem sucedida
    //Verify if the allocation was successful
    if((graph->list_of_adjacency = (LIST**) malloc(sizeof(LIST*)*num_vertex))==NULL) return NULL;

    for(int i=0;i<num_vertex;i++){
        //Cria uma lista para cada vertice
        //Create a list for each vertex
        graph->list_of_adjacency[i] = list_create();
    }

    return graph;
}

//Insere uma aresta direcionada do vertice1 para o vertice2
//Insert a directed edge from vertex1 to vertex2
void graph_insert_directed_edge(GRAPH *graph,int vertex1,int vertex2){
    if(!list_verify_existence(graph->list_of_adjacency[vertex1],vertex2)){ //Verifica se a aresta já existe / Verify if the edge already exist
        list_insert(graph->list_of_adjacency[vertex1],vertex2); 
    }
}

//Cria o tabuleiro sudoku conectando as arestas que precisam ser conectadas
//Create a sudoku board connecting the edges that needs to be connected
void graph_sudoku(GRAPH *graph){
    int matrix[9][9];
    int value = 0;
    int line,column;
    int neighbors[20];
    int i,j,k;

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++,value++){
            matrix[i][j] = value;
        }
    }

    for(i=0,k=0;i<graph->num_vertex;i++,k=0){
        line = i / 9;
        column = i % 9;

        //Anda toda coluna para baixo
        //Pass all the columns under the vertex
        for(j=column+1;j<9;j++,k++)
            neighbors[k] = matrix[line][j];
        //Anda toda coluna para cima
        //Pass all the columns above the vertex
        for(j=column-1;j>=0;j--,k++)
            neighbors[k] = matrix[line][j];
        //Anda toda linha para direita
        //Pass all the line going to the right of the vertex
        for(j=line+1;j<9;j++,k++)
            neighbors[k] = matrix[j][column];
        //Anda toda linha para esquerda
        //Pass all the line going to the left of the vertex
        for(j=line-1;j>=0;j--,k++)
            neighbors[k] = matrix[j][column];

        //Insere os vizinhos do quadrado do sudoku que faltaram
        //Insert he nheibors of the sudoku's square that are missing
        insertQuadrantNeighbor(i,neighbors);

        //Insere as arestas
        //Insert the edges
        for(j=0;j<20;j++){
            graph_insert_directed_edge(graph,i,neighbors[j]);
        }

    }
    
}

//Colore o grafo para completar o sudoku, retorna true se obteve sucesso
//Color the graph to fill the sudoku, returns true with sucess
int graph_color(GRAPH *graph,int *colors,int vertex){
    //Se chegou no ultimo vertice retorna true
    //If reach the last vertex returns true
    if(vertex == 81)
        return TRUE;
    
    //Se já estiver colorido
    //If already with color
    if(colors[vertex]){
        //Chama para o próximo vertice, se retornar true retorna true
        //Calls the function to the next vertex if returns true return true
        if(graph_color(graph,colors,vertex+1))
            return TRUE;
        //Se retornar false retorna false
        //If returns false return false
        else
            return FALSE;
    }

    //Se não tiver colorido analise cor a cor
    //If not colored yet analyse color to color
    for(int i=1;i<=9;i++){
        //Verifica se a cor pode ser colocada naquela posição
        //Verify if the color can be put in that vertexs
        if(verifyColor(graph,vertex,colors,i)){
            //Coloca a cor naquela posição
            //Put the color in that vertex
            colors[vertex] = i;
            //Chama a função para o proximo vertice se retornar true, retorna true
            //Calls the function to the next vertex if returns true return true
            if(graph_color(graph,colors,vertex+1))
                return TRUE;
            //Se não retornar true marca o vertice como não colorido e tenta outra cor
            //If not returns true assign the vertex as not colored and try another color
            colors[vertex] = 0;
        }
    }

    //Se no final não conseguir retorna false
    //If reach here returns false
    return FALSE;
}

//Apaga todo o grafo
//Delete the graph
void graph_delete(GRAPH *graph){
    //Apaga a lista de cada vertice
    //Delete the list of each vertex
    for(int i=0;i<graph->num_vertex;i++){
        list_delete(&graph->list_of_adjacency[i]);
    }
    //Por fim apaga o ponteiro duplo das listas e o graph
    //Lastly delete the double pointer of the lists and the graph
    free(graph->list_of_adjacency);
    free(graph);
}

//Ve os vizinhos do quadrado do sudoku do vertice em questão
//See the neighbors of the sudoku square of the vertex
void insertQuadrantNeighbor(int vertex,int *neighbors){
    int line,column;
    int modline,modcolumn;

    line = vertex/9;
    column = vertex % 9;

    modline = line % 3;
    modcolumn = column % 3;

    if(modline == 0){
        if(modcolumn == 0){
            neighbors[16] = vertex + 10;
            neighbors[17] = vertex + 11;
            neighbors[18] = vertex + 19;
            neighbors[19] = vertex + 20;
        }
        else if(modcolumn == 1){
            neighbors[16] = vertex + 8;
            neighbors[17] = vertex + 10;
            neighbors[18] = vertex + 17;
            neighbors[19] = vertex + 19;
        }
        else{
            neighbors[16] = vertex + 7;
            neighbors[17] = vertex + 8;
            neighbors[18] = vertex + 16;
            neighbors[19] = vertex + 17;
        }
    }
    else if(modline == 1){
        if(modcolumn == 0){
            neighbors[16] = vertex - 8;
            neighbors[17] = vertex - 7;
            neighbors[18] = vertex + 10;
            neighbors[19] = vertex + 11;
        }
        else if(modcolumn == 1){
            neighbors[16] = vertex - 10;
            neighbors[17] = vertex - 8;
            neighbors[18] = vertex + 8;
            neighbors[19] = vertex + 10;
        }
        else{
            neighbors[16] = vertex - 11;
            neighbors[17] = vertex - 10;
            neighbors[18] = vertex + 7;
            neighbors[19] = vertex + 8;
        }
    }
    else{
        if(modcolumn == 0){
            neighbors[16] = vertex - 17;
            neighbors[17] = vertex - 16;
            neighbors[18] = vertex - 8;
            neighbors[19] = vertex - 7;
        }
        else if(modcolumn == 1){
            neighbors[16] = vertex - 19;
            neighbors[17] = vertex - 17;
            neighbors[18] = vertex - 10;
            neighbors[19] = vertex - 8;
        }
        else{
            neighbors[16] = vertex - 20;
            neighbors[17] = vertex - 19;
            neighbors[18] = vertex - 11;
            neighbors[19] = vertex - 10;
        }
    }

}

//Verifica se a cor pode ser colocada no vertice em questão
//Verify if the color can be put in the vertex
int verifyColor(GRAPH *graph, int vertex,int *colors,int color){
    int neighbor;
    for(int i=0;i<list_get_size(graph->list_of_adjacency[vertex]);i++){
        neighbor = list_search_nNeighbor(graph->list_of_adjacency[vertex],i);
        if(colors[neighbor] == color)
            return 0;
    }

    return 1;
}
