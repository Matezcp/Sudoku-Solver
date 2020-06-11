#include "grafo.h"

//A estrutura do grafo eh composta por um vetor de listas e um indicados do numero de vertices
struct _grafo{
    LISTA** lista_de_adjacencia;
    int num_vertices;
};

//Estrutura para auxiliar a ordenação por número de arestas do vértice
struct _num_arestas{
    int numeroDoVertice;
    int numeroDeArestas;
};

//Enum para representar as direções
//typedef enum {vermelho,azul,amarelo,verde} COR;

//Função axuliar bubble sort que ordena do maior para o menor
void bubbleSort(NUMARESTAS *arestas,int tam);


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

//Colore o Grafo
int *grafo_colorido(GRAFO *grafo){
    NUMARESTAS* arestas = calloc(sizeof(NUMARESTAS),grafo->num_vertices);
    int *cores = calloc(sizeof(int),grafo->num_vertices);

    for(int i=0;i<grafo->num_vertices;i++){
        arestas[i].numeroDoVertice = i;
        arestas[i].numeroDeArestas = lista_get_tam(grafo->lista_de_adjacencia[i]);
    }

    bubbleSort(arestas,grafo->num_vertices);

    int cor = 1,acabou = 0,i,vizinho,msmcor = 0;
    do{
        acabou = 1;
        //Atribuindo a cor atual ao primeiro vertice incolor da lista
        for(i=0;i<grafo->num_vertices;i++){
            if(cores[arestas[i].numeroDoVertice]==0){
                cores[arestas[i].numeroDoVertice] = cor;
                acabou = 0;
                i++;
                break;
            }
        }
        //Percorre o resto da lista e se ele é incolor e não é adjacente a um vertice colorido, atribui cor a ele
        for(;i<grafo->num_vertices;i++){
            //É incolor
            if(cores[arestas[i].numeroDoVertice] == 0){
                //Percorre a lista de adjacencia dele e se ouver algum vertice colorido com a cor atual continua a percorrer a lista
                for(int j=0;j<lista_get_tam(grafo->lista_de_adjacencia[arestas[i].numeroDoVertice]);j++){
                    vizinho = lista_buscar_nVizinho(grafo->lista_de_adjacencia[arestas[i].numeroDoVertice],j);
                    if(cores[vizinho] == cor){
                        msmcor = 1;
                        break;
                    }
                }
                //Se não tiver vizinhos de mesma cor colore com a cor
                if(msmcor == 0){
                    cores[arestas[i].numeroDoVertice] = cor;
                }
            }
            msmcor = 0;
        }
        
        cor++;
    }while(!acabou);

    free(arestas);
    return cores;
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

void bubbleSort(NUMARESTAS *arestas,int tam){
    int i, j;
    NUMARESTAS aux;
    for (i = 1; i < tam; i++) {
        for (j = 0; j < tam - 1; j++) {
            if(arestas[j].numeroDeArestas < arestas[j +1].numeroDeArestas){
                aux = arestas[j];
                arestas[j] = arestas[j+1];
                arestas[j+1] = aux;
            }
        }
    }
}

