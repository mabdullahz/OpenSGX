/*
 *  Copyright (C) 2015, OpenSGX team, Georgia Tech & KAIST, All Rights Reserved
 *
 *  This file is part of OpenSGX (https://github.com/sslab-gatech/opensgx).
 *
 *  OpenSGX is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OpenSGX is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with OpenSGX.  If not, see <http://www.gnu.org/licenses/>.
 */

// test network recv

#include "test.h"

// one 4k page : enclave page & offset
// Very first page chunk should be 4K aligned
void enclave_main(int argc, char const *argv[])
{
    int port = atoi(argv[2]);
    int srvr_fd;
    int clnt_fd;
    char buf[256];
    struct sockaddr_in addr;

    srvr_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (srvr_fd == -1) {
        sgx_exit(NULL);
    }
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(srvr_fd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        sgx_exit(NULL);
    }

    if (listen(srvr_fd, 10) != 0) {
        sgx_exit(NULL);
    }

    struct sockaddr_in addres;
    socklen_t len = sizeof(addres);
    clnt_fd = accept(srvr_fd, (struct sockaddr *)&addres, &len);
    if (clnt_fd < 0) {
        puts("ERROR on accept\n");
    }
    memset(buf, 0, 256);
    int n;
/*
    int retQ, retT, retC;
    // Quoting Enclave
    int quote_port = 8026;
    int challenger_port = 8025;
    retQ = sgx_remote_attest_quote(quote_port);

    // Target Enclave
    char *conf = "../user/demo/simple-remote-attest-quote.conf";
    retT = sgx_remote_attest_target(challenger_port, quote_port, conf);

    // Challenger Enclave
    const char *target_ip = "127.0.0.1";
    int target_port = 8025;
    const char *challenge = "Are you SGX enclave?";
    retC = sgx_remote_attest_challenger(target_ip, target_port, challenge);
*/
    while (1) {
        
        //int n = sgx_read(clnt_fd, buf, 255);
        n = read(clnt_fd, buf, 256, 0);
        if (n < 0)
            puts("ERROR on read\n");

        puts(buf);
        //n = sgx_write(clnt_fd, "Successfully received", 21);
        n = send(clnt_fd, "Successfully received", 21, 0);
        if (n < 0)
            puts("ERROR on write\n");

        //close(clnt_fd);
    }

    close(clnt_fd);
    close(srvr_fd);

    sgx_exit(NULL);
}


// #include "test.h"
// #include <unistd.h>
// #include <stdlib.h>

// // one 4k page : enclave page & offset
// // Very first page chunk should be 4K aligned
// void enclave_main(int argc, char const *argv[])
// {
//     int port = 5566;
//     //int port = atoi(argv[2]);
//     int enclave_addr;
//     int clnt_fd;
//     char buf[256];
//     struct sockaddr_in addr;
//     int valread;

//     enclave_addr = socket(PF_INET, SOCK_STREAM, 0);
    
//     // puts(argv[2]);

//     if (enclave_addr == -1) {
//         sgx_exit(NULL);
//     }

//     memset(&addr, 0, sizeof(addr));
//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(port);
//     addr.sin_addr.s_addr = INADDR_ANY;
       
//     // Forcefully attaching socket to the port 8080 
//     if (bind(enclave_addr, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
//         puts("Bind error");
//         sgx_exit(NULL);
//     }

//     puts("Listening!");
//     if (listen(enclave_addr, 10) != 0) {
//         puts("Listen error");
//         sgx_exit(NULL);
//     }

//     // struct sockaddr_in addr;
//     socklen_t len = sizeof(addr);
//     if ((clnt_fd = accept(enclave_addr, (struct sockaddr *)&addr, &len)<0)){ 
//         puts("Client Connection Error!"); 
//     }
//     else{
//         puts("Client Accepted");
//     }

//     read( clnt_fd , buf, 1024); 
//     puts(buf);

//     char *message = "Enclave hello";
//     send(clnt_fd , message , strlen(message) , 0 );     
//     // puts("Waiting for client message!");
//     // valread = read( clnt_fd , buf, 1024); 
//     // printf("%s\n",buf );
//     // send(clnt_fd , message , strlen(message) , 0 ); 
//     // printf("Enclave message sent\n");

//     sgx_exit(NULL);
// }
