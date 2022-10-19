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

#endif