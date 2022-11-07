#include <stdio.h>
#include <stdlib.h>

typedef struct nod{
    int info;
    struct nod *izq, *der;

}TnodoD;

typedef struct {
    TnodoD *inicio, *fin;
}Tcab;

void inserta_inicio(Tcab *cab, int dato);
void inserta_final(Tcab *cab, int dato);
void Inserta_ordD(Tcab *c, int dato);

void elimina_inicio(Tcab *c);
void elimina_fin(Tcab *c);
void elimina_nodo(Tcab *cab, TnodoD *nodo);
void elimina_x(Tcab *cab, int x);
void elimina_pos(Tcab *cab, int p);

TnodoD *busca_dato(Tcab *cab, int x);
TnodoD *busca_pos(Tcab *cab, int p);

void imprime(Tcab *c);

int main(){
    Tcab cab;
    cab.inicio=NULL;
    cab.fin=NULL;
    int i;
    int cant_datos, tipo_insert, tipo_elim, dato;
    printf("ingrese la cantidad de datos");
    scanf("%d", &cant_datos);

    printf("ingrese tipo de insersion: 1.inicio, 2.final, 3.ordenado ");
    scanf("%d", &tipo_insert);

    for ( i = 0; i < cant_datos; ++i) {
        switch (tipo_insert) {
            case 1:
                printf("Dato[%d]:",i);
                scanf("%d", &dato);
                inserta_inicio(&cab, dato);
                break;
            case 2:
                printf("Dato[%d]:",i);
                scanf("%d", &dato);
                inserta_final(&cab, dato);
                break;
            case 3:
                printf("Dato[%d]:",i);
                scanf("%d", &dato);
                Inserta_ordD(&cab, dato);
                break;
        }
    }
        imprime(&cab);

    int d;
    printf("\ningrese tipo de eliminacion: 1.inicio, 2.final, 3. elimina x");
    scanf("%d", &tipo_elim);

        switch (tipo_elim) {
            case 1:
                elimina_inicio(&cab);
                break;
            case 2:
                elimina_fin(&cab);
                break;
            case 3:
                printf("Dato a eliminar:");
                scanf("%d", &d);
                elimina_x(&cab, d);
                break;
        }
    imprime(&cab);
}

//crea nodo
void Crea_nodo(TnodoD **nuevo, int dato){
    *nuevo= (TnodoD*)malloc(sizeof (TnodoD));
    if(*nuevo !=NULL){
        (*nuevo)->info=dato;
        (*nuevo)->izq=NULL;
        (*nuevo)->der=NULL;
    }
}

//inserta inicio
void inserta_inicio(Tcab *cab, int dato){
    TnodoD *nuevo;
    Crea_nodo(&nuevo, dato);
    if(nuevo){
        if (cab->inicio == NULL && cab->fin==NULL){
            cab->inicio=nuevo;
            cab->fin=nuevo;
        }else{
            nuevo->der=cab->inicio;
            cab->inicio->izq=nuevo;
        }
        cab->inicio=nuevo;
    }
}

// inserta final
void inserta_final(Tcab *cab, int dato){
    TnodoD *nuevo;
    Crea_nodo(&nuevo, dato);
    if(nuevo){
        if (cab->inicio ==NULL&& cab->fin==NULL){
            cab->inicio=nuevo;
            cab->fin=nuevo;
        }else{
            nuevo->izq=cab->fin;
            cab->fin->der=nuevo;
        }
        cab->fin=nuevo;
    }
}

//ordenado
void Inserta_ordD(Tcab *c, int dato){
    if( c->inicio==NULL|| c->inicio->info > dato){
        inserta_inicio(c, dato);
    }
    else if(c->inicio->der==NULL){
        inserta_final(c,dato);
    }else{
        Inserta_ordD(c->inicio->der, dato);
    }
}
//eliminar inicio
void elimina_inicio(Tcab *c){
    if(c->inicio !=NULL && c->inicio!=c->fin){
        c->inicio=c->inicio->der;
        free(c->inicio->izq);
        c->inicio->izq=NULL;
    }
    else{
        if(c->inicio==c->fin)
        {
         free(c->inicio);
         c->inicio=c->fin=NULL;
        }
    }
}
//eliminar final
void elimina_fin(Tcab *c){
    if(c->fin !=NULL && c->inicio!=c->fin){
        c->fin=c->fin->izq;
        free(c->fin->der);
        c->fin->der=NULL;
        printf("entro");
    }else{
        if(c->inicio==c->fin)
        {
         free(c->fin);
         c->inicio=c->fin=NULL;
        }
    }
}

// eliminar (por dato,por posicion)
//elimina cualquiera
void elimina_nodo(Tcab *cab, TnodoD *nodo){
    if(nodo != cab->inicio && nodo!=cab->fin){
        nodo->izq->der= nodo->der;
        nodo->der->izq=nodo->izq;
        free(nodo);
    }
}
void elimina_x(Tcab *cab, int x){
    TnodoD *aux=busca_dato(cab, x);
    if (aux==cab->inicio) {
        elimina_inicio(cab);
    }else if(aux==cab->fin) {
        elimina_fin(cab);
    }else {
        elimina_nodo(cab, aux);
        }
}

void elimina_pos(Tcab *cab, int p){
    TnodoD *aux=busca_pos(cab, p);
    if (aux==cab->inicio) {
        elimina_inicio(cab);
    }else if(aux==cab->fin)
        elimina_fin(cab);
    else {
        elimina_nodo(cab, aux);
    }
}

//impresion
void imprime(Tcab *c){
    TnodoD *aux=c->inicio;
    while (aux!=NULL){
        printf("%d", aux->info);
        aux=aux->der;
    }
}

//busquedas
TnodoD *busca_dato(Tcab *cab, int x){
    TnodoD *aux=cab->inicio;
    while (aux!=NULL){
        if (aux->info==x){
            break;
        }
        aux=aux->der;
    }
    return aux;
}
TnodoD *busca_pos(Tcab *cab, int p){
    TnodoD *aux=cab->inicio;
    int i;
    for ( i = 0; i != p && aux!=NULL; ++i) {
        aux=aux->der;
    }
    return aux;
}
