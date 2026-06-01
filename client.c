#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080

int main(int argc, char const* argv[]) {

    // Creating a TCP socket with IPV4
    // Confirm the socket has been created
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket < 0) {
        printf("Network socket could not be created %d\n", network_socket);
        exit(EXIT_FAILURE);
    }


    //Initialize and define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect
    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status < 0) {
        printf("There was an error establishing connection to the server %d \n\n", connection_status);
        exit(EXIT_FAILURE);
    }

    char server_response[256];
    recv(network_socket, server_response, sizeof(server_response), 0);
    printf("The data received from the server is: %s\n\n", server_response);

    close(network_socket);


    return 0;
}