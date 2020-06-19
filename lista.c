#include "lista.h"

typedef struct _no NODE;
//O no vai armazenar um vertice e um indicador para o proximo no
//The node will store the number of the vertex and the pointer to the next node
struct _no{
    int vertex;
    NODE *next;
};

//A lista tem um no de inicio, um de fim e um indicador de tamanho
//The list has an initial node, a final node and a indicator of it's size
struct _lista{
    NODE *ini,*final;
    int size;
};

//Funções axuliares:
//Auxiliary functions:
bool list_empty(LIST *l);
void empty(NODE *p);

//Cria a lista e a retorna
//Create the list and returns it
LIST *list_create(void){
    //aloca a estrutura da lista na heap
    //Allocate the list structure in the heap
    LIST *l = (LIST*)malloc(sizeof(LIST));
    //verifica se a alocacao deu certo
    //Verify if the allocation was successful
    if(l==NULL){											
		printf("Não há espaço suficiente\n");
		exit(1);
	}	
    l->ini = NULL;
    l->final = NULL;
    l->size = 0;
    return l;
}
//Insere um vertice à lista, retorna true se deu certo
//Insert a vertex in the list, returns true if everthing was ok
bool list_insert(LIST *l,int vertex){
    if(l != NULL) {								//verifica se a lista existe / Verify if the list exist
        NODE *node = (NODE*)malloc(sizeof(NODE));							//aloca o novo NO que sera inserido / Allocate the new node that will be insert
        node->vertex = vertex;										//o novo NO recebe o seu conteudo   / The new node recieve the vertex numver
        node->next = NULL;											
        if (list_empty(l)) {               						//se a lista esta vazia, o no sera o primeiro / If the list is empty the node will be the first
            l->ini = node;
        }else{
            l->final->next = node;										//coloca o NO no fim da lista   / Insert the node in the finish of the list
        }
        l->final = node;										
        l->size ++;                                                  //Aumenta o tamanho da lista / Increse the size of the list
        return TRUE;                                        //Retorna true se tudo deu certo / If everthing is ok returns true
    }else{
        return FALSE;                                       //Retorna falso se deu algo errado / If something wrong returns false
    }
}

//Apaga a lista
//Delete the list
void list_delete(LIST **l){
	if(*l == NULL){         //Verifica se a lista existe / Verify if the list exist
		return;
	}
	empty((*l)->ini);        //Chama a função que esvazia a lista no a no / Call the function that frees the list node to node
	free(*l);         
	*l = NULL;
	return;
}

//Retorna o tamanho da lista
//Return the size of the list
int list_get_size(LIST *list){
	return list->size;
}

//Verifica se um vertice está na lista, retorna true se estiver
//Verify if a vertex is already in the list, returns true if it's in the list
bool list_verify_existence(LIST *list,int vertex){
    if(list != NULL){      
        NODE *p = list->ini;
        while(p != NULL && p->vertex != vertex)       
            p = p->next;

        if(p == NULL)   return FALSE;
        else    return TRUE;
    }
    return FALSE;
}

//Retorna o numero do vertice que é o n ezimo termo da lista
//Return the number of the vertex that is the n° element of the list
int list_search_nNeighbor(LIST *list,int n){
    if(list != NULL){      //verifica se a lista existe / Verify if the list exist

		NODE *p = list->ini;
		for(int i=0;i<n;i++){
			p = p->next;
		}

		return p->vertex;
    }
    return FALSE;
}

//funcao recursiva que vai liberando NO por NO
//Recursive function tha free node to node of the list
void empty(NODE *p){											 
	if(p != NULL){
		if(p->next != NULL){
			empty(p->next);
		}
		free(p);
		p = NULL;
	}
	return;
}
//Verifica se a lista está vazia
//Verify if the list is empty
bool list_empty(LIST *l){
	if(l->ini == NULL){												
		return TRUE;
	}
	return FALSE;
}