/* 
 * File:   Constantes.h
 * Author: ellioth
 *
 * Created on March 22, 2016, 1:53 PM
 */

#ifndef CONSTANTES_H
#define	CONSTANTES_H

class Constantes {
public:
    //constantes varias
    static const int CERO=0;
    static const int UNO=1;
    static const int DOS=2;
    static const int TRES=3;
    static const int CUATRO=4;
    static const int CINCO=5;
    static const int SEIS=6;
    static const int SIETE=7;
    static const int DIEZ=10;
    static const bool DEBUG=true;
    static const int CIENTO_VEINTE_OCHO=128;
    static const int SPACE_MEMORY=128;
    //ubiciacion del archivo donde se va a escribir en disco
    static const char* DISK_LOCATION;
    static const int WRITE=1;
    static const int READ=0;
    static const int DEL=2;
    //char para extraer el id del json
    static const char* ID;
    //char para extraer la operacion solicitada(W=1,R=0,Del=2)
    static const char* OPERATION;
    //char para extraer el mensaje dentro del json
    static const char* MSG;
    //char par avisarle al cliente que se acaba de sufrir un memory leak
    static const char* MEMORY_LEAK;
    /*-------errores por parte del server------*/
    //error de apertura en socket
    static const char* ERROR1;
    //error en binding del socket
    static const char* ERROR2;
    //error en la aceptacion del cliente
    static const char* ERROR3;
    //error en la escritura del socket
    static const char* ERROR4;
    //error en la lectura del socket
    static const char* ERROR5;
};

#endif	/* CONSTANTES_H */

