#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv)
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

    iResult = connect(connectSocket, (struct sockaddr *)&client, sizeof(client));
    if (iResult == 1)
    {
        wprintf(L"Error %u \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    wprintf(L"Successfully connected\n");
    closesocket(connectSocket);
    WSACleanup();

    return 0;
}