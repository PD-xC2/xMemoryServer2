/* 
 * File:   lista.h
 * Author: ellioth
 *
 * Created on March 30, 2016, 12:24 AM
 */

#ifndef LISTA_H
#define	LISTA_H
#include <stddef.h>
#include <iostream>
#include "Nodo.h"
#include "Constantes.h"

using namespace std;
class lista :public Constantes{
public:
    lista();
    virtual ~lista();
    void insert(int pID,int pSpace, int pSize);
    void borrar(int pData);
    Nodo* getHead();
    int getSize();
private:
    Nodo* _head;
    int _size;
};

#endif	/* LISTA_H */

