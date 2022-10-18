#ifndef TABLA_H
#define TABLA_H
#include "define.h"

typedef struct nodo_tabla *tabla;

TipoRet crearTabla(tabla &t, char *nombre);
//  Crea una tabla individual vacia con el nombre pasado por parametro.
//  Pre: la base de datos tiene que estar creada.

bool colRep_tabla(tabla t, char *nomCol);
// Retorna true si ya existe una columna con el nombre nomCol.

char *nombreTabla(tabla t);
//  Retorna el nombre de la tabla.

#endif