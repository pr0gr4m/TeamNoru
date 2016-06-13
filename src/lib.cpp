#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "lib.h"

void Delay(int n)
{
	Sleep(n);
}

int getKey(void)
{
	int ch = _getch();
	if (ch == 224 || ch == 0)
	{
		ch = _getch();
	}
	return ch;
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setCursorType(CURSOR_TYPE type)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	switch (type)
	{
	case NOCURSOR:
		curInfo.bVisible = FALSE;
		curInfo.dwSize = 1;
		break;
	case SOLIDCURSOR:
		curInfo.bVisible = TRUE;
		curInfo.dwSize = 100;
		break;
	case NORMALCURSOR:
		curInfo.bVisible = TRUE;
		curInfo.dwSize = 20;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void setConsoleSize(void)
{
	system("mode con: cols=150 lines=50");
	system("cls");
}

void clrscr(void)
{
	system("cls");
}

void setColor(int colFrt, int colBck)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((colBck << 4) | colFrt));
}

void ClearReadBuff(void)
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
}