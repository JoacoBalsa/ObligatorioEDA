#ifndef TABLA_H
#define TABLA_H

// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// tabla.h
// Modulo de Definición de Base de Datos.

#include "define.h"

typedef struct nodo_tabla *tabla;

void crearTabla(tabla &t, char *nombre); 
//  Crea una tabla individual vacia con el nombre pasado por parametro.
//  Pre: la base de datos tiene que estar creada.

bool colRep_tabla(tabla t, char *nomCol);
// Retorna true si ya existe una columna con el nombre nomCol.

char *nombreT(tabla t);
//  Retorna el nombre de la tabla.

void addColumnat (tabla &t, char *NombreCol, char *tipoCol, CalCol calificadorCol);
// Pasamanos para crear una columna.

void printDataTable_t (tabla &t, char *NombreTabla);
// Imprime las tuplas de la tabla de nombre: NombreTabla.

bool ExistePK_t(tabla t);
// Retorna true si en la tabla t hay una columna con PRIMARY_KEY.

bool esPK_t(tabla t, char *nombreCol);
//  Retorna true si la columna en t es PRIMARY_KEY, false en caso contrario.

int cant_colT(tabla t);
// Cuenta la cantidad de columnas de una tabla t.

void eliminarCol_t(tabla t, char *nombreCol);
//  Pasamanos para eliminar la columna nombreCol de la tabla t.

bool Tupla_validaT(tabla &t, char *columnasTupla, char *valoresTupla);
// Pasamanos para fijarnos si en tabla t se puede agragar la tupla con valoresTupla.

void insertarDato_t(tabla &t, char *columnasTupla, char *valoresTupla);
// Pasamanos para insertar una tupla.

void eliminarTupla_t(tabla &t, char *condicionEliminar);
// Pasamanos para eliminar tupla.

bool eliminarTupla_valida_t(tabla t, char *condicionEliminar);
// Pasamanos para eliminarTupla_valida.

void printMetadata_t(tabla t);
// Imprime el esquema de una tabla.

bool Columnas_pertenecen_T(tabla t, char *nomColumnas);

void select_t(tabla T1, tabla &T2, char *nomColumnas);

void selectwhere_t(tabla T1, tabla &T2, char *condicion);

bool mismoEsquemaT(tabla t,char *nombreTabla1, char *nombreTabla2);

char *nombreColumnaT(tabla t);
//  Pasamanos que retorna el nombre de la columna de la tabla.

CalCol califColT(tabla t);
//  Pasamanos que retorna el calificador de la columna de la tabla.

tipoDato tipColT(tabla t);
//  Pasamanos que retorna el tipo de dato de la columna de la tabla.

tabla columnaInicialT(tabla &t);
//  Pasamanos para mover la columna de la tabla t a la columna inicial.

tabla avanzarColT(tabla &t);
//  Pasamanos para avanzar una sola columna.

bool hayColumnasT(tabla t);
//  Retorna true si hay columnas en la tabla t, false en caso contrario (Usada para saber si llegue al final de columnas).

#endif