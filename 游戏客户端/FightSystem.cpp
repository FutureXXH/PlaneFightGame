#include "FightSystem.h"

//发射子弹
void fight(Player& player, GAMEMAP& gamemap, Bullet bullet,  std::vector<Bullet> &bullets)
{
	if (player.nowdelayfighttime < bullet.delay)
	{
		return;
	}
	if (player.Y < 1)return;
	gamemap.gamemap[player.Y - 1][player.X] = '|';
	bullet.X = player.X;
	bullet.Y = player.Y - 1;
	bullets.push_back(bullet);
	player.nowdelayfighttime = 0;

}
//判断子弹是否与玩家碰撞
bool checkfightcollision(Bullet& bullet,Player& player)
{
	if (player.Type == 1&&bullet.Type == 2)
	{
		if (bullet.Y == player.Y&& abs(bullet.X-player.X) < 3 )
		{
			player.HP--;
			return true;
		}
		else if(bullet.Y == player.Y+1 && bullet.X == player.X)
		{
			player.HP--;
			return true;
		}
		return false;
	}
	else if (player.Type == 2 && bullet.Type == 1)
	{
		if (bullet.Y == player.Y && abs(bullet.X - player.X) < 3)
		{
			player.HP--;
			return true;
		}
		else if (bullet.Y == player.Y + 1 && bullet.X == player.X)
		{
			player.HP--;
			return true;
		}
		return false;
	}
	return false;
}

void checkfight(GAMEMAP& gamemap, std::vector<Bullet>& bullets, std::vector<Player>& Players)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].times++;
		if (bullets[i].times >= bullets[i].movetime)
		{
			//更新位置
			gamemap.gamemap[bullets[i].Y][bullets[i].X] = ' ';
			if (bullets[i].Type == 1) //往上的更新
			{
				bullets[i].Y--;
				//判断是否已经到顶
				if (bullets[i].Y < 1)
				{
					bullets.erase(bullets.begin() + i);
					continue;
				}
			}
			else   //往下的更新
			{
				bullets[i].Y++;
				//判断是否已经到底
				if (bullets[i].Y >= gamemap.sizeY-1)
				{
					bullets.erase(bullets.begin() + i);
					continue;
				}
			}
			gamemap.gamemap[bullets[i].Y][bullets[i].X] = '|';
			for (int i2	 = 0; i2 < Players.size(); i2++)
			{
				if (checkfightcollision(bullets[i],Players[i2]))
				{
					gamemap.gamemap[bullets[i].Y][bullets[i].X] = ' ';
					bullets.erase(bullets.begin() + i);
					break;
				}
			}
			
		}
	}
	
}
