#include <stdio.h>
#include <stdlib.h>
struct nodo{
int info;
struct nodo *sig;
};
typedef struct nodo Tnodo;

Tnodo *crea_nodo(int d);
void inserta_inicio(Tnodo **cab, int d);
void imprimir(Tnodo *cab);

int main(){
    Tnodo *lista=NULL;
    int i,dato, n_dato;
    printf("Ingrese la cantidad de datos en la lista");
    scanf("%d", &n_dato);
    for (i=0; i<n_dato; i++){
        printf("Ingrese el nodo [%d]: ", i);
        scanf("%d", &dato);
        inserta_inicio(&lista, dato);
    }
  imprimir(lista);
}

Tnodo *crea_nodo(int d){
Tnodo *aux;
aux= (Tnodo*)(malloc(sizeof(Tnodo)));
if (aux!=NULL){
    aux->info=d;
    aux->sig=NULL;
    }
    return (aux);
}

void inserta_inicio(Tnodo **cab, int d){
Tnodo *aux=NULL;
aux=crea_nodo(d);

if(aux!=NULL){
    aux->sig=*cab;
    *cab=aux;
    }
}

void imprimir(Tnodo *cab){
if(cab!=NULL){
    printf("[%d] ", cab->info);
    imprimir(cab->sig);
    }
}
