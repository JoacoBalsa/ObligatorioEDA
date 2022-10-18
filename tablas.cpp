#include "tabla.h"
#include "tablas.h"
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

TipoRet crearTablas(tablas &ts, char *nombreTabla){
    
    if (ts == NULL){
        ts = new (nodo_tablas);
        ts->t = NULL;
    }
    return crearTabla(ts->t, nombreTabla);
}

TipoRet eliminarTablas(tablas ts, char *nombre){
// Elimina una tabla de nombre: nombre.
    if(ts->t != NULL){
        if(strcmp(nombreTabla_Tablas(ts), nombre) == 0){
            tabla aux = ts->t;
            ts->t = NULL;
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

char *nombreTabla_Tablas(tablas ts){
    return nombreTabla(ts->t);
}

bool colRep_ts(tablas ts, char *nombCol){
    return colRep_tabla(ts->t, nombCol);
}

TipoRet imprimirTablas(tablas ts){
// Imprime el nombre de la tabla (momentaneo ya que solo hay una).
// Pre: Hay tablas para imprimir.
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


