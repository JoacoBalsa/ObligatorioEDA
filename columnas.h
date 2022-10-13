#ifndef COLUMNAS_H
#define COLUMNAS_H
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include <string.h>
#include <iostream>

typedef struct nodo_columna *columna;

columna addColumna(bd &bd, char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificador);
//  Crea la columna vacia.

bool colRep(bd &bd, char *nomTab, char *nombCol);
//  Se fija que no haya otra columna con el nombre nomCol

#endif