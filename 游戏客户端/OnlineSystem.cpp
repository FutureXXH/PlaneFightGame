#include "OnlineSystem.h"

void heartsend(onlinegameinfo& gameinfo)
{
	while (gameinfo.gameover == false)
	{
		//cout << "发送心跳包" << endl;
		sendserver(10000, 0, nullptr, gameinfo.csock);
		this_thread::sleep_for(chrono::seconds(1));
	}
	

}

void sendserver(int head, int size, char* data, SOCKET sock)
{
	char* sendbuf = new char[8 + size];
	memcpy(sendbuf, (char*)&head, 4);
	memcpy(sendbuf+4, (char*)&size, 4);
	if (data != nullptr)
	{
		memcpy(sendbuf + 8, data, size);
	}
	

	for (int i = 0; i < 8+size; i++)
	{
		sendbuf[i] ^= 666;
	}


	send(sock, sendbuf, 8 + size,0);
}

void recvserver(onlinegameinfo& gameinfo)
{
	
	while (true)
	{
		char tempbuf[512];
		memset(tempbuf, 0, 512);

		int recvsize =recv(gameinfo.csock, tempbuf, 512, 0);
		if (recvsize < 8)
		{
			continue;
		}
		int dosize = 0;
		while (dosize < recvsize)//处理粘包问题
		{

			int head = -1;
			int size = -1;
			for (int i = 0; i < 8; i++)
			{
				tempbuf[dosize+i] ^= 666;
			}
			memcpy(&head, tempbuf+dosize, 4);
			memcpy(&size, tempbuf+dosize + 4, 4);
			if (dosize+8+size > recvsize)
			{
				dosize += 8 + size;
				continue;
			}
			char buf[128];
			memset(buf, 0, 128);
			memcpy(buf, tempbuf + dosize, 8 + size);


			int player = 0;
			int x = 0;
			int y = 0;


			switch (head)
			{
			case 10004:
				gameinfo.ismatch = 1;
				break;
			case 10005://初始化玩家
				for (int i = 0; i < size; i++)
				{
					buf[8 + i] ^= 666;
				}
				memcpy(&gameinfo.mapsizeX, buf + 8, 4);
				memcpy(&gameinfo.mapsizeY, buf + 12, 4);
				memcpy(&gameinfo.player1.name, buf + 16, 20);
				memcpy(&gameinfo.player2.name, buf + 36, 20);
				gameinfo.player1.HP = 10;
				gameinfo.player2.HP = 10;
				gameinfo.player1.Type = 1;
				gameinfo.player2.Type = 2;
				gameinfo.ismatch = 2;
				break;

			case 10006://更新玩家位置

				for (int i = 0; i < size; i++)
				{
					buf[8 + i] ^= 666;
				}
				memcpy(&player, buf + 8, 4);
				memcpy(&x, buf + 12, 4);
				memcpy(&y, buf + 16, 4);


				if (player == 1)
				{
					setplayerpos(gameinfo.map, gameinfo.player1, x, y);


				}
				else if (player == 2)
				{
					setplayerpos(gameinfo.map, gameinfo.player2, x, y);
				}


				break;
			case 10007: //初始化玩家位置
				for (int i = 0; i < size; i++)
				{
					buf[8 + i] ^= 666;
				}
				memcpy(&player, buf + 8, 4);
				memcpy(&x, buf + 12, 4);
				memcpy(&y, buf + 16, 4);


				if (player == 1)
				{
					gameinfo.player1.X = x;
					gameinfo.player1.Y = y;


				}
				else
				{
					gameinfo.player2.X = x;
					gameinfo.player2.Y = y;
				}

				break;
			case 10008: //攻击更新  位置-1不处理
			{
				for (int i = 0; i < size; i++)
				{
					buf[8 + i] ^= 666;
				}
				int oldx = -1, oldy = -1, newx = -1, newy = -1;
				memcpy(&oldx, buf + 8, 4);
				memcpy(&oldy, buf + 12, 4);
				memcpy(&newx, buf + 16, 4);
				memcpy(&newy, buf + 20, 4);

				if (oldx != -1 && oldy != -1)
				{
					gameinfo.map.gamemap[oldy][oldx] = ' ';
				}
				if (newx != -1 && newy != -1)
				{
					gameinfo.map.gamemap[newy][newx] = '|';
				}

			}

			break;
			case 10009: //玩家状态数据更新
				for (int i = 0; i < size; i++)
				{
					buf[8 + i] ^= 666;
				}
				int playerhp;
				int type;
				memcpy(&playerhp, buf+8, 4);
				memcpy(&type, buf+12, 4);
				if (type == 1)
				{
					gameinfo.player1.HP = playerhp;
				}
				else
				{
					gameinfo.player2.HP = playerhp;
				}
				break;
			case 10010: //战斗结束 输了
				
				gameinfo.gameover = true;
				gameinfo.win = false;
				break;
			case 10011: //赢了
				gameinfo.win = true;
				gameinfo.gameover = true;

				break;
			case 10012: //掉线结束游戏
				gameinfo.disconnect = true;
				gameinfo.gameover = true;

				break;
			default:
				break;
			}



			dosize += 8 + size;
		}
		
	}

}
