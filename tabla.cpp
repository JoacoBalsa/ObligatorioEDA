#include "tabla.h"
#include "define.h"
#include "columnas.h"
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

struct nodo_tabla
{
    char *nom;
    columna col;
};

TipoRet crearTabla(tabla &t, char *nombre)
{
    //  Crea una tabla individual vacia con el nombre pasado por parametro.
    //  Pre: la base de datos tiene que estar creada.
    if (t == NULL)
    {
        t = new (nodo_tabla);
        strcpy(t->nom, nombre);
        return OK;
    }
    else
    {
        cout << "No se puede sobreescribir la tabla" << endl;
        return ERROR;
    }
}

bool colRep_tabla(tabla t, char *nombCol){
    return colRep(t->col, nombCol);
}

// Capaz es auxiliar
char *nombreTabla(tabla t)
{
    return t->nom;
}

