/* 
 * File:   lista.cpp
 * Author: ellioth
 * 
 * Created on March 30, 2016, 12:24 AM
 */

#include "Lista.h"

lista::lista() {

}

lista::~lista() {
}

/**
 * metodo para insertar en la cola de la lista.
 * @param pData recibe un dato, en este caso seria
 * un numero entero.
 */
void lista::insert(int pID,int pSpace, int pSize) {
    if(_head==NULL){
        _head=new Nodo(pID,pSpace,pSize);
        _size++;
        return;
    }
    Nodo* temp=_head;
    while(temp->getNext()!=NULL)
        temp=temp->getNext();
    Nodo* nuevo= new Nodo(pID,pSpace,pSize);
    temp->setNext(nuevo);
    _size++;
}

/**
 * metodo para borrar un nodo de la lista, si es que
 * este existe en la lista.
 * @param pData recibe un dato tipo pData, este es el
 * dato que se requiere eliminar.
 */
void lista::borrar(int pID) {
    if(_head==NULL)
        return;
    else if(_head->getID()==pID){
        Nodo* temp= _head;
        _head=_head->getNext();
        delete temp;
        _size--;
        return;
    }
    Nodo* temp=_head;
    while(temp->getNext()!=NULL ||temp->getNext()->getID()==pID)
        temp=temp->getNext();
    if(temp->getNext()==NULL && temp->getID()!=pID){
        if(DEBUG)cout<<"dato no existe"<<endl;
        return;
    }
    else{
        Nodo* toDelete= temp->getNext();
        Nodo* next= temp->getNext()->getNext();
        temp->setNext(next);
        if(toDelete!=NULL)
            delete toDelete;
        _size--;
    }
}

/**
 * metodo para obtener la cabeza de la lista, este es el nodo
 * principal de acceso a la lista.
 * @return retorna un dato tipo 'Nodo'; esta es la cabeza de la lista.
 */
Nodo* lista::getHead() {
    return _head;
}

/**
 * metodo usado para obtener el tamaño de la lista.
 * @return retorna un dato tipo entero que es el tamaño
 * de la lista.
 */
int lista::getSize() {
    return _size;
}
