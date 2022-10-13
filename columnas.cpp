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
    //  Crea la columna vacia.
    columna col = new (nodo_columna);
    strcpy(col->nombreCol, NombreCol);
    col->calCol = calificador;
    strcpy(col->tipoCol, tipoCol);
}

 