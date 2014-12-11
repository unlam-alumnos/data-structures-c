#include <stdio.h>
#include <stdlib.h>

/*
 * PILA - IMPLEMENTACIÓN DINÁMICA
 */

#define TODO_OK 0;
#define PILA_VACIA 1;
#define PILA_LLENA 2;

//ESTRUCTURAS
typedef struct{
    int dato;
}t_info;

typedef struct s_nodo{
    t_info info;
    struct s_nodo *sig;
}t_nodo;

typedef t_nodo * t_pila;

//FUNCIONES
void crearPila(t_pila * pPila);
int pilaLlena(const t_pila * pPila);
int ponerEnPila(t_pila * pPila, const t_info * pDato);
int pilaVacia(const t_pila * pPila);
int verTope(const t_pila * pPila, t_info * pDato);
int sacarDePila(t_pila * pPila, t_info * pDato);
void vaciarPila(t_pila * pPila);

int main(){

    t_pila pila;
    crearPila(&pila);

    t_info info;
    info.dato = 4;
    ponerEnPila(&pila,&info);

    printf("PILA LLENA: %s \n",pilaLlena(&pila)?"SI":"NO");

    t_info ext;
    verTope(&pila,&ext);
    printf("TOPE DE PILA: %d \n",ext.dato);

    t_info ext2;
    sacarDePila(&pila,&ext2);
    printf("EXTRAIDO DE PILA: %d \n",ext2.dato);

    vaciarPila(&pila);

    printf("PILA VACIA: %s \n",pilaVacia(&pila)?"SI":"NO");

    return 0;

}

/**
 * Crea la pila
 */
void crearPila(t_pila * pPila){
    *pPila = NULL;
}

/**
 * Pila llena?
 */
int pilaLlena(const t_pila * pPila){
    t_nodo * aux = (t_nodo*)malloc(sizeof(t_nodo));
    free(aux);
    return aux == NULL;
}

/**
 * Inserta un elemento en la pila
 */
int ponerEnPila(t_pila * pPila, const t_info * pDato){
    t_nodo * aux = (t_nodo*)malloc(sizeof(t_nodo));
    if(aux == NULL)
        return PILA_LLENA;
    aux->info = *pDato;
    aux->sig  = *pPila;
    *pPila = aux;
    return TODO_OK;
}

/**
 * Pila vacia?
 */
int pilaVacia(const t_pila * pPila){
    return *pPila==NULL;
}

/**
 * Tope de pila
 */
int verTope(const t_pila * pPila, t_info * pDato){
    if(*pPila == NULL)
        return PILA_VACIA;
    *pDato = (*pPila)->info;
    return TODO_OK;
}

/**
 * Sacar un elemento de la pila
 */
int sacarDePila(t_pila * pPila, t_info * pDato){
    t_nodo *aux;
    if(*pPila == NULL)
        return 0;
    aux = *pPila;
    *pDato = aux->info;
    *pPila = aux->sig;
    free(aux);
    return 1;
}

/**
 * Vaciar la pila
 */
void vaciarPila(t_pila * pPila){
    t_nodo * aux;
    while(*pPila){
        aux = *pPila;
        *pPila = aux->sig;
        free(aux);
    }
}
