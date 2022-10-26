#ifndef COLUMNAS_H
#define COLUMNAS_H
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include "dato.h"
#include <string.h>
#include <iostream>

typedef struct nodo_columna *columna;

columna addColumnaCol(columna col, char *NombreCol, char *tipoCol, CalCol calificador);
//  Añade una columna vacia al final de la tabla. 

char *nombreColumna(columna col);
//  Retorna el nombre de columna.

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

bool tupla_valida_para_columna (columna col, char *column, char *valor);
// Retorna true si el nombre de col fue pasado en columnasTupla y en caso de que no haya sido pasado, que tipocol de col sea ANY, sino retorna false.

void insertarDato_col(columna &col, char *columnasTupla, char *valoresTupla);
// Inserta un dato en cada columna formando asi una tupla.

bool pasan_col(columna col, char *column);
// Retorna true si el nombre de la columna col coincide con column.

#endif