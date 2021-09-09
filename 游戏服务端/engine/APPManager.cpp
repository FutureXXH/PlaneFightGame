#include "APPManager.h"




bool APPManager::InitManager(Concurrency::concurrent_queue<task*>* tasks , TCPSERVER* ptcpserver)
{

    __tasks = tasks;
    Ptcpserver = ptcpserver;
 
    semapthore = CreateSemaphore(NULL, 0, 5000, L"ServiceThread"); //创建信号量

    if (threadnum <= 0)
    {
        threadnum = 2;
    }
     
    //task::__tasks = new Concurrency::concurrent_queue<task*>();
    for (int i = 0; i < threadnum; i++)
    {
        thread* threadp = new thread(&APPManager::ProcessService, this, semapthore);

    }
    SERVERPRINT_INFO << "创建" << threadnum << "个业务处理线程" << endl;

    thread* threadp = new thread(&APPManager::heartcheck, this);

    SERVERPRINT_INFO << "创建心跳包处理线程" << endl;
    return true;
}
//业务线程   从任务队列取出任务处理
void APPManager::ProcessService(HANDLE semapthore)
{
    
    while (true)
    {
        WaitForSingleObject(semapthore, INFINITE); //等待信号量资源
        
        if (__tasks->unsafe_size() > 0)
        {
            
            task* temptask;
            if (!__tasks->try_pop(temptask))
            {
                SERVERPRINT_WARNING << "空任务 " << endl;
                continue;
            }
            if (temptask == nullptr)
            {
                SERVERPRINT_WARNING << "空任务指针" << endl;
                continue;
            }
            //SERVERPRINT_INFO << "发现任务" <<temptask->Head << endl;
            Response(*temptask);

            delete temptask;
            
        }
    }

}
// 处理业务部分 
void APPManager::Response(task& Task)
{
    switch (Task.Head)
    {
    case HEART://心跳包接收
        r10000(Task.clent->sock);
        break;
    case TEST://测试
        r10001(Task.clent->sock);
        break;
    case NEWPLAYER://创建玩家服务器数据信息
        r10002(Task.clent->sock);
        SERVERPRINT_INFO << "创建新连接玩家数据" << endl;
        break;
    case DELETEPLAYER: //删除玩家服务器数据信息
        r10003(Task.clent->sock);
        break;
    case 10004: //
        char name[10];
        memcpy(name, Task.Data, 10);
        r10004(Task.clent->sock,name);
        break;
    case 10006: //
        char op[1];
        memcpy(op,Task.Data,1);
     
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms[i].Player1->PlayerSOCK == Task.clent->sock )
            {
              
                r10006(Task.clent->sock, op[0],rooms[i],1);
                break;
            }
            else if(rooms[i].Player2->PlayerSOCK == Task.clent->sock)
            {
               
                r10006(Task.clent->sock, op[0], rooms[i], 2);
                break;
            }
        }
    

        break;
    default:
        break;
    }

}

bool APPManager::DeletePlayer(SOCKET& playersocket)
{
    {
        unique_lock<shared_mutex> lock(sharedmutex); // 设置写锁
        if (Playerlist.find(playersocket) != Playerlist.end())
        {
            SERVERPRINT_INFO << "正在删除服务器玩家数据:" << Playerlist.at(playersocket)->name << "  " << Playerlist[playersocket] << endl;
            //+
            Playerlist[playersocket]->isConnect = false;
            delete Playerlist[playersocket];
            Playerlist[playersocket] == nullptr;
            Playerlist.erase(playersocket);
            return true;
        }

    }

    return false;
    
}
//游戏心跳包与其他逻辑处理
void APPManager::heartcheck()
{

    int updatetime = 100;
    int updatenowtime = clock();
    while (true)
    {
        if (clock()- updatenowtime >= updatetime)
        {
         
            updatenowtime = clock();
     
        clock_t nowtime = clock();
        for (int i = 0; i < Playerlist.size(); i++)
        {
            if (Playerlist[i] == nullptr) continue;
            Playerlist[i]->nowdelayfighttime++;
            if ((nowtime - Playerlist[i]->starttime) > 4000)
            {
               
                for (int i2 = 0; i2 < rooms.size(); i2++)
                {
                    if (rooms[i2].Player1 == Playerlist[i]|| rooms[i2].Player2 == Playerlist[i])
                    {
                        Ptcpserver->ClientMap->at(rooms[i2].Player1->PlayerSOCK)->Send(10012, nullptr, 0, 666);
                        Ptcpserver->ClientMap->at(rooms[i2].Player2->PlayerSOCK)->Send(10012, nullptr, 0, 666);
                        rooms[i2].isconnect = false;
                        break;
                    }
                }

                r10003(Playerlist[i]->PlayerSOCK);
                
            }
           
        }

        for (int i = 0; i < rooms.size(); i++)
        {
            {
            shared_lock<shared_mutex> lock(sharedmutex); // 设置读锁
            fightCheck(rooms[i]);
            }
            if (rooms[i].Player1->HP <= 0)
            {
                SERVERPRINT_INFO << "游戏结束" << endl;
                Ptcpserver->ClientMap->at(rooms[i].Player1->PlayerSOCK)->Send(10010, nullptr, 0, 666);
                Ptcpserver->ClientMap->at(rooms[i].Player2->PlayerSOCK)->Send(10011, nullptr, 0, 666);
             
                rooms[i].isconnect = false;
          


            }
            else if (rooms[i].Player2->HP <= 0)
            {
                SERVERPRINT_INFO << "游戏结束" << endl;

                Ptcpserver->ClientMap->at(rooms[i].Player2->PlayerSOCK)->Send(10010, nullptr, 0, 666);
                Ptcpserver->ClientMap->at(rooms[i].Player1->PlayerSOCK)->Send(10011, nullptr, 0, 666);

                rooms[i].isconnect = false;
            }


            if (rooms[i].isconnect == false)
            {

                {
                    unique_lock<shared_mutex> lock(sharedmutex); // 设置写锁
                    rooms.erase(rooms.begin() + i);
                    i--;
                }
            }


        }





        }
      
        //this_thread::sleep_for(chrono::seconds(1));
    }
   

}

//========================================================

void APPManager::r10000(SOCKET& playersock)
{
    {
        unique_lock<shared_mutex> lock(sharedmutex); // 设置写锁
        if (Playerlist[playersock] != nullptr)
        {
            Playerlist[playersock]->starttime = clock();
        }
        
    }
}

void APPManager::r10001(SOCKET& playersock)
{
    {
        shared_lock<shared_mutex> lock(sharedmutex); // 设置读锁
        if (Playerlist[playersock]->islogin)
        {
            SERVERPRINT_INFO << "测试数据:已登录" << endl;
        }
        else
        {
            SERVERPRINT_INFO << "测试数据:未登录" << endl;
        }
    }
}


void APPManager::r10002(SOCKET& playersock) //新连接玩家，创建业务层数据
{
    Player* newplayer = new Player(playersock);
    {
    SERVERPRINT_INFO << "玩家连接" << endl;
    unique_lock<shared_mutex> lock(sharedmutex); // 设置写锁
    //Playerlist.emplace(playersock, newplayer);
    Playerlist[playersock] = newplayer;
    Playerlist[playersock]->isConnect = true;
    }
}

void APPManager::r10003(SOCKET& playersock)
{

       
        DeletePlayer(playersock);
        Ptcpserver->DeleteClientSocket(playersock);
   

}

void APPManager::r10004(SOCKET& playersock,char *name)
{
    
       unique_lock<shared_mutex> lock(sharedmutex); // 设置写锁
    if (Playerlist[playersock] != nullptr&& Playerlist[playersock]->isplaying == false && Playerlist[playersock]->ismatch == false)
    {
        memcpy(Playerlist[playersock]->name, name, 10);
        Ptcpserver->ClientMap->at(playersock)->Send(10004, nullptr, 0, 666);
        Playerlist[playersock]->ismatch = true;

         
        if (waitplayer.empty())
        {
            waitplayer.push(Playerlist[playersock]);

        }
        else
        {
            //匹配成功开始初始化地图
            SERVERPRINT_INFO << "匹配成功开始初始化地图" << endl;
            Player* otherplayer = nullptr;
            while (otherplayer == nullptr || otherplayer->isConnect == false)
            {
                if (waitplayer.empty())
                {
                    waitplayer.push(Playerlist[playersock]);
                    return;
                }
                waitplayer.try_pop(otherplayer);
                cout << otherplayer << endl;
            }
            
            GameRoom newroom(otherplayer, Playerlist[playersock], 30, 25);
            rooms.push_back(newroom);
            // 地图大小8，2个玩家名字40
            memcpy(newroom.Player1->name, otherplayer->name, 10);
            memcpy(newroom.Player2->name, Playerlist[playersock]->name, 10);
            newroom.Player1->Type = 1;
            newroom.Player2->Type = 2;
            newroom.Player1->HP = 10;
            newroom.Player2->HP = 10;

            char buf[48];
            memcpy(buf, (char*)&newroom.map.sizeX, 4);
            memcpy(buf + 4, (char*)&newroom.map.sizeY, 4);
            memcpy(buf + 8, newroom.Player1->name, 20);
            memcpy(buf + 28, newroom.Player2->name, 20);
            Ptcpserver->ClientMap->at(playersock)->Send(10005, buf, 48, 666);
            Ptcpserver->ClientMap->at(otherplayer->PlayerSOCK)->Send(10005, buf, 48, 666);
            otherplayer->isplaying = true;
            Playerlist[playersock]->isplaying = true;

            char buf1[12];
            
            int player = 1;
            int x = newroom.map.sizeX / 2;
            int y = newroom.map.sizeY - 5;
            otherplayer->X = x;
            otherplayer->Y = y;
            memcpy(buf1, (char*)&player, 4);
            memcpy(buf1 + 4, (char*)&x, 4);
            memcpy(buf1 + 8, (char*)&y, 4);
            Ptcpserver->ClientMap->at(otherplayer->PlayerSOCK)->Send(10007, buf1, 12, 666);
            Ptcpserver->ClientMap->at(playersock)->Send(10007, buf1, 12, 666);
           
            player = 2;
            x = newroom.map.sizeX / 2;
            y = 5;
            Playerlist[playersock]->X = x;
            Playerlist[playersock]->Y = y;
            memcpy(buf1, (char*)&player, 4);
            memcpy(buf1 + 4, (char*)&x, 4);
            memcpy(buf1 + 8, (char*)&y, 4);
            Ptcpserver->ClientMap->at(otherplayer->PlayerSOCK)->Send(10007, buf1, 12, 666);
            Ptcpserver->ClientMap->at(playersock)->Send(10007, buf1, 12, 666);

        }


    }

}

void APPManager::r10006(SOCKET& playersock,char op,GameRoom& gameroom,int id)
{
    shared_lock<shared_mutex> lock(sharedmutex); // 设置读锁
    //cout << op << endl;
    switch (op)
    {
    case 'w':
        
        if (id == 1)
        {
            
            if (setplayerpos(gameroom.map, *gameroom.Player1, gameroom.Player1->X, gameroom.Player1->Y - 1))
            {
                
                char buf1[12];
                int player = 1;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player1->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player1->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }
        else
        {
            if (setplayerpos(gameroom.map, *gameroom.Player2, gameroom.Player2->X, gameroom.Player2->Y - 1))
            {
                char buf1[12];
                int player = 2;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player2->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player2->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }


        break;
    case 's':
        if (id == 1)
        {

            if (setplayerpos(gameroom.map, *gameroom.Player1, gameroom.Player1->X, gameroom.Player1->Y + 1))
            {

                char buf1[12];
                int player = 1;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player1->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player1->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }
        else
        {
            if (setplayerpos(gameroom.map, *gameroom.Player2, gameroom.Player2->X, gameroom.Player2->Y + 1))
            {
                char buf1[12];
                int player = 2;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player2->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player2->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }
        break;
    case 'a':
        if (id == 1)
        {

            if (setplayerpos(gameroom.map, *gameroom.Player1, gameroom.Player1->X-1, gameroom.Player1->Y))
            {

                char buf1[12];
                int player = 1;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player1->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player1->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }
        else
        {
            if (setplayerpos(gameroom.map, *gameroom.Player2, gameroom.Player2->X-1, gameroom.Player2->Y))
            {
                char buf1[12];
                int player = 2;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player2->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player2->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }
        break;
    case 'd':
        if (id == 1)
        {

            if (setplayerpos(gameroom.map, *gameroom.Player1, gameroom.Player1->X+1, gameroom.Player1->Y ))
            {

                char buf1[12];
                int player = 1;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player1->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player1->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }
        else
        {
            if (setplayerpos(gameroom.map, *gameroom.Player2, gameroom.Player2->X+1, gameroom.Player2->Y ))
            {
                char buf1[12];
                int player = 2;
                memcpy(buf1, (char*)&player, 4);
                memcpy(buf1 + 4, (char*)&gameroom.Player2->X, 4);
                memcpy(buf1 + 8, (char*)&gameroom.Player2->Y, 4);
                Ptcpserver->ClientMap->at(gameroom.Player1->PlayerSOCK)->Send(10006, buf1, 12, 666);
                Ptcpserver->ClientMap->at(gameroom.Player2->PlayerSOCK)->Send(10006, buf1, 12, 666);
            }
        }
        break;
    case 'f':
        
        if (id == 1)
        {
            
            Bullet bullet(1, 5, 3, 1);
            fight(*gameroom.Player1, gameroom.map, bullet, gameroom.bullets);
        }
        else
        {
            
            Bullet bullet(1,5 , 3, 2);
            fight(*gameroom.Player2, gameroom.map, bullet, gameroom.bullets);
        }
       

        break;
    default:
        break;
    }


}




//=========================================================

