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

void insertarDato(dato &d, tipoDato tipo, int pos, char *valor, bool Hay_valor){
    dato iter  = d;
    int aux = 0;
    dato var = new (nodo_dato);
    var->tipo = tipo;
    if (tipo == STRING){
        cout << "tipo == string" << endl;
        if(Hay_valor)
            strcpy(var->caracter, valor);
        else
            strcpy(var->caracter, "EMPTY");
    }
    else{
        cout << "tipo == int" << endl;
        if(Hay_valor)
            var->entero = atoi(valor);
        else
            strcpy(var->caracter, "EMPTY");
    }
    if (iter != NULL){
        while(iter->arriba != NULL)
            iter = iter->arriba;
        if(pos == 0){
            cout << "if pos == 0 " << endl;
            var->arriba = NULL;
            var->abajo = iter;
            iter->arriba = var;
        }
        else if(pos == cantDato(d)){
            cout << "pos == cantDato(d)" << endl;
            cout << pos << " == " << cantDato(d) << endl;
            while(iter->abajo != NULL)
                iter = iter->abajo;
            var->abajo = NULL;
            var->arriba = iter;
            iter->abajo = var;
        }
        else {
            cout << "Entra aca " << endl;
            while(aux != pos){
                aux++;
                iter = iter->abajo;
            }
            var->abajo = iter;
            var->arriba = iter->arriba;
            iter->arriba->abajo = var;
            iter->arriba = var;
        }
    }
    else{
        var->arriba = NULL;
        var->abajo = NULL;
        iter = var;
    }
    d = iter;
}

int insertarPK(dato &d, tipoDato tipo, char *valor){
    dato iter = d;
    dato var = new (nodo_dato);
    var->tipo = tipo;
    int cont = 0;
    if (tipo == STRING){
        strcpy(var->caracter, valor);
    }
    else{
        var->entero = atoi(valor);
    }
    if (iter == NULL){
        var->arriba = NULL;
        var->abajo = NULL;
        d = var;
        return 0;
    }
    while(iter->arriba != NULL)
        iter = iter->arriba;
    while(iter != NULL){
        if(iter->entero > var->entero || (strcmp(iter->caracter, var->caracter)>0)|| iter->abajo == NULL){
            if(iter->arriba == NULL && (iter->entero > var->entero || strcmp(iter->caracter, var->caracter)>0)){
                cout << "iter->arriba == NULL && iter->entero > var->entero" << endl;
                cout << iter->entero << " > " << var->entero << endl;
                var->arriba = NULL;
                var->abajo = iter;
                iter->arriba = var;
                d = iter;
                return cont;
            }
            else if(iter->abajo == NULL && (iter->entero < var->entero || strcmp(iter->caracter, var->caracter) < 0)){
                cout << "iter->abajo == NULL && iter->entero < var->entero" << endl;
                var->abajo = NULL;
                var->arriba = iter;
                iter->abajo = var;
                d = iter;
                return cont+1;
            }
            else if (iter->entero > var->entero || strcmp(iter->caracter, var->caracter)>0){
                cout << "iter->entero > var->entero" << endl;
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

void imprimir_datos(dato d){
    dato iter = d;
    while(iter->arriba != NULL){
        iter = iter->arriba;
    }
    while(iter != NULL){
        if(iter!= NULL)
            cout << iter->entero << endl;
        iter = iter->abajo;
    }
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

void imprimir_tuplas(dato d, int pos){
    dato iter = d;
    while(iter->arriba != NULL){
        iter = iter->arriba;
    }
    if(pos == 0){
        if(iter->tipo == STRING || (strcmp(iter->caracter, "EMPTY") == 0))
            cout << iter->caracter;
        else 
            cout << iter->entero;
    }
    else{
        int aux = 0;
        while(aux < pos){
            iter = iter->abajo;
            aux++;
        }
        if(iter->tipo == STRING || (strcmp(iter->caracter, "EMPTY") == 0))
            cout << iter->caracter;
        else 
            cout << iter->entero;
    }
}


