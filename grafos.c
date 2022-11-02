#include <stdio.h>
#include <stdlib.h>
typedef struct nodV {
    int vert;
    struct nodV *sig;
    struct nodA *abajo;
} TnodoV;
typedef struct nodA {
    struct nodV *arriba;
    struct nodA *sig;
} TnodoA;

int **cargaMatrizA(char *nombre, int *num_ver);
int **creaArregloBidi(int r, int c);
TnodoV *crea_nodoV(int vertice);
TnodoA *crea_nodoA(TnodoV *v);
TnodoV *creaGrafo(int **mA, int num_ver);
TnodoV *creaGrafo2(int **mA, int num_ver);
void InsertFinalV(TnodoV **g, int d);
void InsertFinalA(TnodoV **g, TnodoV *d);
void imprime_grafo(TnodoV *g);

int main() {
    char nombreArchivo[100];
    int **mA, tipo_crea, num_ver;
    TnodoV *G = NULL; // GRAFO

    printf("Nombre del archivo:");
    gets(nombreArchivo);
    mA = cargaMatrizA(nombreArchivo, &num_ver);

    printf(
            "Como desea crear el grafo: 1.Crear la lista de vertices y despues las "
            "aristas, 2.Creando los vertices conforme se insertan las relaciones\n");
    scanf("%d", &tipo_crea);

    switch (tipo_crea) {
        case 1:
            G = creaGrafo(mA, num_ver);
            break;
        case 2:
            G = creaGrafo2(mA, num_ver);
            break;
    }
    imprime_grafo(G);
}

// archivos
int **cargaMatrizA(char *nombre, int *num_ver) {
    FILE *archivo;
    int **mA, r, c;

    archivo = fopen(nombre, "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d", num_ver);
        mA = creaArregloBidi(*num_ver, *num_ver);
        for (r = 0; r < *num_ver; ++r) {
            for (c = 0; c < *num_ver; ++c) {
                fscanf(archivo, "%d", (*(mA + r) + c));
            }
        }
        printf("Si se pudo LEER\n");
        fclose(archivo);
    } else {
        printf("No se pudo LEER\n");
    }
    return mA;
}

int **creaArregloBidi(int r, int c) {
    int **ptr, i, j;
    ptr = (int **)malloc(sizeof(int *) * r);
    if (ptr != NULL) {
        for (i = 0; i < r; i++) {
            *(ptr + i) = (int *)malloc(sizeof(int) * c);
            if (*(ptr + i) == NULL)
                break;
        }
    }
    return ptr;
}
// vertice
TnodoV *crea_nodoV(int vertice) {
    TnodoV *nuevo;
    nuevo = (TnodoV *)malloc(sizeof(TnodoV));
    if (nuevo != NULL) {
        nuevo->vert = vertice;
        nuevo->sig = NULL;
        nuevo->abajo = NULL;
    }
    return nuevo;
}
// arista
TnodoA *crea_nodoA(TnodoV *v) {
    TnodoA *nuevo;
    nuevo = (TnodoA *)malloc(sizeof(TnodoA));
    if (nuevo != NULL) {
        nuevo->arriba = v;
        nuevo->sig = NULL;
    }
    return nuevo;
}

// crea grafo opcion1
TnodoV *creaGrafo(int **mA, int num_ver) {
    TnodoV *origen, *destino, *cab = NULL;
    int i, j, v = 1;

    for (i = 0; i < num_ver; i++) {
        InsertFinalV(&cab, v);
        v++;
    }
    for (j = 0, origen = cab; j < num_ver; origen = origen->sig, j++) {
        for (i = 0, destino = cab; destino != NULL; destino = destino->sig, i++) {
            if (*(*(mA + i) + j) == 1)
                InsertFinalA(&origen->abajo, destino);
        }
    }
    return cab;
}
// crea grafo opcion2
TnodoV *creaGrafo2(int **mA, int num_ver) {
    int i, j;
    TnodoV *origen, *destino, *nuevo, *cab = NULL;

    for (j = 0; j < num_ver; j++) {
        for (i = 0; i < num_ver; i++) {
            if (j == 0) {
                nuevo = crea_nodoV(i + 1);
                if (i == 0) {
                    cab = origen = destino = nuevo;
                } else
                    destino->sig = nuevo;
            }
            if (i > 0) {
                destino = destino->sig;
            }
            if (*(*(mA + i) + j) == 1)
                InsertFinalA(&origen->abajo, destino);
        }
        origen = origen->sig;
        destino = cab;
    }
    return cab;
}
// inserta final recursivo vertice
void InsertFinalV(TnodoV **g, int d) {
    if (*g == NULL) {
        *g = crea_nodoV(d);
    } else {
        InsertFinalV(&(*g)->sig, d);
    }
}
// inserta final recursivo arista
void InsertFinalA(TnodoV **g, TnodoV *d) {
    if (*g == NULL) {
        *g = crea_nodoA(d);
    } else {
        InsertFinalA(&(*g)->sig, d);
    }
}

void imprime_grafo(TnodoV *g) {
    TnodoV *v;
    TnodoA *ar;

    for (v = g; v != NULL; v = v->sig) {
        for (ar = v->abajo; ar != NULL; ar = ar->sig) {
            printf("  %d -> %d  ", v->vert, ar->arriba->vert);
        }
        printf("\n");
    }
}