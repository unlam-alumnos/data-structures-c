#include <stdio.h>
#include <stdlib.h>

/*
 * COLA - IMPLEMENTACIÓN ESTÁTICA
 */

#define TAM_COLA 10

#define TODO_OK 0
#define COLA_VACIA 1
#define COLA_LLENA 2

//ESTRUCTURAS
typedef struct{
    int dato;
}t_info;

typedef struct{
    t_info info[TAM_COLA];
    int pri, ult;
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
    pCola->pri = 0;
    pCola->ult = -1;
}

/**
 * Vacía la cola
 */
void vaciarCola(t_cola * pCola){
    pCola->pri = 0;
    pCola->ult = -1;
}

/**
 * Cola llena?
 */
int colaLlena(t_cola * pCola){
    return ((pCola->pri == 0 && pCola->ult == TAM_COLA-1) || (pCola->ult == pCola->pri - 1 && pCola->ult != -1));
}

/**
 * Inserta un elemento en la cola
 */
int ponerEnCola(t_cola * pCola, const t_info * pDato){
    if((pCola->pri == 0 && pCola->ult == TAM_COLA-1) || (pCola->ult == pCola->pri - 1 && pCola->ult != -1))
        return COLA_LLENA;
    pCola->ult++;
    if(pCola->ult == TAM_COLA)
        pCola->ult = 0;
    pCola->info[pCola->ult] = *pDato;
    return TODO_OK;
}

/**
 * Cola vacia?
 */
int colaVacia(const t_cola * pCola){
    return pCola->ult == -1;
}

/**
 * Frente de cola
 */
int verFrenteDeCola(const t_cola * pCola, t_info * pDato){
    if(pCola->ult == -1)
        return COLA_VACIA;
    *pDato = pCola->info[pCola->pri];
    return TODO_OK;
}

/**
 * Sacar un elemento de la cola
 */
int sacarDeCola(t_cola * pCola, t_info * pDato){
    if(pCola->ult == -1)
        return COLA_VACIA;
    *pDato = pCola->info[pCola->pri];
    if(pCola->pri == pCola->ult){
        pCola->pri = 0;
        pCola->ult = -1;
    }else{
        pCola->pri++;
        if(pCola->pri == TAM_COLA)
            pCola->pri = 0;
    }
    return TODO_OK;
}

