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

/* main temporal: solo para probar calcular */
int main(void)
{
    int motor[] = {10, 50, 70, 30, 90};
    int valvula[] = {20, 25, 10, 80, 5};
    int sin[] = {100, 0, 100, 0};
    int score, estado;

    calcular(motor, 5, 0, 40, &score, &estado);
    printf("MOTOR %d %d\n", score, estado);

    calcular(valvula, 5, 1, 20, &score, &estado);
    printf("VALVULA %d %d\n", score, estado);

    calcular(sin, 4, 1, 100, &score, &estado);
    printf("SIN %d %d\n", score, estado);

    return 0;
}

