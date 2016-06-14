#include <iostream>
#include <conio.h>
#include "map.h"
#include "lib.h"
#include "game.h"
#include "monster.h"
#include "menu.h"
#include "npc.h"
#include "Battle.h"
#include "player.h"

int nx = 1, ny = 1;
int nStage = 0;
Player p;
NPC1 n1;
NPC2 n2;
NPC3 n3;
NPC4 n4;
NPC5 n5;
NPC6 n6;
NPC7 n7;

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
			else if (nStage == 7)
				nx = 5, ny = 2;
			nStage--;
			if (nStage == 6)
				nStage = 3;
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
				else if (ny + dy == 14)
					n2.Dialogue();
				else if (ny + dy == 16)
					n5.Dialogue();
				else if (ny + dy == 6)
					n6.Dialogue();
			}
			else if (nStage == 1)
			{
				n2.Dialogue();
				map[1][21][34] = 0;
				gotoxy(70, 21);
				std::cout << "  ";
				map[0][14][4] = 4;
			}
			else if (nStage == 2)
			{
				n3.Dialogue();
			}
			else if (nStage == 3)
			{
				if (ny + dy == 2)
				{	// 숨겨진 맵으로
					n4.Dialogue();	// 다른 npc로 변경
					map[nStage][ny][nx] = 0;
					map[nStage][2][4] = 0;
					nx = 38, ny = 3;
					nStage = 7;
					map[nStage][ny][nx] = 9;
					map[nStage][1][38] = 4;
					clrscr();
					mapDraw(nStage);
				}
			}
			else if (nStage == 4)
			{
				n5.Dialogue();
				map[4][21][21] = 0;
				gotoxy(44, 21);
				std::cout << "  ";
				map[0][16][28] = 4;
			}
			else if (nStage == 5)
			{
				n6.Dialogue();
				map[5][13][8] = 0;
				gotoxy(18, 13);
				std::cout << "  ";
				map[0][6][12] = 4;
			}
			else if (nStage == 6)
			{
				n7.Dialogue();
				map[6][ny][nx] = 0;
				nx = 32, ny = 14;
				map[6][ny][nx] = 9;
				clrscr();
				mapDraw(nStage);
			}
			else if (nStage == 7)
			{
				n4.Dialogue();
			}
			// npc와 대화
			return;
		}
		else if (nxt == 5)
		{
			// 아이템 습득
			if (nStage == 0)
				p.item_list[0] = 1;
			else if (nStage == 1)
				p.item_list[4] += 1;
			else if (nStage == 2)
				p.item_list[6] += 1;
			else if (nStage == 3)
				p.item_list[5] += 1;
			else if (nStage == 5)
				p.item_list[6] += 1;
			else if (nStage == 6)
				p.item_list[3] = 1;
			else if (nStage == 7)
			{
				if (ny + dy == 16)
					p.item_list[1] = 1;
				else
					p.item_list[2] = 1;
			}
			map[nStage][ny + dy][nx + dx] = 0;
			gotoxy((ny + dy) * 2 + 2, nx + dx);
			std::cout << "  ";
			return;
		}
		else if (nxt == 6)
		{
			// 몬스터 만남
			LowMonster du(1, 30, DEFN);
			Battle b(du);
			clrscr();
			map[nStage][ny + dy][nx + dx] = 0;
			mapDraw(nStage);

			return;
		}
		else if (nxt == 7)
		{
			// 주유소
			gotoxy(5, 35);
			std::cout << "체력과 기력이 회복되었다!";
			getKey();
			p.HealHP(10000);
			p.HealAP(1000);
			gotoxy(5, 35);
			std::cout << "                         ";
			return;
		}
		else if (nxt == 8)
		{
			
			BossMonster boss;
			Battle b(boss);
			clrscr();

			map[nStage][ny][nx] = 0;
			nx = 5, ny = 12;
			map[nStage][ny][nx] = 9;
			clrscr();
			mapDraw(nStage);

			gotoxy(5, 35);
			std::cout << "..!! 보스를 잡았지만 갇혔다?!";
			getKey();
			gotoxy(5, 35);
			std::cout << "                              ";

			// 보스
			return;
		}
		else if (nxt == 10)
		{
			gotoxy(5, 35);
			std::cout << "..!! 비밀 문을 찾았다!!";
			getKey();
			map[nStage][ny][nx] = 0;
			nStage = 0, nx = 1, ny = 1;
			map[nStage][ny][nx] = 9;
			clrscr();
			mapDraw(nStage);
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
			if (nStage != 0 && nStage != 7 && RandInt(100) == 99)
			{
				LowMonster du(1, 30, DEFN);
				Battle b(du);
				clrscr();
				mapDraw(nStage);
				// 10분의 1 확률로 전투
			}
		}
	}
}