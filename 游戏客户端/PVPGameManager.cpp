#include "PVPGameManager.h"


void PlayerController(onlinegameinfo& gameinfo);

void start()
{

	initshow(1);

	char name[20];
	while (true)
	{
		memset(name, 0, 20);
		cin >> name;
		if (strlen(name) > 10)
		{
			cout << "输入格式错误 请重新输入" << endl;
			continue;
		}
		else
		{
			break;
		}
	}

	initshow(2);
	Sleep(800);
	SOCKET csock;
	sockaddr_in Server_adr;
	//连接服务器
	while (!connectserver(csock, Server_adr))
	{

		initshow(3);
		Sleep(1000);
	}

	onlinegameinfo gameinfo;

	gameinfo.csock = csock;
	gameinfo.player1.Type = 1;
	gameinfo.player2.Type = 2;
	//开启心跳包发送线程
	thread* heartsendp = new thread(heartsend,ref(gameinfo));

	//开启接收数据线程
	thread* recvthread = new thread(recvserver , ref(gameinfo));



	//等待匹配玩家
	while (gameinfo.ismatch == 0|| gameinfo.ismatch == 1)
	{
		
		if (gameinfo.ismatch == 0)
		{

			sendserver(10004, 10, name, csock);
			initshow(4);
		}
		else
		{
			initshow(6);
		}
		
		Sleep(500);

	}
	//匹配玩家成功
	initshow(5);
	Sleep(1000);

	//初始化地图
	InitMap(gameinfo.map, gameinfo.mapsizeX, gameinfo.mapsizeY);
	refreshwall(gameinfo.map);
	refreshinfopanel(gameinfo.map);
	setplayerpos(gameinfo.map, gameinfo.player1, gameinfo.player1.X, gameinfo.player1.Y);
	setplayerpos(gameinfo.map, gameinfo.player2, gameinfo.player2.X, gameinfo.player2.Y);


	int updatetime = 50;
	int time = clock();
	//刷新地图 输入玩家操作
	while (gameinfo.gameover == false)
	{
		if (clock() - time >= updatetime)
		{
			time = clock();
			show(gameinfo.map.gamemap, gameinfo.map.sizeX + gameinfo.map.infosizeX, gameinfo.map.sizeY);
			PlayerController(gameinfo);
			refreshgameinfoPVP(gameinfo);
			setplayerpos(gameinfo.map, gameinfo.player1, gameinfo.player1.X, gameinfo.player1.Y);
			setplayerpos(gameinfo.map, gameinfo.player2, gameinfo.player2.X, gameinfo.player2.Y);
		}

	}
	if (gameinfo.win)
	{
		initshow(7);

	   char input;
	   input = _getch();


	
	}
	else 
	{
		if (gameinfo.disconnect == true)
		{
			initshow(9);
			char input;
			input = _getch();
		}
		else
		{
			initshow(8);
			char input;
			input = _getch();
		}

	}

	closesocket(csock);


}

void PlayerController(onlinegameinfo& gameinfo)
{
	if (_kbhit())
	{
		char input;
		input = _getch();
		char buf[1];
		switch (input)
		{
		case 'w':
			
			buf[0] = 'w';
			sendserver(10006, 1, buf, gameinfo.csock);
			break;
		case 's':
			
			buf[0] = 's';
			sendserver(10006, 1, buf, gameinfo.csock);
			break;
		case 'a':
			
			buf[0] = 'a';
			sendserver(10006, 1, buf, gameinfo.csock);
			break;
		case 'd':
			
			buf[0] = 'd';
			sendserver(10006, 1, buf, gameinfo.csock);
			break;
		case 'f':
			
			buf[0] = 'f';
			sendserver(10006, 1, buf, gameinfo.csock);
			break;
		default:
			break;
		}
	}
}



void initshow(int step)
{
	switch (step)
	{
	case 1:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#        输入一个游戏昵称      #" << endl;
		cout << "#                              #" << endl;
		cout << "#    最大10个英文数字字符      #" << endl;
		cout << "#                              #" << endl;
		cout << "################################" << endl;
		break;
	case 2:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#        正在连接服务器        #" << endl;
		cout << "#        请稍后.               #" << endl;
		cout << "#                              #" << endl;
		cout << "#                              #" << endl;
		cout << "################################" << endl;
		break;
	case 3:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#         连接失败             #" << endl;
		cout << "#         正在重连             #" << endl;
		cout << "#                              #" << endl;
		cout << "#                              #" << endl;
		cout << "################################" << endl;
		break;
	case 4:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#        等待服务器            #" << endl;
		cout << "#          响应                #" << endl;
		cout << "#                              #" << endl;
		cout << "#                              #" << endl;
		cout << "################################" << endl;
		break;
	case 5:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#       匹配成功               #" << endl;
		cout << "#      正在进入游戏对战        #" << endl;
		cout << "#                              #" << endl;
		cout << "#                              #" << endl;
		cout << "################################" << endl;
		break;
	case 6:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#      正在匹配在线玩家        #" << endl;
		cout << "#                              #" << endl;
		cout << "#                              #" << endl;
		cout << "#                              #" << endl;
		cout << "################################" << endl;
		break;
	case 7:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#         游戏结束             #" << endl;
		cout << "#      你赢了 \(〃'▽'〃)/     #" << endl;
		cout << "#                              #" << endl;
		cout << "#        按任意键返回           #" << endl;
		cout << "################################" << endl;
		break;
	case 8:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#         游戏结束             #" << endl;
		cout << "#     你输了 o(╥﹏╥)o        #" << endl;
		cout << "#                              #" << endl;
		cout << "#        按任意键返回          #" << endl;
		cout << "################################" << endl;
		break;
	case 9:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#       对战已被强制终止       #" << endl;
		cout << "#      可能对方关闭了连接      #" << endl;
		cout << "#                              #" << endl;
		cout << "#        按任意键返回          #" << endl;
		cout << "################################" << endl;
		break;
	default:
		break;
	}
}