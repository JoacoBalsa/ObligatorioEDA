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

void crearTabla(tabla &t, char *nombre)
{
    if (t == NULL)
    {
        t = new (nodo_tabla);
        strcpy(t->nom, nombre); 
        t->col = NULL;       
    }
}

bool colRep_tabla(tabla t, char *nombCol)
{
    return colRep(t->col, nombCol);
}

char *nombreT(tabla t)
{
    return t->nom;
}

void addColumnat (tabla &t, char *NombreCol, char *tipoCol, CalCol calificadorCol){
    t->col = addColumnaCol(t->col, NombreCol, tipoCol, calificadorCol);
}

void printDataTable_t (tabla &t, char *NombreTabla){
    cout << NombreTabla << endl;
    imprimir_columnas (t->col);
    imprimir_tuplasCol(t->col);
}

bool ExistePK_t(tabla t)
{
    return existe_PK(t->col);
}

bool esPK_t(tabla t, char *nombreCol){
	return esPK_col(t->col, nombreCol);
}

int cant_colT(tabla t){
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

void eliminarTupla_t(tabla t, char *condicionEliminar){
    eliminarTupla_col(t->col, condicionEliminar);
}

bool eliminarTupla_valida_t(tabla t, char *condicionEliminar){
    if(t->col != NULL)
        return eliminarTupla_valida(t->col, condicionEliminar);
    else
        return false;
}