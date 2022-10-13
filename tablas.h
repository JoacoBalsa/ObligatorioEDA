#ifndef TABLAS_H
#define TABLAS_H
#include "define.h"

typedef struct nodo_tablas *tablas;

tablas crearTabla(char *nombre);
// Crea una tabla vacia.

bool nombreExistente(tablas ts, char *nombre);
// Retorna true si ya hay una tabla con ese nombre en la base de datos y false en caso contrario.

#endif