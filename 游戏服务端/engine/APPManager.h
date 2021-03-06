
#ifndef __APPMANAGER_H
#define __APPMANAGER_H

#include "IDefine.h"
#include "TCPSERVER.h"
#include "TaskManager.h"
#include "Player.h"
#include "../GameRoom.h"
#include <thread>
#include <concurrent_queue.h>
#include <unordered_map>
#include <shared_mutex>
#include "../GameManager.h"

using namespace std;


//这里对业务层事件进行处理  并管理业务层玩家数据
// 删除网络层客户端数据 使用 Ptcpserver->DeleteClientSocket(SOCKET ClientSocket)
//删除业务层数据 使用DeletePlayer(Player* player) 


class APPManager
{
public:

	int SafeCode;
	int threadnum = 0;
	unordered_map<SOCKET, Player*> Playerlist;
	//unordered_map<SOCKET, TCPClient*>* ClientMap;
	TCPSERVER* Ptcpserver;
	HANDLE semapthore;
	Concurrency::concurrent_queue<task*>* __tasks;

	vector<GameRoom> rooms;
	Concurrency::concurrent_queue<Player*> waitplayer;
	shared_mutex sharedmutex;

public:
	bool InitManager( Concurrency::concurrent_queue<task*> * tasks, TCPSERVER* ptcpserver);
	void ProcessService(HANDLE semapthore);
	void Response(task & Task);
	bool DeletePlayer(SOCKET& playersocket);
	
	void fightCheck(GameRoom& room);//攻击检测


	void heartcheck();
	bool checkfightcollision(Bullet& bullet, Player& player, GameRoom& room);
	void fight(Player& player, GAMEMAP& gamemap, Bullet bullet, std::vector<Bullet>& bullets);

	void r10000(SOCKET& playersock);
	void r10001(SOCKET& playersock);
	void r10002(SOCKET& playersock);
	void r10003(SOCKET& playersock);
	void r10004(SOCKET& playersock, char* name);// 等待匹配玩家状态
	void r10006(SOCKET& playersock,char op, GameRoom& gameroom, int id);// 玩家操作
	
	
};



#endif // !__APPMANAGER_H


