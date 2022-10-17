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
    return col;
}

char *nombreColumna(columna col){
//  Retorna el nombre de columna
    return col->nombreCol;
}

bool colRep(columna col, char *nombCol){
//  Retorna true si la columna existe, false en caso contrario.
    columna iter = col;
    while(iter->sig != NULL){
        if (strcmp(iter->nombreCol, nombCol)==0)
            return true;
        else{
            iter = iter->sig;
        }
    }
    return false;
}
 