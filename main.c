#include <stdio.h>
#include <stdlib.h>

#define TODO_OK     0
#define DUPLICADO   1
#define SIN_MEMORIA 2
#define NO_EXISTE   3

typedef struct s_nodo{
    int info;
    struct s_nodo *pant ,*psig;
} t_nodo;

typedef t_nodo * t_lista;

int comparar(int * a, int * b);

int main(){

    t_lista pl;
    puts("CREANDO LISTA... \n");
    crear_lista(&pl);

    int pd = 4;
    printf("INSERTANDO %d ... \n",pd);
    insertar_en_orden(&pl,&pd,comparar);
    pd = 1;
    printf("INSERTANDO %d ... \n",pd);
    insertar_en_orden(&pl,&pd,comparar);
    pd = 2;
    printf("INSERTANDO %d ... \n",pd);
    insertar_en_orden(&pl,&pd,comparar);

    puts("LISTANDO... \n");
    listar(&pl);

    return 0;
}

//===== FUNCIONES =====//

void crear_lista(t_lista * pl);
int insertar_en_orden(t_lista * pl, const int *pd, int(*cmp)(int * a, int * b));
void listar(const t_lista * pl);
int eliminar_en_orden(t_lista * pl, int * pd, int(*cmp)(int * a, int * b));

int comparar(int * a, int * b){

    if(*a < *b){
        return -1;
    }else{
        if(*a > *b){
            return 1;
        }else{
            return 0;
        }
    }

}

void crear_lista(t_lista * pl){

    *pl = NULL;

}

// gonza tenia razon, hay que usar auxiliar ;)

int insertar_en_orden(t_lista * pl, const int *pd,int(*cmp)(int *, int *)){

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
            return DUPLICADO;
        }else if(comp > 0){
             ant = act->pant;
             sig = act;
        }else if(comp > 0){
             ant = act;
             sig = act->psig;
        }

    }

    nue = (t_nodo*) malloc(sizeof(t_nodo));
    if(nue == NULL)
        return SIN_MEMORIA;

    nue->info = *pd;
    nue->pant = ant;
    nue->psig = sig;

    if(sig != NULL)
       sig->pant = nue;

    if(ant != NULL)
        ant->psig = nue;

    // apunto al ultimo insertado
    *pl = nue;

    //sino al primero
    //if(nue->pant == NULL)
    //  *pl = nue;

    //sino al ultimo
    //if(nue->psig == NULL)
    //  *pl = nue;

    return TODO_OK;

}

void listar(const t_lista * pl){

    t_nodo * pn = *pl;

    while(pn->pant)
        pn = pn->pant;

    while(pn){

        if(pn->pant != NULL && pn->psig != NULL){
            printf("- %d |A: %d, S: %d\n",pn->info,pn->pant->info,pn->psig->info);
        }else{
            if(pn->pant == NULL && pn->psig != NULL){
                printf("- %d |A: N, S: %d\n",pn->info,pn->psig->info);
            }else{
                printf("- %d |A: %d, S: N\n",pn->info,pn->pant->info);
            }
        }
        pn = pn->psig;

    }

}

int eliminar_en_orden(t_lista * pl, int * pd, int(*cmp)(int * a, int * b)){

    t_nodo * pn;

    while(*pl && (cmp(&(*pl)->info, pd) < 0)){

        pl = &(*pl)->psig;

    }

    if(*pl && (cmp(&(*pl)->info, pd) > 0)){

        return NO_EXISTE;

    }

    pn = *pl;
    *pl = (*pl)->psig;

    if(*pl){ //SI EL SIGUIENTE EXISTE
        (*pl)->pant = pn->pant;
    }

    if(pn->pant != NULL){ //SI EL ANTERIOR EXISTE
        pn->pant->psig = *pl;
    }

    *pd = pn->info;
    free(pn);

    return TODO_OK;

}
