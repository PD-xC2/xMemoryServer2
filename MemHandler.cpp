/* 
 * File:   MemHandler.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 9:10 PM
 */
#include "MemHandler.h"

/**
 * construtor de la clase, recibe un dato, que es el puerto 
 * por donde instancearemos el server.
 * @param port puerto por donde instancearemos nuestro programa
 * @param DiskLocation lugar donde guardaremos los archivos del server
 */
MemHandler::MemHandler(int port, const char* DiskLocation) {
    _servidor= new servidor(port);
    _chuckMemory=malloc(SPACE_MEMORY);
    _writerMemoryPointer=_chuckMemory;
    _MemoryLeft=SPACE_MEMORY;
    _DiskLeft=SPACE_MEMORY;
    _diskLocation=DiskLocation;
    _DiskPointer=CERO;
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
        string IncommingMessage= _servidor->listenMsg();
        rapidjson::Document _JsonDocument;
        _JsonDocument.Parse(IncommingMessage.c_str());
        if(!_JsonDocument.IsObject()){
            std::cout<<"falla, archivo no es tipo json"<<std::endl;
            return;
        }
        rapidjson::Value & data = _JsonDocument[OPERATION];
        int op= data.GetInt();
        if(op==WRITE){
            writeOnMemory(IncommingMessage.c_str());
            _servidor->sendMsg("save\0",CINCO);
        }
        else if(op==READ){
            readOnMemory(IncommingMessage.c_str());
        }
        else if(op==DEL){
            delOnMemory(IncommingMessage.c_str());
            _servidor->sendMsg("del\0",CUATRO);
        }
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
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(mensaje);
    //obtenemos el id
    rapidjson::Value & idFromJson= _JsonDocument[ID];
    int id= idFromJson.GetInt();
    //buscamos el nodo.
    Nodo* temp= _listaDatosAlmacenados->getHead();
    while(temp!=NULL){
        if(temp->getID()==id)
            break;
        temp= temp->getNext();
    }
    std::cout<<"prueba5"<<std::endl;
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
        void * SpaceOnMemory=(_chuckMemory+space);
        for(int i=0; i<size; i++){
            *(dato+i)=*((char*)SpaceOnMemory+i);
        }
        dato[size]='\0';
        _servidor->sendMsg(dato,size+UNO);
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
        dato[size]='\0';
        _servidor->sendMsg(dato,size+UNO);
    }
}

/**
 * metodo para escribir los datos que se le pasen, este es el 
 * Json que se le pasa desde el cliente.
 * @param mensaje recibe un dato tipo const char* que es el Json que
 * se recibio desde el server.
 */
void MemHandler::writeOnMemory(const char* mensaje) {
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(mensaje);
    rapidjson::Value& getDataOfJson= _JsonDocument[MSG];
    //string para obtener el largo de caracteres de la cadena.
    //**no sirve para nada mas**
    rapidjson::StringBuffer sbr;
    rapidjson::Writer<rapidjson::StringBuffer>writer(sbr);
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
    else if(sizeOfData>_DiskLeft){
        _servidor->sendMsg((char*)MEMORY_LEAK,DIEZ+DOS);
        return;
    }
    /*ciclo para escribir sobre la memoria, mientras esta aun le quede
    espacio, crea la variable mensajeFormJson para que se guarde nada
     mas el mensaje propio del dato y no la opracion que se realiza
     o el id del archivo, ya que de esa informacion se encarga la lista
     de los datos guardados en memoria*/
    strcpy((char*)_writerMemoryPointer,getMsgDatas.c_str());
    _writerMemoryPointer+=sizeOfData;
    _MemoryLeft-=sizeOfData;
    //guardamos los datos de punteo a la memoria del nuevo mensaje que 
    //acabamos de guardar.
    _listaDatosAlmacenados->insert(idOfData,spaceOfMemory,sizeOfData);
}

/**
 * metodo para eliminar los datos de la memoria o disco.
 * @param mensaje recibe un dato tipo const char* que es el
 * Json que contiene el Id del mensaje.
 */
void MemHandler::delOnMemory(const char* mensaje) {
    //parseamos el documento
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(mensaje);
    //obtenemos el id
    rapidjson::Value & idFromJson= _JsonDocument[ID];
    int id= idFromJson.GetInt();
    _listaDatosAlmacenados->borrar(id);
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
                diskWriter.seekg(_DiskPointer);
                //obtenemos los datos del json que vamos a guardar
                int DiskPointer= diskWriter.tellg();
                int space=temp->getSpaceSave();
                int size=temp->getSizeSave();
                //obtenemos el puntero de la memoria
                PointerOfMemory=(_chuckMemory+space);
                //escribimos en disco
                diskWriter.write((char*)PointerOfMemory,size);
                //alteramos los datos internos del nodo.
                temp->setSaveDisk();
                temp->setSpaceSave(DiskPointer);
                //movemos el puntero del disco
                _DiskLeft-=size;
                _DiskPointer+=size;
            }
            temp= temp->getNext();
        }
        //cerramos el archivo
        diskWriter.close();
    }
    //limpiamos la memoria y reestablecemos los datos de escritura en memoria
    bzero(_chuckMemory,SPACE_MEMORY);
    _writerMemoryPointer=_chuckMemory;
    _MemoryLeft=SPACE_MEMORY;
}
