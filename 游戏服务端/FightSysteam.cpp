#include "engine/APPManager.h"








//判断子弹是否与玩家碰撞
bool APPManager::checkfightcollision(Bullet& bullet, Player& player ,GameRoom &room)
{

	if (player.Type == 1 && bullet.Type == 2)
	{
		if (bullet.Y == player.Y && abs(bullet.X - player.X) < 3)
		{
			player.HP--;


            int playerhp = player.HP;
            int playertype = 1;
            char buf[8];
            memcpy(buf, (char*)&playerhp, 4);
            memcpy(buf+4, (char*)&playertype, 4);
            Ptcpserver->ClientMap->at(room.Player1->PlayerSOCK)->Send(10009, buf, 8, 666);
            Ptcpserver->ClientMap->at(room.Player2->PlayerSOCK)->Send(10009, buf, 8, 666);
			return true;
		}
		else if (bullet.Y == player.Y + 1 && bullet.X == player.X)
		{
			player.HP--;

            int playerhp = player.HP;
            int playertype = 1;
            char buf[8];
            memcpy(buf, (char*)&playerhp, 4);
            memcpy(buf + 4, (char*)&playertype, 4);
            Ptcpserver->ClientMap->at(room.Player1->PlayerSOCK)->Send(10009, buf, 8, 666);
            Ptcpserver->ClientMap->at(room.Player2->PlayerSOCK)->Send(10009, buf, 8, 666);
			return true;
		}
		return false;
	}
	else if (player.Type == 2 && bullet.Type == 1)
	{
		if (bullet.Y == player.Y && abs(bullet.X - player.X) < 3)
		{
			player.HP--;

            int playerhp = player.HP;
            int playertype = 2;
            char buf[8];
            memcpy(buf, (char*)&playerhp, 4);
            memcpy(buf + 4, (char*)&playertype, 4);
            Ptcpserver->ClientMap->at(room.Player1->PlayerSOCK)->Send(10009, buf, 8, 666);
            Ptcpserver->ClientMap->at(room.Player2->PlayerSOCK)->Send(10009, buf, 8, 666);
			return true;
		}
		else if (bullet.Y == player.Y + 1 && bullet.X == player.X)
		{
			player.HP--;

            int playerhp = player.HP;
            int playertype = 2;
            char buf[8];
            memcpy(buf, (char*)&playerhp, 4);
            memcpy(buf + 4, (char*)&playertype, 4);
            Ptcpserver->ClientMap->at(room.Player1->PlayerSOCK)->Send(10009, buf, 8, 666);
            Ptcpserver->ClientMap->at(room.Player2->PlayerSOCK)->Send(10009, buf, 8, 666);    
			return true;
		}
		return false;
	}
	return false;
}



void APPManager::fightCheck(GameRoom& room)
{

    for (int i = 0; i < room.bullets.size(); i++)
    {
        room.bullets[i].times++;
        if (room.bullets[i].times >= room.bullets[i].movetime)
        {
            int oldx = room.bullets[i].X, oldy = room.bullets[i].Y;
            int newx = room.bullets[i].X, newy = room.bullets[i].Y;
            //更新位置
            //gamemap.gamemap[bullets[i].Y][bullets[i].X] = ' ';
            if (room.bullets[i].Type == 1) //往上的更新
            {
                room.bullets[i].Y--;
                //判断是否已经到顶
                newx = room.bullets[i].X;
                newy = room.bullets[i].Y;
                if (room.bullets[i].Y < 1)
                {
                    room.bullets.erase(room.bullets.begin() + i);
                    newx = -1;
                    newy = -1;
                }
            }
            else   //往下的更新
            {
                room.bullets[i].Y++;
                //判断是否已经到底
                newx = room.bullets[i].X;
                newy = room.bullets[i].Y;
                if (room.bullets[i].Y >= room.map.sizeY - 1)
                {
                    room.bullets.erase(room.bullets.begin() + i);
                    newx = -1;
                    newy = -1;

                }
            }
           
            char buf[16];
            memcpy(buf, (char*)&oldx, 4);
            memcpy(buf + 4, (char*)&oldy, 4);
            memcpy(buf + 8, (char*)&newx, 4);
            memcpy(buf + 12, (char*)&newy, 4);
            Ptcpserver->ClientMap->at(room.Player1->PlayerSOCK)->Send(10008, buf, 16, 666);
            Ptcpserver->ClientMap->at(room.Player2->PlayerSOCK)->Send(10008, buf, 16, 666);
            //gamemap.gamemap[bullets[i].Y][bullets[i].X] = '|';

            if (checkfightcollision(room.bullets[i], *room.Player1,room)|| checkfightcollision(room.bullets[i], *room.Player2, room))
            {
                cout << oldx << " " << oldy << " " << newx << " " << newy << " 击中玩家" << endl;
                //gamemap.gamemap[bullets[i].Y][bullets[i].X] = ' ';
                oldx = newx; oldy = newy;
                newx = -1; newy = -1;
                memcpy(buf, (char*)&oldx, 4);
                memcpy(buf + 4, (char*)&oldy, 4);
                memcpy(buf + 8, (char*)&newx, 4);
                memcpy(buf + 12, (char*)&newy, 4);
                Ptcpserver->ClientMap->at(room.Player1->PlayerSOCK)->Send(10008, buf, 16, 666);
                Ptcpserver->ClientMap->at(room.Player2->PlayerSOCK)->Send(10008, buf, 16, 666);
                room.bullets.erase(room.bullets.begin() + i);
                break;
            }


        }


  
    }

}








//发射子弹
void APPManager::fight(Player& player, GAMEMAP& gamemap, Bullet bullet, std::vector<Bullet>& bullets)
{

	if (player.nowdelayfighttime < bullet.delay)
	{
		return;
	}
	if (player.Y < 1)return;
	//gamemap.gamemap[player.Y - 1][player.X] = '|';
	bullet.X = player.X;
	bullet.Y = player.Y;
	bullets.push_back(bullet);
	player.nowdelayfighttime = 0;
}









