#ifndef COLUMNAS_H
#define COLUMNAS_H

// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// columnas.h
// Modulo de Definición de Base de Datos.

#include "define.h"
#include "bd.h"
#include "tabla.h"
#include "dato.h"
#include <string.h>
#include <iostream>

typedef struct nodo_columna *columna;

columna addColumnaCol(columna col, char *NombreCol, char *tipoCol, CalCol calificador);
//  Añade una columna vacia al final de la tabla. 

bool colRep(columna col, char *nombCol);
//  Retorna true si la columna existe, false en caso contrario.

void imprimir_columnas (columna col);
// Imprime las columnas de una tabla separadas por :

bool existe_PK(columna col);
// Retorna true si ya hay alguna columna con PRIMARY_KEY dentro de una tabla desde la cual se le pasan las columnas.

bool esPK_col(columna col, char *nombreCol);
//  Dada una columna de nombre: nombreCol, retorna true si es PRIMARY_KEY, false en caso contrario.
//  Pre: columna no es vacia.

int cant_col(columna col);
// Cuenta la cantidad de columnas de una tabla.

columna eliminarCol(columna col, char *nombreCol);
// Elimina una columna de nombre: nombreCol y sus datos.
// Pre: la columna a eliminar debe existir, fijarse antes en bd.

bool Tupla_valida(columna col, char *columnasTupla, char *valoresTupla);
// Se fija si en la columna col se puede agregar la tupla de valores valoresTupla. retorna true en caso de que si y false en caso contrario.

bool tupla_valida_para_columna (columna col, char *columnasTupla);
// Retorna true si el nombre de col fue pasado en columnasTupla y en caso de que no haya sido pasado, que tipocol de col sea ANY, sino retorna false.

void insertarDato_col(columna &col, char *columnasTupla, char *valoresTupla);
// Inserta un dato en cada columna formando asi una tupla.

bool cantCol_igual_cantVal (char *columnasTupla, char *valoresTupla);
// Retorna true si la cantidad de columnas de columnasTupla es igual a la cantidad de valores de valoresTupla.

bool valor_PK (columna col, char *columnasTupla);
// Retorna true, si se paso en columnasTupla la columna PRIMARY_KEY de col.

tipoDato tipo_dato(columna col);
//  Retorna el tipoDato de la columna.

bool PasanCol(columna col, char *columnas);
//  Retorna true si el nombre de col fue pasado en columnasTupla.

int insertarPK_col(columna &col, char *columnasTupla, char *valoresTupla);
// Inserta los datos de la PK de la columna col.

bool PK_repetidacol(columna col, char *columnasTupla, char *valoresTupla);
// Retorna true el valor de valoresTupla para la col PK esta repetido dentro de col.

void Valor_dato_col(columna &col,int  pos, char *columnasTupla, char *valoresTupla, bool Hay_valor);
// Encuentra el dato de la columna col y lo inserta;

void imprimir_tuplasCol(columna col);
// Imprime los datos de las columnas col.

void eliminarTupla_col(columna &col, char *condicionEliminar, char *operador);
// Elimina todas las tuplas de una tabla que cumplan con la condición pasada por parametro.

void buscar_operador(char *operador, char *condicionEliminar);
// Se asume que en condicionEliminar hay un operador valido.
// Si se quiere eliminar todas las tuplas hay que pasar por parametro un # en vez de "".

bool eliminarTupla_valida(columna col, char *condicionEliminar);
// Se fija si es valido eliminar la columna.

void printMetadata_col(columna col);
// Imprime el esquema de una tabla.

bool Existe_col (columna col, char *Columnas);
// Se fija que en columnas no haya columnas de mas.

bool Columnas_pertenecen(columna col, char *nomColumnas);

void select(columna T1col, columna &T2col, char *nomColumnas);

columna CopyCol(columna col1, columna col2);
// Copia la columna 1 a la columna 2.

void selectwhere(columna col1, columna &col2, char *condicion);

void OperadorOpuesto(char *operador);
// Cambia el operador a su opuesto si operador = < lo cambia a >.

char *nombreColumna(columna col);
//  Retorna el nombre de columna.

CalCol califCol(columna col);
//  Retorna el calificador de la columna.

tipoDato tipCol(columna col);
//  Retorna el tipo de dato de la columna.

columna columnaInicialCol (columna col);
//  Mueve el puntero de la columna desde donde esta hacia el inicio de las columnas.
//  Fin de pasamanos desde tablas.

columna avanzarCol(columna col);
//  Avanza la columna a la siguiente.

bool hayColumnas(columna col);
//  Retorna true si hay mas columnas, false en caso contrario.

#endif