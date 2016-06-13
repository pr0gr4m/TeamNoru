#include <iostream>
#include <cstring>
#include "npc.h"
#include "lib.h"
#include "player.h"

using std::cout;
using std::endl;
using std::strcpy;

char *sp = "                                                                      ";

NPC1::NPC1()
	: flag(0)
{
	strcpy(str[0], "세상에 넌 누구야 새로 보는 사람이라니...");
	strcpy(str[1], "메뉴를 사용하려면 M을 눌러봐 종료할 땐 B를 누르고");
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
		flag = 1;
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
}

NPC2::NPC2()
	: flag(0)
{
	strcpy(str[0], "던전 깊은 곳에 제 친구들이 있어요... 제발 구해주세요");
	strcpy(str[1], "옛날에 하늘은 푸른색이었다고 해요");
	strcpy(str[2], "마음껏 돌아다닐 수 있는 세상이 됬으면 좋겠어요");
	strcpy(str[3], "포션을 먹으면 회복을 한답니다");
	strcpy(str[4], "회복 스킬에 대해서 아시나요?");
}

void NPC2::Dialogue()
{
	if (flag == 0)
	{
		gotoxy(5, 35);
		cout << str[0];
		getKey();
		gotoxy(5, 36);
		cout << "전 마을로 돌아가서 기다리고 있을게요";
		getKey();
		gotoxy(5, 35);
		cout << sp;
		gotoxy(5, 36);
		cout << sp;
		flag = 1;
	}
	else
	{
		int tmp = RandInt(4) + 1;
		gotoxy(5, 35);
		cout << str[tmp];
		getKey();
		gotoxy(5, 35);
		cout << sp;
		if (tmp == 3)
		{	// 포션 얘기할 때
			if (!RandInt(3))
			{	// 1/3 확률로
				gotoxy(5, 35);
				cout << "여기 빨간 포션을 하나 드릴게요! 잘 사용하세요";
				p.item_list[4] += 1;
				getKey();
				gotoxy(5, 35);
				cout << sp;
			}
		}
		if (tmp == 4)
		{
			if (RandInt(2))
			{
				gotoxy(5, 35);
				cout << "회복 스킬을 가르쳐 드릴게요! 이거 좋은거에요!";
				p.sk_list[6] = 1;
				getKey();
				gotoxy(5, 35);
				cout << sp;
			}
		}
	}
}