/*
 * 파일 : npc.cpp
 * 내용 : NPC 클래스 구현
 * 제작 : 최세일
 */

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

		if (!RandInt(50))
		{	// 1/50 확률로
			gotoxy(5, 35);
			cout << "잠깐만 기다려. 내가 줄 것이 있어.";
			getKey();
			gotoxy(5, 36);
			cout << "도박 스킬이야. 한번 마음껏 써봐";
			getKey();
			gotoxy(5, 35);
			cout << sp;
			gotoxy(5, 36);
			cout << sp;

			p.sk_list[9] = 1;
			gotoxy(5, 35);
			cout << "도박 스킬을 얻었다!";
			getKey();
			gotoxy(5, 35);
			cout << sp;
		}
	}
}

NPC2::NPC2()
	: flag(0)
{
	strcpy(str[0], "던전 깊은 곳에 제 친구들이 있어요... 제발 구해주세요");
	strcpy(str[1], "맵에 보이는 ※는 아이템이랍니다");
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

NPC3::NPC3()	//힐러
	: flag(0)
{
	strcpy(str[0], "부상을 입은것 같군요. 제가 치료해 드릴게요");
	strcpy(str[1], "스킬을 사용해 보세요. 몬스터가 순식간에 사라질 거에요");
	strcpy(str[2], "몰아치기라는 스킬의 존재를 아시나요 ");
	strcpy(str[3], "구출된 아이들과 이야기를 나눠보세요");
	strcpy(str[4], "이근처에 이상한 지역이 있다는 소문이 있어요.. 조심하세요");
}

void NPC3::Dialogue()
{
	int tmp = RandInt(3) + 1;
	gotoxy(5, 35);
	cout << str[0];
	getKey();
	gotoxy(5, 36);
	cout << str[tmp];
	getKey();
	gotoxy(5, 35);
	cout << sp;
	gotoxy(5, 36);
	cout << sp;
	p.HealHP(10000);
}

NPC4::NPC4()	//설명충2
	: flag(0)
{
	strcpy(str[0], "혹시 이근처에 숨겨진 장소가 있다는 것을 아나?");
	strcpy(str[1], "원한다면 데려다주지...");
	strcpy(str[2], "사실 자네가 원하지 않다도 데려다줄 참이엿네");
	strcpy(str[3], "숨겨진 장소로 어서 가지...");
	strcpy(str[4], "이 곳에서 나가면 다시는 돌아올 수 없다네");
}

void NPC4::Dialogue()
{
	if (flag == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			gotoxy(5, 34 + i);
			cout << str[i];
			getKey();
		}
		for (int i = 0; i < 4; i++)
		{
			gotoxy(5, 34 + i);
			cout << sp;
		}
		flag = 1;
	}
	else
	{
		gotoxy(5, 35);
		cout << str[4];
		getKey();
		gotoxy(5, 35);
		cout << sp;

		if (!RandInt(10))
		{
			gotoxy(5, 35);
			cout << "근데 잠시 기다려보게. 내가 좋은걸 하나 알려주지";
			getKey();
			gotoxy(5, 36);
			cout << "바로 몰아치기 스킬이네. 잘 사용 하게나.";
			getKey();
			gotoxy(5, 35);
			cout << sp;
			gotoxy(5, 36);
			cout << sp;
			p.sk_list[4] = 1;
			gotoxy(5, 35);
			cout << "몰아치기Lv2 스킬을 습득했다!";
			getKey();
			gotoxy(5, 35);
			cout << sp;
		}
	}
}

NPC5::NPC5()
	: flag(0)
{
	strcpy(str[0], "구해주셔서 감사합니다... 다른 친구도 구해주세요");
	strcpy(str[1], "과거엔 저도 당신과 같은 모험가였어요.");
	strcpy(str[2], "아이템 흉내를 내는 몬스터가 있다고 해요");
	strcpy(str[3], "우리에게 희망이 있을까요?");
	strcpy(str[4], "저희 아버지는 어디 계신 걸까요...");
}

void NPC5::Dialogue()
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
		{
			if (!RandInt(3))
			{	// 1/3 확률로
				gotoxy(5, 35);
				cout << "여기 파란 포션을 하나 드릴게요! 잘 사용하세요";
				p.item_list[6] += 1;
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
				cout << "회복 스킬을 강화시켜 드릴께요! 잘 사용하세요";
				p.sk_list[7] = 1;	//힐2단계
				getKey();
				gotoxy(5, 35);
				cout << sp;
			}
		}
	}
}

NPC6::NPC6()
	: flag(0)
{
	strcpy(str[0], "드디어 와주셧군요 다크플레임... 아니 모험가님");
	strcpy(str[1], "당신은 우리의 희망이에요");
	strcpy(str[2], "꼭 괴물들을 무찔러 주세요");
	strcpy(str[3], "당신은 어떻게 살아남았나요?");
	strcpy(str[4], "내가 바로 칼날 여왕이다.");
}

void NPC6::Dialogue()
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
		{
			if (!RandInt(3))
			{	// 1/3 확률로
				gotoxy(5, 35);
				cout << "여기 하얀 포션을 하나 드릴게요! 잘 사용하세요";
				p.item_list[5] += 1;
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
				cout << "회복 스킬을 강화시켜 드릴께요! 위력이 굉장할거에요";
				p.sk_list[8] = 1;	//힐3단계
				getKey();
				gotoxy(5, 35);
				cout << sp;
			}
		}
	}
}

NPC7::NPC7()
	: flag(0)
{
	strcpy(str[0], "이부근에 괴물을 물리치러온 모험가는 자네가 오랜만이군...");
	strcpy(str[1], "괴물을 쓰러뜨리고 싶다고? 좋아 내가 길을 알려주지...");
	strcpy(str[2], "그 괴물과 싸우기 위한 스킬도 하나 알려주겠네");
	strcpy(str[3], "자네가 꼭 그녀석을 쓰러뜨리길...");
	strcpy(str[4], "......");
}

void NPC7::Dialogue()
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(5, 35 + i);
		cout << str[i];
		getKey();
	}
	for (int i = 0; i < 4; i++)
	{
		gotoxy(5, 35 + i);
		cout << sp;
	}
	p.sk_list[5] = 1;
}