#include "columnas.h"
#include "dato.h"
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include <string.h>
#include <iostream>

#define NUM 30

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
    if(col != NULL){
        while(col->ant != NULL) // Va al comienzo de las columnas.
            col = col->ant;
        while(col->calCol != ANY && col->sig != NULL) // Se fija si hay columnas no vacias.
            col = col->sig;
    }
    cout << "error 1" << endl;
    //if(col->d == NULL){
        columna nuevaCol = new (nodo_columna);
        //nuevaCol->nombreCol = new(char);
        nuevaCol->nombreCol = new char[NUM];
        cout << "error 2" << endl;
        strcpy(nuevaCol->nombreCol, NombreCol);
        cout << "error 3" << endl;
        nuevaCol->calCol = calificador;
        cout << "error 4" << endl;
        if(tipoCol == "string"){
            nuevaCol->tipoCol = STRING;
            cout << "error 4.string" << endl;
        }else if(tipoCol == "integer"){
            nuevaCol->tipoCol = INT;
            cout << "error 4.integer" << endl;
        }else{
            cout << "tipoCol incorrecto" << endl;
        }
        nuevaCol->sig = NULL;
        cout << "error 5" << endl;
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
    //}
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
        while(iter->sig != NULL)
        {
            if (strcmp(iter->nombreCol, nombCol)==0)
                return true;
            else
                iter = iter->sig;
        }
    }
   return false;
}
 