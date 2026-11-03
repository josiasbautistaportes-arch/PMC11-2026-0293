# Plan PMC11: Mantenimiento por desgaste acumulado

## 1. Objetivo

Hacer un programa en C11 que lee varias unidades (celdas mecatronicas), calcula para cada una cuantas intervenciones tuvo (score) y su estado final, y despues imprime un reporte con el total, el orden y una busqueda por id.

## 2. Datos de entrada

Se lee todo por la entrada estandar. Primero `n m q` y despues `n` registros:

    id nombre tipo p x1 x2 ... xm

- n = cantidad de unidades (1 a 20)
- m = muestras por unidad (1 a 8)
- q = id que se va a buscar (1 a 9999), puede no existir
- id = identificador unico (1 a 9999)
- nombre = 1 a 15 caracteres, solo letras, numeros o guion bajo, sin espacios
- tipo = 0 o 1
- p = umbral base (0 a 100)
- x = cada muestra (0 a 100)

Los datos pueden venir separados por espacios o saltos de linea, asi que no dependo de que cada registro este en una linea.

## 3. Datos de salida

Si todo es valido, en este orden:

    id score estado        (una linea por unidad, en el orden en que entraron)
    TOTAL suma_de_scores
    ORDER id1 id2 ...
    FIND q score           (o FIND q -1 si no existe)

Si hay cualquier error, se imprime solo `ERROR` y el programa termina con `return 0`. No se imprime nada antes.

## 4. Restricciones

- C11, compilar con: gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto
- Sin warnings.
- Archivos: main.c y reto.h.
- Sin malloc, calloc, realloc, free, gets, conio.h, system(), qsort ni bsearch.
- Arreglos estaticos.
- Sin menus ni mensajes extra.
- Primero se lee y valida todo, despues se calcula y al final se imprime.

## 5. Variables y estructuras principales

En reto.h:

- MAX_UNIDADES = 20 y MAX_MUESTRAS = 8.
- struct Configuracion: tipo y p.
- struct RegistroUnidad: id, nombre[16], Configuracion config (anidada), score y estado.

En main:

- int n, m, q.
- RegistroUnidad unidades[MAX_UNIDADES]: los registros en el orden original.
- int muestras[MAX_UNIDADES][MAX_MUESTRAS]: las muestras de cada unidad.
- RegistroUnidad ordenadas[MAX_UNIDADES]: copia para ORDER.
- RegistroUnidad por_id[MAX_UNIDADES]: copia para FIND.
- char nombre_tmp[32]: para leer el nombre antes de validarlo.

En calcular: residuo, umbral y x.

## 6. Funciones y responsabilidades

- calcular(muestras_unidad, m, tipo, p, *score, *estado): procesa las muestras de una unidad y devuelve el score y el estado por referencia.
- total_rec(unidades, n): suma los scores de forma recursiva. Caso base: n == 0 devuelve 0.
- ordenar(unidades, n): ordena por score de mayor a menor y, si empatan, por id de menor a mayor.
- ordenar_por_id(unidades, n): funcion auxiliar. Ordena por id de menor a mayor. Se necesita porque ordenar() usa otro criterio y la busqueda binaria solo funciona si el arreglo esta ordenado por id.
- buscar(unidades, n, q): busqueda binaria por id sobre el arreglo ordenado por id. Devuelve el score o -1.

## 7. Modelo matematico

Para cada unidad, por separado:

    residuo = 0
    score = 0
    umbral = p + 1

Por cada muestra x:

    si tipo == 0:  residuo = residuo + x
    si tipo == 1:  residuo = residuo + x * x
    score = score + residuo / umbral      (division entera)
    residuo = residuo % umbral

Al final:

    estado = 1 si residuo != 0
    estado = 0 si residuo == 0

Una sola muestra puede dar varias intervenciones, por eso se usa la division y no un if.

## 8. Pseudocodigo

### 8.1 Lectura y validacion

    leer n, m, q con scanf
    si scanf no leyo 3 valores -> ERROR
    si n no esta entre 1 y 20 -> ERROR
    si m no esta entre 1 y 8 -> ERROR
    si q no esta entre 1 y 9999 -> ERROR

    para i desde 0 hasta n-1:
        leer id, nombre_tmp, tipo, p
        si no se leyeron los 4 datos -> ERROR
        si id no esta entre 1 y 9999 -> ERROR
        si id ya aparecio en una unidad anterior -> ERROR
        si el largo de nombre_tmp no esta entre 1 y 15 -> ERROR
        si algun caracter del nombre no es letra, numero o '_' -> ERROR
        si tipo no es 0 ni 1 -> ERROR
        si p no esta entre 0 y 100 -> ERROR
        para j desde 0 hasta m-1:
            leer x
            si no se leyo -> ERROR
            si x no esta entre 0 y 100 -> ERROR
            guardar x en muestras[i][j]
        guardar id, nombre, tipo y p en unidades[i]

    intentar leer un token mas
    si se pudo leer -> ERROR (habia datos de sobra)

Cuando algo falla se imprime `ERROR`, se hace return 0 y no se imprime nada mas.

### 8.2 Calculo por unidad

    para i desde 0 hasta n-1:
        calcular(muestras[i], m, unidades[i].config.tipo, unidades[i].config.p,
                 &unidades[i].score, &unidades[i].estado)

### 8.3 Funcion calcular

    residuo = 0
    score = 0
    umbral = p + 1
    para cada muestra x:
        si tipo == 0: residuo += x
        si no: residuo += x * x
        score += residuo / umbral
        residuo = residuo % umbral
    *score = score
    si residuo != 0: *estado = 1
    si no: *estado = 0

### 8.4 Resultados individuales

    para i desde 0 hasta n-1 (orden original):
        imprimir id, score y estado

### 8.5 Total recursivo

    total_rec(unidades, n):
        si n == 0: devolver 0
        devolver unidades[n-1].score + total_rec(unidades, n-1)

    imprimir "TOTAL" y total_rec(unidades, n)

### 8.6 Ordenamiento para ORDER

    copiar unidades en ordenadas (asi no se pierde el orden original)
    ordenar(ordenadas, n):
        para i desde 0 hasta n-2:
            para j desde 0 hasta n-2-i:
                si ordenadas[j] debe ir despues de ordenadas[j+1]:
                    intercambiarlos
    "debe ir despues" significa:
        score de j menor que score de j+1, o
        scores iguales y id de j mayor que id de j+1

    imprimir "ORDER" y los id de ordenadas en ese orden

### 8.7 Busqueda binaria para FIND

    copiar unidades en por_id
    ordenar_por_id(por_id, n)    (id de menor a mayor)
    buscar(por_id, n, q):
        izq = 0, der = n-1
        mientras izq <= der:
            medio = (izq + der) / 2
            si por_id[medio].id == q: devolver su score
            si por_id[medio].id < q: izq = medio + 1
            si no: der = medio - 1
        devolver -1

    imprimir "FIND", q y el resultado de buscar

## 9. Prueba de escritorio (Grupo 1, MOTOR)

MOTOR: tipo 0, p = 40, umbral = 41, muestras 10 50 70 30 90.

| muestra | residuo antes de dividir | intervenciones (residuo/41) | score acumulado | residuo nuevo (residuo%41) |
|---|---|---|---|---|
| 10 | 10 | 0 | 0 | 10 |
| 50 | 60 | 1 | 1 | 19 |
| 70 | 89 | 2 | 3 | 7 |
| 30 | 37 | 0 | 3 | 37 |
| 90 | 127 | 3 | 6 | 4 |

Resultado: score 6, residuo 4, estado 1. Coincide con la salida del profesor (30 6 1).

VALVULA: tipo 1, p = 20, umbral = 21, muestras 20 25 10 80 5.

| muestra | x*x + residuo | intervenciones | score acumulado | residuo nuevo |
|---|---|---|---|---|
| 20 | 400 | 19 | 19 | 1 |
| 25 | 626 | 29 | 48 | 17 |
| 10 | 117 | 5 | 53 | 12 |
| 80 | 6412 | 305 | 358 | 7 |
| 5 | 32 | 1 | 359 | 11 |

Resultado: score 359, residuo 11, estado 1. Coincide con 10 359 1.