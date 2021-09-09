
#ifndef __EMEMYSYSTEM_H
#define __EMEMYSYSTEM_H
#include"GAMEDefine.h"
#include "PlayerManager.h"
#include "FightSystem.h"
#include <vector>


//生成敌人
void SpawnEnemy(GAMEMAP& gamemap, std::vector<Player>& players);

//人工智障
void EnemyAI(std::vector<Player>& players, GAMEMAP& gamemap, std::vector<Bullet>& bullets);



#endif // !__EMEMYSYSTEM_H
