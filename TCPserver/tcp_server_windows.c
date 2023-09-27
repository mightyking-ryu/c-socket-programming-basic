#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUFLEN 256

int main() {

    // declare and initialize variables
    WSADATA wsa_data;
    SOCKET server_socket = INVALID_SOCKET;
    struct sockaddr_in server_address;
    char server_message[BUFLEN] = "You have reached the server!!!";

    // initialize winsock
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    // create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // listen for incomming connection requests
    listen(server_socket, 5);
    printf("[+]listening...\n");

    // accept the connection
    SOCKET client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    printf("[+]connected\n");

    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);

    // cleanup
    closesocket(server_socket);
    WSACleanup();

    return 0;
}