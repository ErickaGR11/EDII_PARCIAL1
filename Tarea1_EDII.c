#include <stdio.h>
int Capturar(int arr1[], int arr2[]);
void Operacion(int arr1[], int arr2[], int arr3[]);
int Imprimir(int arr[]);
int main()
{
    int arr1[5], arr2[5], arr3[5];

     Capturar(arr1, arr2);
     printf("Valores dados ascendentes Arr1:\n");
     Imprimir(arr1);
     printf("\nValores desendentes Arr2: \n");
     Imprimir(arr2);

     Operacion( arr1,  arr2,  arr3);
    printf("\nResultado de la suma Arr3: \n");
     Imprimir(arr3);
}

int Capturar(int arr1[], int arr2[]){
    int *p1; //puntero
    int *p2;

    p1 = &arr1[0];
    p2 = &arr2[5];
    for (int i = 0; i < 6; i++)
    {
        printf("ingrese el valor[%d] del Arreglo 1:\n" , i);
        scanf("%d", p1+i );
    }
    for (int j = 0; j < 6; j++)
    {
        printf("ingrese el valor[%d] del Arreglo 2:\n", j);
        scanf("%d", p2-j );
    }
    return 0;
}
void Operacion(int arr1[], int arr2[], int arr3[]){
    int *p1; //puntero
    int *p2;
    int *p3;
    p1 = &arr1[0];
    p2 = &arr2[5];
    p3=  &arr3[0];

    for (int i = 0; i < 6; i++)
    {
        arr3[i]= arr1[i]+ arr2[i];
        p1++;
        p2--;
        p3++;
    }
}
int Imprimir(int arr[]){
    int *p; //puntero
    int i; //iterador
    p = &arr[0];

    for (i = 0; i < 6; i++)
    {
        printf("[%d]: %d\t", i, *p);
        p++;
    }

    return 0;
}