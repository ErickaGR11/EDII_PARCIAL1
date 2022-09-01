#include <stdio.h>
#include <stdlib.h>

int *crea_arregloUni(int r);
void captura_arregloUni(int *arreglo, int r);
void imprime_arregloUni(int *arreglo, int r);

int **crea_arreglobidi(int r, int c);
void captura_arregloBidi(int **arreglo, int r, int c);
void imprime_arregloBidi(int **arreglo, int r, int c);

int ***crea_arreglo_tridi( int m, int r, int c);
void captura_arregloTridi(int ***arreglo, int m, int r, int c);
void imprimir_arregloTridi(int ***arreglo, int m, int r, int c);

int main(){
    int tipo_arr;
    int *arregloUni, **arregloBidi, ***arregloTridi;
    int r, c, m;
    printf("Tipo de areglo: 1.Unidimensional, 2.Bidimensional, 3.Tridimensional\n");
    scanf("%d", &tipo_arr);
    switch (tipo_arr) {
        case 1:
            printf("Tamano del arreglo:");
            scanf("%d", &r);
            arregloUni=crea_arregloUni(r);
            if (arregloUni!=NULL)
                captura_arregloUni(arregloUni, r);
            break;
        case 2:
            printf("Tamano de renglones:");
            scanf("%d", &r);
            printf("Tamano de columnas:");
            scanf("%d", &c);
            arregloBidi= crea_arreglobidi( r,  c);
            captura_arregloBidi(arregloBidi, r, c);
            break;
        case 3:
            printf("Tamano de matriz, renglones, columnas:");
            scanf("%d %d %d", &m, &r, &c);
            arregloTridi= crea_arreglo_tridi( m,  r,  c);
            captura_arregloTridi(arregloTridi,  m,  r,  c);
            break;
    }
}
//FUNCIONES ARREGLOS UNIDIMENSIONALES
int *crea_arregloUni(int r){
    int *ptr;
    ptr=malloc(sizeof (int)*r);
    if (ptr==NULL)
        printf("No se pudo reservar espacio para el arreglo");
    return (ptr);
}
void captura_arregloUni(int *arreglo, int r){
    for (int i = 0; i < r; ++i) {
        printf("Elemento %d:", i);
        scanf("%d", arreglo+i);
    }
    imprime_arregloUni(arreglo, r);
}
void imprime_arregloUni(int *arreglo, int r){
    for (int i = 0; i < r; ++i) {
        printf("%d: [%d]  ", i, *(arreglo+i));
    }
}
//________________________________________
// FUNCIONES ARREGLOS BIDIMENSIONALES
int **crea_arreglobidi(int r, int c) {
    int **ptr;
    int i, j;
    ptr = (int**)malloc(sizeof(int*) * r);
    if (*ptr != NULL) {
        for (i = 0; i < r; i++) {
            ptr[i] = crea_arregloUni(c);
            //*(ptr+i)=
            if (*(ptr + i) == NULL)
                break;
        }
        if (i < r) {
            for (j = i - 1; j >= i; --j) {
                free(*(ptr + j));
            }
        }
    }
    return (ptr);
}
void captura_arregloBidi(int **arreglo, int r, int c) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; j++) {
            printf("Elemento [%d][%d]:", i, j);
            scanf("%d", *(arreglo + i) + j);
        }
    }
    imprime_arregloBidi(arreglo, r, c);
}
void imprime_arregloBidi(int **arreglo, int r, int c){
    int i, j;
    for ( i=0; i<r; i++) {
        for ( j = 0; j < c; j++) {
            printf("[ %d ]", *(*(arreglo + i) + j));
        }
        printf("\n");
    }
}
//________________________________________
// FUNCIONES ARREGLOS TRIDIMENSIONALES
int ***crea_arreglo_tridi( int m, int r, int c) {
    int ***ptr;
    int i, j;
    ptr = (int***)malloc(sizeof(int**) * m);
    if (*ptr != NULL) {
        for (i = 0; i < m; i++) {
            ptr[i] = crea_arreglobidi(r,c);
            //ptr[i]=*(*ptr+i)
            if (*(*ptr + i) == NULL)
                break;
        }
        if (i <m) {
            for (j = i - 1; j >= i; --j) {
                free(*(ptr + j));
            }
            free(ptr);
            ptr = NULL;
        }
    }
    return (ptr);
}
void captura_arregloTridi(int ***arreglo, int m, int r, int c) {
    int i,j,k;
    for ( i = 0; i < m; ++i) {
        for ( j = 0; j < r; j++) {
            for ( k = 0; k < c; ++k) {
                printf("Elemento [%d][%d][%d]:", i, j, k);
                scanf("%d", *(*(arreglo+i)+j)+k);
            }
        }
    }
    imprimir_arregloTridi(arreglo, m, r, c);
}
void imprimir_arregloTridi(int ***arreglo, int m, int r, int c){
    int i, j,k;
    for ( i=0; i<m; i++) {
        for (j = 0; j < r; j++) {
            for ( k = 0; k < c; ++k) {
                printf("[%d][%d][%d]:%d\n", i,j,k,*((*(*(arreglo+i)+j))+k));
            }
        }
    }
}