/*
 * 파일 : menu.cpp
 * 내용 : 메뉴 출력 및 알고리즘
 * 제작 : 김민주, 박강민
 */

#include "lib.h"
#include "menu.h"
#include "player.h"
#include "fileIO.h"
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

bool askSave()
{
	gotoxy(90, 15); cout << "┌────────────────┐";
	gotoxy(90, 16); cout << "│  세이브를 하시겠습니까?  (Y/N) │";
	gotoxy(90, 17); cout << "└────────────────┘";

	int ch = getKey();

	if (ch == 'y' || ch == 'Y')
		return true;
	else
		return false;
}

bool askExit()
{
	gotoxy(90, 15); cout << "┌────────────────┐";
	gotoxy(90, 16); cout << "│  게임을 종료하겠습니까?  (Y/N) │";
	gotoxy(90, 17); cout << "└────────────────┘";

	int ch = getKey();

	if (ch == 'y' || ch == 'Y')
		return true;
	else
		return false;
}

void printSave(bool isSuccess)
{
	if (isSuccess)
	{
		gotoxy(90, 15); cout << "┌────────────────┐";
		gotoxy(90, 16); cout << "│   정상적으로 저장되었습니다    │";
		gotoxy(90, 17); cout << "└────────────────┘";
	}
	else
	{
		gotoxy(90, 15); cout << "┌────────────────┐";
		gotoxy(90, 16); cout << "│      저장에 실패하였습니다.    │";
		gotoxy(90, 17); cout << "└────────────────┘";
	}
	getKey();
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
			p.equipped();
			// 장착 아이템 보여줌
			break;
		case HITEM:
			eraseMenu();
			p.item_mount();
			// 소유 아이템 보여줌
			break;
		case HSKILL:
			eraseMenu();
			p.view_skills();
			// 보유 스킬 보여줌
			break;
		case SAVE:
			if (askSave())
				printSave(SaveGame());
			// 세이브
			break;
		case EXIT:
			if (askExit())
				exit(0);
			// 끝내기 (프로세스 종료시 자동으로 메모리 해제됨)
			break;
		}
		ClearReadBuff();
	}
}