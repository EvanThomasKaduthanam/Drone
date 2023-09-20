#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_LEN 512

int main(int argc, char **argv)
{
    WSADATA wsaData;
    int iResult = 0;

    char recvBuff[BUFF_LEN];
    int recvBuffLen = BUFF_LEN;

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
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

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

        while(true)
        {
            if(recv(connectSocket, recvBuff, recvBuffLen, 0) == SOCKET_ERROR)
            {
                wprintf(L"Error %u \n", WSAGetLastError());
                return 1;
            }
            else
            {
                std::cout << "Recieved: %s" << recvBuff << std::endl;
                closesocket(connectSocket);
                WSACleanup();
            }
        }
    }
    return 0;
}