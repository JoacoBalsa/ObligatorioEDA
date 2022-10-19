#include "tabla.h"
#include "define.h"
#include "columnas.h"
#include <string.h>
#include <iostream>

using namespace std;

#define MAX_NOMBRE 20

struct nodo_tabla
{
    char nom[MAX_NOMBRE];
    columna col;
};

TipoRet crearTabla(tabla &t, char *nombre)
{
    if (t == NULL)
    {
        t = new (nodo_tabla);
        strcpy(t->nom, nombre); 
        t->col = NULL;       
        return OK;
    }
    else
    {
        cout << "No se puede sobreescribir la tabla" << endl;
        return ERROR;
    }
}

bool colRep_tabla(tabla t, char *nombCol)
{
    return colRep(t->col, nombCol);
}

char *nombreTabla(tabla t)
{
    return t->nom;
}

void addColumnat (tabla &t,  char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificadorCol){
    t->col = addColumnaCol(t->col, NombreCol, tipoCol, calificadorCol);
}
