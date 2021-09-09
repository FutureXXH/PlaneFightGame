#include "PlayerManager.h"


//     自己         敌方
//     *            * *
//   *****         *****
//    * *            *
//    
void clearplayerpos(GAMEMAP& gamemap, Player& player)
{
	if (player.Type == 1)
	{
		gamemap.gamemap[player.Y][player.X] = ' ';
		gamemap.gamemap[player.Y][player.X + 1] = ' ';
		gamemap.gamemap[player.Y][player.X + 2] = ' ';
		gamemap.gamemap[player.Y][player.X - 1] = ' ';
		gamemap.gamemap[player.Y][player.X - 2] = ' ';
		gamemap.gamemap[player.Y + 1][player.X - 1] = ' ';
		gamemap.gamemap[player.Y + 1][player.X + 1] = ' ';
		gamemap.gamemap[player.Y - 1][player.X] = ' ';
	}
	else
	{
		gamemap.gamemap[player.Y][player.X] = ' ';
		gamemap.gamemap[player.Y][player.X + 1] = ' ';
		gamemap.gamemap[player.Y][player.X + 2] = ' ';
		gamemap.gamemap[player.Y][player.X - 1] = ' ';
		gamemap.gamemap[player.Y][player.X - 2] = ' ';
		gamemap.gamemap[player.Y - 1][player.X - 1] = ' ';
		gamemap.gamemap[player.Y - 1][player.X + 1] = ' ';
		gamemap.gamemap[player.Y + 1][player.X] = ' ';
	}

}

bool setplayerpos(GAMEMAP& gamemap, Player& player, int x, int y)
{
	if (x + 2 >= gamemap.sizeX - 1 || x - 2 <= 0 || y - 1 <= 0 || y + 1 >= gamemap.sizeY - 1)
	{
		return false;
	}
	
	clearplayerpos(gamemap, player);
	player.X = x;
	player.Y = y;
	if (player.Type == 1)
	{
		gamemap.gamemap[y][x] = '*';
		gamemap.gamemap[y][x + 1] = '*';
		gamemap.gamemap[y][x + 2] = '*';
		gamemap.gamemap[y][x - 1] = '*';
		gamemap.gamemap[y][x - 2] = '*';
		gamemap.gamemap[y + 1][x - 1] = '*';
		gamemap.gamemap[y + 1][x + 1] = '*';
		gamemap.gamemap[y - 1][x] = '*';
	}
	else
	{
		gamemap.gamemap[y][x] = '*';
		gamemap.gamemap[y][x + 1] = '*';
		gamemap.gamemap[y][x + 2] = '*';
		gamemap.gamemap[y][x - 1] = '*';
		gamemap.gamemap[y][x - 2] = '*';
		gamemap.gamemap[y - 1][x - 1] = '*';
		gamemap.gamemap[y - 1][x + 1] = '*';
		gamemap.gamemap[y + 1][x] = '*';
	}

	

	return true;
}

