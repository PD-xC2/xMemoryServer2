/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on March 22, 2016, 9:08 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "MemHandler.h"
#include <math.h>
/*
 * 
 */
int main(int argc, char** argv) {
    /*pruebas del memHandler
    if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided or size of memory\n");
         exit(1);
    }*/
    std::cout<<"ingrese el puerto donde establecer el servidor"<<std::endl;
    int port;
    cin>>port;
    std::cout<<"ingrese la cantidad de espacio que desea ofrecer(en megas)"<<
            std::endl;
    long space;
    cin>>space;
    double temp= pow(1024,2);
    space*=temp;
    MemHandler * nuevo = new MemHandler(port,space*temp);
    /**
     * ejemplo, si no funciona lo anterior, pruebe con este
     * MemHandler * nuevo = new MemHandler(5000,256);
     */
    return 0;
}

