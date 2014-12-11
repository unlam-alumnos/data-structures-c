#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define COLA_VACIA 1
#define COLA_LLENA 2

/*
 * COLA - IMPLEMENTACIÓN DINÁMICA
 */

//ESTRUCTURAS
typedef struct{
    int dato;
}t_info;

typedef struct s_nodo{
    t_info info;
    struct s_nodo * sig;
}t_nodo;

typedef struct{
    t_nodo * pri;
    t_nodo * ult;
}t_cola;

//FUNCIONES
void crearCola(t_cola * pCola);
void vaciarCola(t_cola * pCola);
int colaLlena(t_cola * pCola);
int ponerEnCola(t_cola * pCola, const t_info * pDato);
int colaVacia(const t_cola * pCola);
int verFrenteDeCola(const t_cola * pCola, t_info * pDato);
int sacarDeCola(t_cola * pCola, t_info * pDato);

int main(){

    t_cola cola;
    crearCola(&cola);

    t_info info;
    info.dato = 4;
    ponerEnCola(&cola,&info);

    printf("COLA LLENA: %s \n",colaLlena(&cola)?"SI":"NO");

    t_info ext;
    verFrenteDeCola(&cola,&ext);
    printf("TOPE DE COLA: %d \n",ext.dato);

    t_info ext2;
    sacarDeCola(&cola,&ext2);
    printf("EXTRAIDO DE COLA: %d \n",ext2.dato);

    vaciarCola(&cola);

    printf("COLA VACIA: %s \n",colaVacia(&cola)?"SI":"NO");

    return 0;

}

/**
 * Crea la cola
 */
void crearCola(t_cola * pCola){
    pCola->pri = pCola->ult = NULL;
}

/**
 * Vacía la cola
 */
void vaciarCola(t_cola * pCola){
    t_nodo * aux;
    while(pCola->pri){
        aux = pCola->pri;
        pCola->pri = aux->sig;
        free(aux);
    }
    pCola->ult = NULL;
}

/**
 * Cola llena?
 */
int colaLlena(t_cola * pCola){
    void * aux = malloc(sizeof(t_nodo));
    free(aux);
    return aux == NULL;
}

/**
 * Inserta un elemento en la cola
 */
int ponerEnCola(t_cola * pCola, const t_info * pDato){

    t_nodo * aux = (t_nodo*)malloc(sizeof(t_nodo));
    if(aux == NULL)
        return COLA_LLENA;
    aux->info = *pDato;
    aux->sig = NULL;
    if(pCola->pri == NULL){
        pCola->pri = aux;
    }else{
        pCola->ult->sig = aux;
    }
    pCola->ult = aux;
    return TODO_OK;


}

/**
 * Cola vacía?
 */
int colaVacia(const t_cola * pCola){
    return pCola->pri == NULL && pCola->ult == NULL;
}

/**
 * Frente de cola
 */
int verFrenteDeCola(const t_cola * pCola, t_info * pDato){
    if(pCola->pri == NULL)
        return COLA_VACIA;
    *pDato = pCola->pri->info;
    return TODO_OK;
}

/**
 * Sacar un elemento de la cola
 */
int sacarDeCola(t_cola * pCola, t_info * pDato){
    t_nodo * aux;
    if(pCola->pri == NULL)
        return COLA_VACIA;
    aux = pCola->pri;
    *pDato = aux->info;
    pCola->pri = aux->sig;
    if(pCola->pri == NULL)
        pCola->ult = NULL;
    free(aux);
    return TODO_OK;
}
