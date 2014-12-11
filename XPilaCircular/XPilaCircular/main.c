//
//  main.c
//  XPilaCircular
//
//  Created by Cristian Miranda on 6/15/13.
//  Copyright (c) 2013 Cristian Miranda. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define PILA_VACIA 1
#define PILA_LLENA 2

typedef struct {
    int num;
}t_info;

typedef struct s_nodo{
    t_info info;
    struct s_nodo *sig;
}t_nodo, *t_pila;


//FUNCIONES DE LISTA CIRCULAR - IMPLEMENTACION EN PILA

void crearPila(t_pila *pp);
int pilaVacia(const t_pila *pp);
int pilaLlena(const t_pila *pp);
void vaciarPila(t_pila *pp);
int verTopeDePila(const t_pila *pp, t_info *pd);
int ponerEnPila(t_pila *pp, const t_info *pd);
int sacarDePila(t_pila *pp, t_info *pd);

/**
 * Funcion para ver el estado de la pila
 */
void debug(const t_pila *pp){
    int fin = 0;
    t_nodo *fondo = *pp;
    t_nodo *tope = (*pp)->sig;
    while(tope != fondo || !fin){
        printf("%d | --> %d\n", tope->info.num, tope->sig->info.num);
        if(tope == fondo){
            fin = 1;
        }else{
            tope = tope->sig;
        }
    }
}

int main(int argc, const char * argv[])
{
    t_pila pila;
    t_info info;
    
    crearPila(&pila);

    info.num = 1;
    ponerEnPila(&pila, &info);
    
    info.num = 2;
    ponerEnPila(&pila, &info);
    
    info.num = 3;
    ponerEnPila(&pila, &info);
    
    printf("\nPila vacia?: %s", pilaVacia(&pila)==1?"SI":"NO");
    
    verTopeDePila(&pila, &info);
    printf("\nTope de pila: %d\n\n", info.num);
    debug(&pila);
    
    //vaciarPila(&pila);
    
    puts("\nSaco de pila... 3\n");
    sacarDePila(&pila,&info);
    debug(&pila);
    
    puts("\nSaco de pila... 2\n");
    sacarDePila(&pila,&info);
    debug(&pila);
    
    puts("\nSaco de pila... 1\n");
    sacarDePila(&pila,&info);
    printf("Pila vacia?: %s", pilaVacia(&pila)==1?"SI":"NO");
    
    return TODO_OK;
}


void crearPila(t_pila *pp){
    *pp = NULL;
}

int pilaVacia(const t_pila *pp){
    return *pp == NULL;
}

int pilaLlena(const t_pila *pp){
    void *aux = malloc(sizeof(t_nodo));
    free(aux);
    return aux == NULL;
}

void vaciarPila(t_pila *pp){
    t_nodo *aux;
    while(*pp){
        aux = (*pp)->sig;
        (*pp)->sig = aux->sig;
        if(aux == *pp)
            *pp = NULL;
        free(aux);
    }
}

int verTopeDePila(const t_pila *pp, t_info *pd){
    if(*pp == NULL)
        return PILA_VACIA;
    
    *pd = (*pp)->sig->info;
    
    return TODO_OK;
}

int ponerEnPila(t_pila *pp, const t_info *pd){
    t_nodo *nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(nue == NULL)
        return PILA_LLENA;
    
    nue->info = *pd;
    if(*pp == NULL){
        nue->sig = nue;
        *pp = nue;
    }else{
        nue->sig = (*pp)->sig;
        (*pp)->sig = nue;
    }
    
    return TODO_OK;
}

int sacarDePila(t_pila *pp, t_info *pd){
    t_nodo *aux;
    if(*pp == NULL)
        return PILA_VACIA;
    
    aux = (*pp)->sig;
    *pd = aux->info;
    (*pp)->sig = aux->sig;

    if(aux == *pp)
        *pp = NULL;
    
    free(aux);
    
    return TODO_OK;
}

