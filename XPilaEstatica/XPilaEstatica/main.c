#include <stdio.h>
#include <stdlib.h>

/*
 * PILA - IMPLEMENTACIÓN ESTÁTICA
 */

#define TAM_PILA 10

#define TODO_OK 0;
#define PILA_VACIA 1;
#define PILA_LLENA 2;

//ESTRUCTURAS
typedef struct {
    int dato;
}t_info;

typedef struct{
    t_info pila[TAM_PILA];
    int tope;
}t_pila;


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
    pPila->tope = 0;
}

/**
 * Pila llena?
 */
int pilaLlena(const t_pila * pPila){
    return pPila->tope == TAM_PILA;
}

/**
 * Inserta un elemento en la pila
 */
int ponerEnPila(t_pila * pPila, const t_info * pDato){
    if(pPila->tope == TAM_PILA)
        return PILA_LLENA;
    pPila->pila[pPila->tope] = *pDato;
    pPila->tope++;
    return TODO_OK;
}

/**
 * Pila vacia?
 */
int pilaVacia(const t_pila * pPila){
    return pPila->tope == 0;
}

/**
 * Tope de pila
 */
int verTope(const t_pila * pPila, t_info * pDato){
    if(pPila->tope == 0)
        return PILA_VACIA;
    *pDato = pPila->pila[pPila->tope - 1];
    return TODO_OK;
}

/**
 * Sacar un elemento de la pila
 */
int sacarDePila(t_pila * pPila, t_info * pDato){
    if(pPila->tope == 0)
        return PILA_VACIA;
    *pDato = pPila->pila[pPila->tope - 1];
    pPila->tope--;
    return TODO_OK;
}

/**
 * Vaciar la pila
 */
void vaciarPila(t_pila * pPila){
    pPila->tope = 0;
}
