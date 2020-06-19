#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#define bool int                                //define o tipo booleano  / Define the boolean type
#define TRUE 1                                  //define o tipo booleano  / Define the boolean type 
#define FALSE 0                                 //define o tipo booleano  / Define the boolean type

typedef struct _lista LIST;

//Cria a lista
//Create the list
LIST *list_create(void);
//Insere um vertice à lista
//Insert a vertex in the list
bool list_insert(LIST *l,int vertex);
//Apaga a lista
//Delete the list
void list_delete(LIST **l);
//Retorna o tamanho da lista
//Return the size of the list
int list_get_size(LIST *list);
//Verifica se um vertice está na lista
//Verify if a vertex is already in the list
bool list_verify_existence(LIST *list,int vertex);
//Retorna o numero do vertice que é o n ezimo termo da lista
//Return the number of the vertex that is the n° element of the list
int list_search_nNeighbor(LIST *list,int n);

#endif