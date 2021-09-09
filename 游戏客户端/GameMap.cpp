#include "GameMap.h"
#pragma warning(disable : 4996)
//最小为20x20;
void InitMap(GAMEMAP& gamemap, int sizex, int sizey)
{
	gamemap.sizeX = sizex;
	gamemap.sizeY = sizey;
	gamemap.gamemap = new char* [gamemap.sizeY];
	for (int i = 0; i < gamemap.sizeY; i++)
	{
		gamemap.gamemap[i] = new char[gamemap.sizeX + gamemap.infosizeX];
		for (int i2 = 0; i2 < gamemap.sizeX + gamemap.infosizeX; i2++)
		{
			gamemap.gamemap[i][i2] = ' ';
		}
	}
}

void refreshwall(GAMEMAP& gamemap)
{
	for (int y = 0; y < gamemap.sizeY; y++)
	{
		if (y == 0 || y == gamemap.sizeY - 1)
		{
			for (int x = 0; x < gamemap.sizeX; x++)
			{
				gamemap.gamemap[y][x] = '#';
			}
		}
		else
		{
			gamemap.gamemap[y][0] = '#';
			gamemap.gamemap[y][gamemap.sizeX - 1] = '#';


		}


	}
}

void refreshinfopanel(GAMEMAP& gamemap)
{
	for (int y = 0; y < gamemap.sizeY; y++)
	{
		if (y == 0 || y == gamemap.sizeY - 1)
		{
			for (int x = 0; x < gamemap.infosizeX + gamemap.sizeX; x++)
			{
				gamemap.gamemap[y][x] = '#';
			}
		}
		else
		{
			gamemap.gamemap[y][gamemap.infosizeX + gamemap.sizeX - 1] = '#';


		}
	}
}

void refreshgameinfo(GAMEMAP& gamemap, Gameinfo& gameinfo, std::vector<Player>& players)
{
	memcpy(&gamemap.gamemap[1][gamemap.infosizeX + gamemap.sizeX - 18], "SuperPlaneFight", 15);
	memcpy(&gamemap.gamemap[3][gamemap.infosizeX + gamemap.sizeX - 15], "GameMode", 8);

	memcpy(&gamemap.gamemap[4][gamemap.infosizeX + gamemap.sizeX - 15], "PVE Mode", 8);

	/*else
	{
		memcpy(&gamemap.gamemap[4][gamemap.infosizeX + gamemap.sizeX - 18], "PVP Online Mode", 15);
	}*/
	//scores
	memcpy(&gamemap.gamemap[6][gamemap.infosizeX + gamemap.sizeX - 18], "scores:", 7);
	itoa(players[0].scores, &gamemap.gamemap[6][gamemap.infosizeX + gamemap.sizeX - 11], 10);

	memcpy(&gamemap.gamemap[7][gamemap.infosizeX + gamemap.sizeX - 18], "HP:", 3);
	itoa(players[0].HP, &gamemap.gamemap[7][gamemap.infosizeX + gamemap.sizeX - 11], 10);
	//memcpy(&gamemap.gamemap[6][gamemap.infosizeX + gamemap.sizeX - 11], "scores:", 4);
}


void refreshgameinfoPVP(onlinegameinfo& gameinfo)
{
	memcpy(&gameinfo.map.gamemap[1][gameinfo.map.infosizeX + gameinfo.map.sizeX - 18], "SuperPlaneFight", 15);
	memcpy(&gameinfo.map.gamemap[3][gameinfo.map.infosizeX + gameinfo.map.sizeX - 15], "GameMode", 8);
	memcpy(&gameinfo.map.gamemap[4][gameinfo.map.infosizeX + gameinfo.map.sizeX - 15], "PVP Mode", 8);

	memcpy(&gameinfo.map.gamemap[5][gameinfo.map.infosizeX + gameinfo.map.sizeX - 15], gameinfo.player1.name, strlen(gameinfo.player1.name));
	memcpy(&gameinfo.map.gamemap[6][gameinfo.map.infosizeX + gameinfo.map.sizeX - 15], "HP:", 3);
	itoa(gameinfo.player1.HP, &gameinfo.map.gamemap[6][gameinfo.map.infosizeX + gameinfo.map.sizeX - 11], 10);

	memcpy(&gameinfo.map.gamemap[7][gameinfo.map.infosizeX + gameinfo.map.sizeX - 15], gameinfo.player2.name, strlen(gameinfo.player2.name));
	memcpy(&gameinfo.map.gamemap[8][gameinfo.map.infosizeX + gameinfo.map.sizeX - 15], "HP:", 3);
	itoa(gameinfo.player2.HP, &gameinfo.map.gamemap[8][gameinfo.map.infosizeX + gameinfo.map.sizeX - 11], 10);

}







void cleargamemap(GAMEMAP& gamemap)
{
	for (int i = 1; i < gamemap.sizeY - 1; i++)
	{
		for (int i2 = 1; i2 < gamemap.sizeX - 1; i2++)
		{
			gamemap.gamemap[i][i2] = ' ';
		}
	}
}
