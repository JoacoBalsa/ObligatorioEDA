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

void imprimir_tuplasCol(columna col){
    if(col != NULL && col->d != NULL){
        columna iter = col;
        int cont = 0, tam = cantDato(iter->d);
        while(cont < tam){
            while(iter->ant != NULL)
                iter = iter->ant;
            while(iter != NULL){
                imprimir_tuplas(iter->d, cont);
                iter = iter->sig;
                if(iter != NULL)
                    cout << ":";
            }
            iter = col;
            cont++;
            cout << endl;
        }
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
    deleteDatos(iter->d);
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

bool Existe_col (columna col, char *Columnas){
    columna iter = col;
    char *aux = new char[strlen(Columnas)+1];
    strcpy(aux, Columnas);
    char *columna = new(char);
    columna = strtok(aux, ":");
    while(columna != NULL){
        while(iter->ant != NULL)
            iter = iter->ant;
        while(iter != NULL && strcmp(iter->nombreCol, columna) != 0){
            iter = iter->sig;
        }
        if(iter == NULL){
            cout << columna << " no existe en la tabla" << endl;
            return false;
        }
        else{
            columna = strtok(NULL, ":");
            iter = col;
        }
    }
    return true;
}

bool Tupla_valida(columna col, char *columnasTupla, char *valoresTupla){
    columna iter = col;
    while(iter->ant != NULL) // Va hasta la primera columna.
        iter = iter->ant;
    if(!valor_PK(iter, columnasTupla)) // Si no se pasa un valor para la PRIMARY_KEY retorna false.
        return false;
    if(PK_repetidacol(iter, columnasTupla, valoresTupla)) // Si ya hay una tupla con ese valor de PRIMARY_KEY retorna false. 
        return false;
    if(!Existe_col(iter, columnasTupla)) // Se fija que todas las columnas pasadas por parametro sean parte de las columnas
        return false;
    if(cantCol_igual_cantVal(columnasTupla, valoresTupla)){ // Se fija que la cant de columans pasadas por parametro es igual a la 
        while(iter->sig != NULL){                           // cant de valores.
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
    char *aux = new (char), *aux2 = new (char);
    int poscol = 0, posval = 0;
    strcpy(valores, valoresTupla);
    strcpy(columnas, columnasTupla);
    while(iter->ant != NULL)
        iter = iter->ant;
    while(iter->calCol != PRIMARY_KEY)
        iter = iter->sig;
    aux = strtok(columnas, ":");
    while(strcmp(iter->nombreCol, aux) != 0){
        aux = strtok(NULL, ":");
        poscol++;
    }
    while(aux != NULL){
        aux = strtok(NULL, ":");
    }
    aux2 = strtok(valores, ":");
    while(posval < poscol){
        aux2 = strtok(NULL, ":");
        posval++;
    }
    return insertarPK(iter->d, iter->tipoCol, aux2);
}

void insertarDato_col(columna &col, char *columnasTupla, char *valoresTupla){
    char *valores = new char[strlen(valoresTupla)+1], *columnas = new char[strlen(columnasTupla)+1];
    strcpy(valores, valoresTupla);
    strcpy(columnas, columnasTupla);
    columna iter = col;
    int pos;
    pos = insertarPK_col(iter, columnas, valores);
    while(iter->ant != NULL)
        iter = iter->ant;
    while(iter != NULL){
        strcpy(valores, valoresTupla);
        strcpy(columnas, columnasTupla);
        if(iter->calCol != PRIMARY_KEY)
            Valor_dato_col(iter, pos, columnas, valores, PasanCol(iter, columnas));
        iter = iter->sig;
    }
}

void Valor_dato_col(columna &col,int  pos, char *columnasTupla, char *valoresTupla, bool Hay_valor){
    char *valores = new char[strlen(valoresTupla)+1], *columnas = new char[strlen(columnasTupla)+1];
    strcpy(valores, valoresTupla);
    strcpy(columnas, columnasTupla);
    if(Hay_valor){
        char *aux = new (char), *aux2 = new (char);
        int poscol = 0, posval = 0;
        aux = strtok(columnas, ":");
        while(strcmp(col->nombreCol, aux) != 0){
            aux = strtok(NULL, ":");
            poscol++;
        }
        while(aux != NULL){
            aux = strtok(NULL, ":");
        }
        aux2 = strtok(valores, ":");
        while(posval < poscol){
            aux2 = strtok(NULL, ":");
            posval++;
        }
        insertarDato(col->d, col->tipoCol, pos, aux2, Hay_valor);
    }
    else{
        insertarDato(col->d, col->tipoCol, pos, valores, Hay_valor);
    }
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

void eliminarTupla_col(columna &col, char *condicionEliminar){
    char *nomCol = new(char), *operador = new(char), *valor = new(char), *aux = new char[strlen(condicionEliminar)+1];
    columna iter = col, borro;
    int pos;
    strcpy(aux, condicionEliminar);
    buscar_operador(operador, condicionEliminar);
    nomCol = strtok(aux, operador);
    while(iter->ant != NULL)// Va hasta la primera columna. 
        iter = iter->ant;
    if(strcmp(operador, "#") != 0){
        while(strcmp(iter->nombreCol, nomCol) != 0)// Busca la columna con el dato a eliminar.
            iter = iter->sig;
    }
    valor = strtok(NULL, operador);
    if(strcmp(operador, "#") != 0){
        pos = posicion_tupla(iter->d, valor, operador);
        while(pos != -1){
            borro = col;
            while(borro->ant != NULL)
                borro = borro->ant;
            while(borro != NULL){
                eliminarTupla(borro->d, pos); //Elimina la tupla encontrada.
                borro = borro->sig;
            }
            pos = posicion_tupla(iter->d, valor, operador); // Busca si hay otra tupla que cumpla con la condicion.
        }
    }else{
        while(iter->d != NULL){
            while(iter->ant != NULL)
                iter = iter->ant;
            while(iter != NULL){
                eliminarTupla(iter->d, 0);
                iter = iter->sig;
            }
            iter = col;
        }
    }
}   

void buscar_operador(char *operador, char *condicionEliminar){
    char *aux = new char[strlen(condicionEliminar)+1];
    strcpy(aux, condicionEliminar);
    if(strstr(aux, "=") != NULL)
        strcpy(operador, "=");
    else if(strstr(aux, "!") != NULL)
        strcpy(operador, "!");
    else if(strstr(aux, "<") != NULL)
        strcpy(operador, "<");
    else if(strstr(aux, ">") != NULL)
        strcpy(operador, ">");
    else
        strcpy(operador, "#");
}

bool eliminarTupla_valida(columna col, char *condicionEliminar){
    char *operador = new(char), *aux = new char[strlen(condicionEliminar)+1], *token = new(char);
    columna iter = col;
    strcpy(aux, condicionEliminar);
    buscar_operador(operador, aux);
    token = strtok(aux, operador);
    while(iter->ant != NULL){
        iter = iter->ant;
    }
    if(strcmp(operador, "#") != 0){
        while(iter != NULL && strcmp(token, iter->nombreCol) != 0){
            iter = iter->sig;
        }
        if(iter == NULL){
            return false;
        }
    }
    else if(iter->d == NULL){
        return false;
    }
    return true;
}
void printMetadata_col(columna col){
    columna iter = col;
    while(iter->ant != NULL)
        iter = iter->ant;
    while(iter != NULL){
        cout << iter->nombreCol << " -> Tipo de Dato: ";
            if(iter->tipoCol==0)
                cout << "INTEGER";
            else
                cout << "STRING";
        cout << ", Calificador: ";
            if(iter->calCol==0)
                cout << "NOT_EMPTY" << endl;
            else if(iter->calCol==1)
                cout << "PRIMARY_KEY" << endl;
            else    
                cout << "ANY" << endl;
        iter=iter->sig;
    }
}

bool Columnas_pertenecen(columna col, char *nomColumnas){
    if(Existe_col(col, nomColumnas))
        return true;
    else
        return false;
}

void select(columna T1col, columna &T2col, char *nomColumnas){
    columna iter1 = T1col;
    char *Columnas = new char[strlen(nomColumnas)+1];
    char *aux = new(char);
    strcpy(Columnas, nomColumnas);
    aux = strtok(Columnas, ":");
    while(aux != NULL){
        while(iter1->ant != NULL) // Va hasta el principio de las columnas.
            iter1 = iter1->ant;
        while(strcmp(iter1->nombreCol, aux) != 0) // Sale cuando encuentra el nombre.
            iter1 = iter1->sig;
        T2col = CopyCol(iter1, T2col);
        aux = strtok(NULL, ":");
    }

}

columna CopyCol(columna col1, columna col2){
    columna nuevaCol = new (nodo_columna);
    nuevaCol->nombreCol = new char[NOM];
    strcpy(nuevaCol->nombreCol, col1->nombreCol);
    nuevaCol->tipoCol = col1->tipoCol;
    nuevaCol->calCol = col1->calCol;
    nuevaCol->d = col1->d;
    nuevaCol->sig = NULL;

    if(col2 == NULL)                         // Si nuevaCol es la primera columna de la tabla.
        nuevaCol->ant = NULL;
    else{                                   // Si ya hay columnas en la tabla. 
        columna iter = col2;
        while(iter->sig != NULL)
            iter = iter->sig;
        iter->sig = nuevaCol;
        nuevaCol->ant = iter;
    }
    return nuevaCol;
}