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
	strcpy(str[0], "���� �� ������ ���� ���� ����̶��...");
	strcpy(str[1], "�޴��� ����Ϸ��� M�� ������ ������ �� B�� ������");
	strcpy(str[2], "������ �������� ���ϴ� �ٿ��� ������ ȭ��ǥ Ű�� ������");
	strcpy(str[3], "���� ������ ����Ʈ���� �������� �����ϰų� �Һ��� �� �־�");
	strcpy(str[4], "�������� ������ ���͵��� ����־�...");
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
	strcpy(str[0], "���� ���� ���� �� ģ������ �־��... ���� �����ּ���");
	strcpy(str[1], "������ �ϴ��� Ǫ�����̾��ٰ� �ؿ�");
	strcpy(str[2], "������ ���ƴٴ� �� �ִ� ������ ������ ���ھ��");
	strcpy(str[3], "������ ������ ȸ���� �Ѵ�ϴ�");
	strcpy(str[4], "ȸ�� ��ų�� ���ؼ� �ƽó���?");
}

void NPC2::Dialogue()
{
	if (flag == 0)
	{
		gotoxy(5, 35);
		cout << str[0];
		getKey();
		gotoxy(5, 36);
		cout << "�� ������ ���ư��� ��ٸ��� �����Կ�";
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
		{	// ���� ����� ��
			if (!RandInt(3))
			{	// 1/3 Ȯ����
				gotoxy(5, 35);
				cout << "���� ���� ������ �ϳ� �帱�Կ�! �� ����ϼ���";
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
				cout << "ȸ�� ��ų�� ������ �帱�Կ�! �̰� �����ſ���!";
				p.sk_list[6] = 1;
				getKey();
				gotoxy(5, 35);
				cout << sp;
			}
		}
	}
}