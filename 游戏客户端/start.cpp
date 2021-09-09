#include <iostream>
#include "PVEGAMEManager.h"
#include "PVPGameManager.h"
void startshow(int type);
int main()
{
	SetConsoleOutputCP(65001);
	HideCursor();

	while (true)
	{



		startshow(1);
		int type = 0;
		cin >> type;
		switch (type)
		{
		case 1:
		{
			bool again = true;
			while (again)
			{
				pvegamestart();
				while (true)
				{
					char p = _getch();
					if (p == 'n')
					{
						again = false;
						break;
					}
					else if (p == 'y')
					{
						again = true;
						break;
					}

				}
			}
		}
		break;
		case 2:
			system("cls");
			start();
			break;
		case 3:
			startshow(2);
			{
				char input;
				input = _getch();
			}
			break;
		case 4:
			startshow(3);
			{
				char input;
				input = _getch();
			}
			break;
		case 5:
			exit(0);
			break;
		default:
			break;
		}



	}






}



void startshow(int type)
{
	switch (type)
	{
	case 1:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#       SuperPlaneFight        #" << endl;
		cout << "#                              #" << endl;
		cout << "#   1.单人模式    2.在线模式   #" << endl;
		cout << "#                              #" << endl;
		cout << "#   3.游戏帮助    4.关于制作   #" << endl;
		cout << "#                              #" << endl;
		cout << "#   5 退出                     #" << endl;
		cout << "################################" << endl;
		cout << "#  开始游戏前请切换英文输入法  #" << endl;
		cout << "# 并关闭大写锁定,否则不会响应  #" << endl;
		cout << "################################" << endl;
		cout << "输入选择序号" << endl;
		break;
	case 2:
		system("cls");
		cout << "################################" << endl;
		cout << "#                              #" << endl;
		cout << "#       游戏帮助               #" << endl;
		cout << "#     w->向上   s->向下        #" << endl;
		cout << "#     a->向左   d->向右        #" << endl;
		cout << "#                              #" << endl;
		cout << "#       f->发射子弹            #" << endl;
		cout << "#                              #" << endl;
		cout << "#       按任意键返回           #" << endl;
		cout << "################################" << endl;
		break;
	case 3:
		system("cls");
		cout << "####################################################################" << endl;
		cout << "#                                   everything made by xuxinhao    #" << endl;
		cout << "#                        关于制作                                  #" << endl;
		cout << "#    关于在线模式，采用客户端-服务端模式，游戏同步采用状态同步模式 #" << endl;
		cout << "# 进行同步（服务端进行游戏逻辑处理 客户端只负责接收操作输出画面）  #" << endl;
		cout << "#                                                                  #" << endl;
		cout << "#    游戏客户端大部分都使用面向过程式编程，自己不创建任何类        #" << endl;
		cout << "#                                                                  #" << endl;
		cout << "#           下面网址可访问客户端与服务端源代码                     #" << endl;
		cout << "#       https://github.com/xuxinhao666666/PlaneFightGame           #" << endl;
		cout << "#                  按任意键返回                                    #" << endl;
		cout << "####################################################################" << endl;
		break;
	default:
		break;
	}


}