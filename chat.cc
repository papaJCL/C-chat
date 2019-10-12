#include <iostream>
#include <unistd.h>  
#include <stdlib.h>
#include <ctype.h>


using namespace std;


void server(){
    cout << "Welcome to chat!" << endl;
}

void help(){
    cout << "Welcome to the help menu!" << endl;
}

void client(string port, string IP){
    cout << "Port : " << port << endl;
    cout << "IP : " << IP << endl;
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

