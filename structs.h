/* 
 * File:   structs.h
 * Author: ellioth
 *
 * Created on March 4, 2016, 11:57 AM
 */

#ifndef STRUCTS_H
#define	STRUCTS_H

/**
 * estructura para definir los 
 * datos del cliente cuando se usan 
 * hilos.
 */
struct ThreadClienteData{
    int sockFd;
    void* data;
};


#endif	/* STRUCTS_H */

