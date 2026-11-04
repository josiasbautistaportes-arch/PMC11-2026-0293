#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

/* Lee y valida toda la entrada.
   Devuelve 1 si es valida y 0 si hay cualquier error. */
static int leer_datos(int *n, int *m, int *q,
                      RegistroUnidad unidades[],
                      int muestras[][MAX_MUESTRAS])
{
    int i, j, k;
    char nombre_tmp[32];
    char extra[2];

    if (scanf("%d %d %d", n, m, q) != 3) {
        return 0;
    }
    if (*n < 1 || *n > MAX_UNIDADES) {
        return 0;
    }
    if (*m < 1 || *m > MAX_MUESTRAS) {
        return 0;
    }
    if (*q < 1 || *q > 9999) {
        return 0;
    }

    for (i = 0; i < *n; i++) {
        int id, tipo, p;
        size_t largo, c;

        if (scanf("%d %31s %d %d", &id, nombre_tmp, &tipo, &p) != 4) {
            return 0;
        }
        if (id < 1 || id > 9999) {
            return 0;
        }
        for (k = 0; k < i; k++) {          /* id repetido */
            if (unidades[k].id == id) {
                return 0;
            }
        }

        largo = strlen(nombre_tmp);
        if (largo < 1 || largo > 15) {
            return 0;
        }
        for (c = 0; c < largo; c++) {
            if (!isalnum((unsigned char)nombre_tmp[c]) && nombre_tmp[c] != '_') {
                return 0;
            }
        }

        if (tipo != 0 && tipo != 1) {
            return 0;
        }
        if (p < 0 || p > 100) {
            return 0;
        }

        for (j = 0; j < *m; j++) {
            int x;

            if (scanf("%d", &x) != 1) {
                return 0;
            }
            if (x < 0 || x > 100) {
                return 0;
            }
            muestras[i][j] = x;
        }

        unidades[i].id = id;
        strcpy(unidades[i].nombre, nombre_tmp);   /* ya validado: cabe */
        unidades[i].config.tipo = tipo;
        unidades[i].config.p = p;
        unidades[i].score = 0;
        unidades[i].estado = 0;
    }

    if (scanf("%1s", extra) == 1) {   /* sobraron datos */
        return 0;
    }
    return 1;
}

int main(void)
{
    int n, m, q, i;
    RegistroUnidad unidades[MAX_UNIDADES];
    RegistroUnidad ordenadas[MAX_UNIDADES];
    RegistroUnidad por_id[MAX_UNIDADES];
    int muestras[MAX_UNIDADES][MAX_MUESTRAS];

    /* 1. leer y validar todo antes de imprimir nada */
    if (!leer_datos(&n, &m, &q, unidades, muestras)) {
        printf("ERROR\n");
        return 0;
    }

    /* 2. calcular score y estado de cada unidad */
    for (i = 0; i < n; i++) {
        calcular(muestras[i], m, unidades[i].config.tipo,
                 unidades[i].config.p,
                 &unidades[i].score, &unidades[i].estado);
    }

    /* 3. resultados individuales, en el orden original */
    for (i = 0; i < n; i++) {
        printf("%d %d %d\n", unidades[i].id, unidades[i].score,
               unidades[i].estado);
    }

    /* 4. total recursivo */
    printf("TOTAL %d\n", total_rec(unidades, n));

    /* 5. ORDER: copia ordenada por score e id */
    for (i = 0; i < n; i++) {
        ordenadas[i] = unidades[i];
    }
    ordenar(ordenadas, n);
    printf("ORDER");
    for (i = 0; i < n; i++) {
        printf(" %d", ordenadas[i].id);
    }
    printf("\n");

    /* 6. FIND: copia ordenada por id y busqueda binaria */
    for (i = 0; i < n; i++) {
        por_id[i] = unidades[i];
    }
    ordenar_por_id(por_id, n);
    printf("FIND %d %d\n", q, buscar(por_id, n, q));

    return 0;
}