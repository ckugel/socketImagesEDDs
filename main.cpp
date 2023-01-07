#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

struct sockaddr_in address;
const int addrlen = sizeof(address);
int server_fd;

void handShake(char* buffer) {
    int new_socket, valread;
    new_socket = accept(server_fd, (struct sockaddr*) &address,(socklen_t*) &addrlen);

    valread = read(new_socket, buffer, 1024);
    
    printf("%s\n", buffer);
    // closing the connected socket
    close(new_socket);
}

int main(int argc, char const* argv[]) {
    int opt = 1;
    char* buffer = new char[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0) {
        std::cout << "Failed to bind" << std::endl;
    }

    if (listen(server_fd, 3) < 0) {
        std::cout << "Failed to listen" << std::endl;
    }


    handShake(buffer);

    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}