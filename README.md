# **PROGRAMA PARA MEDIR VELOCIDAD DE PROCESADOR**

## PARA COMPILAR

> Debe tener en cuenta que el programa esta elaborado en el lenguaje de programación C, y  por tanto debe ejecutar un compilador compatible con su maquina.
>Para compilar use el siguiente commando: **gcc main.c paralelismo.c -o concurrencia**

## PROCEDIMIENTO
>
> La idea es utilizar el programa que se provee para sacar datos estadisticos de la velocidad de procesamiento de diferentes maquinas, tanto para el proceso secuencial como el de concurrencia, corriendo el script en repetidas ocaciones para una misma operación, de la siguiente forma:

1. El equipo debe escoger una operación de las 9 que tiene el programa, para correrla en las tres maquinas. Las operaciones son:
    - a. Calcular la media de cada columna de la matriz A
    - b. Calcular la varianza de cada columna de la matriz A
    - c. Calcular la variación estandar de cada columna de la matriz A
    - d. Calcular el valor minimo y el valor maximo de cada columna de la matriz A
    - e. Calcular la suma de la matriz A con la matriz B
    - f. Calcular el producto punto de la matriz A con la matriz B
    - g. Calcular el producto de un escalar con la matriz A
    - h. Calcular la normalización (Opción 1) de las columnas de la matriz A
    - i. Calcular la normalización (Opción 2) de las columnas de la matriz A

2. El programa tiene la opción en el menu para correr cualquiera de las opciones anteriormente mencionadas, en forma de secuencia o a través de concurrencia. Esta ultima, indicando el número de hilos. La idea es implementar la misma opción del menu tanto para secuencia como para concurrencia.

3. Se debe correr la misma operación en las 3 computadoras, cuyos procesadores se desean evaluar.

4. Al correr la operación en forma de concurrencia, se debe seleccionar la misma cantidad de hilos para las 3 computadoras.

5. Se sugiere que por operación y modo de procesamiento se hagan minimo 5 repeticiones, cada una de ellas se guarde en una tabla para posteriormente juntarla con lo realizado por el resto del equipo. Se sugiere de igual forma que, dicho número sea el mismo para las 3 computadoras, de modo que se faciliten los calculos.

## **TABLA DE DATOS SUGERIDA**
>
> A continuación se ofrece la ilustración de una tabla que trata de explicar los datos finales que ha tomado el equipo, con cada maquina.

|            | PROCESADOR1 | PROCESADOR2 | PROCESADOR3 |
|------------|-------------|-------------|-------------|
|SECUENCIAL  | D1SPro1     | D1SPro2     | D1SPro3     |
|            | D2SPro1     | D2SPro2     | D2SPro3     |
|            | D3SPro1     | D3SPro2     | D3SPro3     |
|            | D4SPro1     | D4SPro2     | D4SPro3     |
|            | D5SPro1     | D5SPro2     | D5SPro3     |
|CONCURRENCIA| D1CPro1     | D1CPro2     | D1CPro3     |
|            | D2CPro1     | D2CPro2     | D2CPro3     |
|            | D3CPro1     | D3CPro2     | D3CPro3     |
|            | D4CPro1     | D4CPro2     | D4CPro3     |
|            | D5CPro1     | D5CPro2     | D5CPro3     |
