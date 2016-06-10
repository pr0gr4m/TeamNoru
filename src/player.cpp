#include "player.h"
#include"lib.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include<conio.h>
#include<iomanip>
using std::cout;
using std::cin;
using std::setfill;
using std::setw;
player::player()
{
}


player::~player()
{
}
void player::Setstr(int nstr){
	str += nstr;
}
void player::Setluck(int nluck){
	luck += nluck;
}
void player::Setdex(int ndex){
	dex += ndex;
}
void player::Sethealth(int nhealth){
	health += nhealth;
}
void player::Setitem(int *nitem){//������׸� ó��
	for (int i = 0; i < 7; i++)
		item[i] += nitem[i];
}
void player::Sethp(){
	float hp = health * 4 + str*1.5;
	nHp += ((int)hp-HP);
	HP = (int)hp;
}
void player::Setap(){
	float ap = str*1.5 + dex * 2;
	AP = (int)ap;
}
int player::pattack(){
	srand(time(NULL));
	float pattack = str*2.5 - (rand() % str + 1);
	return (int)pattack;
}
int player::pdefense(){
	float pdefense = str*1.5;
	return (int)pdefense;
}
bool player::critical(){
	if ((dex*1.5 + luck * 2) > (rand() % 100 + 1))
		return true;
}
void player::statuschange(){//gotoxy�ְ� ��ǥ������Ź�帳�ϴ�.
	int nstr = 0, ndex = 0, nhealth = 0, nluck = 0, xp = 0, yp = 0, off = 0;
	while (off == 0)
	{
		gotoxy(x, y);	cout << "��������������������������������������������";
		gotoxy(x, y + 1);	cout << "��STATUS CHANGE��";
		gotoxy(x, y + 2);	cout << "��Strength : " << setw(3) << setfill(' ') << str << " + - " << nstr << "��";
		gotoxy(x, y + 3);	cout << "��Dex      : " << setw(3) << setfill(' ') << dex << " + - " << ndex << "��";
		gotoxy(x, y + 4);	cout << "��Health   : " << setw(3) << setfill(' ') << health << " + - " << nhealth << "��";
		gotoxy(x, y + 5);	cout << "��Luck     : " << setw(3) << setfill(' ') << luck << " + - " << nluck << "��";
		gotoxy(x, y + 6); cout << "��  ���� �������ͽ�����Ʈ: " << setw(2) << setfill(' ') << sp << "��";
		gotoxy(x, y + 7); cout << "��������������������������������������������";

		if (xp == yp == 0){
			gotoxy(x + 1, y + 2);
			setColor(BLACK, LIGHTGRAY);
			cout << "Strength : " << setw(3) << setfill(' ') << str << " + - " << nstr;
		}
		else if (xp == 0 || yp == 1){
			gotoxy(x + 1, y + 3);
			setColor(BLACK, LIGHTGRAY);
			cout << "Dex      : " << setw(3) << setfill(' ') << dex << " + - " << ndex;
		}
		else if (xp == 0 || yp == 2){
			gotoxy(x + 1, y + 4);
			setColor(BLACK, LIGHTGRAY);
			cout << "Health   : " << setw(3) << setfill(' ') << health << " + - " << nhealth;
		}
		else if (xp == 0 || yp == 3){
			gotoxy(x + 1, y + 5);
			setColor(BLACK, LIGHTGRAY);
			cout << "Luck     : " << setw(3) << setfill(' ') << luck << " + - " << nluck;
		}
		else if (xp == 1 || yp == 0){
			gotoxy(x + 15, y + 2);
			setColor(BLACK, LIGHTGRAY);
			cout << " + - " << nstr;
		}
		else if (xp == 1 || yp == 1){
			gotoxy(x + 15, y + 3);
			setColor(BLACK, LIGHTGRAY);
			cout << " + - " << ndex;
		}
		else if (xp == 1 || yp == 2){
			gotoxy(x + 15, y + 4);
			setColor(BLACK, LIGHTGRAY);
			cout << " + - " << nhealth;
		}
		else if (xp == 1 || yp == 3){
			gotoxy(x + 15, y + 5);
			setColor(BLACK, LIGHTGRAY);
			cout << " + - " << nluck;
		}
		ClearReadBuff();
		int ch = getKey();
		switch (ch)
		{
		case UP: w : W :
			if (xp == 0)
			{
				yp--;
				if (yp < 0)
					yp = 0;
			}
			else
			{
				if (yp == 0)
				{
					if (sp == 0)
					{
						gotoxy(); cout << "������������������������������������";
						gotoxy(); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(); cout << "������������������������������������";
					}
					else
					{
						nstr++;
						sp--;
					}
				}
				else if (yp == 1)
				{
					if (sp == 0)
					{
						gotoxy(); cout << "������������������������������������";
						gotoxy(); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(); cout << "������������������������������������";
					}
					else
					{
						ndex++;
						sp--;
					}
				}
				else if (yp == 2)
				{
					if (sp == 0)
					{
						gotoxy(); cout << "������������������������������������";
						gotoxy(); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(); cout << "������������������������������������";
					}
					else
					{
						nhealth++;
						sp--;
					}
				}
				else if (yp == 3)
				{
					if (sp == 0)
					{
						gotoxy(); cout << "������������������������������������";
						gotoxy(); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(); cout << "������������������������������������";
					}
					else
					{
						nluck++;
						sp--;
					}
				}
				break;
		case DOWN: s : S :
			if (xp == 0)
			{
				yp++;
				if (yp > 5)
					yp = 5;
			}
			else
			{
				if (yp == 0)
				{
					if (nstr > 0)
					{
						nstr--;
						sp++;
					}
				}
				else if (yp == 1)
				{
					if (ndex > 0)
					{
						ndex--;
						sp++;
					}
				}
				else if (yp == 2)
				{
					if (nhealth > 0)
					{
						nhealth--;
						sp++;
					}
				}
				else if (yp == 3)
				{
					if (nluck > 0)
					{
						nluck--;
						sp++;
					}
				}
				break;
		case LEFT: a : A :
			xp--;
			if (xp < 0)
				xp = 0;
			break;
		case RIGHT: d : D :
			xp++;
			if (xp > 1)
				xp == 1;
			break;
		case 10:
			if (sp != 0)
			{
				gotoxy(); cout << "������������������������������������";
				gotoxy(); cout << "������ �������ͽ�����Ʈ�� �ֽ��ϴ٦�";
				gotoxy(); cout << "�������� �����Ͻðڽ��ϱ�?  (Y/N) ��";
				gotoxy(); cout << "������������������������������������";
				ClearReadBuff();
				while (true)
				{
					int yn = getch();
					if (yn == 89 || yn == 121)
					{
						off++;
						break;
					}
					else if (yn == 78 || yn == 110)
					{
						gotoxy(); cout << "����������������������";
						gotoxy(); cout << "�����Ḧ ����մϴ� ��";
						gotoxy(); cout << "����������������������";
						break;
					}
				}
			}
			else
				off++;
			break;
		case 13:
			if (sp != 0)
			{
				gotoxy(); cout << "������������������������������������";
				gotoxy(); cout << "������ �������ͽ�����Ʈ�� �ֽ��ϴ٦�";
				gotoxy(); cout << "������ ���������� �������ͽ�����Ʈ��";
				gotoxy(); cout << "���й�� �Ұ����մϴ�             ��";
				gotoxy(); cout << "�������� �����Ͻðڽ��ϱ�?  (Y/N) ��";
				gotoxy(); cout << "������������������������������������";
				ClearReadBuff();
				while (true)
				{
					int yn = getch();
					if (yn == 89 || yn == 121)
					{
						off++;
						break;
					}
					else if (yn == 78 || yn == 110)
					{
						gotoxy(); cout << "����������������������";
						gotoxy(); cout << "�����Ḧ ����մϴ� ��";
						gotoxy(); cout << "����������������������";
						break;
					}
				}
			}
			else
				off++;
			break;
		default:
			break;
			}
			}
		}
	}
	Setstr(nstr);
	Setdex(ndex);
	Sethealth(nhealth);
	Setluck(nluck);
	Setap();
	Sethp();
}
void player::Lvup(){//��ǥ�����ʿ�
	gotoxy(); cout << "����������������������";
	gotoxy(); cout << "��     Level Up! �� ��";
	gotoxy(); cout << "����������������������";
	ClearReadBuff();
	getch();//�ƹ��ų� ������ �ǰ� �س����ſ��� �ٲټŵ� �˴ϴ�.
	Lv++;
	nexp -= exp;
	exp *= 2;
	sp += 5;
	statuschange();
}