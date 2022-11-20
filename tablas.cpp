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

TipoRet crearTablas(tablas &ts, char *nombreTabla){
    if (ts == NULL){
        ts = new (nodo_tablas);
        ts->t = NULL;
        ts->izq = NULL;
        ts->der = NULL;
        crearTabla(ts->t, nombreTabla);
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
    return OK; 
}

TipoRet eliminarTablas(tablas ts, char *nombre){
    ts = eliminar(ts, nombre);
    return OK;
}

tablas eliminar(tablas ts, char *nombreTabla){
    if(strcmp(nombreTabla, nombreT(ts->t)) < 0){
        ts->izq = eliminar(ts->izq, nombreTabla);
        return ts;
    }else if(strcmp(nombreTabla, nombreT(ts->t)) > 0){
        ts->der = eliminar(ts->der, nombreTabla);
        return ts;
    }else{ // Encontro la tabla a eliminar
        tablas aux;
        if(ts->izq == NULL && ts->der == NULL){     //  Caso sin hojas/ramas
            delete ts;
            return NULL;
        }else if(ts->izq == NULL && ts->der!=NULL){ // Caso solo rama/hoja a la der
            aux = ts->der;
            delete ts;
            return aux;
        }else if(ts->der == NULL && ts->izq!=NULL){ // Caso solo rama/hoja a la izq
            aux = ts->izq;
            delete ts;
            return aux;
        }else{                                      // Caso tiene 2 ramas/hojas
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
        ts = ts->izq;
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

bool nombreTabla_Tablas(tablas ts, char *nombreTabla){
// Retorna True si hay una tabla nombreTabla en ts
    if(ts == NULL)
        return false;
    else if(strcmp(nombreT(ts->t), nombreTabla) == 0)
        return true;
    else if (strcmp(nombreT(ts->t), nombreTabla) > 0)
        return nombreTabla_Tablas(ts->izq, nombreTabla);
    else 
        return nombreTabla_Tablas(ts->der, nombreTabla);
}

bool colRep_ts(tablas ts, char *nombreTabla, char *nombCol)
{
    tablas aux = buscar_tabla(ts, nombreTabla);
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
    tablas aux = buscar_tabla(ts, nombreTabla);
    addColumnat(aux->t, NombreCol, tipoCol, calificadorCol);
}

void printDataTable_ts (tablas &ts, char *NombreTabla){
    tablas aux = buscar_tabla(ts, NombreTabla);
    printDataTable_t(aux->t, NombreTabla);
}

bool ExistePK_ts(tablas ts, char *nombreTabla){
    tablas aux = buscar_tabla(ts, nombreTabla);
    return ExistePK_t(aux->t);
}

bool esPK_ts(tablas ts, char *nombreTabla, char *nombreCol){
    tablas aux = buscar_tabla(ts, nombreTabla);
	return esPK_t(aux->t, nombreCol);
}

int cant_colTS(tablas ts,char *NombreTabla){
    tablas aux = buscar_tabla(ts, NombreTabla);
    return cant_colT(aux->t);
}

void dropCol_ts(tablas ts, char *nombreTabla, char *nombreCol){
    tablas aux = buscar_tabla(ts, nombreTabla);
    eliminarCol_t(aux->t, nombreCol);
}

bool Tupla_validaTS (tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla){
    tablas aux = buscar_tabla(ts, nombreTabla);
    return Tupla_validaT(aux->t, columnasTupla, valoresTupla);
}

void insertarDato_ts(tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla){
    tablas aux = buscar_tabla(ts, nombreTabla);
    insertarDato_t(aux->t, columnasTupla, valoresTupla);
}

tablas buscar_tabla(tablas ts, char *nomTabla){
    tablas aux = ts;
    while(strcmp(nombreT(aux->t), nomTabla)!=0){ //Busca la tabla que se le pasa por parametro.
        if(strcmp(nombreT(aux->t), nomTabla) < 0)
            aux = aux->der;
        else
            aux = aux->izq;
    }
    return aux;
}

void eliminarTupla_ts(tablas &ts, char *nombreTabla, char *condicionEliminar){
    tablas aux = buscar_tabla(ts, nombreTabla);
    eliminarTupla_t(aux->t, condicionEliminar);
}

bool eliminarTupla_valida_ts(tablas ts, char *nombreTabla, char *condicionEliminar){
    tablas aux = buscar_tabla(ts, nombreTabla);
    return eliminarTupla_valida_t(aux->t, condicionEliminar);
}

void printMetadata_ts(tablas ts, char *nombreTabla){
    tablas aux = buscar_tabla(ts, nombreTabla);
    printMetadata_t(aux->t);
}

void select_ts(tablas &ts, char *Tabla1, char *nomColumnas, char *Tabla2){
    tablas T1 = buscar_tabla(ts, Tabla1), T2 = buscar_tabla(ts, Tabla2);
    select_t(T1->t, T2->t, nomColumnas);
}

bool Columnas_pertenecen_TS(tablas ts, char *nomTabla1, char *nomColumnas){
    tablas aux = buscar_tabla(ts, nomTabla1);
    return Columnas_pertenecen_T(aux->t, nomColumnas);
}

void selectwhere_ts(tablas &ts, char *nomTabla1, char *condicion, char *nomTabla2){
    tablas T1 = buscar_tabla(ts, nomTabla1), T2 = buscar_tabla(ts, nomTabla2); // Busca la tabla T1 y T2 
    selectwhere_t(T1->t, T2->t, condicion); // Pasa las tablas y la condicion al selectwhere_t
}