#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodoArb{
    int info, FE; //FE factor de equilibrio
    struct nodoArb *izq;
    struct nodoArb *der;

}TNodoArb;

void crea_nodo(TNodoArb **arb, int info);
int insert_arbol(TNodoArb**r, int info);
TNodoArb *elimina_nodo(TNodoArb **r, int info);
void preorden(TNodoArb *a);
void posorden(TNodoArb *a);
void inorden(TNodoArb *a);
TNodoArb *hijomenor(TNodoArb **raiz);
TNodoArb *hijomayor(TNodoArb **raiz);
int insercionBalanceado(TNodoArb **r, int info, bool indicador);
int RotacionesDer(TNodoArb **r);
int RotacionesIzq(TNodoArb **r);
TNodoArb *eliminaBalanceado(TNodoArb **r, int info, bool indicador);
int Elimina_RotaIzq(TNodoArb **nodo, bool indicador);
int Elimina_RotaDer(TNodoArb **nodo, bool indicador);

int main(){
    TNodoArb *arbol=NULL;
    int nodo, info, opc;
    //bool indicador=false;

    printf("ingrese una opcion de insersion: 1.arboles BB, 2. arboles AVL\n");
    scanf("%d", &opc);

    printf("ingrese la cantidad de nodos\n");
    scanf("%d", &nodo);

    for (int i = 0; i < nodo; ++i) {
        switch (opc) {
            case 1:
                printf("ingrese Dato[%d]", i);
                scanf("%d", &info);
                insert_arbol(&arbol, info);
                break;
            case 2:
                printf("ingrese Dato[%d]", i);
                scanf("%d", &info);
                insercionBalanceado(&arbol, info, false);
                break;
        }
    }

    printf("ingrese una opcion de eliminacion: 1.arboles BB, 2. arboles AVL\n");
    scanf("%d", &opc);

    printf("nodo a eliminar\n");
    scanf("%d", &info);

    switch (opc) {
        case 1:
            elimina_nodo(&arbol, info);
            break;
        case 2:
            eliminaBalanceado(&arbol,info, false);
            break;
    }

    printf("ingrese una opcion de impresion: 1.Preorden, 2. Posorden, 3. Inorden\n");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("Preorden\n");
            preorden(arbol);
            break;
        case 2:
            printf("Posorden\n");
            posorden(arbol);
            break;
        case 3:
            printf("Inorden\n");
            inorden(arbol);
            break;

    }

}

void crea_nodo(TNodoArb **arb, int info){
    TNodoArb *nuevo;

    nuevo=(TNodoArb*) malloc(sizeof (TNodoArb));
    *arb=nuevo;
    nuevo->info=info;
    nuevo->izq=NULL;
    nuevo->der=NULL;
    nuevo->FE=0;

}

int insert_arbol(TNodoArb **r, int info){
    TNodoArb *nuevo;
    int bandera=0;

    if(*r==NULL){
        crea_nodo(&nuevo, info);
        *r=nuevo;
        bandera=1;
    }else if(((*r)->info) == info ){
        printf("El dato ya existe");

    }else if(info<(*r)->info){
        bandera= insert_arbol(&((*r)->izq), info);
    }else{
        bandera= insert_arbol(&((*r)->der), info);
    }
    return bandera;
}


TNodoArb *elimina_nodo(TNodoArb **r, int info){
    TNodoArb *aux, *aux2;
    int temporal;

    if(*r!=NULL){
        if(info<(*r)->info){
            aux= elimina_nodo(&((*r)->izq), info);
        }else if(info >(*r)->info){
            aux= elimina_nodo(&((*r)->der), info);
        }else{
            aux=*r;
            if((*r)->izq ==NULL){
                *r=aux->der;
            }else if((*r)->der ==NULL){
                *r=aux->izq;
            }else{
               aux2=hijomenor(&(aux->izq));
               temporal=aux->info;
               aux->info=aux2->info;
               aux2->info=temporal;
               aux=aux2;
            }
        }
    }else{
        aux=NULL;
        printf("no se encontro");
    }
    return aux;
}
void preorden(TNodoArb *a){
    if(a!=NULL){
        printf("%d", a->info);
        preorden(a->izq);
        preorden(a->der);
    }
}
void posorden(TNodoArb *a){
    if(a){
        posorden(a->izq);
        posorden(a->der);
        printf("%d", a->info);
    }
}
void inorden(TNodoArb *a){
    if(a){
        inorden(a->izq);
        printf("%d",a->info);
        inorden(a->der);
    }
}
//mas chico de sus mayores
TNodoArb *hijomenor(TNodoArb **raiz){
    TNodoArb *aux, *anterior;

    aux=*raiz;
    while (aux->izq!=NULL){
        anterior=aux;
        aux=aux->izq;
    }
    if(anterior){
        anterior->izq=aux->der;
       // aux->der=NULL;
    }else
        *raiz=aux->der;
    aux->der=NULL;

    return (aux);
}

//mayor de sus menores
TNodoArb *hijomayor(TNodoArb **raiz){
    TNodoArb *aux, *anterior=NULL;

    aux=*raiz;
    while (aux->der!=NULL){
        anterior=aux;
        aux=aux->der;
    }
    if(anterior){
        anterior->der=aux->izq;
        // aux->der=NULL;
    }else
        *raiz=aux->izq;
    aux->izq=NULL;

    return (aux);
}
int insercionBalanceado(TNodoArb **raiz, int info, bool indicador){
    TNodoArb *nuevo;
    if(*raiz!=NULL) {
        if (info < (*raiz)->info) {
             insercionBalanceado(&((*raiz)->izq), info, indicador);
            if (indicador == true)
                RotacionesIzq(raiz);
        } else {
            if (info > (*raiz)->info) {
                 insercionBalanceado(&((*raiz)->der), info, indicador);
                if (indicador == true)
                    RotacionesDer(raiz);
            } else
                printf("El dato ya existe");
        }
    }else {
        crea_nodo(&nuevo, info);
        *raiz = nuevo;
    }
    return 0;
}

TNodoArb *eliminaBalanceado(TNodoArb **r, int info, bool indicador){
    TNodoArb *aux, *aux1, *aux2;

    if(*r!=NULL){
        if(info<(*r)->info){
            aux= eliminaBalanceado(&((*r)->izq), info, indicador);
            Elimina_RotaIzq(r, indicador);
        }else if(info >(*r)->info){
            aux= eliminaBalanceado(&((*r)->der), info,indicador);
            Elimina_RotaDer(r, indicador);
        }else{
            aux=*r;
            indicador=true;
            if(aux->izq ==NULL){
                *r=aux->der;
            }else if(aux->der ==NULL){
                *r=aux->izq;
            }else{
                aux1=(*r)->izq;
                indicador=false;
                while (aux1->der!=NULL){
                    aux2=aux1;
                    aux1=aux1->der;
                    indicador=true;
                }
                (*r)->info= aux->info;
                aux=aux1;
                if(indicador==true){
                    aux2->der=aux->izq;
                }else{
                    (*r)->izq=aux1->izq;
                }
                Elimina_RotaDer((&(*r)->izq), indicador);//___
            }
        }
    }else{
        aux=NULL;
        printf("no se encontro");
    }
    return aux;
}

//rotaciones
int RotacionesDer(TNodoArb **nodo){
    TNodoArb *aux, *aux1;
    bool indicador=false;
    if((*nodo)->FE) {
        switch ((*nodo)->FE) {
            case 1:
                (*nodo)->FE = 0;
                indicador = false;
                break;
            case 0:
                (*nodo)->FE = 1;
                break;
            case -1:
                aux = (*nodo)->der;
                break;
        }
        if ((*nodo)->FE >= 0) {//rotacion derecha derecha_simple
            aux = (*nodo)->der;
            (*nodo)->der = aux->izq;
            aux->izq = *nodo;
            *nodo = aux;
        } else { //rotacion derecha izq_compuesta
            aux = (*nodo)->der;
            aux1 = aux->izq;
            (*nodo)->der = aux1->izq;
            aux->izq = aux1->der;
            aux1->der = aux;
            aux1->izq = *nodo;
             if (aux1->FE == 1) {
                 (*nodo)->FE = -1;
             } else {
                 (*nodo)->FE = 0;
             }
             if (aux1->FE == -1) {
                 (*nodo)->FE = 1;
             } else {
                 (*nodo)->FE = 0;
             }
             *nodo = aux1;
        }
        (*nodo)->FE==0;
        indicador=false;
    }
    return 0;
}

int RotacionesIzq(TNodoArb **nodo){
    TNodoArb *aux, *aux1;

    bool indicador=false;
    if((*nodo)->FE) {
        switch ((*nodo)->FE) {
            case 1:
                (*nodo)->FE = 0;
                indicador = false;
                break;
            case 0:
                (*nodo)->FE = 1;
                break;
            case -1:
                aux = (*nodo)->izq;
                break;
        }
        if ((*nodo)->FE <= 0) {//rotacion izquierda izquierda_simple
            aux = (*nodo)->izq;
            (*nodo)->izq = aux->der;
            aux->der = *nodo;
            *nodo = aux;
        } else { //rotacion izquierda derecha _ compuesta
            aux = (*nodo)->izq;
            aux1 = aux->der;
            (*nodo)->izq = aux1->der;
            aux->der = aux1->izq;
            aux1->izq = aux;
            aux1->der = *nodo;

            if (aux1->FE == -1)
                (*nodo)->FE = 1;
             else {
                (*nodo)->FE = 0;
            }
            if (aux1->FE == 1)
                (*nodo)->FE = -1;
            else {
                (*nodo)->FE = 0;
            }
            *nodo = aux1;
        }
        (*nodo)->FE == 0;
        indicador = false;
    }
    return 0;
}


//rotaciones de elimnacion
int Elimina_RotaDer(TNodoArb **nodo, bool indicador){
    TNodoArb *aux, *aux1;

    if(indicador==true){
        if((*nodo)->FE) {
            switch ((*nodo)->FE) {
                case 1:
                    (*nodo)->FE = 0;
                    indicador = false;
                    break;
                case 0:
                    (*nodo)->FE = 1;
                    break;
                case -1:
                    aux = (*nodo)->der;
                    break;
            }
            if ((*nodo)->FE >= 0) {//rotacion derecha derecha_simple
                aux = (*nodo)->der;
                (*nodo)->der = aux->izq;
                aux->izq = *nodo;
                *nodo = aux;
                if (aux->FE) {
                    switch (aux->FE) {
                        case 0:
                            (*nodo)->FE = 1;
                            aux->FE = -1;
                            indicador = false;
                            break;
                        case 1:
                            (*nodo)->FE = 0;
                            aux->FE = 0;
                    }
                    *nodo = aux;
                } else { //rotacion derecha izq_compuesta
                    aux = (*nodo)->der;
                    aux1 = aux->izq;
                    (*nodo)->der = aux1->izq;
                    aux->izq = aux1->der;
                    aux1->der = aux;
                    aux1->izq = *nodo;
                    if (aux1->FE == 1) {
                        (*nodo)->FE = -1;
                    } else {
                        (*nodo)->FE = 0;
                    }
                    if (aux1->FE == -1) {
                        (*nodo)->FE = 1;
                    } else {
                        (*nodo)->FE = 0;
                    }
                    *nodo = aux1;
                    aux1->FE = 0;
                }
            }
        }
    }
    return 0;
}

int Elimina_RotaIzq(TNodoArb **nodo, bool indicador) {
    TNodoArb *aux, *aux1;
 //  bool indicador = false;
    if (indicador == true) {
        if ((*nodo)->FE) {
            switch ((*nodo)->FE) {
                case 1:
                    (*nodo)->FE = 0;
                    break;
                case 0:
                    (*nodo)->FE = 1;
                    indicador = false;
                    break;
                case -1:
                    aux = (*nodo)->izq;
                    break;
            }
            if ((*nodo)->FE <= 0) {//rotacion izquierda izquierda_simple
                aux = (*nodo)->izq;
                (*nodo)->izq = aux->der;
                aux->der = *nodo;
                *nodo = aux;
                if (aux->FE) {
                    switch (aux->FE) {
                        case 0:
                            (*nodo)->FE = -1;
                            aux->FE = 1;
                            indicador = false;
                            break;
                        case -1:
                            (*nodo)->FE = 0;
                            aux->FE = 0;
                            break;
                    }
                    *nodo = aux;
                } else { //rotacion izquierda derecha _ compuesta
                    aux = (*nodo)->izq;
                    aux1 = aux->der;
                    (*nodo)->izq = aux1->der;
                    aux->der = aux1->izq;
                    aux1->izq = aux;
                    aux1->der = *nodo;

                    if (aux1->FE == -1)
                        (*nodo)->FE = 1;
                    else {
                        (*nodo)->FE = 0;
                    }
                    if (aux1->FE == 1)
                        (*nodo)->FE = -1;
                    else {
                        (*nodo)->FE = 0;
                    }
                    *nodo = aux1;
                    aux1->FE = 0;
                }
            }
        }
    }
    return 0;
}
