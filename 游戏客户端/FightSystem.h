#ifndef __FIGHTSYSTEM_H
#define __FIGHTSYSTEM_H
#include "GAMEDefine.h"
#include <vector>

extern std::vector<Bullet> bullets;
extern std::vector<Player> Players;

//发射子弹
void fight(Player& player, GAMEMAP& gamemap, Bullet bullet, std::vector<Bullet>& bullets);
//检查子弹是否碰撞
bool checkfightcollision(Bullet& bullet, Player& player);

//检查战斗情况
void checkfight(GAMEMAP& gamemap, std::vector<Bullet>& bullets, std::vector<Player>& Players);





#endif // !__FIGHTSYSTEM_H
