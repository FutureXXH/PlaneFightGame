

#ifndef __PLAYER_H
#define __PLAYER_H
#include"IDefine.h"
#include <time.h>

//这里对业务层玩家数据进行定义

class Player
{
public:

	char name[20];
	int HP = 10;
	bool islogin;
	bool isConnect;
	bool isplaying = false;
	bool ismatch = false;
	int X;
	int Y;
	int Type;
	int nowdelayfighttime = 0;
	int scores = 0;

	SOCKET PlayerSOCK;
	clock_t starttime;

	
	Player(SOCKET sock);
	~Player();
};



#endif // !__PLAYER_H
