/*
 * ���� : main.cpp
 * ���� : ���� �Լ�
 * ���� : 1.0
 */

#include <iostream>
#include <ctime>
#include "monster.h"
#include "map.h"
#include "lib.h"
#include "game.h"
#include "player.h"
#include "skill.h"
#include <fstream>
#include "fileIO.h"
#include <cstdlib>

using namespace std;

Skill * skList[10];
ITEM * itList[7];

void initSkill()
{
	skList[0] = new Smite(1);
	skList[1] = new Smite(2);
	skList[2] = new Smite(3);
	skList[3] = new Super(1);
	skList[4] = new Super(2);
	skList[5] = new Super(3);
	skList[6] = new Heal(1);
	skList[7] = new Heal(2);
	skList[8] = new Heal(3);
	skList[9] = new Gamble();
}

void initItem()
{
	itList[0] = new Weapon(MIDDLE);
	itList[1] = new Weapon(HIGH);
	itList[2] = new Armor(MIDDLE);
	itList[3] = new Armor(HIGH);
	itList[4] = new HPPotion(LOW);
	itList[5] = new HPPotion(MIDDLE);
	itList[6] = new APPotion();
}

static const char *open_file = "ASCII\\opening.txt";

int main()
{
	initSkill();
	initItem();
	SetRand();

	std::ifstream fi(fileName, ios::in | ios::binary);

	if (fi.is_open())
	{
		gotoxy(10, 5); cout << "������������������������������������";
		gotoxy(10, 6); cout << "��  ���̺������� �����մϴ�.      ��";
		gotoxy(10, 7); cout << "��  ������ �ҷ����ðڽ��ϱ�?(Y/N) ��";
		gotoxy(10, 8); cout << "������������������������������������";
		
		int ch;
		while (true)
		{
			ch = getKey();
			if (ch == 'y' || ch == 'Y')
			{
				LoadGame();
				break;
			}
			else if (ch == 'n' || ch == 'N')
			{
				gotoxy(10, 10); cout << "�̸��� �Է��ϼ��� : ";
				char buf[BUF_LEN];
				cin.getline(buf, BUF_LEN);
				p = Player(buf);
				break;
			}
		}
	}
	else
	{
		gotoxy(10, 20); cout << "�̸��� �Է��ϼ��� : ";
		char buf[BUF_LEN];
		cin.getline(buf, BUF_LEN);
		p = Player(buf);
	}

	char buf[BUF_LEN];

	std::ifstream op(open_file, ios::in | ios::binary);
	if (!op.is_open())
	{
		std::cerr << "���� ���� ����." << endl << "ASCII ������ �ؽ�Ʈ ������ Ȯ���� �ֽʽÿ�." << endl;
		exit(1);
	}

	bigConsoleSize();
	std::memset(buf, 0, BUF_LEN);
	while (!op.eof())
	{
		op.read((char*)buf, BUF_LEN - 1);
		buf[BUF_LEN - 1] = 0;
		cout << buf;
		std::memset(buf, 0, BUF_LEN);
	}
	op.close();
	getKey();

	gameScreen();

	for (int i = 0; i < 10; i++)
		delete skList[i];
	for (int i = 0; i < 7; i++)
		delete itList[i];

	return 0;
}