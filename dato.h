#ifndef DATO_H
#define DATO_H
// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// dato.h
// Modulo de Definición de Base de Datos.
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include "columnas.h"
#include <string.h>
#include <iostream>

typedef struct nodo_dato *dato;

//dato nuevoDato(columna &col);
//  Crea un nuevo dato (valor de columnaTupla)

void insertarDato_d(columna col, dato datos, char *valorTupla);
// Inserta el dato en la columna.

#endif