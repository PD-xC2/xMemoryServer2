/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on March 22, 2016, 9:08 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    char* temp= "12345678901234567890\0";
    string data= temp;
    string nuevo= data.substr(0,(data.length()-10));
    nuevo.append("}\0");
    cout<<temp<<endl;
    cout<<nuevo<<endl;
    return 0;
}

