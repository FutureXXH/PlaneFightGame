#ifndef __GAMEDEFINE_H
#define __GAMEDEFINE_H
#include <WinSock2.h>
#include <atomic>
#include "engine/Player.h"

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


	~GAMEMAP(){
		if (gamemap != nullptr)
		{
			for (int i = 0; i < sizeY; i++)
			{
				if (gamemap[i] != nullptr)
				{
					delete[] gamemap[i];
				}

			}
			delete[] gamemap;
		}

	
	}
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







#endif // !__GAMEDEFINE_H



