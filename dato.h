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

void insertarDato(dato &d, tipoDato tipo, int pos, char *valor, bool Hay_valor);
// Inserta el dato dependiendo del tipo, en caso de que no haya valor inserta EMPTY.

void imprimir_tuplas(dato d, int pos);
// Imprime las tuplas de una tabla

void imprimir_datos(dato d);

void imprimirPK(dato d, int pos);

void deleteDatos(dato &d);
//Elimina todos los datos de una columna.

int posicion_tupla(dato d, char *valor, char *operador);
// Devuelve la posicion de la tupla a eliminar en caso de no haber ninguna retorna -1.

void eliminarTupla(dato &d, int pos);
// Elimina la tupla en la posicion pos.

#endif