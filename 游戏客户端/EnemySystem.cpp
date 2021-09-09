#include "EnemySystem.h"

void SpawnEnemy(GAMEMAP& gamemap, std::vector<Player>& players)
{
	Player spawnenemy(1, 5+(rand()%(gamemap.sizeX-10)),3+ (rand() % (gamemap.sizeY - gamemap.sizeY/2)),2);
	setplayerpos(gamemap, spawnenemy, spawnenemy.X, spawnenemy.Y);
	players.push_back(spawnenemy);

}

void EnemyAI(std::vector<Player>& players, GAMEMAP& gamemap, std::vector<Bullet>& bullets)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].Type == 1)continue;
		if ((rand() % 100) >= 60)
		{
			setplayerpos(gamemap, players[i], players[i].X + (rand() % 10) / 5, players[i].Y + (rand() % 10) / 5);
		}
		else
		{
			setplayerpos(gamemap, players[i], players[i].X - (rand() % 10) / 5, players[i].Y - (rand() % 10) / 5);
		}
		
		if ((rand()%100)  >= 60)
		{
			Bullet bullet(1, 20, 3,2);
			fight(players[i], gamemap, bullet, bullets);
		}

	}
}
