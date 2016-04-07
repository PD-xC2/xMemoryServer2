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
#include <c++/4.6/iosfwd>
//#include "MemHandler.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" 


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
    char JsonExample[]="{\"id\":0,\"op\":1, \"msg\":{\"name\":1234,\"edad\":20}}";
    //MemHandler * nuevo = new MemHandler(5000,"server_datas.txt");
    rapidjson::Document _JsonParser;
    _JsonParser.ParseInsitu(JsonExample);
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
    /* funciona tal y como lo esperaba!!
    rapidjson::Document prueba;
    prueba.Parse(Jsoanidado.c_str());
    rapidjson::Value & prueba2= prueba["name"];
    std::cout<<prueba2.GetInt()<<std::endl;*/
    /*char json[Jsoanidado.length()+1];
    strcpy(json,Jsoanidado.c_str());
    json[Jsoanidado.length()]='\0';
    std::fstream escribir("server_datas.txt");
    escribir.seekg(0,std::ios::end);
    escribir.write(json,Jsoanidado.length());
    escribir.close();*/
    return 0;
}

