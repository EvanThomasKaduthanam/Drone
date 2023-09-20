#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#define BUFF_LEN 512

// To Reciece Data
int recvData(SOCKET *ls)
{
    char recvBuff[BUFF_LEN];
    int recvBuffLen = BUFF_LEN;

    if (recv(*ls, recvBuff, recvBuffLen, 0) == SOCKET_ERROR)
    {
        wprintf(L"Recv Failed: %u \n", WSAGetLastError());
        closesocket(*ls);
        return 1;
    }
    else
    {
        std::cout << "Successful Recieve" << std::endl;
        return 0;
    }
}

// To Send Data
int sendData(SOCKET *ls)
{
    char SEND_BUFF[BUFF_LEN];
    int sendBuffLen = BUFF_LEN;

    if (send(*ls, SEND_BUFF, sendBuffLen, 0) == SOCKET_ERROR)
    {
        wprintf(L"Send Failed: %u \n", WSAGetLastError());
        closesocket(*ls);
        return 1;
    }
    else
    {
        std::cout << "Successful Send" << std::endl;
        return 0;
    }
}

// Future Work
int initSocket(SOCKET *ls)
{
    return 0;
}

int main(void)
{
    WSADATA wsaData;

    SOCKET listenSocket = INVALID_SOCKET;
    int iResult = 0;
    sockaddr_in server;

    char SEND_BUFF[BUFF_LEN];
    int sendBuffLen = BUFF_LEN;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        wprintf(L"Error: %u \n", WSAGetLastError());
        return 1;
    }

    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
        wprintf(L"Error: %u\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(9090);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (bind(listenSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        wprintf(L"Error: %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, 1) == SOCKET_ERROR)
    {
        wprintf(L"Error: %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    std::cout << "[LISTENING] server is listening for clients" << std::endl;

    SOCKET acceptSocket = INVALID_SOCKET;

    std::cout << "[ACCEPTING] server is accepting for clients" << std::endl;
    while (true)
    {
        acceptSocket = accept(listenSocket, NULL, NULL);
        if (acceptSocket == SOCKET_ERROR)
        {
            wprintf(L"Error: %u \n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        else
        {
            std::cout << "s[ACCEPTED] server accepted a client" << std::endl;
            std::cout << "Enter a string: " << std::endl;
            std::cin >> SEND_BUFF;
            if(send(acceptSocket, SEND_BUFF, sendBuffLen, 0) == SOCKET_ERROR)
            {
                wprintf(L"Error: %u \n", WSAGetLastError());
                WSACleanup();
                return 1;
            }
            else
            {
                std::cout << "Sent Done" << std::endl;
            }
            
        }
    }
    return 0;
}
/*
    -Server accepting Clients: YES
    -Server sending to client: YES
    -Server recieving from client: YES
    -Server taking input from keyboard: NO
*/