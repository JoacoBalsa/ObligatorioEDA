// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
// Trabajo Obligatorio
// dato.cpp
// Modulo de Implementación de Base de Datos.

#include <iostream>
#include "dato.h"
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include "columnas.h"
#include <string.h>

using namespace std;

#define MAX_DATO 30

struct nodo_dato
{
    tipoDato tipo;
    char caracter[MAX_DATO];
    int entero;
    dato arriba;
    dato abajo;                                                                                                                                                                                           
};

/*void insertarDato_d(columna col,dato datos, char *valorTupla){
    dato d = new(nodo_dato);
    dato iter = datos;
    if(datos != NULL) // Si ya hay datos va hasta el final de la lista
        while(iter->abajo!= NULL)
            iter = iter->abajo;
    if (tipo_dato(col) == INT)
        d->entero = atoi(valorTupla);
    else
      strcpy(d->caracter, valorTupla);
    iter->abajo = d;
    d->arriba = iter;
    d->abajo = NULL;
}*/

int insertarPK(dato &d, tipoDato tipo, char *valor){
    dato iter = d;
    dato var = new (nodo_dato);
    int cont = 0;
    if (tipo == STRING){
        strcpy(var->caracter, valor);
    }
    else{
        var->entero = atoi(valor);
    }
    if (iter == NULL){
        iter = var;
        iter->abajo = NULL;
        iter->arriba = NULL;
        d = iter;
        return 0;
    }
    while(iter->arriba != NULL)
        iter = iter->arriba;
    while(iter != NULL){
        (strcmp(iter->caracter, var->caracter)>0);
        if((iter->entero > var->entero || (strcmp(iter->caracter, var->caracter)>0))|| iter->abajo == NULL){
            if(iter->arriba == NULL && (iter->entero > var->entero || strcmp(iter->caracter, var->caracter)>0)){
                var->arriba = NULL;
                var->abajo = iter;
                iter->arriba = var;
                d = iter;
                return cont;
            }
            else if(iter->abajo == NULL && (iter->entero < var->entero || strcmp(iter->caracter, var->caracter) < 0)){
                var->abajo = NULL;
                var->arriba = iter;
                iter->abajo = var;
                d = iter;
                return cont+1;
            }
            else if (((iter->entero > var->entero)) || strcmp(iter->caracter, var->caracter)>0){
                var->arriba = iter->arriba;
                var->abajo = iter;
                iter->arriba->abajo = var;
                iter->arriba= var;
                d = iter;
                return cont;
            }
        }
        cont++;
        iter = iter->abajo;
    }
    return cont;
}

bool PK_repetida (dato d, tipoDato tipo, char *valor){
    dato iter = d;
    while(iter->arriba != NULL)
        iter = iter->arriba;
    while(iter != NULL){
        if(tipo == INT){
            if(iter->entero == atoi(valor))
                return true;
        }
        else{
            if(strcmp(iter->caracter, valor) == 0)
                return true;
        }
        iter = iter->abajo;
    }
    return false;
}

int cantDato (dato d){
    int cant = 0;
    if(d != NULL){
        dato iter = d;
        while(iter->arriba != NULL)
            iter=iter->arriba;
        while(iter != NULL){
            cant++;
            iter=iter->abajo;
        }
    }
    return cant;
}

