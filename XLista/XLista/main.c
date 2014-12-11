#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define LISTA_VACIA 1
#define LISTA_LLENA 2
#define CLAVE_DUPLICADA 3

typedef struct{
    int num;
}t_info;

typedef struct s_nodo{
    t_info info;
    struct s_nodo *sig;
}t_nodo, *t_lista;

// FUNCIONES DE LISTA
void crearLista(t_lista * pl);
int listaLlena(const t_lista * pl);
int listaVacia(const t_lista * pl);
void vaciarLista(t_lista * pl);
void mostrarLista(const t_lista *pl, void(*mostrar)(const t_info *));

int insertarAdelante(t_lista * pl, const t_info * pd);
int insertarAlFinal(t_lista * pl, const t_info * pd);
int insertarAlFinalSinDuplicados(t_lista * pl, const t_info * pd, int(*cmp)(const t_info *, const t_info *));
int insertarEnOrden(t_lista *pl, const t_info *pd, int(*cmp)(const t_info *, const t_info *));

int ordenar(t_lista *pl, int(*cmp)(const t_info *, const t_info *));

int buscarEnListaOrdenada(t_lista *pl, t_info *pd, int (*cmp)(const t_info *, const t_info *), int eliminar);
int buscarEnListaNoOrdenada(t_lista *pl, t_info *pd, int (*cmp)(const t_info *, const t_info *), int eliminar);

int eliminarDuplicadosListaOrdenada(t_lista *pl, int (*cmp)(const t_info *, const t_info *), int eliminarTodos);
int eliminarDuplicadosListaNoOrdenada(t_lista *pl, int (*cmp)(const t_info *, const t_info *), int eliminarTodos);


// FUNCIONES DE t_info
void mostrar(const t_info *);
int comparar(const t_info *, const t_info *);
void acumular(t_info *, const t_info *);

int main(){

    t_lista pl;
    t_info pd;
    
    printf("Lista simplemente enlazada.\n");
    puts("-----------------------\n");

    puts("Creo la lista...");
    crearLista(&pl);
    
    puts("Carga inicial...\n");
    for(int i = 0;i <= 10; i++){
        pd.num = rand() % 20;
        insertarEnOrden(&pl, &pd, comparar);
    }
    
    mostrarLista(&pl, mostrar);

    puts("\n\nOrdeno...");
    ordenar(&pl, comparar);
    
    puts("Muestro...\n");
    mostrarLista(&pl, mostrar);
    
    puts("\n\nInserto un par de duplicados...");
    for(int i=0; i < 3; i++){
        pd.num = i;
        insertarAdelante(&pl, &pd);
        insertarAlFinal(&pl, &pd);
    }
    
    puts("Muestro...\n");
    mostrarLista(&pl, mostrar);
    
    puts("\n\nBusco y elimino el '12'...");
    pd.num = 12;
    buscarEnListaNoOrdenada(&pl, &pd, comparar, 1);
    
    puts("Muestro...\n");
    mostrarLista(&pl, mostrar);
    
    puts("\n\nOrdeno...");
    ordenar(&pl, comparar);
    
    puts("Muestro...\n");
    mostrarLista(&pl, mostrar);
    
    puts("\n\nElimino duplicados...");
    eliminarDuplicadosListaOrdenada(&pl, comparar, 1);
    
    puts("Muestro...\n");
    mostrarLista(&pl, mostrar);
    
    puts("\n\nInserto el '9' en orden...");
    pd.num = 9;
    insertarEnOrden(&pl, &pd, comparar);
    
    puts("Muestro...\n");
    mostrarLista(&pl, mostrar);
    
    puts("\n\nBusco y elimino el '9'...");
    buscarEnListaOrdenada(&pl, &pd, comparar, 1);
    
    puts("Muestro...\n");
    mostrarLista(&pl, mostrar);
    
    return TODO_OK;
}

/*
 * FUNCIONES DE LISTA
 */

void crearLista(t_lista * pl){
    *pl = NULL;
}

int listaLlena(const t_lista * pl){
    void *nue = malloc(sizeof(t_nodo));
    free(nue);
    return nue == NULL;
}

int listaVacia(const t_lista * pl){
    return *pl == NULL;
}

void vaciarLista(t_lista * pl){
    if(*pl){
        vaciarLista(&(*pl)->sig);
        free(*pl);
        *pl = NULL;
    }
}

void mostrarLista(const t_lista *pl, void(*mostrar)(const t_info *)){
    while(*pl){
        mostrar(&(*pl)->info);
        pl = &(*pl)->sig;
    }
}

int insertarAdelante(t_lista * pl, const t_info * pd){
    t_nodo *nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(nue == NULL)
        return LISTA_LLENA;

    nue->info = *pd;
    nue->sig = *pl;

    *pl = nue;

    return TODO_OK;
}

int insertarAlFinal(t_lista * pl, const t_info * pd){

    while(*pl)
        pl = &(*pl)->sig;

    *pl = (t_nodo*)malloc(sizeof(t_nodo));
    if(*pl == NULL)
        return LISTA_LLENA;

    (*pl)->info = *pd;
    (*pl)->sig = NULL;

    return TODO_OK;

}

int insertarAlFinalSinDuplicados(t_lista * pl, const t_info * pd, int(*cmp)(const t_info *, const t_info *)){
    while(*pl && cmp(&(*pl)->info, pd))
        pl = &(*pl)->sig;
    
    if(*pl)
        return CLAVE_DUPLICADA;
    
    *pl = (t_nodo*)malloc(sizeof(t_nodo));
    if(*pl == NULL)
        return LISTA_LLENA;
    
    (*pl)->info = *pd;
    (*pl)->sig = NULL;
    
    return TODO_OK;
}

int insertarEnOrden(t_lista *pl, const t_info *pd, int(*cmp)(const t_info *, const t_info *)){
    t_nodo * nue;

    while(*pl && cmp(&(*pl)->info, pd) < 0)
        pl = &(*pl)->sig;
    
    if(*pl && cmp(&(*pl)->info, pd) == 0){
        acumular(&(*pl)->info, pd);
        return CLAVE_DUPLICADA;
    }
    
    nue = (t_nodo*) malloc(sizeof(t_nodo));
    nue->info = *pd;
    nue->sig = *pl;
    
    *pl = nue;
    
    return TODO_OK;
}

int ordenar(t_lista *pl, int (*cmp)(const t_info *, const t_info *)){
    
    t_nodo *aux, **q;
    int marca = 1;
    
    if(!*pl)
        return LISTA_VACIA;
    
    while(marca){
        
        //Vuelvo al principio de la lista
        q = pl;
        marca = 0;
        
        while(*q && (*q)->sig){
            
            if(cmp(&(*q)->info, &(*q)->sig->info) > 0){
            
                //Hay que hacer una nueva pasada
                marca = 1;
            
                //Intercambio
                aux = *q;
                *q = aux->sig;
                aux->sig = (*q)->sig;
                (*q)->sig = aux;
            
            }
            
            //Avanzo
            q = &(*q)->sig;
            
        }
        
    }
    
    return TODO_OK;
    
}

int buscarEnListaOrdenada(t_lista *pl, t_info *pd, int (*cmp)(const t_info *, const t_info *), int eliminar){
    
    t_nodo * aux;
    
    while(*pl && cmp(&(*pl)->info, pd) < 0)
        pl = &(*pl)->sig;
    
    if(*pl && cmp(&(*pl)->info, pd) == 0){
        
        *pd = (*pl)->info;
        
        if(eliminar){
            aux = *pl;
            *pl = aux->sig;
            free(aux);
        }
        
    }
        
    return TODO_OK;
    
}

int buscarEnListaNoOrdenada(t_lista *pl, t_info *pd, int (*cmp)(const t_info *, const t_info *), int eliminar){
    
    t_nodo * aux;
    
    while(*pl && cmp(&(*pl)->info, pd) != 0)
        pl = &(*pl)->sig;
    
    if(*pl && cmp(&(*pl)->info, pd) == 0){
        
        *pd = (*pl)->info;
        
        if(eliminar){
            aux = *pl;
            *pl = aux->sig;
            free(aux);
        }
        
    }
    
    return TODO_OK;
    
}

// 1 - 2 - 2 - 2 - 3 - 3 - 4 

int eliminarDuplicadosListaOrdenada(t_lista *pl, int (*cmp)(const t_info *, const t_info *), int eliminarTodos){
    t_nodo * aux;
    t_lista * q = pl;
    int marca = 1;
    
    if(!*pl)
        return LISTA_VACIA;
        
    while((*q)->sig){
        
        marca = 0;
        
        while(cmp(&(*q)->info, &(*q)->sig->info) == 0){
            marca = 1;
            aux = (*q)->sig;
            (*q)->sig = aux->sig;
            free(aux);
        }
        
        if(eliminarTodos && marca){
            aux = *q;
            *q = aux->sig;
            free(aux);
        }else{
            q = &(*q)->sig;
        }
            
    }
    
    return TODO_OK;
}

// 5 - 3 - 2 - 5 - 3 - 1

int eliminarDuplicadosListaNoOrdenada(t_lista *pl, int (*cmp)(const t_info *, const t_info *), int eliminarTodos){
    t_nodo * aux;
    t_lista * q = pl, *pSig;
    int marca = 1;
    
    if(!*pl)
        return LISTA_VACIA;
    
    while(*q){
        
        marca = 0;
        pSig = &(*q)->sig;
        
        while(*pSig){
            
            if(cmp(&(*q)->info, &(*pSig)->info) == 0){
                marca = 1;
                aux = *pSig;
                *pSig = aux->sig;
                free(aux);
            }else{
                pSig = &(*pSig)->sig;
            }
            
        }
        
        if(eliminarTodos && marca){
            aux = *q;
            *q = aux->sig;
            free(aux);
        }else{
            q = &(*q)->sig;
        }
        
    }
    
    return TODO_OK;
}


/*
 * FUNCIONES DE t_info
 */

void mostrar(const t_info * pd){
    printf("-> %d -", pd->num);
}

int comparar(const t_info * p1, const t_info * p2){
    return p1->num - p2->num;
}

void acumular(t_info * p1, const t_info * p2){
    p1->num += p2->num;
}