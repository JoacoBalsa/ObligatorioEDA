#include <tabla.h>
#include "define.h"
#include <string.h>

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
    //  columnas columna (implementar)
};

tabla crearTabla(char *nombre)
{
    //  Crea una tabla individual vacia con el nombre pasado por parametro.

    tabla t = new (nodo_tabla);
    t->nom = new char[MAX_NOMBRE];
    strcpy(t->nom, nombre);
    //  Columnas: debe implementarse
    return t;
}

// Capaz es auxiliar
char *nombreTabla(tabla t)
{
    return t->nom;
}
