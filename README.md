## Final 13/12/24

## Objetivo del proyecto: 
Este proyecto consiste en un programa que procesa las multas de estacionamiento de ciudades, que en este caso, fueron las de Chicago y Nueva York. 

Mediante el procesamiento y almacenamiento de datos, el programa se encarga de llevar a cabo las queries 1,2 y 3 recibiendo los datos a procesar en dos archivos distintos: tickets.csv y infractions.csv que corresponden a los datos de multas e infracciones respectivamente.

## Archivos
main.c
Lee, analiza y procesa los datos proporcionados mediante archivos csv para la realización de las queries 1, 2 y 3.

## Librerías
1. agencyTreeADT: 
Esta librería contiene funciones que permiten el manejo de los datos en un árbol binario (AVL).

2. errorManagement:
Esta librería contiene definiciones de macros y funciones auxiliares que permiten el manejo de errores en el programa.

3. formats:
Esta librería proporciona un conjunto de estructuras y configuraciones que permiten manejar los datos según el formato ofrecido por ciudad.

4. genericStackADT.h:
Esta libreria contiene funciones basicas de un stack generico, utilizado para recorrer los arboles binarios de forma iterariva.

5. lib:
Esta librería cuenta con funciones auxiliares que fueron utilizadas a lo largo del programa.

6. processData:
Esta librería cuenta con funciones que se encargan de procesar y almacenar información relacionada con tickets e infracciones en las estructuras de datos correspondientes.

7. readData:
Esta librería sirve para lectura de archivos CSVs y cuenta con funciones que permiten leer y procesar los datos proporcionados.

8. runAllQueries:
Esta libreria se encarga de ejecutar las queries.

9. validIDADT:
Esta librería está diseñada para gestionar un conjunto de IDs relacionados con infracciones, donde cada ID tiene una descripción asociada. Permite almacenar, agregar, verificar y comparar IDs.

## Subdirectorios 
1. include
Subdirectorio que contiene archivos de encabezado que contiene las declaraciones necesarias para el funcionamiento del programa.

2. src
Subdirectorio que contiene los archivos de implementación del programa.

## Compilación
Para compilar el programa, usar el comando 'make' especificando el formato de ciudad:
make FORMAT=CHI para el formato de Chicago.
make FORMAT=NYC para el formato de Nueva York.

## Ejecución
Para la ejecución del programa utilizar el comando ./nombreDelEjecutable tickets.csv infractions.csv, donde tickets.csv contiene información de multas y infractions.csv contiene información de infracciones (en caso de querer modificar cantidad de parámetros, modificar la constante simbólica del main.c "EXPECTEDARGS"). Las funciones de lectura esperan que se pasen los parametros con los formatos acordes y que se utilicen los archivos con el formato correspondiente.

## Autores:
Geronimo Naso Rodriguez - nro. de legajo: 64177 - gerorodriguez@itba.edu.ar
Ivonne Samanta Choe - nro. de legajo: 64880 - ichoe@itba.edu.ar
Juan Ignacio Garcia Vautrin Raggio - nro. de legajo: 63319 - jgarciavautrinraggi@itba.edu.ar

