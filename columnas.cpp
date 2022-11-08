// Estructuras de Datos y Algoritmos - Curso 2022
// Tecnologo en Informatica FIng - DGETP - UTEC
// Trabajo Obligatorio
// columnas.cpp
// Modulo de Implementación de Base de Datos.

#include <iostream>
#include "columnas.h"
#include "dato.h"
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include <string.h>


#define NOM 30

using namespace std;

struct nodo_columna
{
    char *nombreCol;
    CalCol calCol;
    tipoDato tipoCol;
    columna sig;
    columna ant;
    dato d;
};

columna addColumnaCol(columna col,char *NombreCol, char *tipoCol, CalCol calificador)
{
    columna nuevaCol = new (nodo_columna);
    nuevaCol->nombreCol = new char[NOM];
    strcpy(nuevaCol->nombreCol, NombreCol);
    nuevaCol->calCol = calificador;
    if(strcmp(tipoCol, "string") == 0){
        nuevaCol->tipoCol = STRING;
    }else if(strcmp(tipoCol, "integer") == 0){
        nuevaCol->tipoCol = INT;
    }
    nuevaCol->sig = NULL;
    if(col == NULL)                         // Si nuevaCol es la primera columna de la tabla.
        nuevaCol->ant = NULL;
    else{                                   // Si ya hay columnas en la tabla. 
        columna iter = col;
        while(iter->sig != NULL)
            iter = iter->sig;
        iter->sig = nuevaCol;
        nuevaCol->ant = iter;
    }
    nuevaCol->d = NULL;
    return nuevaCol;
}

char *nombreColumna(columna col)
{
    return col->nombreCol;
}


bool colRep(columna col, char *nombCol){
    if(col != NULL){
        columna iter = col;
        while(iter->ant != NULL)
            iter = iter->ant;
        while(iter != NULL)
        {
            if (strcmp(iter->nombreCol, nombCol)==0)
                return true;
            else
                iter = iter->sig;
        }
    }
   return false;
}

void imprimir_columnas (columna col){
    if(col != NULL){
        columna iter = col;
        while (iter->ant != NULL)// Va al principio de la lista de columnas
            iter = iter->ant;
        while(iter->sig != NULL){
            cout << iter->nombreCol << ":";
            iter = iter->sig;
        }
        cout << iter->nombreCol << endl;
    }
}

bool existe_PK(columna col){
    if(col != NULL){
        columna iter = col;
        while(iter->ant != NULL)
            iter = iter->ant;
        while(iter != NULL){
            if(iter->calCol == PRIMARY_KEY)
                return true;
            else
                iter = iter->sig;
        }
    }
    return false;
}
 
bool esPK_col(columna col, char *nombreCol){
    if (col != NULL){
        columna iter = col;
        while (iter->ant != NULL)
            iter = iter->ant;
        while (strcmp(iter->nombreCol, nombreCol) != 0){
            iter = iter->sig;
        }
        if (iter->calCol == PRIMARY_KEY)
            return true;
        else
            return false;
    }
    return false;
}

int cant_col(columna col){
    int cont = 0;
    if (col != NULL){
        columna iter = col;
        while (iter->ant != NULL)
            iter = iter->ant;
        while (iter != NULL){
            iter = iter->sig;
            cont++;
        }
    }
    return cont;
}

columna eliminarCol(columna col, char *nombreCol){
    columna iter = col;
    while (iter->ant != NULL)                       //  Va hasta el principio de la lista de columnas. 
        iter = iter->ant;
    while (strcmp(iter->nombreCol, nombreCol) != 0){
        iter = iter->sig;
    }
    //deleteDatos_col(iter);
    if(iter->ant == NULL && iter->sig == NULL){     //  Caso de una sola columna.
        delete iter;
        return NULL;
    }
    else{
        columna aux = iter;
        if(iter->ant == NULL){                      //  Caso de primera columna.                 
            iter = iter->sig;
            iter->ant = NULL;
        }
        else if(iter->sig == NULL){                 //  Caso de ser la utlima columna.
            iter = iter->ant;   
            iter->sig = NULL;
        }
        else{
            iter = iter->sig;
            iter->ant = aux->ant;
            aux->ant->sig = iter;
        }
        delete aux;
        return iter;
    }
}

bool Tupla_valida(columna col, char *columnasTupla, char *valoresTupla){
    columna iter = col;
    while(iter->ant != NULL)
        iter = iter->ant;
    if(!valor_PK(iter, columnasTupla))
        return false;
    if(PK_repetidacol(iter, columnasTupla, valoresTupla))
        return false;
    if(cantCol_igual_cantVal(columnasTupla, valoresTupla)){
        while(iter->sig != NULL){
            if(!tupla_valida_para_columna(iter, columnasTupla))
                return false;
            else
                iter = iter->sig;
        }
    }
    else
        return false;
    return true;
}

bool PK_repetidacol(columna col, char *columnasTupla, char *valoresTupla){
    columna iter = col;
    if(iter->d != NULL){
        char *valores = new char[strlen(valoresTupla)+1], *columnas = new char[strlen(columnasTupla)+1];
        strcpy(valores, valoresTupla);
        strcpy(columnas, columnasTupla);
        char *aux = new(char), *aux2 = new(char);
        while(iter->ant != NULL)
            iter = iter->ant;
        while(iter->calCol != PRIMARY_KEY)
            iter = iter->sig;
        aux = strtok(columnas, ":");
        aux2 = strtok(valores, ":");
        while(strcmp (aux, iter->nombreCol) != 0){
            columnas = &columnas[strlen(aux) + 1];
            valores = &valores[strlen(aux2) + 1];
            aux = strtok(columnas, ":");
            aux2 = strtok(valores, ":");
        }
        if(PK_repetida(iter->d, iter->tipoCol, aux2)){
            cout << "La columna " << iter->nombreCol << " es PRIMARY_KEY no se pueden repetir valores" << endl; 
            return true;
        }
    }
    return false;
}

bool tupla_valida_para_columna (columna col, char *columnasTupla){
    if(col->calCol == ANY)
        return true;
    else{
        char *columnas = new char[strlen(columnasTupla)+1];
        char *aux = new(char);
        strcpy(columnas, columnasTupla);
        aux = strtok(columnas, ":");
        while(aux != NULL){
            if(strcmp(aux,col->nombreCol) == 0){
                return true;
            }
            else
                aux = strtok(NULL, ":");
        }
    }
    cout << col->nombreCol << " no es de tipo ANY debes asignarle un valor" << endl;
    return false;
}

bool cantCol_igual_cantVal (char *columnasTupla, char *valoresTupla){
    char *valores = new char[strlen(valoresTupla)+1], *columnas = new char[strlen(columnasTupla)+1];
	strcpy(valores, valoresTupla);
	strcpy(columnas, columnasTupla);
    char *aux = new (char);
    int contCol = 0, contVal = 0;
    aux = strtok (columnas, ":");
    while(aux != NULL){
        aux = strtok (NULL, ":");
        contCol++;
    }
    aux = strtok(valores, ":");
    while(aux != NULL){
        aux = strtok (NULL, ":");
        contVal++;
    }
    if (contCol > contVal)
        cout << "Pasaste mas columnas que valores" << endl;
    else if (contVal > contCol)
        cout << "Pasaste mas valores que columnas" << endl; 
    return (contCol == contVal);
}

int insertarPK_col(columna &col, char *columnasTupla, char *valoresTupla){
    columna iter = col;
    char *valores = new char[strlen(valoresTupla)+1], *columnas = new char[strlen(columnasTupla)+1];
	strcpy(valores, valoresTupla);
	strcpy(columnas, columnasTupla);
    char *aux = new(char), *aux2 = new(char);
    while(iter->ant != NULL)
        iter = iter->ant;
    while(iter->calCol != PRIMARY_KEY)
        iter = iter->sig;
    aux = strtok(columnas, ":");
    aux2 = strtok(valores, ":");
    while(strcmp (aux, iter->nombreCol) != 0){
        columnas = &columnas[strlen(aux) + 1];
        valores = &valores[strlen(aux2) + 1];
        aux = strtok(columnas, ":");
        aux2 = strtok(valores, ":");
    }
    return insertarPK(iter->d, iter->tipoCol, aux2);
}

void insertarDato_col(columna &col, char *columnasTupla, char *valoresTupla){
    char *valores = new char[strlen(valoresTupla)+1], *columnas = new char[strlen(columnasTupla)+1];
    strcpy(valores, valoresTupla);
    strcpy(columnas, columnasTupla);
    columna iter = col;
    int cont = 0, pos, tam = cant_col(iter), i = 0;
    bool columnas_con_Dato[tam];
    while(iter->ant != NULL)
        iter = iter->ant;
    while(iter != NULL && cont < tam){
        columnas_con_Dato[cont] = PasanCol(iter, columnas);
        iter = iter->sig;
        cont++;
    }
    iter = col;
    pos = insertarPK_col(iter, columnas, valores);
    cout << columnasTupla << endl;
    while(iter->ant != NULL)
        iter = iter->ant;
    while(iter != NULL){
        strcpy(valores, valoresTupla);
        strcpy(columnas, columnasTupla);
        if(iter->calCol != PRIMARY_KEY){
            cout << iter->nombreCol << endl;
            Valor_dato_col(iter, pos, columnas, valores, columnas_con_Dato[i]);
        }
        i++;
        iter = iter->sig;
    }
}

void Valor_dato_col(columna &col,int  pos, char *columnasTupla, char *valoresTupla, bool empty){
    char *valores = new char[strlen(valoresTupla)+1], *columnas = new char[strlen(columnasTupla)+1];
    strcpy(valores, valoresTupla);
    strcpy(columnas, columnasTupla);
    cout << columnas << endl;
    cout << valores << endl;
    char *aux = new (char), *aux2 = new (char);
    cout << "hasta aca todo bien"<< endl;
    aux = strtok(columnas, ":");
    aux2 = strtok(valores, ":");
    while(strcmp (aux, col->nombreCol) != 0){
        columnas = &columnas[strlen(aux) + 1];
        valores = &valores[strlen(aux2) + 1];
        cout <<"aca llego"<< endl;
        aux = strtok(columnas, ":");
        aux2 = strtok(valores, ":");
    }
    cout<< "inserto en la columna: " << aux << "El valor: " << aux2; 
    insertarDato(col->d, col->tipoCol, pos, aux2, empty);
}

bool PasanCol(columna col, char *columnasTupla){
    char *columnas = new char[strlen(columnasTupla)+1];
    char *aux = new(char);
    strcpy (columnas, columnasTupla);
    aux = strtok (columnas, ":");
    while(aux != NULL){
        if(strcmp(aux, col->nombreCol) == 0){
            return true;
        }
        else
            aux = strtok(NULL, ":");
    }
    return false;
}

bool valor_PK (columna col, char *columnasTupla){
    columna iter = col;
    char *columnas = new char[strlen(columnasTupla)+1];
    char *aux = new (char);
	strcpy(columnas, columnasTupla);
    while(iter->ant != NULL){
        iter = iter->ant;
    }
    while(iter->calCol != PRIMARY_KEY){
        iter = iter->sig;
    }
    aux = strtok(columnas, ":");
    while(aux != NULL){
        if(strcmp(aux, iter->nombreCol) == 0)
            return true;
        aux = strtok(NULL, ":");
    }
    cout << iter->nombreCol << " es PRIMARY_KEY no puede quedar sin valor." << endl;
    return false;
}

tipoDato tipo_dato(columna col){
    return col->tipoCol;
}
