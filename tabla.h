#ifndef TABLA_H
#define TABLA_H
#include "define.h"

typedef struct nodo_tabla *tabla;

TipoRet crearTabla(tabla &t, char *nombre);
//  Crea una tabla vacia.

char *nombreTabla(tabla t);
//  Retorna el nombre de la tabla.

bool colRep_tabla(tabla t, char *nomCol);


#endif