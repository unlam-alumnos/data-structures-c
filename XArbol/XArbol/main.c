#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define ARBOL_LLENO 1
#define CLAVE_DUPLICADA 3
#define NO_ENCONTRADO 4
#define ENCONTRADO 5

typedef struct{
    int num;
}t_info;

typedef struct s_nodo{
    t_info info;
    struct s_nodo *izq, *der;
}t_nodo, *t_arbol;

int comparar(const t_info * a, const t_info * b);

void crearArbol(t_arbol *pa);
int arbolVacio(const t_arbol *pa);
int arbolLleno(const t_arbol *pa);
int vaciarArbol(t_arbol *pa);

int recorrerEnPreOrden(const t_arbol *pa);
int recorrerEnOrden(const t_arbol *pa);
int recorrerEnPostOrden(const t_arbol *pa);

void mostrar(const t_info *info);
int insertarEnArbol(t_arbol *pa, const t_info *pd, int (*cmp)(const t_info *, const t_info *));
int buscarEnArbol(const t_arbol *pa, t_info *pd, int (*cmp)(const t_info *, const t_info *));

int altura(const t_arbol *pa);

int esCompleto(const t_arbol *pa);
int determinarCompleto(const t_arbol *pa, int h);
int esBalanceado(const t_arbol *pa);
int determinarBalanceado(const t_arbol *pa, int h);
int esAVL(const t_arbol *pa);

int contarNodos(const t_arbol *pa);
int contarHojas(const t_arbol *pa);
int podarAAlturaYContar(t_arbol *pa, int h);

int main()
{
    printf("Arboles en C!\n");

    t_arbol a;
    crearArbol(&a);

    t_info d;
    d.num=100;
    insertarEnArbol(&a,&d, comparar);
    d.num=50;
    insertarEnArbol(&a,&d, comparar);
    d.num=500;
    insertarEnArbol(&a,&d, comparar);
    d.num=40;
    insertarEnArbol(&a,&d, comparar);
    d.num=60;
    insertarEnArbol(&a,&d, comparar);
    d.num=800;
    insertarEnArbol(&a,&d, comparar);
    d.num=30;
    insertarEnArbol(&a,&d, comparar);
    d.num=50;
    insertarEnArbol(&a,&d, comparar);
    d.num=600;
    insertarEnArbol(&a,&d, comparar);

    printf("\n - RECORRIDO EN PREORDEN: \n");
    recorrerEnPreOrden(&a);

    printf("\n \n - RECORRIDO EN ORDEN: \n");
    recorrerEnOrden(&a);

    printf("\n \n - RECORRIDO EN POSTORDEN: \n");
    recorrerEnPostOrden(&a);

    printf("\n \n ALTURA DEL ARBOL: %d \n", altura(&a));

    printf("\n CANTIDAD DE NODOS DEL ARBOL: %d \n \n",contarNodos(&a));

    printf("\n CANTIDAD DE HOJAS DEL ARBOL: %d \n \n",contarHojas(&a));

    return 0;
}

int comparar(const t_info * a, const t_info * b){
    if(a->num < b->num){
        return -1;
    }else{
        if(a->num > b->num){
            return 1;
        }else{
            return 0;
        }
    }
}

void crearArbol(t_arbol *pa){
    *pa = NULL;
}

int arbolVacio(const t_arbol *pa){
    return *pa == NULL;
}

int arbolLleno(const t_arbol *pa){
    void* aux = malloc(sizeof(t_nodo));
    free(aux);
    return aux == NULL;
}

int recorrerEnPreOrden(const t_arbol *pa){
    if(*pa){
        int n = 0;
        mostrar(&(*pa)->info);
        n += recorrerEnPreOrden(&(*pa)->izq) + 1;
        n += recorrerEnPreOrden(&(*pa)->der) + 1;
        return n + 1;
    }
    return 0;
}

int recorrerEnOrden(const t_arbol *pa){
    if(*pa){
        int n = recorrerEnOrden(&(*pa)->izq) + 1;
        mostrar(&(*pa)->info);
        n += recorrerEnOrden(&(*pa)->der) + 1;
        return n + 1;
    }
    return 0;
}

int recorrerEnPostOrden(const t_arbol *pa){
    if(*pa){
        int n = recorrerEnPostOrden(&(*pa)->izq) + 1;
        n += recorrerEnPostOrden(&(*pa)->der) + 1;
        mostrar(&(*pa)->info);
        return n + 1;
    }
    return 0;
}

void mostrar(const t_info *info){
    printf("- %d -", info->num);
}

int insertarEnArbol(t_arbol *pa, const t_info *pd, int (*cmp)(const t_info *, const t_info *)){

    if(!*pa){
        t_nodo *nue = (t_nodo*) malloc(sizeof(t_nodo));
        if(nue == NULL)
            return ARBOL_LLENO;

        nue->izq = NULL;
        nue->der = NULL;
        nue->info = *pd;

        *pa = nue;

        return TODO_OK;
    }

    if(cmp(&(*pa)->info, pd) > 0){
        return insertarEnArbol(&(*pa)->izq, pd, cmp);
    }else if(cmp(&(*pa)->info, pd) < 0){
        return insertarEnArbol(&(*pa)->der, pd, cmp);
    }else{
        return CLAVE_DUPLICADA;
    }

}

int buscarEnArbol(const t_arbol *pa, t_info *pd, int (*cmp)(const t_info *, const t_info *)){
    if(!*pa)
        return NO_ENCONTRADO;

    if(cmp(&(*pa)->info, pd) > 0){
        return buscarEnArbol(&(*pa)->izq, pd, cmp);
    }else if(cmp(&(*pa)->info, pd) < 0){
        return buscarEnArbol(&(*pa)->der, pd, cmp);
    }else{
        *pd = (*pa)->info;
        return ENCONTRADO;
    }

}

int altura(const t_arbol *pa){
    if(*pa){
        int hi = altura(&(*pa)->izq);
        int hd = altura(&(*pa)->der);
        return hi > hd ? hi+1 : hd+1;
    }
    return 0;
}

int esCompleto(const t_arbol *pa){
    int h = altura(pa);
    return determinarCompleto(pa, h);
}

int determinarCompleto(const t_arbol *pa, int h){
    if(*pa){
        return determinarCompleto(&(*pa)->izq, h-1) && determinarCompleto(&(*pa)->der, h-1);
    }
    return h==0;
}

int esBalanceado(const t_arbol *pa){
    int h = altura(pa);
    return determinarBalanceado(pa, h);
}

int determinarBalanceado(const t_arbol *pa, int h){
    if(*pa){
        return determinarBalanceado(&(*pa)->izq, h-1) && determinarBalanceado(&(*pa)->der, h-1);
    }
    return h<=1;
}

int esAVL(const t_arbol *pa){
    if(*pa){
        if(abs(altura(&(*pa)->izq)) - altura(&(*pa)->der) > 1)
            return 0; //No es AVL
        return esAVL(&(*pa)->izq) && esAVL(&(*pa)->der);
    }
    return 1; //Si no hay nodo se dice que es AVL
}

int contarNodos(const t_arbol *pa){
    if(*pa)
        return contarNodos(&(*pa)->izq) + contarNodos(&(*pa)->der) + 1;
    return 0;
}

int contarHojas(const t_arbol *pa){
    if(*pa){
        if((*pa)->izq == NULL && (*pa)->der == NULL)
            return 1;
        return contarHojas(&(*pa)->izq) + contarHojas(&(*pa)->der);
    }
    return 0;
}

int vaciarArbol(t_arbol *pa){
    if(*pa){
        int n = vaciarArbol(&(*pa)->izq) + vaciarArbol(&(*pa)->der);
        free(*pa);
        *pa = NULL;
        return n + 1;
    }
    return 0;
}

int podarAAlturaYContar(t_arbol *pa, int h){
    if(*pa){
        if(h==0)
            return vaciarArbol(pa);
        return podarAAlturaYContar(&(*pa)->izq, h-1) + podarAAlturaYContar(&(*pa)->der, h-1);
    }
    return 0;
}
