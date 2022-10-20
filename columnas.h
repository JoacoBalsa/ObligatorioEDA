#ifndef COLUMNAS_H
#define COLUMNAS_H
#include "define.h"
#include "bd.h"
#include "tabla.h"
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

#endif