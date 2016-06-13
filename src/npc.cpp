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

NPC3::NPC3()	//����
	: flag(0)
{
	strcpy(str[0], "�λ��� ������ ������. ���� ġ���� �帱�Կ�");
	strcpy(str[1], "��ų�� ����� ������. ���Ͱ� ���İ��� ����� �ſ���");
	strcpy(str[2], "����ġ�� ��ų�� �Ϲݰ��� �������� ����Ѵ�ϴ� ");
	strcpy(str[3], "��Ÿ��ų�� ������ 100�� �������� �ټ� �ִٰ� �ؿ�");
	strcpy(str[4], "�̱�ó�� �̻��� ������ �ִٴ� �ҹ��� �־��.. �����ϼ���");
}

void NPC3::Dialogue()
{
	int tmp = RandInt(3) + 1;
	gotoxy(5, 35);
	cout << str[0];
	getKey();
	cout << str[tmp];
	gotoxy(5, 36);
	getKey();
	gotoxy(5, 35);
	cout << sp;
	gotoxy(5, 36);
	cout << sp;
}

NPC4::NPC4()	//������2
	: flag(0)
{
	strcpy(str[0], "Ȥ�� �̱�ó�� ������ ��Ұ� �ִٴ� ���� �Ƴ�?");
	strcpy(str[1], "���Ѵٸ� ����������...");
	strcpy(str[2], "��� �ڳװ� ������ �ʴٵ� �������� ���̿���");
	strcpy(str[3], "������ ��ҷ� � ����...");
	strcpy(str[4], "�ƹ����� ����ҷ� ���ƿü� ������ ������ ����");
}

void NPC4::Dialogue()
{
	if (flag == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			gotoxy(5, 34 + i);
			cout << str[i];
			getKey();
		}
		for (int i = 0; i < 3; i++)
		{
			gotoxy(5, 35 + i);
			cout << sp;
		}
		flag = 1;
	}
	else
	{
		for (int i = 3; i < 5; i++)
		{
			gotoxy(5, 32 + i);
			cout << str[i];
			getKey();
		}
		for (int i = 0; i < 2; i++)
		{
			gotoxy(5, 35 + i);
			cout << sp;
		}
	}
}

NPC5::NPC5()
	: flag(0)
{
	strcpy(str[0], "�����ּż� �����մϴ�... �ٸ� ģ���� �����ּ���");
	strcpy(str[1], "���ſ� ���� ��Ű� ���� ���谡�����.");
	strcpy(str[2], "����� ���ڱ� ������ �ѻ��� �Դ� �ٶ���...");
	strcpy(str[3], "�츮���� ����� �������?");
	strcpy(str[4], "���� �ƹ����� ��� ��� �ɱ��...");
}

void NPC5::Dialogue()
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
		{
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
				cout << "ȸ�� ��ų�� ��ȭ���� �帱����! �� ����ϼ���";
				p.sk_list[7] = 1;	//��2�ܰ�
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
	strcpy(str[0], "���� ���ּ˱��� ��ũ�÷���... �ƴ� ���谡��");
	strcpy(str[1], "����� �츮�� ����̿���");
	strcpy(str[2], "�� �������� ���� �ּ���");
	strcpy(str[3], "����� ��� ��Ƴ��ҳ���?");
	strcpy(str[4], "���� �ٷ� Į�� �����̴�.");
}

void NPC6::Dialogue()
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
		{
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
				cout << "ȸ�� ��ų�� ��ȭ���� �帱����! ������ �����Ұſ���";
				p.sk_list[8] = 1;	//��3�ܰ�
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
	strcpy(str[0], "�̺αٿ� ������ ����ġ���� ���谡�� �ڳװ� �������̱�...");
	strcpy(str[1], "������ �����߸��� �ʹٰ�? ���� ���� ���� �˷�����...");
	strcpy(str[2], "�ڳװ� �� �׳༮�� �����߸���...");
	strcpy(str[3], "����� ��ٳ�");
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
}