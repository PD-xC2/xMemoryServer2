/* 
 * File:   servidor.h
 * Author: ellioth
 *
 * Created on March 22, 2016, 1:52 PM
 */

#ifndef SERVIDOR_H
#define	SERVIDOR_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <pthread.h>
#include <stdlib.h>
#include "Constantes.h"
#include "structs.h"

using namespace std;
class servidor : public Constantes{
public:
    servidor(int port);
    virtual ~servidor();
    void sendMsg(char* pMsg, int pSize);
    char* listenMsg();
private:
    pthread_t _hiloLectura;
    //datos propios de la instanciacion del servidor
    int _sockfd, _newsockfd, _portno, _n, _codigos;
    socklen_t _clilen;
    char* _id;
    void* _dataRecivedFromSocket;
    struct sockaddr_in _serv_addr, _cli_addr;
    void error(const char* msg);
    /**
     * metodo estatico para que inicialice el ciclo del servidor
     * que va a escuchar los pedidos del cliente, ya sea lectura o escritura.
     * (NO SE DEBE DE USAR POR FUENTES EXTERIORES)
     * @param data dato tipo servidor, este dato es el 'this' de esta clase.
     * @return no retorna nada para el usuario.
     */
    static void* startThreadLectura(void* data){
        return ((servidor*)data)->listenMsg();
    };
};

#endif	/* SERVIDOR_H */

