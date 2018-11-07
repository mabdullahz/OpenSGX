//taken from https://www.geeksforgeeks.org/socket-programming-cc/

// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8081

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *message = "message from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    else {
        puts("Client Accepted!");
    }
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer );

    char enclavePort[20];
    int port = rand() % 10000 + 5000;
    sprintf(enclavePort, "%d", port);

    //char * command = "cd /home/frostmourne/Desktop/opensgx-6cc1fe695b61bd34eed199402b8ea575a6fe49ed/user && ./test.sh test/golum ";
    char * command = "cd /home/gollum/Downloads/opensgx-6cc1fe695b61bd34eed199402b8ea575a6fe49ed/user && ./test.sh test/golum ";
    char * finalCommand[100];

    puts("HERE");
    strcpy(finalCommand, command);

    strcat(finalCommand, enclavePort);
    send(new_socket , enclavePort , strlen(enclavePort) , 0 ); 
    puts("HEREeeee");
    printf("message message sent\n"); 
    system(finalCommand); // invokes the enclave
    close(server_fd);

    

    return 0; 
}