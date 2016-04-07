/* 
 * File:   MemHandler.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 9:10 PM
 */

#include <c++/4.6/iosfwd>

#include "MemHandler.h"

/**
 * construtor de la clase, recibe un dato, que es el puerto 
 * por donde instancearemos el server.
 * @param port dato tipo entero, es el puerto donde crearemos
 * el server.
 */
MemHandler::MemHandler(int port, const char* DiskLocation) {
    _servidor= new servidor(port);
    _chuckMemory=malloc(SPACE_MEMORY);
    _writerMemoryPointer=_chuckMemory;
    _diskLocation=DiskLocation;
    _listaDatosAlmacenados= new lista();
    LoopForService();
}

/**
 * destructor de la clase, se encarga de liberar toda la memoria 
 * que estabamos usando.
 */
MemHandler::~MemHandler() {
    free(_chuckMemory);
    _writerMemoryPointer=NULL;
    delete _listaDatosAlmacenados;
    delete _servidor;
}

/**
 * metodo usado para establecer el ciclo que infinito que se 
 * ejecutara por si solo y estara revizando para pedidos del cliente
 * y cuando el cliente envie algo, vamos a agarrar el mensaje,
 * parsearlo e indetificar lo que se ocupa para luego devolver lo
 * que se a pedido.
 */
void MemHandler::LoopForService() {
    //ciclo para esuchar los mensajes del cliente
    while(true){
        //obtenemos el mensaje.
        char* IncommingMessage= _servidor->listenMsg();
        _JsonDocument.Parse(IncommingMessage);
        Value & dataFromJson = _JsonDocument[OPERATION];
        int op= dataFromJson.GetInt();
        if(op==WRITE)
            writeOnMemory((const char*)IncommingMessage);
        else if(op==READ)
            readOnMemory((const char*)IncommingMessage);
    }
}

/**
 * metodo para leer los datos que se le soliciten,
 * ya sea desde disco o memoria.
 * @param mensaje recibe una dato tipo const char*, este es el Json 
 * que contendra el Id del dato que se nos pide.
 */
void MemHandler::readOnMemory(const char* mensaje) {
    //parseamos el documento
    _JsonDocument.Parse(mensaje);
    //obtenemos el id
    Value & idFromJson= _JsonDocument[ID];
    int id= idFromJson.GetInt();
    //buscamos el nodo.
    Nodo* temp= _listaDatosAlmacenados->getHead();
    while(temp!=NULL){
        if(temp->getID()==id)
            break;
        temp= temp->getNext();
    }
    //verificamos que el nodo no sea nulo
    if(temp==NULL){
        _servidor->sendMsg("NULL\0",CUATRO);
        return;
    }
    //verificamos que los datos esten en memoria.
    else if(!temp->saveAtDisk()){
        int space=temp->getSpaceSave();
        int size= temp->getSizeSave();
        char dato[size+UNO];
        void * SpaceOnMemory= (_chuckMemory+space);
        for(int i=0; i<size; i++){
            *(dato+i)=*((char*)SpaceOnMemory+i);
        }
        dato[size+UNO]='\0';
        _servidor->sendMsg(dato,size+UNO);
        delete [] dato;
    }
    //tomamos por hecho que los datos estan en disco
    else{
        int space=temp->getSpaceSave();
        int size= temp->getSizeSave();
        char dato[size+UNO];
        fstream readOnDisk(_diskLocation);
        if(readOnDisk.is_open()){
            readOnDisk.seekg(CERO);
            readOnDisk.seekg(space);
            readOnDisk.read(dato,size);
        }
        dato[size+UNO]='\0';
        _servidor->sendMsg(dato,size+UNO);
        delete [] dato;
    }
}

/**
 * metodo para escribir los datos que se le pasen, este es el 
 * Json que se le pasa desde el cliente.
 * @param mensaje recibe un dato tipo const char* que es el Json que
 * se recibio desde el server.
 */
void MemHandler::writeOnMemory(const char* mensaje) {
    _JsonDocument.Parse(mensaje);
    Value& getDataOfJson= _JsonDocument[MSG];
    //string para obtener el largo de caracteres de la cadena.
    //**no sirve para nada mas**
    StringBuffer sbr;
    Writer<StringBuffer>writer(sbr);
    getDataOfJson.Accept(writer);
    string getMsgDatas= sbr.GetString();
    //id del mensaje que nos esta entrando.
    getDataOfJson= _JsonDocument[ID];
    int idOfData=getDataOfJson.GetInt();
    //espacio en memoria donde se almacenara el dato
    int spaceOfMemory=(SPACE_MEMORY-_MemoryLeft);
    //tamaño del mensaje que nos esta entrando
    int sizeOfData=getMsgDatas.length();
    /*opcion por si ya no nos queda espacio en memoria, 
     en ese caso pasamos todo a disco y verificamos que aun nos quede 
     espacio en disco*/
    if(sizeOfData>=_MemoryLeft && sizeOfData<_DiskLeft){
        PassToDisk();
    }
    /*ciclo para escribir sobre la memoria, mientras esta aun le quede
    espacio, crea la variable mensajeFormJson para que se guarde nada
     mas el mensaje propio del dato y no la opracion que se realiza
     o el id del archivo, ya que de esa informacion se encarga la lista
     de los datos guardados en memoria*/
    char mensajeFromJson[getMsgDatas.length()+UNO];
    strcpy(mensajeFromJson,getMsgDatas.c_str());
    mensajeFromJson[getMsgDatas.length()]='\0';
    for(int i=0; i<sizeOfData; i++,_MemoryLeft--){
        //movemos el puntero
        _writerMemoryPointer+=i;
        //escribimos en la memoria.
        *((char*)_writerMemoryPointer)=*(mensajeFromJson+i);
    }
    //guardamos los datos de punteo a la memoria del nuevo mensaje que 
    //acabamos de guardar.
    _listaDatosAlmacenados->insert(idOfData,spaceOfMemory,sizeOfData);
}

/**
 * metodo para pasar todos los datos de la memoria al disco.
 */
void MemHandler::PassToDisk() {
    fstream diskWriter(_diskLocation);
    if(diskWriter.is_open()){
        Nodo* temp=_listaDatosAlmacenados->getHead();
        void* PointerOfMemory;
        for(int i=0; i<_listaDatosAlmacenados->getSize(); i++){
            if(!temp->saveAtDisk()){
                //movmevos el puntero del archivo a la ultima posicion
                diskWriter.seekg(CERO,ios::end);
                //obtenemos los datos del json que vamos a guardar
                int space=temp->getSpaceSave();
                int size=temp->getSizeSave();
                //obtenemos el puntero de la memoria
                PointerOfMemory=(_chuckMemory+space);
                //escribimos en disco
                diskWriter.write((char*)PointerOfMemory,size);
                //alteramos los datos internos del nodo.
                temp->setSaveDisk();
                temp->setSpaceSave(_DiskPointer);
                //movemos el puntero del disco
                _DiskLeft-=size;
            }
            temp= temp->getNext();
        }
        //cerramos el archivo
        diskWriter.close();
    }
    //limpiamos la memoria
    bzero(_chuckMemory,DOSCIENTOS_CINCUENTA_Y_SEIS);
}
