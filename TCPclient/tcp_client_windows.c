#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUFLEN 256

int main() {

    // declare and initialize variables
    WSADATA wsa_data;
    SOCKET network_socket = INVALID_SOCKET;
    struct sockaddr_in server_address;
    char server_response[BUFLEN];

    // initialize winsock
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    // create a socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect to server
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // check for error with the connection
    if (connection_status == 0) {
        printf("[+]Connection successful.\n\n");
    }
    else if (connection_status < 0) {
        printf("[-]Connection failed!\n\n");
    }

    // receive data from the server
    recv(network_socket, server_response, sizeof(server_response), 0);

    // print out server's response
    printf("The server sent the data: %s\n", server_response);

    // cleanup
    closesocket(network_socket);
    WSACleanup();

    return 0;
}