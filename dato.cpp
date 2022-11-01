// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
// Trabajo Obligatorio
// dato.cpp
// Modulo de Implementación de Base de Datos.

#include <iostream>
#include "dato.h"
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include "columnas.h"
#include <string.h>


#define MAX_DATO 30

struct nodo_dato
{
    tipoDato tipo;
    char caracter[MAX_DATO];
    int entero;
    dato arriba;
    dato abajo;                                                                                                                                                                                           
};

void insertarDato_d(columna col,dato datos, char *valorTupla){
    dato d = new(nodo_dato);
    dato iter = datos;
    if(datos != NULL) // Si ya hay datos va hasta el final de la lista
        while(iter->abajo!= NULL)
            iter = iter->abajo;
    if (tipo_dato(col) == INT)
        d->entero = atoi(valorTupla);
    else
      strcpy(d->caracter, valorTupla);
    iter->abajo = d;
    d->arriba = iter;
    d->abajo = NULL;
}

