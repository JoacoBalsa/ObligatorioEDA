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
    tablas izq;
    tablas der;
};

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

bool nombreExistente(tablas ts, char *nombre)
{
    // Retorna true si ya hay una tabla con ese nombre en la base de datos y false en caso contrario.
    if (ts == NULL)
        return false;
    else
    {
        if (strcmp(ts->t->nom, nombre) == 0)
            return true;
        else
            return nombreExistente(ts->sig, nombre);
    }
}*/
