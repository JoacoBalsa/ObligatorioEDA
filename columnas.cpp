#include "columnas.h"
#include "dato.h"
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include <string.h>
#include <iostream>

#define NOM 30

using namespace std;

struct nodo_columna
{
    char *nombreCol;
    CalCol calCol;
    tipoDato tipoCol;
    columna sig;
    columna ant;
    dato d;
};

columna addColumnaCol(columna col,char *NombreCol, char *tipoCol, CalCol calificador)
{
    /*if(col != NULL){
        while(col->ant != NULL) // Va al comienzo de las columnas.
            col = col->ant;
        while(col->calCol != ANY && col->sig != NULL) // Se fija si hay columnas no vacias.
            col = col->sig;
    }*/
    columna nuevaCol = new (nodo_columna);
    nuevaCol->nombreCol = new char[NOM];
    strcpy(nuevaCol->nombreCol, NombreCol);
    nuevaCol->calCol = calificador;
    if(strcmp(tipoCol, "string") == 0){
        nuevaCol->tipoCol = STRING;
    }else if(strcmp(tipoCol, "integer") == 0){
        nuevaCol->tipoCol = INT;
    }
    nuevaCol->sig = NULL;
    if(col == NULL){ // Si nuevaCol es la primera columna de la tabla.
        nuevaCol->ant = NULL;
       return nuevaCol;
    }
    else{ //Si ya hay columnas en la tabla. 
        columna iter = col;
        while(iter->sig != NULL)
            iter = iter->sig;
        iter->sig = nuevaCol;
        nuevaCol->ant = iter;
        return nuevaCol;
    }
}

char *nombreColumna(columna col)
{
    return col->nombreCol;
}

bool colRep(columna col, char *nombCol)
{
    if(col != NULL){
        columna iter = col;
        while(iter->ant != NULL)
            iter = iter->ant;
        while(iter != NULL)
        {
            if (strcmp(iter->nombreCol, nombCol)==0)
                return true;
            else
                iter = iter->sig;
        }
    }
   return false;
}

void imprimir_columnas (columna col){
    if(col != NULL){
        columna iter = col;
        while (iter->ant != NULL)// Va al principio de la lista de columnas
            iter = iter->ant;
        while(iter->sig != NULL){
            cout << iter->nombreCol << ":";
            iter = iter->sig;
        }
        cout << iter->nombreCol << endl;
    }
}

bool existe_PK(columna col){
    if(col != NULL){
        columna iter = col;
        while(iter->ant != NULL)
            iter = iter->ant;
        while(iter != NULL){
            if(iter->calCol == PRIMARY_KEY)
                return true;
            else
                iter = iter->sig;
        }
    }
    return false;
}
 