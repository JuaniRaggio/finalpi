## Final 13/12/24
---
### Qué debe contener un README?
---
## Autores:
Geronimo Naso Rodriguez - nro. de legajo: 64177 - gerorodriguez@itba.edu.ar
Ivonne Samanta Choe - nro. de legajo: 64880 - ichoe@itba.edu.ar
Juan Ignacio Garcia Vautrin Raggio - nro. de legajo: 63319 - jgarciavautrinraggi@itba.edu.ar

## Objetivo del proyecto: 
Este proyecto consiste en un programa que procesa las multas de estacionamiento de ciudades, que en este caso, fueron las de Chicago y Nueva York. 

Mediante el procesamiento y almacenamiento de datos, el programa se encarga de llevar a cabo las queries 1,2 y 3 recibiendo los datos a procesar en dos archivos distintos: tickets.csv y infractions.csv que corresponden a los datos de multas e infracciones respectivamente.

## Archivos

main.c
Lee, analiza y procesa los datos proporcionados mediante archivos csv para la realización de las queries 1, 2 y 3.

## Librerías
agencyTreeADT: 
Esta librería contiene funciones que permiten el manejo de los datos en un árbol binario (AVL).

diffTreeADT: COMPLETAR

errorManagement:
Esta librería contiene definiciones de macros y funciones auxiliares que permiten el manejo de errores en el programa.

formats:
Esta librería proporciona un conjunto de estructuras y configuraciones que permiten manejar los datos según el formato ofrecido por ciudad.

lib:
Esta librería cuenta con funciones auxiliares que fueron utilizadas a lo largo del programa.

processData:
Esta librería cuenta con funciones que se encargan de procesar y almacenar información relacionada con tickets e infracciones en las estructuras de datos correspondientes.

queries: COMPLETAR

readData:
Esta librería sirve para lectura de archivos CSVs y cuenta con funciones que permiten leer y procesar los datos proporcionados.

validIDADT:
Esta librería está diseñada para gestionar un conjunto de IDs relacionados con infracciones, donde cada ID tiene una descripción asociada. Permite almacenar, agregar, verificar y comparar IDs.

## Subdirectorios  CHECK
1. include
Subdirectorio que contiene archivos de encabezado que contiene las declaraciones necesarias para el funcionamiento del programa.

2. src
Subdirectorio que contiene los archivos de implementación del programa.

## Compilación

Para compilar, ejecutar el............

## Ejecución

Para la ejecución del programa, pasar 2 parámetros (en caso de querer modificar cantidad de parámetros, modificar la constante simbólica del main.c "EXPECTEDARGS"). Primero, el archivo .csv de multas y luego el archivo .csv de infracciones. Las funciones de lectura esperan que se pasen los parametros con los formatos acordes y que se utilicen los archivos con el formato correspondiente.

****Esta bien lo de la cant de parametros??? tengo q aclarar mas sobre la modificacion de parametros?? como agregar defines en el formats.h,etc??
**** CHECK!


- Lista de archivos fuente y de encabezado, con una breve explicación de cada uno ****
- Si existen subdirectorios, para qué sirve cada uno ***
- Comandos necesarios para compilar el proyecto
- Cómo ejecutar el programa, detallando los parámetros necesarios ***
- Autores del proyecto ---- **** 
- Opcionalmente información de contacto -- ****


