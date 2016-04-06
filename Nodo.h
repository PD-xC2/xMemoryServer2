/* 
 * File:   Nodo.h
 * Author: ellioth
 *
 * Created on March 30, 2016, 12:25 AM
 */

#ifndef NODO_H
#define	NODO_H

/**
 * clase que crea nodos para uso en la lista.
 */
class Nodo {
public:
    Nodo(int pId,int pData, int pSize);
    virtual ~Nodo();
    Nodo* getNext();
    void setNext(Nodo* pNext);
    int getSpaceSave();
    int getSizeSave();
    int getID();
    void setSpaceSave(int pSpace);
    void setSaveDisk();
    bool saveAtDisk();
private:
    int _IdData;
    int _AtSpaceSave;
    int _SizeData;
    Nodo* _next;
    bool _saveAtDisk;
};

#endif	/* NODO_H */

