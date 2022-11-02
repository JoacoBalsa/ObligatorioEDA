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
    int cont = 1;
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
        if(iter->entero > var->entero || iter->abajo == NULL || (strcmp(iter->caracter, var->caracter)>0)){
            if(iter->arriba == NULL && iter->entero > var->entero){
                var->arriba = NULL;
                var->abajo = iter;
                iter->arriba = var;
                d = iter;
                cout << "arriba = NULL " << d->entero << endl;
                return 0;
            }
            else if(iter->abajo == NULL && iter->entero < var->entero){
                var->abajo = NULL;
                var->arriba = iter;
                iter->abajo = var;
                d = iter;
                cout << "abajo == NULL " << d->entero << endl; 
                return cont;
            }
            else if ((iter->entero > var->entero) || (strcmp(iter->caracter, var->caracter)>0)){
                var->arriba = iter->arriba;
                var->abajo = iter;
                iter->arriba= var;
                d = iter;
                cout << "el siguiente mayor que yo " << d->entero << endl; 
                return cont;
            }
        }
        cont++;
        iter = iter->abajo;
    }

}

int cantDato (dato d){
    while(d->arriba!=NULL)
        d=d->arriba;
    int cant = 0;
    while(d!=NULL){
        cant++;
        d=d->abajo;
    }
    return cant;
}

