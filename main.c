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

/* main temporal: solo para probar total_rec */
int main(void)
{
    RegistroUnidad u[2];

    u[0].score = 6;
    u[1].score = 359;

    printf("TOTAL %d\n", total_rec(u, 2));
    printf("TOTAL %d\n", total_rec(u, 1));
    printf("TOTAL %d\n", total_rec(u, 0));

    return 0;
}

