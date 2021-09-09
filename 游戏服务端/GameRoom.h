#ifndef __GAMEROOM_H
#define __GAMEROOM_H
#include "engine/Player.h"
#include "GAMEDefine.h"
#include <vector>

class GameRoom
{
public:
	Player* Player1;
	Player* Player2;

	GAMEMAP map;
	std::vector<Bullet>  bullets;
	bool isconnect = true;
	
	void Init();
	void update();


	void end();

	GameRoom(Player* player1, Player* player2, int sizex, int sizey)
	{
		Player1 = player1;
		Player2 = player2;
		map.sizeX = sizex;
		map.sizeY = sizey;
	}
};


#endif // !__GAMEROOM_H

