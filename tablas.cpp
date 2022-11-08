// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
// Trabajo Obligatorio
// tablas.cpp
// Modulo de Implementación de Base de Datos.

#include <iostream>
#include "tabla.h"
#include "tablas.h"
#include "columnas.h"
#include "define.h"
#include <string.h>


using namespace std;

#define MAX_NOMBRE 20

struct nodo_tablas
{
    tabla t;
    tablas izq;
    tablas der;
};

TipoRet crearTablas(tablas &ts, char *nombreTabla)
{
    if (ts == NULL){
        ts = new (nodo_tablas);
        ts->t = NULL;
        ts->izq = NULL;
        ts->der = NULL;
        return crearTabla(ts->t, nombreTabla);
    }else{
        if(strcmp(nombreT(ts->t), nombreTabla) > 0){        //nombreTabla_Tablas(ts, nombreTabla) -> (condicion anterior)
            return crearTablas(ts->izq, nombreTabla);
        }else if(strcmp(nombreT(ts->t), nombreTabla) < 0){
            return crearTablas(ts->der, nombreTabla);
        }else if (strcmp(nombreT(ts->t), nombreTabla) == 0){
            cout << "No se puede sobreescribir la tabla";
            return ERROR;
        }
    } 
}

TipoRet eliminarTablas(tablas ts, char *nombre)
{
    ts = eliminar(ts, nombre);
    return OK;
    /*if(ts->t != NULL){
        if(nombreTabla_Tablas(ts, nombre)){ // Si existe la tabla
            tablas aux = ts;
            while(strcmp(nombreT(aux->t), nombre)!=0){ //Busca la tabla que se le pasa por parametro.
                if(strcmp(nombreT(aux->t), nombre) < 0)
                    aux = aux->der;
                else
                    aux = aux->izq;
            }
            //---------------Encontró la tabla---------------------

            //---------------Eliminó la tabla---------------------
            cout << "Tabla eliminada correctamente." << endl;
            return OK;
        }else{
            cout << "Nombre Tabla no existe en la base de datos." << endl;   
            return ERROR;
        }
    }else{
        cout << "No hay tablas para borrar." << endl;
        return ERROR;
    }*/
}

tablas eliminar(tablas ts, char *nombreTabla){
    if(strcmp(nombreT(ts->t), nombreTabla) > 0){
        ts->izq = eliminar(ts->izq, nombreTabla);
        return ts;
    }else if(strcmp(nombreT(ts->t), nombreTabla) < 0){
        ts->der = eliminar(ts->der, nombreTabla);
        return ts;
    }else{ // Encontro la tabla a eliminar
        tablas aux;
        if(ts->izq == NULL && ts->der == NULL){
            delete ts;
            return NULL;
//---------------------Corregir esto---------------------//
        }else if(ts->izq == NULL){ // Caso tiene solo rama/hoja a la derecha
            aux = ts->der;
            delete ts;
            return NULL;
        }else if(ts->der == NULL){ // Caso tiene solo rama/hoja a la izquierda
            aux = ts->izq;
            delete ts;
            return NULL;
//---------------------Corregir esto---------------------//
        }else{ // Caso tiene 2 ramas/hojas
            if(profundidad(ts->izq) > profundidad(ts->der))
                aux = max_izq(ts->izq);
            else
                aux = min_der(ts->der);
            aux->izq = ts->izq;
            aux->der = ts->der;
            delete ts;
            return aux;
        }
    }
}

tablas max_izq(tablas &ts){
    if(ts->der == NULL){
        tablas aux = ts;
        ts = ts->der;
        return aux;
    }else
        return max_izq(ts->der);
}

tablas min_der(tablas &ts){
    if(ts->izq == NULL){
        tablas aux = ts;
        ts = ts->der;
        return aux;
    }else
        return min_der(ts->izq);
}

int profundidad(tablas ts){
    if(ts == NULL)
        return 0;
    else
        return 1 + max(profundidad(ts->izq), profundidad(ts->der));
}

int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

bool nombreTabla_Tablas(tablas ts, char *nombreTabla) 
// Retorna True si hay una tabla nombreTabla en ts
{
    if(ts == NULL)
        return false;
    else if(strcmp(nombreT(ts->t), nombreTabla) == 0)
        return true;
    else if (strcmp(nombreT(ts->t), nombreTabla) > 0)
        return nombreTabla_Tablas(ts->izq, nombreTabla);
    else if(strcmp(nombreT(ts->t), nombreTabla) < 0)
        return nombreTabla_Tablas(ts->der, nombreTabla);
}

bool colRep_ts(tablas ts, char *nombreTabla, char *nombCol)
{
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    return colRep_tabla(aux->t, nombCol);
}

TipoRet imprimirTablas(tablas ts)
{
    if(ts != NULL){
        imprimirTablas(ts->izq);
        char *nombre;
        nombre = nombreT(ts->t);
        cout << nombre << endl; 
        imprimirTablas(ts->der);
    }
    return OK;
}

void addColumnats (tablas &ts, char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificadorCol){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    addColumnat(aux->t, NombreCol, tipoCol, calificadorCol);
}

void printDataTable_ts (tablas &ts, char *NombreTabla){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), NombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), NombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    printDataTable_t(aux->t, NombreTabla);
}

bool ExistePK_ts(tablas ts, char *nombreTabla){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    return ExistePK_t(aux->t);
}

bool esPK_ts(tablas ts, char *nombreTabla, char *nombreCol){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
	return esPK_t(ts->t, nombreCol);
}

int cant_colTS(tablas ts,char *NombreTabla){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), NombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), NombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    return cant_colT(ts->t);
}

void dropCol_ts(tablas ts, char *nombreTabla, char *nombreCol){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    eliminarCol_t(aux->t, nombreCol);
}

bool Tupla_validaTS (tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    return Tupla_validaT(aux->t, columnasTupla, valoresTupla);
}

void insertarDato_ts(tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nombreTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nombreTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    insertarDato_t(aux->t, columnasTupla, valoresTupla);
}