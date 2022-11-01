// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
// Trabajo Obligatorio
// tabla.cpp
// Modulo de Implementación de Base de Datos.

#include <iostream>
#include "tabla.h"
#include "define.h"
#include "columnas.h"
#include <string.h>


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

void printDataTable_t (tabla &t, char *NombreTabla){
    cout << NombreTabla << endl;
    imprimir_columnas (t->col);
}

bool ExistePK_t(tabla t)
{
    return existe_PK(t->col);
}

bool esPK_t(tabla t, char *nombreTabla, char *nombreCol){
	return esPK_col(t->col, nombreCol);
}

int cant_colT(tabla t,char *NombreTabla){
    return cant_col(t->col);
}

void eliminarCol_t(tabla t, char *nombreCol){
    t->col = eliminarCol(t->col, nombreCol);
}

bool Tupla_validaT(tabla &t, char *columnasTupla, char *valoresTupla){
    if(t->col != NULL){
        if(existe_PK(t->col))
            return Tupla_valida(t->col, columnasTupla, valoresTupla);
        else{
            cout << t->nom << " No tiene ninguna columna PRIMARY_KEY" << endl;
            return false;
        }
    }
    else{
        cout << "No hay columnas en la tabla " << t->nom << endl;
        return false;
    }
}

void insertarDato_t(tabla &t, char *columnasTupla, char *valoresTupla){
    insertarDato_col(t->col, columnasTupla, valoresTupla);
}