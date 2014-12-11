//
//  main.c
//  XColaCircular
//
//  Created by Cristian Miranda on 6/15/13.
//  Copyright (c) 2013 Cristian Miranda. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define COLA_VACIA 1
#define COLA_LLENA 2

typedef struct {
    int num;
}t_info;

typedef struct s_nodo{
    t_info info;
    struct s_nodo *sig;
}t_nodo, *t_cola;

//FUNCIONES DE LISTA CIRCULAR - IMPLEMENTACION EN COLA

void crearCola(t_cola *pc);
int colaVacia(const t_cola *pc);
int colaLlena(const t_cola *pc);
void vaciarCola(t_cola *pc);
int verFrenteDeCola(const t_cola *pc, t_info *pd);
int ponerEnCola(t_cola *pc, const t_info *pd);
int sacarDeCola(t_cola *pc, t_info *pd);

/**
 * Funcion para ver el estado de la cola
 */
void debug(const t_cola *pc){
    int fin = 0;
    t_nodo *ult = *pc;
    t_nodo *pri = (*pc)->sig;
    while(pri != ult || !fin){
        printf("%d | --> %d\n", pri->info.num, pri->sig->info.num);
        if(pri == ult){
            fin = 1;
        }else{
            pri = pri->sig;
        }
    }
}

int main(int argc, const char * argv[])
{

    t_cola cola;
    t_info info;
    
    crearCola(&cola);
    
    info.num = 1;
    ponerEnCola(&cola, &info);
    
    info.num = 2;
    ponerEnCola(&cola, &info);
    
    info.num = 3;
    ponerEnCola(&cola, &info);
    
    printf("\nCola vacia?: %s", colaVacia(&cola)==1?"SI":"NO");
    
    verFrenteDeCola(&cola, &info);
    printf("\nFrente de cola: %d\n\n", info.num);
    debug(&cola);
    
    //vaciarCola(&cola);
    
    puts("\nSaco de cola... 1\n");
    sacarDeCola(&cola,&info);
    debug(&cola);
    
    puts("\nSaco de cola... 2\n");
    sacarDeCola(&cola,&info);
    debug(&cola);
    
    puts("\nSaco de cola... 3\n");
    sacarDeCola(&cola,&info);
    printf("Cola vacia?: %s", colaVacia(&cola)==1?"SI":"NO");
    
    return TODO_OK;

}

void crearCola(t_cola *pc){
    *pc = NULL;
}

int colaVacia(const t_cola *pc){
    return *pc == NULL;
}

int colaLlena(const t_cola *pc){
    void *aux = malloc(sizeof(t_nodo));
    free(aux);
    return aux == NULL;
}

void vaciarCola(t_cola *pc){
    t_nodo *aux;
    while(*pc){
        aux = (*pc)->sig;
        (*pc)->sig = aux->sig;
        if(aux == *pc)
            *pc = NULL;
        free(aux);
    }
}

int verFrenteDeCola(const t_cola *pc, t_info *pd){
    if(*pc == NULL)
        return COLA_VACIA;
    
    *pd = (*pc)->sig->info;
    
    return TODO_OK;
}

int ponerEnCola(t_cola *pc, const t_info *pd){
    t_nodo *nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(nue == NULL)
        return COLA_LLENA;
    
    nue->info = *pd;
    if(*pc == NULL){
        nue->sig = nue;
    }else{
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
    }
    *pc = nue;
    
    return TODO_OK;
}

int sacarDeCola(t_cola *pc, t_info *pd){
    t_nodo *aux;
    if(*pc == NULL)
        return COLA_VACIA;
    
    aux = (*pc)->sig;
    *pd = aux->info;
    (*pc)->sig = aux->sig;
    
    if(aux == *pc)
        *pc = NULL;
    
    free(aux);
    
    return TODO_OK;
}
