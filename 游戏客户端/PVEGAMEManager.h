#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include "FightSystem.h"
#include "GAMEDefine.h"
#include "PlayerManager.h"
#include "GameMap.h"
#include "Show.h"
#include "EnemySystem.h"
#include <time.h>

void PlayerController(Player& player, GAMEMAP& gamemap, std::vector<Bullet>& bullets);
void updateplayerinfo(std::vector<Player>& players, GAMEMAP& gamemap);

bool gameover = false;
int pvegamestart()
{
	gameover = false;
	GAMEMAP map;
	Gameinfo gameinfo;
	gameinfo.gamemdoe = 1;
	InitMap(map, 30, 25);
	refreshwall(map);
	refreshinfopanel(map);
	
	std::vector<Bullet> bullets;
	std::vector<Player> players;
	

	Player player1(10, map.sizeX / 2, map.sizeY - 2,1);//初始化玩家

	players.push_back(player1);

	refreshgameinfo(map, gameinfo,players);
	show(map.gamemap, map.sizeX + map.infosizeX, map.sizeY);//初始化显示地图框架
	setplayerpos(map, players[0], map.sizeX/2, map.sizeY-5);//设置玩家初始位置

	int updatetime = 50; 
	int time = clock();
	int enemyupdatetime = 200;
	int time2 = clock();
	int spawnenemytime = 25;
	int time3 = 0;
	SpawnEnemy(map, players);
	while (!gameover)
	{
		
		
		if (clock() - time >= updatetime)
		{
			time = clock();
			show(map.gamemap, map.sizeX + map.infosizeX, map.sizeY);
			PlayerController(players[0], map, bullets);
			updateplayerinfo(players,map);
			checkfight(map, bullets, players);
			refreshgameinfo(map, gameinfo, players);
		}
		if (clock() - time2 >= enemyupdatetime)
		{
			time3++;
			if (time3 >= spawnenemytime)
			{
				time3 = 0;
				SpawnEnemy(map, players);
			}
			time2 = clock();
			EnemyAI(players, map, bullets);
		}


		
	}
	return 0;
}

void updateplayerinfo(std::vector<Player>& players, GAMEMAP& gamemap)
{
	for (int i = 0; i < players.size(); i++)
	{
		setplayerpos(gamemap, players[i], players[i].X, players[i].Y);
		players[i].nowdelayfighttime++;
		if (players[i].HP <= 0)
		{
			if (players[i].Type == 2)
			{
				clearplayerpos(gamemap, players[i]);
				players.erase(players.begin() + i);
				players[0].scores++;
				i--;
			}
			else
			{
				cleargamemap(gamemap);
				gameover = true;
				players.clear();
				memcpy(&gamemap.gamemap[5][gamemap.infosizeX/2], "Game over", 9);
				memcpy(&gamemap.gamemap[6][gamemap.infosizeX / 3], "'y' -> playagain", 16);
				memcpy(&gamemap.gamemap[7][gamemap.infosizeX / 3], "'n' -> Quit", 11);
				show(gamemap.gamemap, gamemap.sizeX + gamemap.infosizeX, gamemap.sizeY);
			}
		}
	}
}

void PlayerController(Player& player, GAMEMAP& gamemap, std::vector<Bullet>& bullets)
{
	if (_kbhit())
	{
		char input;
		input = _getch();
		switch (input)
		{
		case 'w':
			setplayerpos(gamemap, player, player.X, player.Y - 1);
			break;
		case 's':
			setplayerpos(gamemap, player, player.X, player.Y + 1);
			break;
		case 'a':
			setplayerpos(gamemap, player, player.X - 1, player.Y);
			break;
		case 'd':
			setplayerpos(gamemap, player, player.X + 1, player.Y);
			break;
		case 'f':
		{
			Bullet bullet(1, 10, 3, 1);
			fight(player, gamemap, bullet, bullets);
		}
			break;
		default:
			break;
		}
	}

}



#endif // !__GAMEMANAGER_H
