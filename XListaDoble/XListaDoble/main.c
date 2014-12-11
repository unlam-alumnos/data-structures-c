#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define LISTA_VACIA 1
#define LISTA_LLENA 2
#define CLAVE_DUPLICADA 3
#define NO_EXISTE   4

typedef struct{
    int num;
}t_info;

typedef struct s_nodo{
    t_info info;
    struct s_nodo *pant ,*psig;
} t_nodo;

typedef t_nodo * t_lista;

void crear_lista(t_lista * pl);
int listaLlena(const t_lista * pl);
int listaVacia(const t_lista * pl);
void vaciarLista(t_lista * pl);
void listar(const t_lista * pl);

int insertarAdelante(t_lista * pl, const t_info * pd);
int insertarAlFinal(t_lista * pl, const t_info * pd);

int insertarEnOrden(t_lista * pl, const t_info *pd, int(*cmp)(const t_info * a, const t_info * b));
int eliminarDeListaOrdenada(t_lista * pl, t_info * pd, int(*cmp)(const t_info * a, const t_info * b));
int eliminarDeListaNoOrdenada(t_lista * pl, t_info * pd, int(*cmp)(const t_info * a, const t_info * b));

int ordenar(t_lista *pl, int(*cmp)(const t_info *, const t_info *));

// FUNCIONES DE t_info
int comparar(const t_info * a, const t_info * b);
void acumular(t_info *, const t_info *);

int main(){

    t_lista pl;
    t_info pd;

    puts("CREANDO LISTA... \n");
    crear_lista(&pl);

    pd.num = 4;
    printf("INSERTANDO %d ... \n",pd.num);
    //insertarEnOrden(&pl, &pd, comparar);
    insertarAdelante(&pl, &pd);
    //insertarAlFinal(&pl, &pd);

    pd.num = 1;
    printf("INSERTANDO %d ... \n",pd.num);
    //insertarEnOrden(&pl, &pd, comparar);
    //insertarAdelante(&pl, &pd);
    insertarAlFinal(&pl, &pd);

    pd.num = 2;
    printf("INSERTANDO %d ... \n",pd.num);
    //insertarEnOrden(&pl, &pd, comparar);
    insertarAdelante(&pl, &pd);
    //insertarAlFinal(&pl, &pd);

    printf("\nLISTA VACIA?: %s\n", listaVacia(&pl)==1?"SI":"NO");

    puts("LISTANDO... \n");
    listar(&pl);

    ordenar(&pl, comparar);

    puts("LISTANDO... \n");
    listar(&pl);

    puts("\nELIMINANDO EL 4... \n");
    pd.num = 4;
    eliminarDeListaNoOrdenada(&pl, &pd, comparar);

    puts("LISTANDO... \n");
    listar(&pl);

    return 0;
}


void crear_lista(t_lista * pl){
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

void vaciarLista(t_lista *pl){

    t_nodo *aux;
    t_nodo *act = *pl;

    while(act && act->pant)
        act = act->pant;

    while(act){
        aux = act;
        act = act->psig;
        free(aux);
    }

    *pl = NULL;

}

void listar(const t_lista * pl){

    t_nodo *act = *pl;

    while(act && act->pant)
        act = act->pant;

    while(act){

        if(act->pant != NULL && act->psig != NULL){
            printf("- %d |A: %d, S: %d\n", act->info.num, act->pant->info.num, act->psig->info.num);
        }else if(act->pant == NULL && act->psig != NULL){
                printf("- %d |A: N, S: %d\n", act->info.num, act->psig->info.num);
        }else if(act->pant != NULL && act->psig == NULL){
                printf("- %d |A: %d, S: N\n", act->info.num, act->pant->info.num);
        }else{
            printf("- %d |A: N, S: N\n", act->info.num);
        }

        act = act->psig;

    }

}

int insertarAdelante(t_lista * pl, const t_info * pd){
    t_nodo *act = *pl;

    t_nodo *nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(nue == NULL)
        return LISTA_LLENA;

    while(act && act->pant)
        act = act->pant;

    nue->info = *pd;
    nue->pant = NULL;
    nue->psig = act;

    if(act != NULL)
        act->pant = nue;

    // Apunto al ultimo insertado
    *pl = nue;

    // Sino al primero
    //if(nue->pant == NULL)
    //  *pl = nue;

    // Sino al ultimo
    //if(nue->psig == NULL)
    //  *pl = nue;

    return TODO_OK;
}

int insertarAlFinal(t_lista * pl, const t_info * pd){

    t_nodo *act = *pl;
    t_nodo *ant = NULL;

    while(act){
        ant = act;
        act = act->psig;
    }

    act = (t_nodo*)malloc(sizeof(t_nodo));
    if(act == NULL)
        return LISTA_LLENA;

    act->info = *pd;
    act->pant = ant;
    act->psig = NULL;

    if(ant != NULL)
        ant->psig = act;

    // Apunto al ultimo insertado
    *pl = act;

    // Sino al primero
    //if(act->pant == NULL)
    //  *pl = act;

    // Sino al ultimo
    //if(act->psig == NULL)
    //  *pl = act;

    return TODO_OK;

}

int insertarEnOrden(t_lista * pl, const t_info *pd, int(*cmp)(const t_info * a, const t_info * b)){

    t_nodo * act = *pl;
    t_nodo * ant = NULL;
    t_nodo * sig = NULL;
    t_nodo * nue;

    int comp;

    if(act){

        // retrocede con act
        while(act->pant && cmp(&act->info, pd) > 0)
            act = act->pant;

        // avanza con act
        while(act->psig && cmp(&act->info, pd) < 0)
            act = act->psig;

        comp = cmp(&act->info, pd);

        if(comp == 0){
            return CLAVE_DUPLICADA;
        }else if(comp < 0){
            ant = act;
            sig = act->psig;
        }else if(comp > 0){
            ant = act->pant;
            sig = act;
        }

    }

    nue = (t_nodo*) malloc(sizeof(t_nodo));
    if(nue == NULL)
        return LISTA_LLENA;

    nue->info = *pd;
    nue->pant = ant;
    nue->psig = sig;

    if(sig != NULL)
       sig->pant = nue;

    if(ant != NULL)
        ant->psig = nue;

    // Apunto al ultimo insertado
    *pl = nue;

    // Sino al primero
    //if(nue->pant == NULL)
    //  *pl = nue;

    // Sino al ultimo
    //if(nue->psig == NULL)
    //  *pl = nue;

    return TODO_OK;

}

int eliminarDeListaOrdenada(t_lista * pl, t_info *pd, int(*cmp)(const t_info * a, const t_info * b)){

    t_nodo *aux;
    t_nodo *act = *pl;

    if(act == NULL)
        return LISTA_VACIA;

    while(act && act->pant)
        act = act->pant;

    while(act && (cmp(&act->info, pd) < 0))
        act = act->psig;

    if(act && (cmp(&act->info, pd) == 0)){

        aux = act;
        *pd = aux->info;

        //Si existe el siguiente, actualizo su "pant"
        if(act->psig != NULL)
            act->psig->pant = act->pant;

        //Si existe el anterior, actualizo su "psig"
        if(act->pant != NULL)
            act->pant->psig = act->psig;

        if(act->psig)
            act = act->psig;
        else
            act = act->pant;

        free(aux);

        *pl = act;

        return TODO_OK;
    }

    return NO_EXISTE;
}

int eliminarDeListaNoOrdenada(t_lista * pl, t_info *pd, int(*cmp)(const t_info * a, const t_info * b)){

    t_nodo *aux;
    t_nodo *act = *pl;

    if(act == NULL)
        return LISTA_VACIA;

    while(act && act->pant)
        act = act->pant;

    while(act && (cmp(&act->info, pd) != 0))
        act = act->psig;

    if(act && (cmp(&act->info, pd) == 0)){

        aux = act;
        *pd = aux->info;

        //Si existe el siguiente, actualizo su "pant"
        if(act->psig != NULL)
            act->psig->pant = act->pant;

        //Si existe el anterior, actualizo su "psig"
        if(act->pant != NULL)
            act->pant->psig = act->psig;

        if(act->psig)
            act = act->psig;
        else
            act = act->pant;

        free(aux);

        *pl = act;

        return TODO_OK;

    }

    return NO_EXISTE;

}

int ordenar(t_lista *pl, int (*cmp)(const t_info *, const t_info *)){

    t_nodo *a, *b, *q, *act = *pl;
    int marca = 1;

    if(!act)
        return LISTA_VACIA;

    while(act && act->pant)
        act = act->pant;

    while(marca){

        //Vuelvo al principio de la lista
        q = act;
        marca = 0;

        while(q && q->psig){

            if(cmp(&q->info, &q->psig->info) > 0){

                //Hay que hacer una nueva pasada
                marca = 1;

                //Intercambio "A" con "B"
                a = q;
                b = q->psig;

                a->psig = b->psig;
                b->pant = a->pant;

                if(a->pant != NULL)
                    a->pant->psig = b;

                if(b->psig != NULL)
                    b->psig->pant = a;

                b->psig = a;
                a->pant = b;

            }

            //Avanzo
            q = q->psig;

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
