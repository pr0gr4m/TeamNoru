#include <iostream>
#include <Windows.h>
#include <conio.h>

int getKeyNoBuff(void)
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

void setConsoleSize(void)
{
	system("mode con: cols=200 lines=60");
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