/* 
 * File:   MemHandler.h
 * Author: ellioth
 *
 * Created on March 22, 2016, 9:10 PM
 */

#ifndef MEMHANDLER_H
#define	MEMHANDLER_H
#include "Constantes.h"
#include "Lista.h"
#include "Nodo.h"
#include "servidor.h"
#include <string>
#include <string.h>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

class MemHandler :public Constantes {
public:
    MemHandler(int port,long pMemorySize);
    virtual ~MemHandler();
    void LoopForService();
private:
    servidor * _servidor;
    lista * _listaDatosAlmacenados;
    void* _chuckMemory;
    void* _writerMemoryPointer;
    const char* _diskLocation;
    long _MemoryLeft;
    long _DiskLeft;
    long _DiskPointer;
    long _Memory_Size;
    void PassToDisk();
    void writeOnMemory(const char* mensaje);
    void readOnMemory(const char * mensaje);
    void delOnMemory(const char * mensaje);
};

#endif	/* MEMHANDLER_H */

