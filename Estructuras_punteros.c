#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int clave;
    char nombre[50];
    int generacion;
    char carrera[50];
    char asesor[50];
}Alumno;

Alumno *crea_arregloDinamico( int n);
void Captura(Alumno *arreglo, int n);
void imprime(Alumno *arreglo, int n);

int main(){

    Alumno *arreglo;
    int n;
    printf("Dame la cantidad de alumnos:");
    scanf("%d", &n);

    arreglo=crea_arregloDinamico(n);
    Captura(arreglo,n);
    imprime(arreglo, n);

}
Alumno *crea_arregloDinamico(int n){
    Alumno *arr_alumnos;
    arr_alumnos= (Alumno *) malloc(sizeof (Alumno)*n);
    if (arr_alumnos==NULL) {
        printf("No se reservo espacio");
    }
    return (arr_alumnos);
}

void Captura(Alumno *arreglo, int n){
    char *cadena;
    int i;
    for ( i = 0; i < n; ++i) {
        printf("Clave");
        scanf("%d", &(*(arreglo+i)).clave);
        fflush(stdin);

        printf("Nombre Completo");
        gets(cadena);
        strcpy(((*(arreglo+i)).nombre), cadena);
        //gets(((*(arreglo+i)).nombre));

        printf("Generacion");
        scanf("%d", &(*(arreglo+i)).generacion);
        fflush(stdin);

        printf("Carrera");
        gets(cadena);
        strcpy(((*(arreglo+i)).carrera), cadena);
        //gets(((*(arreglo+i)).carrera));

        printf("Asesor");
        gets(cadena);
        strcpy(((*(arreglo+i)).asesor), cadena);
        //gets(((*(arreglo+i)).asesor));
    }
}

void imprime(Alumno *arreglo, int n){
    int i;
    for ( i = 0; i < n; ++i) {
        printf("\nclave: %d", (*(arreglo+i)).clave);
        printf("\nnombre: %s", (*(arreglo+i)).nombre);
        printf("\ngeneracion: %d", (*(arreglo+i)).generacion);
        printf("\ncarrera: %s", (*(arreglo+i)).carrera);
        printf("\nasesor: %s", (*(arreglo+i)).asesor);
    }
}