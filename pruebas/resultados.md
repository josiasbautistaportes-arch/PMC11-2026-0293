# Resultados de las pruebas

Comando de compilacion:

    gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto

## 1. Casos publicos del profesor

Se corrieron con `py evaluar.py publicas.json reto.exe` y tambien con los archivos de `pruebas/publicas/` usando `diff`. Los seis dieron OK.

| Grupo | Que comprueba | Resultado |
|---|---|---|
| 1 | Calculo normal con tipo 0 y tipo 1 | OK |
| 2 | Minimos: todo en 0 | OK |
| 3 | Empates de score, gana el id menor | OK |
| 4 | m = 8 y valores extremos | OK |
| 5 | FIND ausente (-1) y reinicio del residuo entre unidades | OK |
| 6 | Muestra 101 fuera de rango, sale solo ERROR | OK |

Casos correctos: 6 / 6.

## 2. Casos propios

La salida esperada la calcule a mano antes de correr el programa. Despues se comparo con `diff` y no hubo diferencias.

### Propia 1: valida normal

Entrada (`pruebas/propias/propia1.in`):

    3 4 20
    20 BOMBA 0 9 5 5 5 5
    7 EJE 1 3 2 2 2 2
    15 FAJA 0 4 10 3 8 0

Esperado y obtenido (igual):

    20 2 0
    7 4 0
    15 4 1
    TOTAL 10
    ORDER 7 15 20
    FIND 20 2

Estado: correcto. Comprueba mezcla de tipo 0 y tipo 1, ids desordenados y un empate de score (EJE y FAJA, con 4), donde ORDER pone primero el id menor.

### Propia 2: valida de borde, con q ausente

Entrada (`pruebas/propias/propia2.in`):

    2 2 1
    9999 MAXIMO 1 0 100 100
    5 CERO_P 0 0 100 0

Esperado y obtenido (igual):

    9999 20000 0
    5 100 0
    TOTAL 20100
    ORDER 9999 5
    FIND 1 -1

Estado: correcto. Comprueba id 9999, p = 0 (umbral 1), x = 100, tipo 1 y un q que no existe (FIND da -1). Tambien un score de 20000 en un solo registro.

### Propia 3: invalida

Entrada (`pruebas/propias/propia3.in`):

    2 1 5
    5 A 0 10 3
    5 B 1 10 4

Esperado y obtenido (igual):

    ERROR

Estado: correcto. El id 5 esta repetido, y el programa imprime solo ERROR.

## 3. Traza manual contrastada (FAJA, propia 1)

FAJA: tipo 0, p = 4, umbral = 5, muestras 10 3 8 0.

| muestra | residuo antes de dividir | intervenciones (residuo/5) | score acumulado | residuo nuevo (residuo%5) |
|---|---|---|---|---|
| 10 | 10 | 2 | 2 | 0 |
| 3 | 3 | 0 | 2 | 3 |
| 8 | 11 | 2 | 4 | 1 |
| 0 | 1 | 0 | 4 | 1 |

Resultado a mano: score 4, residuo 1, estado 1. El programa imprimio `15 4 1`, igual que la traza.

## 4. Fallos encontrados

En las pruebas con los casos publicos y propios no hubo ningun fallo, asi que no hubo nada que corregir. La evidencia de revision es la traza manual de la seccion 3.