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
		if(nombreTabla_Tablas(bd->ts, nombreTabla))
			return eliminarTablas(bd->ts, nombreTabla);
		else{
			cout << "No existe una tabla con ese nombre" << endl;
			return ERROR;
		}
	else{
		cout << "No hay tablas en la base de datos." << endl;
		return ERROR;
	}
}

TipoRet addCol(bd &bd, char *nombreTabla, char *NombreCol, char *tipoCol, char *calificadorCol)
{
	// cout << " - addCol " << nombreTabla << " " << NombreCol << " " << tipoCol << " " << calificadorCol << endl;
	if(nombreTabla_Tablas(bd->ts, nombreTabla)){ // Se fija que exista una tabla con ese nombre.
		if (!colRep_bd(bd,nombreTabla, NombreCol)){
			if(strcmp(tipoCol,"integer") == 0 || strcmp(tipoCol,"string") == 0){ // Se fija el tipo de la columna
				if (strcmp(calificadorCol, "PRIMARY_KEY") == 0)
				{
					if(!ExistePK_ts(bd->ts, nombreTabla))
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
	if(nombreTabla_Tablas(bd->ts, nombreTabla)){ // Se fija que exista una tabla con ese nombre.
		if(colRep_bd(bd,nombreTabla, NombreCol)){
			if(esPK_BD(bd, nombreTabla, NombreCol) && cant_colBD(bd, nombreTabla) > 1){
				cout << "No se puede borrar la PRIMARY_KEY si hay mas columnas" << endl;
				return ERROR;
			}else
				dropCol_ts(bd->ts, nombreTabla, NombreCol);
		}
		else{
			cout << "No existe una columna de nombre "<< NombreCol << endl;
			return ERROR; 
		}
	}else{
		cout << "No existe en la base de datos una tabla de nombre " << nombreTabla << endl;
		return ERROR;
	}
	return OK;
}

TipoRet alterCol(bd &bd, char *nombreTabla, char *nombreCol, char *tipoColNuevo, char *calificadorColNuevo, char *nombreColNuevo)
{
	// cout << " - alterCol " << nombreTabla << " "<< nombreCol << " " << tipoColNuevo  << " " << calificadorColNuevo << " " << nombreColNuevo << endl;;
	return NO_IMPLEMENTADA;
}

TipoRet insertInto(bd &bd, char *nombreTabla, char *columnasTupla, char *valoresTupla)
{
	// cout << " - insertInto " << nombreTabla << " " << columnasTupla << " " << valoresTupla<< endl;;
	if(nombreTabla_Tablas(bd->ts, nombreTabla)){
		if(Tupla_validaTS(bd->ts, nombreTabla, columnasTupla, valoresTupla)){
			insertarDato_ts(bd->ts, nombreTabla, columnasTupla, valoresTupla);
		}
		else{
			return ERROR;
		}
	}
	else{
		cout << "No existe en la base de datos una tabla de nombre: " << nombreTabla << endl;
		return ERROR;
	}
	return OK;
}

TipoRet deleteFrom(bd &bd, char *nombreTabla, char *condicionEliminar)
{
	// cout << " - deletefrom " << nombreTabla << " " << condicionEliminar << endl;;
	if(nombreTabla_Tablas(bd->ts, nombreTabla)){ 
		if(eliminarTupla_valida_ts(bd->ts, nombreTabla, condicionEliminar)){
			eliminarTupla_ts(bd->ts, nombreTabla, condicionEliminar);
		}else
			return ERROR;
	}
	else{
		cout << "No existe en la base de datos una tabla de nombre: " << nombreTabla << endl;
		return ERROR;
	}
	return OK;
}

TipoRet update(bd &bd, char *nombreTabla, char *condicionModificar, char *columnaModificar, char *valorModificar)
{
	// cout << " - update " << nombreTabla << " " << condicionModificar << " " << columnaModificar << " " << valorModificar << endl;
	return NO_IMPLEMENTADA;
}

TipoRet selectWhere(bd &bd, char *nomTabla1, char *condicion, char *nomTabla2)
{
	// cout << " - selectWhere " << nomTabla1 << " " << condicion << " " << nomTabla2 << endl;
	if(nombreTabla_Tablas(bd->ts, nomTabla1)){
		char *operador = new(char), *columna = new(char), *aux = new char[strlen(condicion)+1];
		strcpy(aux, condicion);
		buscar_operador(operador, aux);
		columna = strtok(aux, operador);
		if(!nombreTabla_Tablas(bd->ts, nomTabla2)){						// Si no existe la tabla 2
			if(Columnas_pertenecen_TS(bd->ts, nomTabla1, columna)){	// Si las columnas pertenecen a Tabla1
				createTable(bd, nomTabla2);												
				selectwhere_ts(bd->ts, nomTabla1, condicion, nomTabla2);
			}
			else{
				return ERROR;
			}
		}else{
			cout << nomTabla2 << " ya existe en la base de datos" << endl;
			return ERROR;
		}
	}else{
		cout << nomTabla1 << " no existe en la base de datos" << endl;
		return ERROR;
	}
	return OK;
}

TipoRet select(bd &bd, char *nomTabla1, char *nomColumnas, char *nomTabla2)
{
	// cout << " - select " << nomTabla1 << " " << nomColumnas << " " << nomTabla2 << endl;
	if(nombreTabla_Tablas(bd->ts, nomTabla1)){
		if(!nombreTabla_Tablas(bd->ts, nomTabla2)){						// Si no existe la tabla 2
			if(Columnas_pertenecen_TS(bd->ts, nomTabla1, nomColumnas)){	// Si las columnas pertenecen a Tabla1
				createTable(bd, nomTabla2);												
				select_ts(bd->ts, nomTabla1, nomColumnas, nomTabla2);
			}
			else{
				return ERROR;
			}
		}else{
			cout << nomTabla2 << " ya existe en la base de datos" << endl;
			return ERROR;
		}
	}else{
		cout << nomTabla1 << " no existe en la base de datos" << endl;
		return ERROR;
	}
	return OK;
}

TipoRet join(bd &bd, char *nomTabla1, char *nomTabla2, char *nomTabla3)
{
	// cout << " - join " << nomTabla1 << " " << nomTabla2 << " " << nomTabla3 << endl;
	return NO_IMPLEMENTADA;
}

TipoRet union_(bd &bd, char *nombreTabla1, char *nombreTabla2, char *nombreTabla3)
{
	// cout << " - union_ " << nombreTabla1 << " " << nombreTabla2 << " " << nombreTabla3 << endl;
	if(nombreTabla_Tablas(bd->ts, nombreTabla1) && nombreTabla_Tablas(bd->ts, nombreTabla2)){	
		if(!nombreTabla_Tablas(bd->ts, nombreTabla3)){				//	Si la tabla nombreTabla3 no existe
			if(mismoEsquema(bd->ts, nombreTabla1, nombreTabla2)){	//  Si las tablas 1 y 2 tienen el mismo esquema entro
				createTable(bd, nombreTabla3);
				union_ts(bd->ts, nombreTabla1, nombreTabla2, nombreTabla3);
			}else{
				cout << "Los esquemas de " << nombreTabla1 << " y " << nombreTabla2 << " no son iguales" << endl;
				return ERROR;
			}
		}else{
			cout << "La tabla de nombre "<< nombreTabla3 << " ya existe" << endl;
			return ERROR;
		}
	}else{
		cout << "Una de las tablas o las dos no se especifica/ron o no existe/n en la base de datos"<< endl;
		return ERROR;
	}
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

TipoRet printdatatable(bd bd, char *NombreTabla)
{
	// cout << " - printdatatable " << NombreTabla << endl;
	if(bd->ts != NULL){
		if(nombreTabla_Tablas(bd->ts, NombreTabla)){
			printDataTable_ts (bd->ts, NombreTabla);
			return OK;
		}else{	
			cout << "Tabla no existente en la base de datos" << endl;
			return ERROR;
		}
	}else{
		cout << "No hay tablas mostrar" << endl;
		return ERROR;
	}
}

TipoRet printTables(bd bd)
{
	// cout << " - printTables " << endl;
	cout << "Las tablas de la BD son:" << endl;
	if(bd->ts != NULL){
		return imprimirTablas(bd->ts);
	}else{
		cout << "No hay tablas" << endl;
		return ERROR;
	}

}

TipoRet printMetadata(bd bd, char *nombreTabla)
{
	// cout << " - printMetadata " << nombreTabla << endl;
	if(bd->ts != NULL){
		if(nombreTabla_Tablas(bd->ts, nombreTabla)){
			printMetadata_ts(bd->ts, nombreTabla);
			return OK;
		}else{	
			cout << "Tabla no existente en la base de datos" << endl;
			return ERROR;
		}
	}else{
		cout << "No hay tablas para mostrar" << endl;
		return ERROR;
	}
}

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
bool colRep_bd(bd &bd, char *nombreTabla,  char *nombCol)
{ 
	return colRep_ts(bd->ts, nombreTabla, nombCol);
}

bool esPK_BD(bd &bd, char *nombreTabla, char *NombreCol){
	return esPK_ts(bd->ts, nombreTabla, NombreCol);
}

int cant_colBD(bd &bd, char *NombreTabla){
	return cant_colTS(bd->ts, NombreTabla);
}

