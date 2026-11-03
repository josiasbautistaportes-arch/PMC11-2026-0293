#include <stdio.h>
#include "reto.h"

/* Procesa las muestras de UNA unidad y devuelve score y estado
   por referencia. Cada llamada empieza con residuo = 0 y score = 0. */
void calcular(const int muestras_unidad[], int m, int tipo, int p,
              int *score, int *estado)
{
    int residuo = 0;
    int umbral = p + 1;
    int i;

    *score = 0;
    for (i = 0; i < m; i++) {
        int x = muestras_unidad[i];

        if (tipo == 0) {
            residuo += x;
        } else {
            residuo += x * x;
        }
        *score += residuo / umbral;   /* intervenciones completas */
        residuo = residuo % umbral;   /* lo que sobra */
    }

    if (residuo != 0) {
        *estado = 1;
    } else {
        *estado = 0;
    }
}

/* Suma recursiva de los scores de las primeras n unidades */
int total_rec(const RegistroUnidad unidades[], int n)
{
    if (n == 0) {   /* caso base */
        return 0;
    }
    return unidades[n - 1].score + total_rec(unidades, n - 1);
}

/* Ordena por score de mayor a menor; si empatan, por id de menor a mayor */
void ordenar(RegistroUnidad unidades[], int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            int cambiar = 0;

            if (unidades[j].score < unidades[j + 1].score) {
                cambiar = 1;
            } else if (unidades[j].score == unidades[j + 1].score &&
                       unidades[j].id > unidades[j + 1].id) {
                cambiar = 1;
            }

            if (cambiar) {
                RegistroUnidad aux = unidades[j];
                unidades[j] = unidades[j + 1];
                unidades[j + 1] = aux;
            }
        }
    }
}

/* Ordena por id de menor a mayor (hace falta para la busqueda binaria) */
void ordenar_por_id(RegistroUnidad unidades[], int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (unidades[j].id > unidades[j + 1].id) {
                RegistroUnidad aux = unidades[j];
                unidades[j] = unidades[j + 1];
                unidades[j + 1] = aux;
            }
        }
    }
}

/* Busqueda binaria por id. El arreglo debe estar ordenado por id.
   Devuelve el score o -1 si no existe. */
int buscar(const RegistroUnidad unidades[], int n, int q)
{
    int izq = 0;
    int der = n - 1;

    while (izq <= der) {
        int medio = (izq + der) / 2;

        if (unidades[medio].id == q) {
            return unidades[medio].score;
        } else if (unidades[medio].id < q) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }
    return -1;
}

/* main temporal: solo para probar buscar */
int main(void)
{
    RegistroUnidad u[3] = {{30, "C", {0, 0}, 2, 1},
                           {10, "A", {0, 0}, 8, 1},
                           {20, "B", {0, 0}, 5, 1}};

    ordenar_por_id(u, 3);

    printf("FIND 20 %d\n", buscar(u, 3, 20));
    printf("FIND 10 %d\n", buscar(u, 3, 10));
    printf("FIND 30 %d\n", buscar(u, 3, 30));
    printf("FIND 99 %d\n", buscar(u, 3, 99));
    printf("FIND 5 %d\n", buscar(u, 3, 5));

    return 0;
}

