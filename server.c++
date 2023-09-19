#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#define BUF_LEN 512

int sendData(void)
{

    return 0;
}

int initSocket(SOCKET *ls)
{
}

int main(void)
{
    WSADATA wsaData;

    char recvBuff[BUF_LEN];
    int recvBuffLen = BUF_LEN;

    SOCKET listenSocket = INVALID_SOCKET;
    int iResult = 0;
    sockaddr_in server;

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

    iResult = bind(listenSocket, (struct sockaddr *)&server, sizeof(server));
    if (iResult == 1)
    {
        wprintf(L"Error: %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    iResult = listen(listenSocket, 1);
    if (iResult == 1)
    {
        wprintf(L"Error: %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    SOCKET acceptSocket = INVALID_SOCKET;
    std::cout << "[LISTENING] server is listening for clients" << std::endl;

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
            std::cout << "[ACCEPTED] server accepted a client" << std::endl;
        }
    }
    return 0;
}
