#include <iostream>
#include <cstring>
#include "npc.h"
#include "lib.h"

using std::cout;
using std::endl;
using std::strcpy;

char *sp = "                                                                      ";

NPC1::NPC1()
	: flag(0)
{
	strcpy(str[0], "세상에 넌 누구야 새로 보는 사람이라니...");
	strcpy(str[1], "메뉴를 사용하려면 M을 눌러봐");
	strcpy(str[2], "스탯을 찍으려면 원하는 줄에서 오른쪽 화살표 키를 눌러봐");
	strcpy(str[3], "소유 아이템 리스트에서 아이템을 장착하거나 소비할 수 있어");
	strcpy(str[4], "던전에는 무서운 몬스터들이 살고있어...");
}

void NPC1::Dialogue()
{
	if (flag == 0)
	{
		gotoxy(5, 35);
		cout << str[0];
		getKey();
		gotoxy(5, 35);
		cout << sp;
	}
	else
	{
		for (int i = 1; i < 5; i++)
		{
			gotoxy(5, 34 + i);
			cout << str[i];
			getKey();
		}
		for (int i = 0; i < 4; i++)
		{
			gotoxy(5, 35 + i);
			cout << sp;
		}
	}
	flag = 1;
}