#include "columnas.h"
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include <string.h>
#include <iostream>

struct nodo_columna
{
    char *nombreCol;
    CalCol calCol;
    char *tipoCol;
    columna sig;
};

columna addColumna(bd &bd, char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificador)
{
    columna col = new (nodo_columna);
    strcpy(col->nombreCol, NombreCol);
    col->calCol = calificador;
    strcpy(col->tipoCol, tipoCol);
    return col;
}

char *nombreColumna(columna col)
{
    return col->nombreCol;
}

bool colRep(columna col, char *nombCol)
{
    columna iter = col;
    while(iter->sig != NULL)
    {
        if (strcmp(iter->nombreCol, nombCol)==0)
            return true;
        else
            iter = iter->sig;
    }
    return false;
}
 