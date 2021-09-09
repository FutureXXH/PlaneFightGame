#ifndef __PVPGAMEMANAGER_H
#define __PVPGAMEMANAGER_H
#pragma once

#pragma comment(lib,"ws2_32.lib")
#include "GAMEDefine.h"
#include "OnineConnector.h"
#include "OnlineSystem.h"
#include "GameMap.h"
#include "Show.h"

#include <iostream>
#include <atomic>
#include <thread>
#include <conio.h>

#pragma warning(disable : 4996)

using namespace std;


void start();

void initshow(int step);





#endif // !__PVPGAMEMANAGER_H
