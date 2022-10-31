#include "columnas.h"
#include "dato.h"
#include "define.h"
#include "bd.h"
#include "tabla.h"
#include <string.h>
#include <iostream>

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
    /*if(col != NULL){
        while(col->ant != NULL) // Va al comienzo de las columnas.
            col = col->ant;
        while(col->calCol != ANY && col->sig != NULL) // Se fija si hay columnas no vacias.
            col = col->sig;
    }*/
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
    else{                                   //Si ya hay columnas en la tabla. 
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


bool colRep(columna col, char *nombCol)
{
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
    /*columna iter = col;
    char *aux = new(char), *aux2 = new(char);
    while (iter->ant != NULL) // Va hasta la primera columna.
        iter = iter->ant;
    aux = strtok (columnasTupla, ":");
    aux2 = strtok(valoresTupla, ":");
    while (iter != NULL &&(aux != NULL) && (aux2 != NULL)){
        if(!tupla_valida_para_columna(iter, aux, aux2))
            return false;
        else{
            if(iter->calCol != ANY){
                columnasTupla = &columnasTupla[strlen(aux) + 1];
                valoresTupla = &valoresTupla[strlen(aux2) + 1];
                if(columnasTupla != NULL)
                    aux = strtok(columnasTupla, ":");
                if (valoresTupla != NULL)
                    aux2 = strtok(valoresTupla, ":");
            }
            iter = iter->sig;
        }
    }
    if(aux != NULL && aux2 == NULL){
        cout << "Faltan valores para las columnas" << endl;
        return false;
    }
    else if(aux2 != NULL && aux == NULL){
        cout << "Se ingresaron mas valores que columnas" << endl;
        return false;
    }
    return true;*/
    columna iter = col;
    while(iter->ant != NULL)
        iter = iter->ant;
    if(!valor_PK(iter, columnasTupla))
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

bool tupla_valida_para_columna (columna col, char *columnasTupla){
    /*columna iter = col;
    //cout << "Nombre columna que entra: " << iter->nombreCol << endl;
    if(iter->calCol == ANY){
        //cout << column << "---->";
        //cout << valor << endl;
        return true;
    }
    while(iter->ant != NULL)
        iter = iter->ant;
    while(iter != NULL){
        if(strcmp(iter->nombreCol, column) == 0){
            //cout << "Nombre columna que iguala: " << iter->nombreCol << endl;
            //cout << column << "---->";
            //cout << valor << endl;
            return true;
        }
        else
            iter = iter->sig;
    }
    cout << col->nombreCol << " no es de tipo ANY debes asignarle un valor" << endl;
    //cout << column << "---->";
    //cout << valor << endl; 
    return false;*/
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

void insertarDato_col(columna &col, char *columnasTupla, char *valoresTupla){
    //insertarDato_d(valoresTupla);
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

/*bool pasan_col(columna col, char *column){
    columna iter = col;
    cout << col->nombreCol << " Entre con este nombre a pasan_col" << endl;
    while(iter != NULL){
        if (strcmp(iter->nombreCol, column) == 0){
            cout << "Consumi " << column << endl;
            return true;
        }
        iter = iter->sig;
    }
    //cout << "error pasan_col" << endl;
    return false;
}*/