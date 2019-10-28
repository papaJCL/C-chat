#include <iostream>
#include <unistd.h>  
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <algorithm>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <netdb.h>


using namespace std;


void server(){
    cout << "Welcome to chat!" << endl;
    
    int sockfd, newsockfd;
    char buffer[240];
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    
    int opt = 1;
    
    socklen_t addrlen = sizeof(client_addr);            
        
    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        cout << "Cannot create a socket" << endl;
        exit(1);
    }
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        exit(1);
    } 
        
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serv_addr.sin_port = htons( 8080 ); 
    
    
    if (bind(sockfd, (struct sockaddr *)&serv_addr,  sizeof(serv_addr))<0){
        cout << "Could not bind" << endl;
        exit(1);
    }
    
    char ip[INET_ADDRSTRLEN]; 
    inet_ntop(AF_INET, &(serv_addr.sin_addr), ip, INET_ADDRSTRLEN); 
    
    cout << "Waiting for a connection on\n" << ip << " port " << ntohs(serv_addr.sin_port) << endl;
    
    listen(sockfd, 2);
    socklen_t clilen = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clilen);
    if (newsockfd < 0) cout << "ERROR on accept";
    cout << "Found a friend! You receieve first!" << endl;
    
    while(true){
        int valread = read( newsockfd , buffer, 240);
        cout << "Friend: ";
        cout << buffer;
        cout << "You: ";
        bzero(buffer,240);
        fgets(buffer,240,stdin);
        while (strlen(buffer) > 140){
            cout << "Error: Input too long" << endl;
            cout << "You: ";
            bzero(buffer,240);
            fgets(buffer,240,stdin);
            if (strlen(buffer) < 141){
                send(newsockfd , buffer , strlen(buffer) , 0 ); 
                bzero(buffer,240); 
                continue;
            }
        }
        send(newsockfd , buffer , strlen(buffer) , 0 ); 
        bzero(buffer,240); 
    }
}

void client(string port1, string IP){    
    int sockfd;
        
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[240];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0){
        cout << "Cannot create a socket" << endl;
        exit(1);
    }
    
    
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serv_addr.sin_port = htons(8080); 
    
    socklen_t addr_size = sizeof serv_addr; 
    int con = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof serv_addr); 
    cout << "Connecting to server... " << endl;
    if (con == 0){
        cout << "Connected!" << endl;
        cout << "Connected to a friend! You send first! " << endl;
    }
    else{
        cout << "Could not connect to host!" << endl;
        exit(1);
    }
    while(true){
        cout << "You: ";
        bzero(buffer,240);
        fgets(buffer,240,stdin);
        if (strlen(buffer) > 140){
            cout << "Error: Input too long" << endl;
            continue;
        }
        send(sockfd , buffer , strlen(buffer) , 0 ); 
        bzero(buffer,240);
        int valread = read( sockfd , buffer, 240);
        cout << "Friend: " << buffer;
    }
    
    
}

void help(){
    cout << "Welcome to the help menu!" << endl;
    cout << "To use this program you want to have two terminals open" << endl;
    cout << "For the first terminal(server side) just type ./chat" << endl;
    cout << "For the second terminal(client side) type ./chat then -p with the port number then -s with the ip number(that is shown from the first terminal)" << endl;
    cout << "./chat -p 3760 -s 192.168.47.232" << endl;
    cout << "To see the help menu type ./chat -h" << endl;
    exit(1);
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

void checkClient(string port, string IP){
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
    client(port, IP);
}


int main(int argc, char *argv[]) {
    
    if (argc == 1){
        server();
    }
    else{
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
        checkClient(port,IP);
    }
    return 0;
}

