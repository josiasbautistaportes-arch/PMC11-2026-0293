#ifndef RETO_H
#define RETO_H

/* Capacidades maximas */
#define MAX_UNIDADES 20
#define MAX_MUESTRAS 8
#define MAX_NOMBRE 16   /* 15 caracteres + '\0' */

/* Configuracion de procesamiento de una unidad */
typedef struct {
    int tipo;   /* 0 = acumula x, 1 = acumula x*x */
    int p;      /* umbral base (el umbral real es p + 1) */
} Configuracion;

/* Registro de una unidad */
typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    Configuracion config;   /* estructura anidada */
    int score;              /* intervenciones */
    int estado;             /* 0 o 1 */
} RegistroUnidad;

/* Prototipos */
void calcular(const int muestras_unidad[], int m, int tipo, int p,
              int *score, int *estado);
int total_rec(const RegistroUnidad unidades[], int n);
void ordenar(RegistroUnidad unidades[], int n);
void ordenar_por_id(RegistroUnidad unidades[], int n);
int buscar(const RegistroUnidad unidades[], int n, int q);

#endif