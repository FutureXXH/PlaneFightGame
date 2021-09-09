#include "GameManager.h"


//     自己         敌方
//     *            * *
//   *****         *****
//    * *            *
//    
void clearplayerpos(GAMEMAP& gamemap, Player& player)
{


}

bool setplayerpos(GAMEMAP& gamemap, Player& player, int x, int y)
{
	if (x + 2 >= gamemap.sizeX - 1 || x - 2 <= 0 || y - 1 <= 0 || y + 1 >= gamemap.sizeY - 1)
	{
		return false;
	}
	//clearplayerpos(gamemap, player);
	player.X = x;
	player.Y = y;


	return true;
}
