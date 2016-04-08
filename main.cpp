/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on March 22, 2016, 9:08 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "Lista.h"
#include "Nodo.h"
#include "MemHandler.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

const char* getJson(){
    char* temp= (char*)std::malloc(57);
    std::cout<<"prueba1"<<std::endl;
    fstream readFromDisk("server_datas.txt");
    std::cout<<"prueba2"<<std::endl;
    readFromDisk.seekg(0);
    std::cout<<"prueba3"<<std::endl;
    readFromDisk.read(temp,56);
    std::cout<<"prueba4"<<std::endl;
    temp[56]='\0';
    string tempLocal=temp;
    std::cout<<tempLocal.length()<<std::endl;
    return (const char*)temp;
}

/*
 * 
 */
int main(int argc, char** argv) {
    //prueba para cortar cadena de caracteres
    /* 
    char* temp= "12345678901234567890\0";
    string data= temp;
    string nuevo= data.substr(0,(data.length()-10));
    nuevo.append("}\0");
    cout<<temp<<endl;
    cout<<nuevo<<endl;*/
    
    //pruebas del memHandler
    MemHandler * nuevo = new MemHandler(5000,"server_datas.txt");
    /*lista * list = new lista();
    list->insert(0,0,23);
    list->insert(2,23,46);
    list->insert(5,46,69);
    list->insert(3,69,92);
    Nodo* temp =list->getHead();
    for(int i =0; i<list->getSize(); i++){
        std::cout<<"id:"<<temp->getID()<<",space:"<<temp->getSpaceSave()<<",size:"<<temp->getSizeSave()<<std::endl;
        temp=temp->getNext();
    }
    /*const char* temp1="{\"id\":0,\"op\":1,\"msg\":{\"name\":1234,\"edad\":20}}";
    string JsonExample=getJson();
     //{"id":0,"op":1, "msg":{"name":1234,"edad":20}}
    rapidjson::Document _JsonParser;
    _JsonParser.Parse(JsonExample.c_str());
    rapidjson::Value & Data= _JsonParser["id"];
    int _id= Data.GetInt();
    Data=_JsonParser["op"];
    int _op=Data.GetInt();
    Data=_JsonParser["msg"];
    rapidjson::StringBuffer sbr;
    rapidjson::Writer<rapidjson::StringBuffer>writer(sbr);
    Data.Accept(writer);
    std::cout<<"id:"<<_id<<",op:"<<_op<<std::endl;
    std::string Jsoanidado= sbr.GetString();
    std::cout<<Jsoanidado<<std::endl;
    std::free(temp);
    /* //funciona tal y como lo esperaba!!
    rapidjson::Document prueba;
    prueba.Parse(Jsoanidado.c_str());
    rapidjson::Value & prueba2= prueba["name"];
    std::cout<<prueba2.GetInt()<<std::endl;
    char json[Jsoanidado.length()+1];
    strcpy(json,Jsoanidado.c_str());
    json[Jsoanidado.length()]='\0';
    std::fstream escribir("server_datas.txt");
    escribir.seekg(0,std::ios::end);
    escribir.write(json,Jsoanidado.length());
    escribir.close();*/
    return 0;
}

