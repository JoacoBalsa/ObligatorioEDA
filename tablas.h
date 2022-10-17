#ifndef TABLAS_H
#define TABLAS_H
#include "define.h"

typedef struct nodo_tablas *tablas;

void crearTablas(tablas &ts, char *nombreTabla);
//Se mete a ts y crea una tabla t

char *nombreTabla_Tablas(tablas ts);
//Busca en una tabla t dentro de ts y retorna su nombre

bool colRep_ts(tablas ts, char *nombCol);
#endif