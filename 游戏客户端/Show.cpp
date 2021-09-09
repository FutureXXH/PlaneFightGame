#include "Show.h"



void zeroxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void show(char** gamemap,int sizex,int sizey)
{
	zeroxy(0, 0);
	for (int y = 0; y < sizey; y++)
	{
		for (int x = 0; x < sizex; x++)
		{
			cout << gamemap[y][x];
		}
		cout << endl;
	}

}


