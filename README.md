# PMC11: Mantenimiento por desgaste acumulado

Instituto Tecnologico de Las Americas (ITLA)
Asignatura: Programacion para Mecatronicos
Estudiante: Josias Bautista
Matricula: 2026-0293
Correo: 20260293@itla.edu.do
Practica individual, 25 puntos. Lenguaje C11.

## Descripcion del problema

El programa lee varias unidades (celdas mecatronicas). Cada una trae un id, un nombre, un tipo, un umbral base p y m muestras de desgaste. Para cada unidad calculo cuantas intervenciones tuvo (score) y su estado final. Al final imprimo un reporte con el total, el orden y una busqueda por id.

## Objetivo

Hacer el simulador en C11 con los componentes que pide el profesor: dos archivos (main.c y reto.h), estructuras anidadas, una matriz de muestras, una funcion recursiva, un ordenamiento y una busqueda binaria, con validacion estricta de la entrada.

## Modelo de desgaste

Cada unidad se procesa por separado. Empiezo con residuo = 0 y score = 0, y el umbral es p + 1. Por cada muestra x:

- si tipo es 0, sumo x al residuo
- si tipo es 1, sumo x * x al residuo
- sumo residuo / (p + 1) al score (division entera)
- dejo residuo = residuo % (p + 1)

Al final, estado es 1 si el residuo no es 0, y 0 si es 0. Una sola muestra puede dar varias intervenciones, por eso uso la division y no un if.

## Decisiones de implementacion

- Primero leo y valido toda la entrada, despues calculo y al final imprimo. Asi, si hay un error, solo sale ERROR y nada mas.
- Valido n, m y q antes de leer los registros, para no salirme de los arreglos de tamano 20.
- Leo el nombre en un buffer de 32 y reviso que mida de 1 a 15 y tenga solo letras, numeros o guion bajo.
- Despues del ultimo registro intento leer un dato mas. Si existe, imprimo ERROR.
- ordenar() ordena por score de mayor a menor y por id de menor a mayor en empates. Lo hago sobre una copia para no perder el orden original, que es el que se imprime en las lineas individuales.
- La busqueda binaria necesita el arreglo ordenado por id, y ordenar() usa otro criterio. Por eso agregue la funcion ordenar_por_id(), que trabaja sobre otra copia.
- total_rec() suma los scores de forma recursiva. El caso base es n == 0.
- No uso memoria dinamica, qsort ni bsearch. Todo son arreglos estaticos.

## Archivos

- main.c: lectura y validacion, calcular, total_rec, ordenar, ordenar_por_id, buscar y main.
- reto.h: constantes, estructuras Configuracion y RegistroUnidad, y prototipos.
- plan.md: analisis, pseudocodigo y prueba de escritorio.
- evaluar.py: ejecutor de pruebas que dio el profesor.
- publicas.json: los seis casos publicos.
- pruebas/publicas/: entradas (.in) y salidas esperadas (.out) de los seis casos publicos.
- pruebas/propias/: tres casos propios (.in y .out).
- pruebas/resultados.md: resultados, comparacion esperado contra obtenido y traza manual.

## Compilacion

    gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto

Compila sin errores y sin warnings.

## Ejecucion

    ./reto < pruebas/publicas/grupo1.in

Banco de pruebas publicas (en mi Windows uso py):

    py evaluar.py publicas.json reto.exe

## Formato de entrada

Primero n m q y despues n registros:

    id nombre tipo p x1 x2 ... xm

Los datos pueden estar separados por espacios o saltos de linea. Rangos: n de 1 a 20, m de 1 a 8, q e id de 1 a 9999, tipo 0 o 1, p y x de 0 a 100, nombre de 1 a 15 caracteres (letras, numeros o guion bajo). Los id no se pueden repetir.

## Formato de salida

    id score estado        (una linea por unidad, en el orden de entrada)
    TOTAL suma_de_scores
    ORDER id1 id2 ...
    FIND q score           (FIND q -1 si el id no existe)

Con cualquier error de entrada se imprime solo ERROR.

## Resultados de las pruebas

Los seis casos publicos dan OK con evaluar.py y con diff. Los tres casos propios tambien: una valida normal, una valida de borde con q ausente (FIND da -1) y una invalida por id repetido. Calcule a mano la salida esperada de los casos propios antes de correr el programa. El detalle y la traza manual estan en pruebas/resultados.md.

## Fuentes consultadas

Corona Nakamura, M. A. y Ancona Valdez, M. de los A. (2011). Diseno de algoritmos y su codificacion en lenguaje C. McGraw-Hill, primera edicion.

## Historial de commits anteriores al commit final

| Commit | Hash | Avance realizado |
|---|---|---|
| Commit 1 | 55ac439 | Estructura inicial del proyecto |
| Commit 2 | 853aa3d | Analisis y pseudocodigo en plan.md |
| Commit 3 | 06d7cdb | Constantes, estructuras y prototipos en reto.h |
| Commit 4 | 2ced9e2 | Funcion calcular, probada con casos del enunciado |
| Commit 5 | 4ff4521 | Funcion total_rec (suma recursiva) |
| Commit 6 | 2de5a88 | Funciones ordenar y ordenar_por_id |
| Commit 7 | a041bdd | Funcion buscar (busqueda binaria) |
| Commit 8 | 0e50c1d | evaluar.py y publicas.json |
| Commit 9 | 7447c4e | Lectura y validacion de la entrada |
| Commit 10 | 3ea8dee | Integracion del calculo y el reporte en main |
| Commit 11 | 83d2e2c | Entradas y salidas esperadas de los casos publicos |
| Commit 12 | ff4ce35 | Tres casos propios |
| Commit 13 | 7f16842 | Resultados de pruebas y traza manual |

El hash completo del commit final se entrega aparte, junto con el enlace del repositorio.