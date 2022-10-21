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

void addColumnat (tabla &t,  char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificadorCol);
// Pasamanos para crear una columna.

void printDataTable_t (tabla &t, char *NombreTabla);
// Imprime las tuplas de la tabla de nombre: NombreTabla.

bool ExistePK_t(tabla t);
// Retorna true si en la tabla t hay una columna con PRIMARY_KEY.

bool esPK_t(tabla t, char *nombreTabla, char *nombreCol);
//  Retorna true si la columna en t es PRIMARY_KEY, false en caso contrario.

int cant_colT(tabla t,char *NombreTabla);
// Cuenta la cantidad de columnas de una tabla t.

void eliminarCol_t(tabla t, char *nombreCol);
//  Pasamanos para eliminar la columna nombreCol de la tabla t.

#endif