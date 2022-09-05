#include <stdio.h>
#include <stdlib.h>

void crea_arregloUni(int **arreglo, int n);
void captura_arregloUni_random(int *arreglo, int n);
void imprime_arregloUni(int *arreglo, int n);

int main(){
    int n;
    int *arregloUni;
    n= rand()%100+10;
    crea_arregloUni(&arregloUni, n);
    printf("Total de elementos: %d\n", n);
    if (arregloUni!=NULL){
        captura_arregloUni_random(arregloUni, n);
    }
}
void captura_arregloUni_random(int *arreglo, int n){
    int i, contpar=0, contimp=0;
    int *arrpar, *arrimpar;
    for ( i = 0; i < n; ++i) {
        *(arreglo+i)= rand()%100;
        if (*(arreglo + i) % 2 == 0)
            contpar++;
        else
            contimp++;
    }
    imprime_arregloUni(arreglo, n);
    printf("\n\nCantidad de numeros pares: %d", contpar);
    printf("\nCantidad de numeros impares: %d\n", contimp);

    crea_arregloUni(&arrpar, contpar);
    crea_arregloUni(&arrimpar, contpar);
    contpar=0; contimp=0;
    for ( i = 0; i < n; ++i) {
        if (*(arreglo + i) % 2 == 0) {
            *(arrpar + contpar) = *(arreglo + i);
            contpar++;
        }
        else{
            *(arrimpar + contimp) = *(arreglo + i);
            contimp++;
        }
    }
    printf("\nArreglo pares\n");
    imprime_arregloUni(arrpar, contpar);
    printf("\nArreglo impares\n");
    imprime_arregloUni(arrimpar, contimp);
}

void imprime_arregloUni(int *arreglo, int n){
    int i;
    for ( i = 0; i < n; ++i) {
        printf("[%d]:%d  ", i, *(arreglo+i));
    }
}
void crea_arregloUni(int **arreglo, int n){
    *arreglo=malloc(sizeof (int)*n);
    if (*arreglo==NULL)
        printf("No se pudo reservar espacio para el arreglo");
}
