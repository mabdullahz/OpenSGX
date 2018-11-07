//taken from https://www.geeksforgeeks.org/socket-programming-cc/

// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{
    struct sockaddr_in serv_addr, enclave_addr; 
    int server_sock = 0, valread, enclave_sock = 0; 
    char *message = "message from client"; 
    char buffer[1024] = {0}; 
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(atoi(argv[2])); 
    
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(server_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    send(server_sock , message , strlen(message) , 0 ); 
    printf("Clinet message sent\n"); 
    valread = read( server_sock , buffer, 1024); 
    printf("%s\n",buffer );
    sleep(2);

    if ((enclave_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    }

    memset(&enclave_addr, '0', sizeof(enclave_addr)); 
   
    enclave_addr.sin_family = AF_INET; 
    enclave_addr.sin_port = htons(atoi(buffer)); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, argv[1], &enclave_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(enclave_sock, (struct sockaddr *)&enclave_addr, sizeof(enclave_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    else {
        printf("Connection to Enclave successful!\n");
    }
     
    send(enclave_sock, "From client to enclave", 22, 0);
    char buffer2[1024] = {0};

    while (1) {
    	
    	read( enclave_sock , buffer2, 1024); 
    	printf("From enclave:");
    	puts(buffer2);
    	sleep(3);
    	send(enclave_sock, "From client to enclave", 22, 0);
    }
    // send(enclave_sock , message , strlen(message) , 0 ); 
    // printf("Client message sent\n"); 
    // valread = read( enclave_sock , buffer, 1024); 
    // printf("%s\n",buffer );

    return 0; 
} 