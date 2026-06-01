#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 8080

int main(int argc, char const* argv[]) {

    char server_message[256] = "You have reached the server";

    // Creating a TCP socket with IPV4
    // Confirm the socket has been created
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("Server socket could not be created %d\n", server_socket);
        exit(EXIT_FAILURE);
    }


    // Initaliing the address fields
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;


    // Bind the socket to the address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("Socket binding has failed\n\n");
        exit(EXIT_FAILURE);
    };


    if (listen(server_socket, 5) < 0) {
        printf("Socket listening failed\n\n");
        exit(EXIT_FAILURE);
    }else {
        printf("The server is listening....\n\n");
    }

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    if (client_socket < 0) {
        printf("Client socket is negative, couldn't accept");
        exit(EXIT_FAILURE);
    }

    send(server_socket, server_message, sizeof(server_message), 0);
    close(server_socket);
    close(client_socket);

    return 0;

}