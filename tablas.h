#ifndef TABLAS_H
#define TABLAS_H
#include "define.h"

typedef struct nodo_tablas *tablas;


TipoRet crearTablas(tablas &ts, char *nombreTabla);
//  Crea una tabla t con nombre nombreTabla dentro de tablas ts.

TipoRet eliminarTablas(tablas ts, char *nombre);
// Elimina la tabla nombre de la bd, devuelve error si no se pasa un nombre o si no existe esa tabla.

char *nombreTabla_Tablas(tablas ts);
//  Busca en una tabla t dentro de ts y retorna su nombre.

bool colRep_ts(tablas ts, char *nombCol);
//  Retorna true si la columna ya existe, false en caso contrario.

TipoRet imprimirTablas(tablas ts);
// Imprime el nombre de la tabla (momentaneo ya que solo hay una).
// Pre: Hay tablas para imprimir.

void addColumnats (tablas &ts, char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificadorCol);
// Pasamanos, para crear columna.

void printDataTable_ts (tablas &ts, char *NombreTabla);
// Pasamanos para el printdatatable.

bool ExistePK_ts(tablas ts);
// Pasamanos para fijarnos si existe una columna con PK en una tabla t.


#endif