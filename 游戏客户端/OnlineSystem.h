#ifndef __ONLINESYSTEM_H
#define __ONLINESYSTEM_H
#pragma warning(disable : 4996)
#include "GAMEDefine.h"
#include <winsock2.h>
#include<thread>
#include <iostream>
#include "PlayerManager.h"
using namespace std;




void heartsend(onlinegameinfo& gameinfo);

void sendserver(int head,int size,char* data,SOCKET sock);

void recvserver(onlinegameinfo & gameinfo);



#endif // !__ONLINESYSTEM_H
