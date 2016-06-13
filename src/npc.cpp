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
	strcpy(str[0], "���� �� ������ ���� ���� ����̶��...");
	strcpy(str[1], "�޴��� ����Ϸ��� M�� ������");
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