#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#define bool int                                //define o tipo booleano 
#define TRUE 1                                  //define o tipo booleano 
#define FALSE 0                                 //define o tipo booleano 

typedef struct _lista LISTA;

//Cria a lista
LISTA *lista_criar(void);
//Insere um vertice à lista
bool lista_inserir(LISTA *l,int vertice);
// Remove um vertice da lista
bool lista_remover(LISTA *l,int vertice);
//Imprime a lista
void lista_imprime(LISTA *l);
//Verifica se a lista está vazia
bool lista_vazia(LISTA *l);
//Apaga a lista
void lista_apagar(LISTA **l);
//Verifica se existe um determinado vertice na lista
bool lista_verificar_existencia(LISTA *lista,int vertice_buscado);

#endif