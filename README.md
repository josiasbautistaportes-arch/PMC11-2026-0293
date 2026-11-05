# PMC11: Mantenimiento por desgaste acumulado

Instituto Tecnologico de Las Americas (ITLA)
Asignatura: Programacion para Mecatronicos
Estudiante: Josias Bautista
Matricula: 2026-0293
Correo: 20260293@itla.edu.do

## Que hace el programa

Lee varias unidades con su id, nombre, tipo, umbral p y m muestras. Para cada una calcula el score (intervenciones) y el estado. Al final imprime TOTAL, ORDER y FIND.

## Como calculo el desgaste

Cada unidad empieza con residuo = 0 y score = 0. El umbral es p + 1. Por cada muestra x:

- tipo 0: residuo += x
- tipo 1: residuo += x * x
- score += residuo / (p + 1)
- residuo = residuo % (p + 1)

Al final, estado = 1 si el residuo no es 0, si no estado = 0. Uso division y no un if porque una muestra puede dar varias intervenciones.

## Decisiones

- Primero leo y valido todo, despues calculo e imprimo. Si hay error, solo sale ERROR.
- Reviso n, m y q antes de leer los registros para no salirme de los arreglos.
- El nombre lo leo en un buffer de 32 y reviso que mida de 1 a 15 y sea letras, numeros o guion bajo.
- Despues del ultimo registro intento leer otro dato. Si existe, es ERROR.
- ordenar() trabaja sobre una copia para no perder el orden original.
- La busqueda binaria necesita orden por id, asi que hice ordenar_por_id() sobre otra copia.
- total_rec() es recursiva y su caso base es n == 0.
- No uso malloc, qsort ni bsearch.

## Archivos

- main.c: lectura, validacion, funciones y main
- reto.h: constantes, estructuras y prototipos
- plan.md: analisis y pseudocodigo
- evaluar.py y publicas.json: banco de pruebas del profesor
- pruebas/: casos publicos y propios, y resultados.md

## Compilar y ejecutar

    gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto
    ./reto < pruebas/publicas/grupo1.in
    py evaluar.py publicas.json reto.exe

## Entrada

Primero n m q y luego n registros:

    id nombre tipo p x1 x2 ... xm

Rangos: n 1 a 20, m 1 a 8, q e id 1 a 9999, tipo 0 o 1, p y x 0 a 100. Los id no se repiten.

## Salida

    id score estado
    TOTAL suma
    ORDER id1 id2 ...
    FIND q score      (o FIND q -1)

Con cualquier error imprime solo ERROR.

## Pruebas

Los 6 casos publicos dan OK. Tambien los 3 propios: uno normal, uno de borde con q ausente y uno invalido. Los esperados de los propios los calcule a mano antes de correr el programa. Mas detalle y la traza manual en pruebas/resultados.md.

## Fuentes

Corona Nakamura, M. A. y Ancona Valdez, M. de los A. (2011). Diseno de algoritmos y su codificacion en lenguaje C. McGraw-Hill, primera edicion.

## Commits anteriores al final

| Commit | Hash | Avance |
|---|---|---|
| 1 | 55ac439 | Estructura inicial |
| 2 | 853aa3d | Analisis y pseudocodigo |
| 3 | 06d7cdb | reto.h |
| 4 | 2ced9e2 | calcular |
| 5 | 4ff4521 | total_rec |
| 6 | 2de5a88 | ordenar y ordenar_por_id |
| 7 | a041bdd | buscar |
| 8 | 0e50c1d | evaluar.py y publicas.json |
| 9 | 7447c4e | Lectura y validacion |
| 10 | 3ea8dee | Integracion en main |
| 11 | 83d2e2c | Casos publicos .in y .out |
| 12 | ff4ce35 | Casos propios |
| 13 | 7f16842 | resultados.md |
| 14 | 3adbb3e | README completo |

El hash del commit final va aparte, con el enlace del repositorio.