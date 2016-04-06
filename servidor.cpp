/* 
 * File:   servidor.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 1:52 PM
 */

#include "servidor.h"

servidor::servidor(int port) {
    _portno= port;
    _dataRecivedFromSocket= malloc(DOSCIENTOS_CINCUENTA_Y_SEIS);
    bzero(_dataRecivedFromSocket,DOSCIENTOS_CINCUENTA_Y_SEIS);
    _sockfd = socket(AF_INET, SOCK_STREAM, CERO);
    //resivision de si la conexion del socket 
    // fue positiva o fallida.
    if (_sockfd <CERO)
        error(ERROR1);
    //se escibe 0s en la variables puesta.
    //esto garantiza que no se use memoria sucia.
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    //establecemos los datos que se van a utilizar 
    //en el socket.
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(_portno);
    if (bind(_sockfd, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr))<CERO)
        error(ERROR2);
    //se pone a escuchar en el socket si hay nuevas conexiones.
    listen(_sockfd,CINCO);
    _clilen = sizeof(_cli_addr);
    _newsockfd = accept(_sockfd, (struct sockaddr*) &_cli_addr, &_clilen);
    if (_newsockfd < CERO)
        error(ERROR3);
    if(DEBUG)
        printf("servidor: got connection from %s port %d\n",
                inet_ntoa(_cli_addr.sin_addr), ntohs(_cli_addr.sin_port));
    close(_sockfd);
}

servidor::~servidor() {
}

char* servidor::listenMsg() {
    bzero(_dataRecivedFromSocket, DOSCIENTOS_CINCUENTA_Y_SEIS);
    _n = recv(_newsockfd,_dataRecivedFromSocket,
            DOSCIENTOS_CINCUENTA_Y_SEIS-UNO,0);
    if(_n<CERO)
        error(ERROR3);
    return (char*)_dataRecivedFromSocket;
    
}

void servidor::error(const char* msg) {
    perror(msg);
    exit(UNO);
}

void servidor::sendMsg(char* pMsg, int pSize) {
    _n=send(_newsockfd, pMsg, pSize,0);
    if (_n < CERO) 
        error(ERROR5);
    if(DEBUG)
        cout<<"mensaje enviado"<<endl;
}
