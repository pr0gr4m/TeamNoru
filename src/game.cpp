#include <iostream>
#include <conio.h>
#include "map.h"
#include "lib.h"
#include "game.h"
#include "monster.h"
#include "menu.h"
#include "npc.h"

static int nx = 1, ny = 1;
static int nStage = 0;

NPC1 n1;

void gameScreen(void)
{
	int ch;
	setCursorType();
	mapDraw(nStage);

	while (1)
	{
		ch = _getch();
		if (ch == 0 || ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			case UP: case DOWN:
			case LEFT: case RIGHT:
				Move(ch);
				break;
			}
		}
		else
		{
			switch (ch)
			{
			case 'm': case 'M':
				chooseMenu();
				clrscr();
				mapDraw(nStage);
			}
		}
	}
}

void Move(int dir)
{
	int dx = 0, dy = 0;
	int i, j;

	switch (dir)
	{
	case LEFT:
		dx = -1;
		break;
	case RIGHT:
		dx = 1;
		break;
	case UP:
		dy = -1;
		break;
	case DOWN:
		dy = 1;
		break;
	}

	int nxt = map[nStage][ny + dy][nx + dx];

	if (nxt != 1)
	{
		if (nxt == 2)
		{	// 이전 맵으로
			map[nStage][ny][nx] = 0;
			if (nStage == 1)
				nx = 19, ny = 23;
			else if (nStage == 2)
				nx = 38, ny = 5;
			else if (nStage == 3)
				nx = 38, ny = 3;
			else if (nStage == 4)
				nx = 34, ny = 22;
			else if (nStage == 5)
				nx = 37, ny = 1;
			else if (nStage == 6)
				nx = 19, ny = 1;
			nStage--;
			map[nStage][ny][nx] = 9;
			clrscr();
			mapDraw(nStage);
		}
		else if (nxt == 3)
		{	// 다음 맵으로
			map[nStage][ny][nx] = 0;
			if (nStage == 0)
				nx = 1, ny = 21;
			else if (nStage == 1)
				nx = 1, ny = 9;
			else if (nStage == 2)
				nx = 2, ny = 21;
			else if (nStage == 3)
				nx = 2, ny = 19;
			else if (nStage == 4)
				nx = 19, ny = 22;
			else if (nStage == 5)
				nx = 1, ny = 4;
			nStage++;
			map[nStage][ny][nx] = 9;
			clrscr();
			mapDraw(nStage);
		}
		else if (nxt == 4)
		{
			if (nStage == 0)
			{
				// 첫 번째 맵의 5번째 줄에 있는 npc
				if (ny + dy == 5)
					n1.Dialogue();
			}
			// npc와 대화
			return;
		}
		else if (nxt == 5)
		{
			// 아이템 습득
			return;
		}
		else if (nxt == 6)
		{
			// 몬스터 만남
			return;
		}
		else
		{
			gotoxy(nx * 2 + 2, ny);
			std::cout << "  ";
			map[nStage][ny][nx] = 0;
			nx += dx;
			ny += dy;
			map[nStage][ny][nx] = 9;
			gotoxy(nx * 2 + 2, ny);
			std::cout << "Ｐ";
			if (nStage != 0 && !RandInt(5))
			{
				LowMonster du(1, 20, DEFN);
				clrscr();
				du.printASCII();
				getKey();
				clrscr();
				mapDraw(nStage);
				// 10분의 1 확률로 전투
			}
		}
	}
}