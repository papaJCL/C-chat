#include <iostream>
#include <unistd.h>  
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <algorithm>


using namespace std;


void server(){
    cout << "Welcome to chat!" << endl;
}

void help(){
    cout << "Welcome to the help menu!" << endl;
}
bool checkIfInt(string port){
    for (size_t  i = 0; i < port.length(); i++){
        if (isdigit(port[i]) == 0){
            return false;
        }
    }
    return true;
}

bool checkForPeriods(string IP){
    int counter = 0;
    for (size_t  i = 0; i < IP.length(); i++){
        if (IP[i] == '.'){
            counter++;
        }
    }
    if (counter == 0){
        return false;
    }
    return true;
}

bool CheckValidIPNumber(string IP){
    IP.erase(std::remove(IP.begin(), IP.end(), '.'), IP.end());
    if (checkIfInt(IP) == false){
        return false;
    }
    return true;
}

bool checkIP(string IP){
    if (checkForPeriods(IP) == false){
        return false;
    }
    if (CheckValidIPNumber(IP) == false){
        return false;
    }
    return true;
}

void client(string port, string IP){
    if (checkIP(IP) == false && checkIfInt(port)==false){
        cout << "Both IP Address and Port are not valid. Please try again!" << endl;
        exit (1);
    }
    else if (checkIP(IP) == false){
        cout << "Not a valid IP Address.Please try again!" << endl;
        exit (1);
    }
    else if (checkIfInt(port) == false){
        cout << "Port must be a number. Please try again!" << endl;
        exit (1);
    }
    
}




 

int main(int argc, char *argv[]) {
    
    if (argc == 1){
        server();
    }
    
    int opt; 
    string IP;
    string port;
    
    while((opt = getopt(argc, argv, "hp:s:")) != -1)  { 
        switch(opt)  {  
            case 'h':
                help();
                break;
            case 'p':
                port = optarg;
                break;
            case 's':
                IP = optarg;
                break;
        }
    }
    
    
    
    client(port,IP);
    
    
    
    
    return 0;
}

