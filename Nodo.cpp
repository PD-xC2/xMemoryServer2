/* 
 * File:   Nodo.cpp
 * Author: ellioth
 * 
 * Created on March 30, 2016, 12:25 AM
 */

#include "Nodo.h"
/**
 * contructor de la clase, este recibe un Id y el dato, que el
 * id es el tamaño de datos que guardamos en memoria y el pData
 * es la posicion en memoria en donde guardamos ese dato.
 * @param pId dato ripo entero, es el tamaño del dato que guardamos
 * en memoria o disco.
 * @param pData dato tipo entero, esta es la posicion en memoria 
 * o disco en donde guardamos los datos.
 */
Nodo::Nodo(int pId, int pData, int pSize) {
    _IdData= pId;
    _AtSpaceSave= pData;
    _SizeData=pSize;
    _saveAtDisk=false;
}

Nodo::~Nodo() {
}

int Nodo::getSpaceSave() {
    return _AtSpaceSave;
}

/**
 * metodo para establecer el espacio de memoria o 
 * disco donde guardamos los datos.
 * @param pSpace recibe un dato tipo entero que es el espacio
 * donde se le guardo al dato.
 */
void Nodo::setSpaceSave(int pSpace) {
    _AtSpaceSave= pSpace;
}

/**
 * metodo para obtener el id de un nodo, este es 
 * el tamañp 
 * @return 
 */
int Nodo::getID() {
    return _IdData;
}

/**
 * metodo para obtener la cantidad de memoria que se esta usando para
 * guardar el dato.
 * @return retorna un dato tipo entero.
 */
int Nodo::getSizeSave() {
    return _SizeData;
}

/**
 * metodo para darnos cuenta cuando un dato se paso 
 * a guardar a disco.
 * @return retorna un dato tipo booleano si es falso o no.
 */
bool Nodo::saveAtDisk() {
    return _saveAtDisk;
}

/**
 * metodo para indicar que un dato se pasa a que se 
 * guarde de memoria a disco.
 */
void Nodo::setSaveDisk() {
    _saveAtDisk=true;
}

Nodo* Nodo::getNext() {
    return _next;
}

void Nodo::setNext(Nodo* pNext) {
    _next=pNext;
}

