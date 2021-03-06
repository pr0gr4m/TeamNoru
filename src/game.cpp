/*
 * 파일 : game.cpp
 * 내용 : 게임 전반 알고리즘
 * 제작 : 박강민
 */

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
#include <fstream>

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

static const char *end_file = "ASCII\\Ending.txt";

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
			HighMonster m(20, 30, AGGR);
			Battle b(m);
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
			if (!RandInt(20))
			{
				p.sk_list[3] = 1;
				gotoxy(5, 35);
				std::cout << "몰아치기Lv1 스킬을 습득하였다!";
				getKey();
				gotoxy(5, 35);
				std::cout << "                              ";
			}
			return;
		}
		else if (nxt == 8)
		{
			gotoxy(5, 35);
			std::cout << "심상치 않은 기운이 느껴지는 구체다..";
			getKey();
			gotoxy(5, 36);
			std::cout << "이것에서 발산되는 기운 때문에 몬스터가 생기는듯 하다.";
			getKey();
			gotoxy(5, 37);
			std::cout << "내일의 안녕을 위하여!!!";
			getKey();
			
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

			char buf[BUF_LEN];

			std::ifstream ep(end_file, std::ios::in | std::ios::binary);
			if (!ep.is_open())
			{
				std::cerr << "파일 오픈 실패." << std::endl << "ASCII 폴더와 텍스트 파일을 확인해 주십시오." << std::endl;
				exit(1);
			}

			bigConsoleSize();
			std::memset(buf, 0, BUF_LEN);
			while (!ep.eof())
			{
				ep.read((char*)buf, BUF_LEN - 1);
				buf[BUF_LEN - 1] = 0;
				std::cout << buf;
				std::memset(buf, 0, BUF_LEN);
			}
			ep.close();
			std::cin.get();

			setConsoleSize();
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
			if (nStage != 0 && nStage != 7 && !RandInt(30))		// 1/30 확률
			{
				if (nStage >= 1 && nStage <= 3)
				{
					int rand_mon = RandInt(3);
					if (rand_mon == 1)
					{
						LowMonster m(nStage * (RandInt(3) + 1), nStage * 10, AGGR);
						Battle b(m);
						clrscr();
						mapDraw(nStage);
					}
					else if (rand_mon == 2)
					{
						LowMonster m(nStage * (RandInt(3) + 1), nStage * 5, DEFN);
						Battle b(m);
						clrscr();
						mapDraw(nStage);
					}
					else
					{
						LowMonster m(nStage * (RandInt(3) + 1));
						Battle b(m);
						clrscr();
						mapDraw(nStage);
					}
					if (!RandInt(10))	// 1 / 10 확률로
					{
						p.sk_list[0] = 1;
						gotoxy(5, 35);
						std::cout << "강타Lv1 스킬을 얻었다!";
						getKey();
						gotoxy(5, 35);
						std::cout << "                      ";
					}
				}
				else if (nStage >= 4 && nStage <= 6)
				{
					int rand_mon = RandInt(3);
					if (rand_mon == 1)
					{
						HighMonster m(nStage * (RandInt(3) + 1), nStage * 20, AGGR);
						Battle b(m);
						clrscr();
						mapDraw(nStage);
					}
					else if (rand_mon == 2)
					{
						HighMonster m(nStage * (RandInt(3) + 1), nStage * 15, DEFN);
						Battle b(m);
						clrscr();
						mapDraw(nStage);
					}
					else
					{
						HighMonster m(nStage * (RandInt(3) + 1));
						Battle b(m);
						clrscr();
						mapDraw(nStage);
					}
					if (!RandInt(10))	// 1 / 10 확률로
					{
						p.sk_list[1] = 1;
						gotoxy(5, 35);
						std::cout << "강타Lv2 스킬을 얻었다!";
						getKey();
						gotoxy(5, 35);
						std::cout << "                      ";
					}
					else if (!RandInt(20))	// 9/200 확률로
					{
						p.sk_list[2] = 1;
						gotoxy(5, 35);
						std::cout << "강타Lv3 스킬을 얻었다!";
						getKey();
						gotoxy(5, 35);
						std::cout << "                      ";
					}
				}
			}
			return;
		}
	}
}