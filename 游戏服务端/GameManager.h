#ifndef __PLAYERMANAGER_H
#define __PLAYERMANAGER_H


#include <iostream>
#include <conio.h>
#include"GAMEDefine.h"
#include "engine/Player.h"


//    清理飞机位置
void clearplayerpos(GAMEMAP& gamemap, Player& player);


//
//     *
//   *****
//    * *
//    设置飞机位置
bool setplayerpos(GAMEMAP& gamemap, Player& player, int x, int y);









#endif // !__PLAYERMANAGER_H
