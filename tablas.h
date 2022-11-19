#ifndef TABLAS_H
#define TABLAS_H

// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// tablas.h
// Modulo de Definición de Base de Datos.

#include "define.h"

typedef struct nodo_tablas *tablas;


TipoRet crearTablas(tablas &ts, char *nombreTabla);
//  Crea una tabla t con nombre nombreTabla dentro de tablas ts.

TipoRet eliminarTablas(tablas ts, char *nombre);
// Elimina la tabla nombre de la bd, devuelve error si no se pasa un nombre o si no existe esa tabla.
// Actualizar para tablas

tablas eliminar(tablas ts, char *nombreTabla);
// Elimina recusrivamente una tabla del arbol ts.

tablas max_izq(tablas &ts);

tablas min_der(tablas &ts);

int profundidad(tablas ts);
// Retorna la profundidad del arbol;

int max(int a, int b);
// Retorna el maximo de a y b. 

bool nombreTabla_Tablas(tablas ts, char *nombreTabla);
// Retorna True si hay una tabla nombreTabla en ts

bool colRep_ts(tablas ts, char *nombreTabla, char *nombCol);
//  Retorna true si la columna ya existe, false en caso contrario.

TipoRet imprimirTablas(tablas ts);
//  Imprime el nombre de la tablas.
//  Pre: Hay tablas para imprimir.

void addColumnats (tablas &ts, char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificadorCol);
//  Pasamanos, para crear columna.

void printDataTable_ts (tablas &ts, char *NombreTabla);
//  Pasamanos para el printdatatable.

bool ExistePK_ts(tablas ts, char *nombreTabla);
//  Pasamanos para fijarnos si existe una columna con PK en una tabla t.

bool esPK_ts(tablas ts, char *nombreTabla, char *nombreCol);
//  Retorna true si la el calificador de la columna que se le pasa es PRIMARY_KEY.

int cant_colTS(tablas ts, char *nombreTabla);
//  Retorna la cantidad de columnas que tiene una tabla.

void dropCol_ts(tablas ts, char *nombreTabla, char *nombreCol);
//  Pasamanos para eliminar la columna nombreCol de la tabla nombreTabla incluida en ts.

bool Tupla_validaTS (tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla);
// Pasamanos para fijarnos si una tupla es valida para insertar en la tabla nombreTabla, con columnas columnasTupla.

void insertarDato_ts(tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla);
// Pasamanos para insertar una tupla.

tablas buscar_tabla(tablas ts, char *nomTabla);
// Busca la tabla pasada por parametro en el arbol ts.

void eliminarTupla_ts(tablas &ts, char *nombreTabla, char *condicionEliminar);
// Pasamanos para eliminar tupla.

bool eliminarTupla_valida_ts(tablas ts,char *nombreTabla, char *condicionEliminar);
// Retorna true si la tupla es valida para poder eliminar.

void printMetadata_ts(tablas ts, char *nombreTabla);
// Pasamanos para printMetadata.

void select_ts(tablas &ts, char *nomTabla1, char *nomColumnas, char *nomTabla2 );

bool Columnas_pertenecen_TS(tablas ts, char *nomTabla1, char *nomColumnas);

#endif