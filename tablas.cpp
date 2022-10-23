#include "tabla.h"
#include "tablas.h"
#include "columnas.h"
#include "define.h"
#include <string.h>
#include <iostream>

using namespace std;

#define MAX_NOMBRE 20

struct nodo_tablas
{
    tabla t;
    /*tablas izq;
    tablas der;*/
};

TipoRet crearTablas(tablas &ts, char *nombreTabla)
{
    if (ts == NULL)
        ts = new (nodo_tablas);
    ts->t = NULL;
    return crearTabla(ts->t, nombreTabla);
}

TipoRet eliminarTablas(tablas ts, char *nombre)
{
    if(ts->t != NULL){
        if(strcmp(nombreTabla_Tablas(ts), nombre) == 0){
            tablas aux = ts;
            ts = NULL;
            delete aux;
            cout << "Tabla eliminada correctamente." << endl;
            return OK;
        }else{
            cout << "Nombre Tabla no existe en la base de datos." << endl;   
            return ERROR;
        }
    }else{
        cout << "No hay tablas para borrar." << endl;
        return ERROR;
    }
}

char *nombreTabla_Tablas(tablas ts)
{
    return nombreTabla(ts->t);
}

bool colRep_ts(tablas ts, char *nombCol)
{
    return colRep_tabla(ts->t, nombCol);
}

TipoRet imprimirTablas(tablas ts)
{
    if(ts->t != NULL){
        char *nombre;
        nombre = nombreTabla(ts->t);
        cout << "Nombre de tabla 1: " << nombre << endl;
        return OK;
    }else{
        cout << "No hay tablas para imprimir." << endl;
        return ERROR;
    }
}

void addColumnats (tablas &ts, char *nombreTabla, char *NombreCol, char *tipoCol, CalCol calificadorCol){
    addColumnat(ts->t, nombreTabla, NombreCol, tipoCol, calificadorCol);
}

void printDataTable_ts (tablas &ts, char *NombreTabla){
    printDataTable_t (ts->t, NombreTabla);
}

bool ExistePK_ts(tablas ts){
    return ExistePK_t(ts->t);
}

bool esPK_ts(tablas ts, char *nombreTabla, char *nombreCol){
	return esPK_t(ts->t, nombreTabla, nombreCol);
}

int cant_colTS(tablas ts,char *NombreTabla){
    return cant_colT(ts->t, NombreTabla);
}

void dropCol_ts(tablas ts, char *nombreTabla, char *nombreCol){
    eliminarCol_t(ts->t, nombreCol);
}

bool Tupla_validaTS (tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla){
    return Tupla_validaT(ts->t, columnasTupla, valoresTupla);
}

void insertarDato_ts(tablas &ts, char *nombreTabla, char *columnasTupla, char *valoresTupla){
    insertarDato_t(ts->t, columnasTupla, valoresTupla);
}