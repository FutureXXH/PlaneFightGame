#include "OnineConnector.h"

bool connectserver(SOCKET& Csock, SOCKADDR_IN& Server_adr)
{
    WSADATA wsd;
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        std::cout << "Winsock初始化失败" << std::endl;
        return false;
    }

    Csock = socket(AF_INET,SOCK_STREAM,0);


    memset(&Server_adr, 0, sizeof(Server_adr));
    Server_adr.sin_family = AF_INET;
    //Server_adr.sin_addr.s_addr = inet_addr("10.17.77.37");
    Server_adr.sin_addr.s_addr = inet_addr("47.108.173.15");
    Server_adr.sin_port = htons(6666);


    if (connect(Csock, (SOCKADDR*)&Server_adr, sizeof(Server_adr)) != SOCKET_ERROR)
    {
        return true;
    }
    else
    {
        return false;
    }



}
