#ifndef __GAMEDEFINE_H
#define __GAMEDEFINE_H
#include <WinSock2.h>
#include <atomic>


struct Gameinfo
{
	//游戏模式 1单机 2联机
	int gamemdoe;

};

struct GAMEMAP
{
	char** gamemap;
	int sizeX, sizeY;
	int infosizeX = 20;
};


struct Player
{
	int HP;
	int X;
	int Y;
	int Type; // 1 玩家自身  2敌人玩家
	int scores;
	int nowdelayfighttime = 0;
	char name[10];
	Player() {  };
	Player(int hp, int x, int y, int type) { HP = hp; X = x, Y = y; scores = 0; Type = type; }
};


struct Bullet
{
	int harm;
	int delay;

	int movetime;
	int Type; //1 往上 2 往下
	int times = 0;
	int X;
	int Y;

	Bullet(int h, int d, int mt, int type) { harm = h; delay = d; movetime = mt; Type = type; }
};



struct onlinegameinfo
{
	SOCKET csock;
	std::atomic<int> ismatch;
	GAMEMAP map;
	
	int mapsizeX;
	int mapsizeY;
	bool gameover =false;
	bool win = false;
	bool disconnect = false;

	Player player1;
	Player player2;

	onlinegameinfo(){};
};




#endif // !__GAMEDEFINE_H



