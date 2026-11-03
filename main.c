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

/* main temporal: solo para probar ordenar y ordenar_por_id */
static void imprimir_ids(const char *etiqueta, const RegistroUnidad u[], int n)
{
    int i;

    printf("%s", etiqueta);
    for (i = 0; i < n; i++) {
        printf(" %d", u[i].id);
    }
    printf("\n");
}

int main(void)
{
    RegistroUnidad a[2] = {{30, "MOTOR", {0, 40}, 6, 1},
                           {10, "VALVULA", {1, 20}, 359, 1}};
    RegistroUnidad b[3] = {{30, "C", {0, 0}, 2, 1},
                           {20, "B", {0, 0}, 2, 1},
                           {10, "A", {0, 0}, 2, 1}};
    RegistroUnidad c[3] = {{30, "X", {0, 0}, 500, 1},
                           {10, "Y", {0, 0}, 6, 1},
                           {20, "Z", {0, 0}, 100, 1}};

    ordenar(a, 2);
    imprimir_ids("ORDER", a, 2);

    ordenar(b, 3);
    imprimir_ids("ORDER", b, 3);

    ordenar(c, 3);
    imprimir_ids("ORDER", c, 3);

    ordenar_por_id(c, 3);
    imprimir_ids("POR_ID", c, 3);

    return 0;
}