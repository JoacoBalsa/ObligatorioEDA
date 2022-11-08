// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// dato.h
// Modulo de Definición de Base de Datos.
#ifndef DATO_H
#define DATO_H
#include <iostream>
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include "columnas.h"
#include <string.h>


typedef struct nodo_dato *dato;

//dato nuevoDato(columna &col);
//  Crea un nuevo dato (valor de columnaTupla)

//void insertarDato_d(dato datos, char *valorTupla);
// Inserta el dato en la columna.

int cantDato(dato d);
//  Retorna la cantidad de datos en la columna.

int insertarPK (dato &d, tipoDato Tipocol, char *valor);
// Inserta la PK y retorna la posicion en la que la inserto.

bool PK_repetida (dato d, tipoDato tipo, char *valor);
// devuelve true si el valor se repite en datos.


#endif