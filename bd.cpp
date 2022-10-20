// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
// Trabajo Obligatorio
// bd.c
// Modulo de Implementación de Base de Datos.

#include <iostream>
#include "bd.h"
#include "tabla.h"
#include "tablas.h"
#include "columnas.h"
#include "define.h"
#include <string.h>

using namespace std;

struct nodo_bd
{
	tablas ts;
};

/*---------------------------------------------PRIMERA ENTREGA--------------------------------------------*/
bd createBD()
{
	bd base = new (nodo_bd);
	return base;
}

TipoRet createTable(bd &bd, char *nombreTabla)
{
	// cout << " - createTable " << nombreTabla << endl;
	return crearTablas(bd->ts, nombreTabla);
}

TipoRet dropTable(bd &bd, char *nombreTabla)
{
	// cout << " - dropTable " << nombreTabla << endl;;
	if(bd->ts != NULL)
		return eliminarTablas(bd->ts, nombreTabla);
	else{
		cout << "No hay tablas en la base de datos." << endl;
		return ERROR;
	}
}

TipoRet addCol(bd &bd, char *nombreTabla, char *NombreCol, char *tipoCol, char *calificadorCol)
{
	// cout << " - addCol " << nombreTabla << " " << NombreCol << " " << tipoCol << " " << calificadorCol << endl;
	if(strcmp(nombreTabla_Tablas(bd->ts), nombreTabla) == 0){ // Se fija el nombre de la tabla
		if (!colRep_bd(bd, NombreCol)){
			if(strcmp(tipoCol,"integer") == 0 || strcmp(tipoCol,"string") == 0){ // Se fija el tipo de la columna
				if (strcmp(calificadorCol, "PRIMARY_KEY") == 0)
				{
					if(!ExistePK_ts(bd->ts))
						addColumnats(bd->ts, nombreTabla, NombreCol, tipoCol, PRIMARY_KEY);
					else{
						cout << "Ya existe una columna con PRIMARY_KEY" << endl;
						return ERROR;
					}

				}
				else if (strcmp(calificadorCol, "NOT_EMPTY") == 0)
				{
					addColumnats(bd->ts, nombreTabla, NombreCol, tipoCol, NOT_EMPTY);
				}
				else if (strcmp(calificadorCol, "ANY") == 0)
				{
					addColumnats(bd->ts, nombreTabla, NombreCol, tipoCol, ANY);
				}
				else
				{
					cout << "Calificador de columna no valido" << endl;
					return ERROR;
				}
			}
			else{
				cout << "El tipo de columna no se especifica o no corresponde" << endl;
				return ERROR;
			}
		}
		else{
			cout << "Ya existe una columna con ese nombre" << endl;
			return ERROR;
		}
	}
	else{
		cout << "No existe una tabla con ese nombre o no se especifica el nombre" << endl;
		return ERROR;
	}
	return OK;
}

TipoRet dropCol(bd &bd, char *nombreTabla, char *NombreCol)
{
	// cout << " - dropCol " << nombreTabla << " " << NombreCol << endl;;
	return NO_IMPLEMENTADA;
}

TipoRet alterCol(bd &bd, char *nombreTabla, char *nombreCol, char *tipoColNuevo, char *calificadorColNuevo, char *nombreColNuevo)
{
	// cout << " - alterCol " << nombreTabla << " "<< nombreCol << " " << tipoColNuevo  << " " << calificadorColNuevo << " " << nombreColNuevo << endl;;
	return NO_IMPLEMENTADA;
}

TipoRet insertInto(bd &bd, char *nombreTabla, char *columnasTupla, char *valoresTupla)
{
	// cout << " - insertInto " << nombreTabla << " " << columnasTupla << " " << valoresTupla<< endl;;
	return NO_IMPLEMENTADA;
}

TipoRet deleteFrom(bd &bd, char *nombreTabla, char *condicionEliminar)
{
	// cout << " - deletefrom " << nombreTabla << " " << condicionEliminar << endl;;
	return NO_IMPLEMENTADA;
}

TipoRet update(bd &bd, char *nombreTabla, char *condicionModificar, char *columnaModificar, char *valorModificar)
{
	// cout << " - update " << nombreTabla << " " << condicionModificar << " " << columnaModificar << " " << valorModificar << endl;
	return NO_IMPLEMENTADA;
}
/*---------------------------------------------PRIMERA ENTREGA--------------------------------------------*/

TipoRet selectWhere(bd &bd, char *nomTabla1, char *condicion, char *nomTabla2)
{
	// cout << " - selectWhere " << nomTabla1 << " " << condicion << " " << nomTabla2 << endl;
	return NO_IMPLEMENTADA;
}

TipoRet select(bd &bd, char *nomTabla1, char *nomColumnas, char *nomTabla2)
{
	// cout << " - select " << nomTabla1 << " " << nomColumnas << " " << nomTabla2 << endl;
	return NO_IMPLEMENTADA;
}

TipoRet join(bd &bd, char *nomTabla1, char *nomTabla2, char *nomTabla3)
{
	// cout << " - join " << nomTabla1 << " " << nomTabla2 << " " << nomTabla3 << endl;
	return NO_IMPLEMENTADA;
}

TipoRet union_(bd &bd, char *nombreTabla1, char *nombreTabla2, char *nombreTabla3)
{
	// cout << " - union_ " << nombreTabla1 << " " << nombreTabla2 << " " << nombreTabla3 << endl;
	return NO_IMPLEMENTADA;
}

TipoRet intersec(bd &bd, char *nombreTabla1, char *nombreTabla2, char *nombreTabla3)
{
	// cout << " - intersec " << nombreTabla1 << " " << nombreTabla2 << " " << nombreTabla3 << endl;
	return NO_IMPLEMENTADA;
}

TipoRet minus_(bd &bd, char *nombreTabla1, char *nombreTabla2, char *nombreTabla3)
{
	// cout << " - minus_ " << nombreTabla1 << " " << nombreTabla2 << " " << nombreTabla3 << endl;
	return NO_IMPLEMENTADA;
}

/*---------------------------------------------PRIMERA ENTREGA--------------------------------------------*/
TipoRet printdatatable(bd bd, char *NombreTabla)
{
	// cout << " - printdatatable " << NombreTabla << endl;
	if(strcmp(nombreTabla_Tablas(bd->ts), NombreTabla) == 0){
		printDataTable_ts (bd->ts, NombreTabla);
		return OK;
	}else{	
		cout << "Tabla no existente en la base de datos" << endl;
		return ERROR;
	}
}
/*---------------------------------------------PRIMERA ENTREGA--------------------------------------------*/

TipoRet printTables(bd bd)
{
	// cout << " - printTables " << endl;
	//###################################################-Hacer de nuevo en la seg entrega para que sea en orden-###################################################
	if(bd->ts != NULL)
		return imprimirTablas(bd->ts);
	else{
		cout << "No hay tablas" << endl;
		return ERROR;
	}

}

/*---------------------------------------------PRIMERA ENTREGA--------------------------------------------*/
TipoRet printMetadata(bd bd, char *nombreTabla)
{
	// cout << " - printMetadata " << nombreTabla << endl;
	return NO_IMPLEMENTADA;
}
/*---------------------------------------------PRIMERA ENTREGA--------------------------------------------*/

TipoRet undo(bd &bd)
{
	// cout << " - undo" << endl;
	return NO_IMPLEMENTADA;
}

TipoRet redo(bd &bd)
{
	// cout << " - redo" << endl;
	return NO_IMPLEMENTADA;
}

bd destroyBD(bd &bd)
{
	return NULL;
}

//------------------------------------------------Auxiliar------------------------------------------------
bool colRep_bd(bd &bd, char *nombCol)
{ 
	return colRep_ts(bd->ts, nombCol);
}

bool nombreExistente(bd &bd, char *nombre)
{
    if (bd->ts == NULL)
        return false;
    else
    {
        if (strcmp(nombreTabla_Tablas(bd->ts), nombre) == 0)
            return true;
		else
			return false;
    }
}

