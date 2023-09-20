#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_LEN 512

// To Reciece Data
int recvData(SOCKET *s)
{
    char recvBuff[BUFF_LEN];
    int recvBuffLen = BUFF_LEN;

    if (recv(*s, recvBuff, recvBuffLen, 0) == SOCKET_ERROR)
    {
        wprintf(L"Recv Failed: %u \n", WSAGetLastError());
        return 1;
    }
    else
    {
        std::cout << "Recieved " << recvBuff << std::endl;
        return 0;
    }
}

int main()
{
    WSADATA wsaData;
    int iResult = 0;

    SOCKET connectSocket = INVALID_SOCKET;
    sockaddr_in client;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult == 1)
    {
        wprintf(L"Error: %u \n", WSAGetLastError());
        return 1;
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(9090);
    client.sin_addr.s_addr = inet_addr("192.168.1.5");

    // std::cout << "SOCKET BINDED" << std::endl;
    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET)
    {
        wprintf(L"Error %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    std::cout << "SOCKET BINDED" << std::endl;

    if (connect(connectSocket, (struct sockaddr *)&client, sizeof(client)) == SOCKET_ERROR)
    {
        wprintf(L"Error %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        wprintf(L"Successfully connected\n");

        while (true)
        {
            iResult = recvData(&connectSocket);
            if (iResult == 1)
            {
                wprintf(L"Error %u \n", WSAGetLastError());
                return 1;
            }
        }
    }
    return 0;
}