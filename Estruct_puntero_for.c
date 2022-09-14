#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int clave;
    char *nombre;
    int generacion;
    char *carrera;
    char *asesor;
}Alumno;
int menu(int *tam);
void *crea_arregloDinamico( int tipo, int tam);
void Captura(void *arr, int tipo, int tam);
void imprime(void *arr, int tipo, int tam);

int main(){
    void *arreglo;
    int t, tam;
    t= menu( &tam);
    arreglo=crea_arregloDinamico(t, tam);
    Captura(arreglo, t, tam);
    imprime(arreglo, t, tam);

}
int menu(int *tam){
    int t;
    printf("Ingrese la cantidad de elementos");
    scanf("%d", tam);
    printf("Tipo de dato: 1. int, 2.float, 3.char, 4.Alumno");
    scanf("%d", &t);

    return (t);
}

void *crea_arregloDinamico(int tipo, int tam) {
    void *arr;
    switch (tipo) {
        case 1:
            arr = malloc(sizeof(int) * tam);
            break;
        case 2:
            arr = malloc(sizeof(float) * tam);
            break;
        case 3:
            arr = malloc(sizeof(char) * tam);
            break;
        case 4:
            arr = malloc(sizeof(Alumno) * tam);
            break;
    }
    return (arr);
}
void Captura(void *arr, int tipo, int tam) {
    char cadena[100];
    int t;
    int  i;
    for ( i = 0; i < tam; ++i) {
        switch (tipo) {
            case 1:
                printf("Entero %d:", i);
                scanf("%d", ((int*)arr)+i);
                break;
            case 2:
                printf("Flotante %d:", i);
                scanf("%f", ((float*)arr+i));
                break;
            case 3:
                printf("Char %d:",i);
                fflush(stdin);
                scanf("%c", ((char*)arr)+i);
                break;
            case 4:
                printf("Clave %d:",i);
                scanf("%d", &(((Alumno *)arr)+i)->clave);
                fflush(stdin);
                printf("Nombre %d:", i);
                gets(cadena);
                t= strlen(cadena);
                (((Alumno *)arr)+i)->nombre=(char*)malloc(sizeof (char)*t);
                strcpy(((((Alumno *)arr)+i)->nombre), cadena);
                //scanf("%s", ((Alumno *)arr+i)->nombre);
                //gets(((Alumno *)arr+i)->nombre);

                printf("Generacion %d:", i);
                scanf("%d", &((((Alumno *)arr)+i)->generacion));
                fflush(stdin);
                printf("Carrera %d:", i); //*
                gets(cadena);
                t= strlen(cadena);
                (((Alumno *)arr)+i)->carrera=(char*)malloc(sizeof (char)*t);
                strcpy(((((Alumno *)arr)+i)->carrera), cadena);
                //gets((((Alumno *)arr)+i)->carrera);
                //scanf("%s", (((Alumno *)arr)+i)->carrera);
                fflush(stdin);
                printf("Asesor %d:", i); //*
                gets(cadena);
                t= strlen(cadena);
                (((Alumno *)arr)+i)->asesor=(char*)malloc(sizeof (char)*t);
                strcpy(((((Alumno *)arr)+i)->asesor), cadena);
                //gets((((Alumno *)arr)+i)->asesor);
               // scanf("%s", (((Alumno *)arr)+i)->asesor);
                break;
        }
    }
}
void imprime(void *arr, int tipo, int tam){
    int i;
    for ( i = 0; i < tam; ++i) {
        switch (tipo) {
            case 1:
                printf("El entero %d es: %d\n", i, *((int *)arr)+i);
                break;
            case 2:
                printf("El flotante %d es: %f\n", i, *((float*)arr)+i);

                break;
            case 3:
                printf("El Char %d es: %c\n", i, *((char *)arr)+i);
                fflush(stdin);
                break;
            case 4:
                printf("La clave %d es: %d\n",  i, (((Alumno *)arr)+i)->clave);
                printf("El nombre %d es: %s\n", i,(((Alumno *)arr)+i)->nombre);
                printf("La generacion %d es: %d\n", i,(((Alumno *)arr)+i)->generacion);
                printf("La carrera %d es: %s\n", i,(((Alumno *)arr)+i)->carrera);
                printf("El asesor %d es: %s\n", i,(((Alumno *)arr)+i)->asesor);
        }
    }
}

