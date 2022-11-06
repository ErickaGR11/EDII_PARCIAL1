#include <stdio.h>
#include <stdlib.h>
struct nodo{
    int info;
    struct nodo *sig;
};
typedef struct nodo Tnodo;

Tnodo *crea_nodo(int d);
void inserta_inicio(Tnodo **cab, int d);
void imprime(Tnodo *cab);
void InsertaOrdenado(Tnodo **cab, int d);
void InsertaOrd(Tnodo **cab, int d);
void InsertaFinal(Tnodo **cab, int d);
void InsertFinal(Tnodo **cab, int d);
Tnodo *EliminaInicio(Tnodo **cab);
Tnodo *EliminaFinalR(Tnodo **cab);
Tnodo *EliminaFinal(Tnodo **cab);
Tnodo *Busca_Elimina(Tnodo **cab, int d);
void Insersion_Elimina_case(Tnodo **cab);

int main() {
    Tnodo *lista = NULL;
    Insersion_Elimina_case(&lista);

}

void Insersion_Elimina_case(Tnodo **cab) {
    int i, d, n_dato, tipo_insersion, tipo_eliminacion;

    printf("Ingrese la cantidad de datos en la lista");
    scanf("%d", &n_dato);

    printf("Ingrese el tipo de insersion de la lista: 1.InsertaInicio, 2.InsertaOrdenadoIterat, "
           "3.InsertaOrdenadoRecur, 4.InsertaFinal");

    scanf("%d", &tipo_insersion);

    for (i = 0; i < n_dato; i++) {
        switch (tipo_insersion) {
            case 1:
                printf("Ingrese el nodo [%d]: ", i);
                scanf("%d", &d);
                inserta_inicio(cab, d);
                break;
            case 2:
                printf("Ingrese el nodo [%d]: ", i);
                scanf("%d", &d);
                InsertaOrd(cab, d);
                break;
            case 3:
                printf("Ingrese el nodo [%d]: ", i);
                scanf("%d", &d);
                InsertaOrdenado(cab, d);
                break;
            case 4:
                printf("Ingrese el nodo [%d]: ", i);
                scanf("%d", &d);
                InsertFinal(cab, d);
                break;
            case 5://iterativo CHECAR
                printf("Ingrese el nodo [%d]: ", i);
                scanf("%d", &d);
                InsertaFinal(cab, d);
                break;
        }
    }
    imprime(*cab);

    printf("\nIngrese el tipo de eliminacion: 1. Eliminacion al inicio, 2. Eliminar Final iterativo, "
           "3.Eliminar Final recursivo, 4. Buscar y Eliminar");
    scanf("%d", &tipo_eliminacion);

    switch (tipo_eliminacion) {
        case 1:
            EliminaInicio(cab);
            break;
        case 2:
            EliminaFinal(cab);
            break;
        case 3:
            EliminaFinalR(cab);
            break;
        case 4:
            printf("Ingrese el dato a buscar y eliminar");
            scanf("%d", &d);
            Busca_Elimina(cab, d);
            break;
    }
    imprime(*cab);
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

//iterativo
//CHECAAAAAAARRR
void InsertaFinal(Tnodo **cab, int d) {
    if (*cab==NULL){
        *cab= crea_nodo(d);
    }else {
        while (*cab != NULL) {
            *cab = (*cab)->sig;
            *cab = crea_nodo(d);
        }
    }
}

//recursivo
void InsertFinal(Tnodo **cab, int d){
    if (*cab==NULL){
        *cab= crea_nodo(d);
    }else{
        InsertFinal((&(*cab)->sig), d);

    }
}

//iterativo
void InsertaOrd(Tnodo **cab, int d){
    Tnodo *aux, *anterior;

    if(*cab==NULL || (*cab)->info > d){
        inserta_inicio(cab, d);
    }else {
        aux=*cab;
        while(aux!=NULL && aux->info<d){
            anterior=aux;
            aux= aux->sig;
        }
        anterior->sig=crea_nodo(d);
        anterior->sig->sig= aux;
    }
}

//recursivo
void InsertaOrdenado(Tnodo **cab, int d){

    if(*cab==NULL || ((*cab)->info) >= d){
        inserta_inicio(cab, d);
    }else{
        InsertaOrdenado(&((*cab)->sig), d);
    }
}

void imprime(Tnodo *cab){
    if(cab!=NULL){
        printf("[%d] ", cab->info);
        imprime(cab->sig);
    }
}
Tnodo *EliminaFinal(Tnodo **cab){
    Tnodo *aux, *ant;
    aux=*cab;
    if(*cab==NULL){
        printf("Vacio");
    }else{
        if((*cab)->sig==NULL)
            *cab= NULL;
        else{
            while((aux->sig)!=NULL){
                ant=aux;
                aux=aux->sig;
            }
            ant->sig=NULL;
        }
    }
    return(aux);
}

//recursivo
Tnodo *EliminaFinalR(Tnodo **cab){
    Tnodo *aux;
    aux=*cab;
    if(*cab != NULL){
        if((*cab)->sig !=NULL){
            *cab =NULL;
        }else{
            aux= EliminaFinalR(&(*cab)->sig);
        }
    }
    return (aux);
}

Tnodo *EliminaInicio(Tnodo **cab){
    Tnodo *aux;
    aux=*cab;
    if(*cab != NULL){
        *cab=aux->sig;
        aux->sig=NULL;
    }
    return (aux);
}


Tnodo *Busca_Elimina(Tnodo **cab, int d){
    Tnodo *aux;
    aux=*cab;
    if(*cab != NULL){
        if ((*cab)->info == d){
            *cab=aux->sig;
            aux->sig=NULL;
        }else{
            aux= Busca_Elimina(&((*cab)->sig), d);
        }
    }
    return (aux);
}