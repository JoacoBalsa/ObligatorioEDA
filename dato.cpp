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
    cout << "Entro en insertar PK" << endl;
    dato iter = d;
    dato var = new (nodo_dato);
    int cont = 0;
    if (tipo == STRING){
        strcpy(var->caracter, valor);
    }
    else{
        var->entero = atoi(valor);
        cout << "Mi valor es " << var->entero << endl;
    }
    if (iter == NULL){
        iter = var;
        iter->abajo = NULL;
        iter->arriba = NULL;
        d = iter;
        cout << "entro aca" << endl;
        return 0;
    }
    while(iter->arriba != NULL)
        iter = iter->arriba;
    while(iter != NULL){
        if(iter->entero > var->entero || iter->abajo == NULL){ //|| (strcmp(iter->caracter, var->caracter)>0)){
            if(iter->arriba == NULL && iter->entero > var->entero){
                var->arriba = NULL;
                var->abajo = iter;
                iter->arriba = var;
                d = iter;
                cout << "arriba = NULL " << d->entero << endl;
                return cont;
            }
            else if(iter->abajo == NULL && iter->entero < var->entero){
                var->abajo = NULL;
                var->arriba = iter;
                iter->abajo = var;
                d = iter;
                cout << "abajo == NULL " << d->entero << endl;
                return cont+1;
            }
            else if ((iter->entero > var->entero)){//|| //(strcmp(iter->caracter, var->caracter)>0)){
                var->arriba = iter->arriba;
                var->abajo = iter;
                iter->arriba->abajo = var;
                iter->arriba= var;
                d = iter;
                cout << "el siguiente mayor que yo " << d->entero << endl;
                return cont;
            }
        }
        cont++;
        iter = iter->abajo;
    }
    return cont;
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

