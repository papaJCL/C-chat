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

void client(){
    cout << "On client side!" << endl;
}

 

int main(int argc, char *argv[]) {
    
    int opt; 
    while((opt = getopt(argc, argv, ":if:lrx")) != -1)  {  
        if (char(optopt) == 'h'){
            help();
        }
        else if (char(optopt) == 'p'){
            
            client();
        }
    } 
    
    if (argc == 1){
        server();
    }
    
    
    return 0;
}

