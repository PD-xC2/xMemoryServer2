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

using namespace rapidjson;

class MemHandler :public Constantes {
public:
    MemHandler(int port, char* DiskLocation);
    virtual ~MemHandler();
    void LoopForService();
private:
    Document _JsonDocument;
    servidor * _servidor;
    lista * _listaDatosAlmacenados;
    void* _chuckMemory;
    void* _writerMemoryPointer;
    char* _diskLocation;
    int _MemoryLeft;
    int _DiskLeft;
    int _DiskPointer;
    void PassToDisk();
    void writeOnMemory(const char* mensaje);
    void readOnMemory(const char * mensaje);
};

#endif	/* MEMHANDLER_H */

