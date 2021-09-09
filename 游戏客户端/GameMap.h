
#ifndef __GAMEMAP_H
#define __GAMEMAP_H
#include <iostream>
#include"GAMEDefine.h"
#include <vector>

//初始化地图
void InitMap(GAMEMAP& gamemap, int sizex, int sizey);


//刷新墙
void refreshwall(GAMEMAP& gamemap);


//刷新信息面板框架
void refreshinfopanel(GAMEMAP& gamemap);


//刷新信息面板框架中的信息数据
void  refreshgameinfo(GAMEMAP& gamemap,Gameinfo & gameinfo,std::vector<Player>& players);

void refreshgameinfoPVP(onlinegameinfo& gameinfo);

//清理游戏地图
void cleargamemap(GAMEMAP& gamemap);


#endif // !__GAMEMAP_H

