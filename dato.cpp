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

void insertarDato(dato &d, tipoDato tipo, int pos, char *valor, bool empty){
    dato iter  = d;
    int aux = 0;
    dato var = new (nodo_dato);
    if (tipo == STRING || empty)
        if(!empty)
            strcpy(var->caracter, valor);
        else
            strcpy(var->caracter, "EMPTY");
    else
        var->entero = atoi(valor);
    while(iter->arriba != NULL)
        iter = iter->arriba;
    if(pos == 0){
        var->arriba = NULL;
        var->abajo = iter;
        iter->arriba = var;
    }
    else if(pos == cantDato(d)){
        while(iter->abajo != NULL)
            iter = iter->abajo;
        var->abajo = NULL;
        var->arriba = iter;
        iter->abajo = var;
    }
    else {
        while(aux != pos){
            aux++;
            iter = iter->abajo;
        }
        var->arriba = iter;
        var->abajo = iter->abajo;
        iter->abajo = var;
    }
    d = iter;
    cout << "hola iegue" << endl;
}

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

