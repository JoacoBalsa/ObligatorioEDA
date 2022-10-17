#include "tabla.h"
#include "tablas.h"
#include "define.h"
#include <string.h>
#include <iostream>

using namespace std;

#define MAX_NOMBRE 20

/*
    GUIA IMPLEMENTACION DE TABLAS

- Crear Tabla : createTable
- Eliminar Tabla: dropTable

- Listar Tabla: printDataTable
- Listar Esquema: printMetadata

*/
struct nodo_tablas
{
    tabla t;
    /*tablas izq;
    tablas der;*/
};

void crearTablas(tablas &ts, char *nombreTabla){
    crearTabla(ts->t, nombreTabla);
}

char *nombreTabla_Tablas(tablas ts){
    return nombreTabla(ts->t);
}

bool colRep_ts(tablas ts, char *nombCol){
    return colRep_tabla(ts->t, nombCol);
}

/*TipoRet crearTablas(tablas &ts, char *nombre)
// Crea una tabla y la conecta con las anteriores.
{
    if (!nombreExistente(ts, nombre)) // Funcion a implementar
    {
        tablas iter = ts;
        while (iter->t != NULL) // Para insertar la tabla al final
        {
            iter = iter->sig;
        }
        crearTabla(iter->t, nombre);
        return OK;
    }
    else
    {
        cout << "Nombre de tabla ya existente" << endl;
        return ERROR;
    }
}


}*/
