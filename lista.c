#include "lista.h"

typedef struct _no NO;
//O no vai armazenar um vertice e um indicador para o proximo no
struct _no{
    int vertice;
    NO *prox;
};

//A lista tem um no de inicio, um de fim e um indicador de tamanho
struct _lista{
    NO *ini,*fim;
    int tam;
};

LISTA *lista_criar(void){
    LISTA *l = (LISTA*)malloc(sizeof(LISTA));						//aloca a estrutura da lista na heap
    if(l==NULL){													//verifica se a alocacao deu certo
		printf("Não há espaço suficiente\n");
		exit(1);
	}	
    l->ini = NULL;
    l->fim = NULL;
    l->tam = 0;
    return l;
}
bool lista_inserir(LISTA *l,int vertice){
    if(l != NULL) {								//verifica se a lista existe
        NO *no = (NO*)malloc(sizeof(NO));							//aloca o novo NO que sera inserido
        no->vertice = vertice;										//o novo NO recebe o seu conteudo
        no->prox = NULL;											//o novo NO aponta para nada
        if (lista_vazia(l)) {               						//se a lista esta vazia, o no sera o primeiro
            l->ini = no;
        }else{
            l->fim->prox = no;										//coloca o NO no fim da lista
        }
        l->fim = no;												//aponta o fim para o novo NO, ja que ele entra na ultima posicao
        l->tam ++;                                                  //Aumenta o tamanho da lista
        return TRUE;
    }else{
        return FALSE;
    }
}

bool lista_verificar_existencia(LISTA *lista,int vertice_buscado){
    if(lista != NULL){      //verifica se a lista existe
        NO *p = lista->ini;
        while(p != NULL && p->vertice != vertice_buscado)       //O no p que aponta para o inicio na lista a percorre até chegar ao fim ou achar o vertice desejado
            p = p->prox;

        if(p == NULL)   return FALSE;                   //Verifica se p achou o fim da lista ou o no desejado
        else    return TRUE;
    }
    return FALSE;
}
bool lista_remover(LISTA *l,int vertice_procurado){
	int id;
	if(l!=NULL){                                                        //verifica se a lista existe
		if(lista_vazia(l)){                                     //Verifica se a lista não está vazia
			printf("A lista está vazia\n");
		}
		else{
			NO *p = l->ini;
			NO *aux = NULL;             //No auxiliar aponta para o no anterior ao no p
			while(p != NULL && p->vertice != vertice_procurado){		 //procura ate acabar a lista ou achar o item
				aux = p;											 //salva o NO anterior
				p = p->prox;
			}
			if(p!=NULL){											 //so executa se o item foi achado
				if(p==l->ini){										 //se for o primeiro item	
					l->ini = p->prox;
					p->prox = NULL;
				}
				else {
					aux->prox = p->prox;
				}
				if(p==l->fim){										 //se for o ultimo item 
					l->fim = aux;
				}
				l->tam--;
				free(p);
				return(TRUE);
			}
		}	
	}
	return(FALSE);
}
void lista_imprime(LISTA *l){
	if(l != NULL && !lista_vazia(l)){
		NO *p = l->ini;
		while(p != NULL){											 //roda ate chegar no fim da lista
            printf("%d ",p->vertice);                           //Impre o vertice do no e faz p ir ao proximo no
			p = p->prox;
		}
	}
    printf("\n");           
	return;
}
void esvaziar(NO *p){											  	//funcao recursiva que vai liberando NO por NO
	if(p != NULL){
		if(p->prox != NULL){
			esvaziar(p->prox);
		}
		free(p);
		p = NULL;
	}
	return;
}

void lista_apagar(LISTA **l){	
	if(*l == NULL){         //Verifica se a lista existe
		return;
	}
	esvaziar((*l)->ini);        //Chama a função que esvazia a lista no a no
	free(*l);           //Por fim da free no ponteiro da lista e faz ele apontar para NULL
	*l = NULL;
	return;
}

bool lista_vazia(LISTA *l){
	if(l->ini == NULL){												//se a primeira posicao eh NULL, entao nao tem nenhum NO
		return TRUE;
	}
	return FALSE;
}

int lista_get_tam(LISTA *lista){
	return lista->tam;
}

int lista_buscar_nVizinho(LISTA *lista,int n){
    if(lista != NULL){      //verifica se a lista existe

		NO *p = lista->ini;
		for(int i=0;i<n;i++){
			p = p->prox;
		}

		return p->vertice;
    }
    return FALSE;
}