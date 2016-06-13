#include "lib.h"
#include "menu.h"
#include "player.h"
#include <iostream>

using namespace std;

void printMenu()
{
	int x = 85, y = 1;
	gotoxy(x, y);		cout << "┌────────────────────┐";
	gotoxy(x, y + 1);	cout << "│                                        │";
	gotoxy(x, y + 2);	cout << "│                                        │";
	gotoxy(x, y + 3);	cout << "│                                        │";
	gotoxy(x, y + 4);	cout << "│            스       탯                 │";
	gotoxy(x, y + 5);	cout << "│                                        │";
	gotoxy(x, y + 6);	cout << "│                                        │";
	gotoxy(x, y + 7);	cout << "│            장착 아이템                 │";
	gotoxy(x, y + 8);	cout << "│                                        │";
	gotoxy(x, y + 9);	cout << "│                                        │";
	gotoxy(x, y + 10);	cout << "│            소유 아이템                 │";
	gotoxy(x, y + 11);	cout << "│                                        │";
	gotoxy(x, y + 12);	cout << "│                                        │";
	gotoxy(x, y + 13);	cout << "│            보유   스킬                 │";
	gotoxy(x, y + 14);	cout << "│                                        │";
	gotoxy(x, y + 15);	cout << "│                                        │";
	gotoxy(x, y + 16);	cout << "│            세  이  브                  │";
	gotoxy(x, y + 17);	cout << "│                                        │";
	gotoxy(x, y + 18);	cout << "│                                        │";
	gotoxy(x, y + 19);	cout << "│            끝  내  기                  │";
	gotoxy(x, y + 20);	cout << "│                                        │";
	gotoxy(x, y + 21);	cout << "│                                        │";
	gotoxy(x, y + 22);	cout << "│                                        │";
	gotoxy(x, y + 23);	cout << "│                                        │";
	gotoxy(x, y + 24);	cout << "└────────────────────┘";
}

void eraseMenu()
{
	for (int i = 1; i <= 25; i++)
	{
		gotoxy(85, i); cout << "                                             ";
	}
}

void chooseMenu()
{
	int cx = 93, cy = 5;
	int chNum = 0;
	int ch, flag = 0;
	while (true)
	{
		ch = 0, flag = 0;
		printMenu();
		gotoxy(cx, cy); cout << "▶";
		while (1)
		{
			ch = getKey();
			switch (ch)
			{
			case UP: 
			case 'w': case 'W':
				if (chNum <= STAT)
					break;
				chNum--;
				gotoxy(cx, cy); cout << "  ";
				cy -= 3;
				gotoxy(cx, cy); cout << "▶";
				break;
			case DOWN: 
			case 's': case 'S':
				if (chNum >= EXIT)
					break;
				chNum++;
				gotoxy(cx, cy); cout << "  ";
				cy += 3;
				gotoxy(cx, cy); cout << "▶";
				break;
			case 10: case 13:
				flag = 1;
				break;
			case 'b': case 'B':
				return;
			}
			if (flag)
				break;
		}

		switch (chNum)
		{
		case STAT:
			eraseMenu();
			p.statuschange();
			// 스탯 창
			break;
		case WITEM:
			eraseMenu();
			// 장착 아이템 보여줌
			break;
		case HITEM:
			eraseMenu();
			p.view_itemlist();
			getKey();
			// 소유 아이템 보여줌
			break;
		case HSKILL:
			// 보유 스킬 보여줌
			break;
		case SAVE:
			// 세이브
			break;
		case EXIT:
			// 끝내기
			break;
		}
		ClearReadBuff();
	}
}