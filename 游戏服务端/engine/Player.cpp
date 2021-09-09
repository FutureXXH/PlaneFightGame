#include "Player.h"

Player::Player(SOCKET sock)
{
	
	isConnect = true;
	islogin = false;
	PlayerSOCK = sock;

	starttime = clock();


}

Player::~Player()
{

	SERVERPRINT_INFO << "已删除玩家业务层数据" << std::endl;
}
