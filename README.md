# **PROGRAMA PARA MEDIR VELOCIDAD DE PROCESADOR**

## PARA COMPILAR

> Debe tener en cuenta que el programa esta elaborado en el lenguaje de programación C, y  por tanto debe ejecutar un compilador compatible con su maquina.
>Para compilar use el siguiente commando: **gcc main.c paralelismo.c -o concurrencia**

## PROCEDIMIENTO
>
> La idea es utilizar el programa que se provee para sacar datos estadisticos de la velocidad de procesamiento de diferentes maquinas, tanto para el proceso secuencial como el de concurrencia, corriendo el script en repetidas ocaciones para una misma operación, de la siguiente forma:

1. El equipo debe escoger una operación de las 9 que tiene el programa, para correrla en las tres maquinas. Las operaciones son:
    - [ ] Calcular la media de cada columna de la matriz A
    - [ ] Calcular la varianza de cada columna de la matriz A
    - [ ] Calcular la variación estandar de cada columna de la matriz A
    - [ ] Calcular el valor minimo y el valor maximo de cada columna de la matriz A
    - [ ] Calcular la suma de la matriz A con la matriz B
    - [ ] Calcular el producto punto de la matriz A con la matriz B
    - [ ] Calcular el producto de un escalar con la matriz A
    - [ ] Calcular la normalización (Opción 1) de las columnas de la matriz A
    - [ ] Calcular la normalización (Opción 2) de las columnas de la matriz A

2. El programa tiene la opción en el menu para correr cualquiera de las opciones anteriormente mencionadas, en forma de secuencia o a través de concurrencia. Esta ultima, indicando el número de hilos. La idea es implementar la misma opción del menu tanto para secuencia como para concurrencia.

3. Se debe correr la misma operación en las 3 computadoras, cuyos procesadores se desean evaluar.

4. Al correr la operación en forma de concurrencia, se debe seleccionar la misma cantidad de hilos para las 3 computadoras.

5. Se sugiere que por operación y modo de procesamiento se hagan minimo 5 repeticiones, cada una de ellas se guarde en una tabla para posteriormente juntarla con lo realizado por el resto del equipo. Se sugiere de igual forma que, dicho número sea el mismo para las 3 computadoras, de modo que se faciliten los calculos.

## **TABLA DE DATOS SUGERIDA**
>
> A continuación se ofrece la ilustración de una tabla que trata de explicar los datos finales que ha tomado el equipo, con cada maquina.

<table>
    <thead>
        <tr>
            <th>TIPO PROCESADO 1</th>
            <th>PROCESADOR 1</th>
            <th>PROCESADOR 2</th>
            <th>PROCESADOR 3</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan=5 align="center">SECUENCIAL</td>
            <td align="left">Tm1SePr1</td>
            <td align="left">Tm1SePr2</td>
            <td align="left">Tm1SePr3</td>
        </tr>
        <tr>
            <td align="left">Tm2SePr1</td>
            <td align="left">Tm2SePr2</td>
            <td align="left">Tm2SePr3</td>            
        </tr>
        <tr>
            <td align="left">Tm3SePr1</td>
            <td align="left">Tm3SePr2</td>
            <td align="left">Tm3SePr3</td> 
        </tr>
        <tr>
            <td align="left">Tm4SePr1</td>
            <td align="left">Tm4SePr2</td>
            <td align="left">Tm4SePr3</td> 
        </tr>
                    <tr>
            <td align="left">Tm5SePr1</td>
            <td align="left">Tm5SePr2</td>
            <td align="left">Tm5SePr3</td> 
        </tr>
                <tr>
            <td rowspan=5 align="center">CONCURRENCIA</td>
            <td align="left">Tm1CoPr1</td>
            <td align="left">Tm1CoPr2</td>
            <td align="left">Tm1CoPr3</td>
        </tr>
        <tr>
            <td align="left">Tm2CoPr1</td>
            <td align="left">Tm2CoPr2</td>
            <td align="left">Tm2CoPr3</td>
        </tr>
        <tr>
            <td align="left">Tm3CoPr1</td>
            <td align="left">Tm3CoPr2</td>
            <td align="left">Tm3CoPr3</td>
        </tr>
        <tr>
            <td align="left">Tm4CoPr1</td>
            <td align="left">Tm4CoPr2</td>
            <td align="left">Tm4CoPr3</td>
        </tr>
                    <tr>
            <td align="left">Tm5CoPr1</td>
            <td align="left">Tm5CoPr2</td>
            <td align="left">Tm5CoPr3</td>
        </tr>
    </tbody>
</table>
