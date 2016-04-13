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
    void insert(int pID,long pSpace, long pSize);
    void borrar(int pID);
    Nodo* getHead();
    int getSize();
    bool find(int pID);
private:
    Nodo* _head;
    int _size;
};

#endif	/* LISTA_H */

