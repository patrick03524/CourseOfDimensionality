# Práctica de Laboratorio: Estructura del OctTree

Universidad Católica San Pablo

Alumno: Patrick Xavier Márquez Choque

## Introducción

Código desarrollado en C++ de la estructura OctTree

La siguiente estructura de la Estructura OctTree define en primer lugar un nodo raíz(Cada nodo tendrá 8 Nodos Hijos de los cuales).

Para explicar con más detalle como se ha implementado es necesario explicarlo con un ejemplo.

Podemos definir un OctTree de dimensiones (0,0,0) - (4,4,4)

Grafica sería el siguiente cubo con 3 dimensiones *x*, *y* y *z*

Ejemplo: (0,0,0) - (4,4,4)

root -> [(0,0,0),(4,4,4)]

a0 ->[(0,2,0),(2,4,2)] -> Cuadrante "0"

a1 ->[(2,2,0),(4,4,2)] -> Cuadrante "1"

a2 ->[(0,0,0),(2,2,2)] -> Cuadrante "2"

a3 ->[(2,0,0),(4,2,2)] -> Cuadrante "3"

a4 ->[(0,0,2),(2,2,4)] -> Cuadrante "4"

a5 ->[(2,0,2),(4,2,4)] -> Cuadrante "5"

a6 ->[(0,2,2),(2,4,4)] -> Cuadrante "6"

a7 ->[(2,2,2),(4,4,4)] -> Cuadrante "7"

![Alt text](https://github.com/patrick03524/CourseOfDimensionality/blob/master/Laboratorio%20OctTree/Source/Imgs/cubo_sin_fondo.png)

Cada zona tiene un color diferente y en primer lugar se organizaron 8 octantes desde a0,a1,a2,...a7 

Y a su vez cada cuadrante tendrá 8 nodos de tamaño (1,1,1) que representará un nodo con la menor dimensión posible: 1x1x1 px
