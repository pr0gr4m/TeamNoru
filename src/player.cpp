#include "player.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "lib.h"
#include <iomanip>
#include "menu.h"
#include "item.h"
using std::cout;
using std::cin;
using std::setfill;
using std::setw;
using std::endl;
using std::setiosflags;
using std::ios;
extern Skill * skList[10];
extern ITEM * itList[7];

Player::Player()
{
	// �ε�� ����Ʈ ������
}

Player::Player(const char *n)
{
	strcpy(name, n);
	initializig();
	Sethp();
	Setap();
	nHp = HP;
	nAP = AP;
}

void Player::initializig(){
	str = 15;
	luck = 5;
	dex = 10;
	health = 5;
	Lv = 1;
	exp = 30;
	sp = 0;
	weapon = NULL;
	armor = NULL;
	weapon_num = -1;
	armor_num = -1;
	for (int i = 0; i < SKILL_NUM; i++)
		sk_list[i] = 0;
	for (int i = 0; i < ITEM_NUM; i++)
		item_list[i] = 0;
}

Player& Player::operator=(const Player& player)
{
	if (this == &player)
		return *this;
	strcpy(name, player.name);
	str = player.str;
	luck = player.luck;
	dex = player.dex;
	health = player.health;
	Lv = player.health;
	exp = player.exp;
	sp = player.sp;
	weapon = player.weapon;
	armor = player.armor;
	weapon_num = player.weapon_num;
	armor_num = player.armor_num;
	for (int i = 0; i < SKILL_NUM; i++)
		sk_list[i] = player.sk_list[i];
	for (int i = 0; i < ITEM_NUM; i++)
		item_list[i] = player.item_list[i];
	Sethp();
	Setap();
	nHp = HP;
	nAP = AP;
	return *this;
}

void Player::Setstr(int nstr){
	str += nstr;
}
void Player::Setluck(int nluck){
	luck += nluck;
}
void Player::Setdex(int ndex){
	dex += ndex;
}
void Player::Sethealth(int nhealth){
	health += nhealth;
}
void Player::Sethp(){
	float hp = health * 4 + str*1.5;
	HealHP((int)hp-HP);
	HP = (int)hp;
}

void Player::Setap(){
	float ap = str*1.5 + dex * 2;
	HealAP((int)ap - AP);
	AP = (int)ap;
}

int Player::pattack(){
	float pattack = str*2.5 - (rand() % str + 1);
	return (int)pattack;
}

int Player::pdefense(){
	float pdefense = str*1.5;
	return (int)pdefense;
}

bool Player::critical(){
	if ((dex*1.5 + luck * 2) > (rand() % 100 + 1))
		return true;
}

int Player::attackDamage()
{
	int dmg = pattack();
	if (weapon != NULL)
		dmg += (weapon->Amount());

	if (critical())
		return dmg * 2;
	else
		return dmg;
}

int Player::beatenDamage(int dmg){
	int defensivePower = pdefense();
	if (armor != NULL)
		defensivePower += (armor->Amount());
	int calDmg = dmg - defensivePower > 0 ? dmg - defensivePower : 0;
	if (nHp <= calDmg)
		nHp = 0;
	else
		nHp -= calDmg;
	return calDmg;
}

int Player::HealHP(int hp){
	if (hp > HP - nHp)
		nHp = HP;
	else
		nHp += hp;
	return nHp;
}

int Player::HealAP(int ap){
	if (ap > AP - nAP)
		nAP = AP;
	else
		nAP += ap;
	return nAP;
}

void Player::Getexp(int pexp){
	nexp += pexp;
	if (nexp >= exp)
		Lvup();
}

void Player::statuschange(){//gotoxy�ְ� ��ǥ������Ź�帳�ϴ�.
	int nstr = 0, ndex = 0, nhealth = 0, nluck = 0, xp = 0, yp = 0, off = 0;
	int x = 92, y = 3;
	while (off == 0)
	{
		gotoxy(x, y);		cout << "                              ";
		gotoxy(x, y);		cout << "������������������������������";
		gotoxy(x, y + 1);	cout << "��STATUS CHANG              ��";
		gotoxy(x, y + 2);	cout << "��Strength : " << setw(3) << setfill(' ') << str << "   + -   " << nstr << "  ��";
		gotoxy(x, y + 3);	cout << "��Dex      : " << setw(3) << setfill(' ') << dex << "   + -   " << ndex << "  ��";
		gotoxy(x, y + 4);	cout << "��Health   : " << setw(3) << setfill(' ') << health << "   + -   " << nhealth << "  ��";
		gotoxy(x, y + 5);	cout << "��Luck     : " << setw(3) << setfill(' ') << luck << "   + -   " << nluck << "  ��";
		gotoxy(x, y + 6);	cout << "������ �������ͽ�����Ʈ: " << setw(2) << setfill(' ') << sp << " ��";
		gotoxy(x, y + 7);	cout << "������������������������������";

		if (xp ==0 && yp == 0){
			gotoxy(x + 2, y + 2);
			setColor(BLACK, LIGHTGRAY);
			cout << "Strength : " << setw(3) << setfill(' ') << str << "   + -   " << nstr;
			setColor();
		}
		else if (xp == 0 && yp == 1){
			gotoxy(x + 2, y + 3);
			setColor(BLACK, LIGHTGRAY);
			cout << "Dex      : " << setw(3) << setfill(' ') << dex << "   + -   " << ndex;
			setColor();
		}
		else if (xp == 0 && yp == 2){
			gotoxy(x + 2, y + 4);
			setColor(BLACK, LIGHTGRAY);
			cout << "Health   : " << setw(3) << setfill(' ') << health << "   + -   " << nhealth;
			setColor();
		}
		else if (xp == 0 && yp == 3){
			gotoxy(x + 2, y + 5);
			setColor(BLACK, LIGHTGRAY);
			cout << "Luck     : " << setw(3) << setfill(' ') << luck << "   + -   " << nluck;
			setColor();
		}
		else if (xp == 1 && yp == 0){
			gotoxy(x + 18, y + 2);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -   " << nstr;
			setColor();
		}
		else if (xp == 1 && yp == 1){
			gotoxy(x + 18, y + 3);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -   " << ndex;
			setColor();
		}
		else if (xp == 1 && yp == 2){
			gotoxy(x + 18, y + 4);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -   " << nhealth;
			setColor();
		}
		else if (xp == 1 && yp == 3){
			gotoxy(x + 18, y + 5);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -   " << nluck;
			setColor();
		}
		ClearReadBuff();
		int ch = getKey();
		switch (ch)
		{
		case UP: case 'w': case 'W':
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
						gotoxy(90, 15); cout << "������������������������������������";
						gotoxy(90, 16); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(90, 17); cout << "������������������������������������";
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
						gotoxy(90, 15); cout << "������������������������������������";
						gotoxy(90, 16); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(90, 17); cout << "������������������������������������";
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
						gotoxy(90, 15); cout << "������������������������������������";
						gotoxy(90, 16); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(90, 17); cout << "������������������������������������";
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
						gotoxy(90, 15); cout << "������������������������������������";
						gotoxy(90, 16); cout << "������ �������ͽ�����Ʈ�� �����ϴ٦�";
						gotoxy(90, 17); cout << "������������������������������������";
					}
					else
					{
						nluck++;
						sp--;
					}
				}	
			}
			break;
		case DOWN: case 's': case 'S':
			if (xp == 0)
			{
				yp++;
				if (yp > 3)
					yp = 3;
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
			}
		case LEFT: case 'a' : case 'A':
			xp--;
			if (xp < 0)
				xp = 0;
			break;
		case RIGHT: case 'd': case 'D':
			xp++;
			if (xp > 1)
				xp = 1;		// ���� �� == ����?//��Ż�� �������¶� �׷������ϴ�
			break;
		case 10: case 13:
			if (sp != 0)
			{
				gotoxy(90, 15); cout << "������������������������������������";
				gotoxy(90, 16); cout << "������ �������ͽ�����Ʈ�� �ֽ��ϴ٦�";
				gotoxy(90, 17); cout << "�������� �����Ͻðڽ��ϱ�?  (Y/N) ��";
				gotoxy(90, 18); cout << "������������������������������������";
				ClearReadBuff();
				while (true)
				{
					int yn = getKey();
					if (yn == 'y' || yn == 'Y')
					{
						off++;
						break;
					}
					else if (yn == 'n' || yn == 'N')
					{
						gotoxy(90, 15); cout << "                                    ";
						gotoxy(90, 16); cout << "                                    ";
						gotoxy(90, 17); cout << "                                    ";
						gotoxy(90, 18); cout << "                                    ";
						gotoxy(90, 15); cout << "����������������������";
						gotoxy(90, 16); cout << "�����Ḧ ����մϴ� ��";
						gotoxy(90, 17); cout << "����������������������";
						_sleep(200);
						gotoxy(90, 15); cout << "                                    ";
						gotoxy(90, 16); cout << "                                    ";
						gotoxy(90, 17); cout << "                                    ";
						break;
					}
				}
			}
			else
				off++;
			break;
		default:
			// �� ��
			break;
		}
	}
	Setstr(nstr);
	Setdex(ndex);
	Sethealth(nhealth);
	Setluck(nluck);
	Setap();
	Sethp();
}

void Player::Lvup(){//��ǥ�����ʿ�
	gotoxy(10, 30); cout << "������������������������";
	gotoxy(10, 31); cout << "��     Level Up! ��   ��";
	gotoxy(10, 32); cout << "������������������������";
	ClearReadBuff();
	getKey();//�ƹ��ų� ������ �ǰ� �س����ſ��� �ٲټŵ� �˴ϴ�.
	Lv++;
	nexp -= exp;
	exp *= 2;
	sp += 5;
	// ������ �޴����� ����
}
void Player::view_itemlist(){
	int x = 92, y = 3;
	int i=1;
	gotoxy(x, y);cout << "��������������������������������";
	gotoxy(x, y+1); cout << "��                            ��";
	gotoxy(x, y+2); cout << "��                            ��";
	gotoxy(x, y+3); cout << "��                            ��";
	gotoxy(x, y+4); cout << "��                            ��";
	gotoxy(x, y+5); cout << "��                            ��";
	gotoxy(x, y+6); cout << "��                            ��";
	gotoxy(x, y+7); cout << "��                            ��";
	gotoxy(x, y+8); cout << "��                            ��";
	gotoxy(x, y+9); cout << "��                            ��";
	gotoxy(x, y + 10); cout << "��                            ��";
	gotoxy(x, y + 11); cout << "��                            ��";
	gotoxy(x, y + 12); cout << "��                            ��";
	gotoxy(x, y + 13); cout << "��                            ��";
	gotoxy(x, y+14); cout << "��������������������������������";
	if (item_list[0] != 0)
	{
		gotoxy(x+3, y +1 +i); 
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[0] << " X " << setw(5) << setfill(' ') << item_list[0] ;
		i+=2;
	}
	if (item_list[1] != 0)
	{
		gotoxy(x+3, y+1 +i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[1] << " X " << setw(5) << setfill(' ') << item_list[1] ;
		i+=2;
	}
	if (item_list[2] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[2] << " X " << setw(5) << setfill(' ') << item_list[2] ;
		i+=2;
	}
	if (item_list[3] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[3] << " X " << setw(5) << setfill(' ') << item_list[3] ;
		i+=2;
	}
	if (item_list[4] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[4] << " X " << setw(5) << setfill(' ') << item_list[4] ;
		i+=2;
	}
	if (item_list[5] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[5] << " X " << setw(5) << setfill(' ') << item_list[5] ;
		i+=2;
	}
	if (item_list[6] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[6] << " X " << setw(5) << setfill(' ') << item_list[6] ;
		i+=2;
	}
	
}
void Player::item_mount(){
	int yp = 0, i, j = 0, off=0;
	int x = 95, y = 4;
	int ion[7];
	for (i = 0; i < ITEM_NUM; i++)
	{
		if (item_list[i] != 0)
		{
			ion[j] = i;
			j++;
		}
		if (i == ITEM_NUM - 1 && j == 0)
		{
			view_itemlist();
			off++;
			while (true)
			{
				ClearReadBuff();
				int ch = getKey();
				if (ch == 'b' || ch == 'B')
					break;
			}
		}
	}
	while (off==0)
	{
		view_itemlist();
		if (yp == 0)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y + 1);
			cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[ion[0]] << " X " << setw(5) << setfill(' ') << item_list[ion[0]] ;
			setColor();
		}
		else if (yp == 1)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y + 2 + 1);
			cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[ion[1]] << " X " << setw(5) << setfill(' ') << item_list[ion[1]] ;
			setColor();
		}
		else if (yp == 2)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y + 4 + 1);
			cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[ion[2]] << " X " << setw(5) << setfill(' ') << item_list[ion[2]] ;
			setColor();
		}
		else if (yp == 3)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y + 6 + 1);
			cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[ion[3]] << " X " << setw(5) << setfill(' ') << item_list[ion[3]] ;
			setColor();
		}
		else if (yp == 4)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y + 8 + 1);
			cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[ion[4]] << " X " << setw(5) << setfill(' ') << item_list[ion[4]] ;
			setColor();
		}
		else if (yp == 5)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y + 10 + 1);
			cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[ion[5]] << " X " << setw(5) << setfill(' ') << item_list[ion[5]] ;
			setColor();
		}
		else if (yp == 6)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y + 12 + 1);
			cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[ion[6]] << " X " << setw(5) << setfill(' ') << item_list[ion[6]] ;
			setColor();
		}
		ClearReadBuff();
		int ch = getKey();
		switch (ch)
		{
		case UP:case 'w' : case 'W':
			yp--;
			if (yp < 0)
				yp = 0;
			break;
		case DOWN: case 's': case 'S':
			yp++;
			if (yp > j-1)
				yp = j-1;
			break;
		case 10: case 13:
			if (ion[yp] == 0 || ion[yp] == 1)
			{
				gotoxy(90, 15); cout << "������������������������������������";
				gotoxy(90, 16); cout << "�����⸦ �����Ͻð� ���ϱ�? (Y/N) ��";
				gotoxy(90, 17); cout << "������������������������������������";
				while (true)
				{
					int yn = getKey();
					if (yn == 'y' || yn == 'Y')
					{
						if (Lv < itList[yp]->Level())
						{
							gotoxy(90, 15); cout << "������������������������������������";
							gotoxy(90, 16); cout << "�������� ���ڶ� ������ �� �����ϴ٦�";
							gotoxy(90, 17); cout << "������������������������������������";
							_sleep(300);
							gotoxy(90, 15); cout << "                                           ";
							gotoxy(90, 16); cout << "                                           ";
							gotoxy(90, 17); cout << "                                           ";
						} 
						else
						{
							weapon = (Weapon*)itList[yp];
							weapon_num = yp;
							gotoxy(90, 15); cout << "                                           ";
							gotoxy(90, 16); cout << "                                           ";
							gotoxy(90, 17); cout << "                                           ";
						}
						break;
					}
					else if (yn == 'n' || yn == 'N')
					{
						break;
					}
				}
				
			}
			else if (ion[yp] == 2 || ion[yp] == 3)
			{
				gotoxy(90, 15); cout << "��������������������������������������";
				gotoxy(90, 16); cout << "������ �����Ͻð� ���ϱ�? (Y/N) ��";
				gotoxy(90, 17); cout << "��������������������������������������";
				while (true)
				{
					int yn = getKey();
					if (yn == 'y' || yn == 'Y')
					{
						if (Lv < itList[yp]->Level())
						{
							gotoxy(90, 15); cout << "������������������������������������";
							gotoxy(90, 16); cout << "�������� ���ڶ� ������ �� �����ϴ٦�";
							gotoxy(90, 17); cout << "������������������������������������";
							_sleep(300);
							gotoxy(90, 15); cout << "                                           ";
							gotoxy(90, 16); cout << "                                           ";
							gotoxy(90, 17); cout << "                                           ";
						}
						else
						{
							armor = (Armor *)itList[yp];
							armor_num = yp;
							gotoxy(90, 15); cout << "                                           ";
							gotoxy(90, 16); cout << "                                           ";
							gotoxy(90, 17); cout << "                                           ";
						}						
						break;
					}
					else if (yn == 'n' || yn == 'N')
					{
						break;
					}
				}
			}
			/*else
				//����*/
				break;
		
		case 'b': case 'B':
			off++;
		default:
			break;
		}
	}
	//���⿡ �޴��� ���ư��°� �־�� �մϴ�.
}

void Player::setWeapon()
{
	weapon = (Weapon*)itList[weapon_num];
}

void Player::setArmor()
{
	armor = (Armor *)itList[armor_num];
}

void Player::equipped()
{
	int x=92, y=3;
	gotoxy(x, y); cout << "����������������������������������������";
	gotoxy(x, y + 1); cout << "��                                    ��";
	gotoxy(x, y + 2); cout << "�� Weapon                             ��";
	gotoxy(x, y + 3); cout << "��                                    ��";
	gotoxy(x, y + 4); cout << "��                                    ��";
	gotoxy(x, y + 5); cout << "��                                    ��";
	gotoxy(x, y + 6); cout << "��                                    ��";
	gotoxy(x, y + 7); cout << "�� Armor                              ��";
	gotoxy(x, y + 8); cout << "��                                    ��";
	gotoxy(x, y + 9); cout << "��                                    ��";
	gotoxy(x, y + 10); cout << "��                                    ��";
	gotoxy(x, y + 11); cout << "��                                    ��";
	gotoxy(x, y + 12); cout << "��                                    ��";
	gotoxy(x, y + 13); cout << "��                                    ��";
	gotoxy(x, y + 14); cout << "����������������������������������������";
	if (weapon==NULL)
	{
		gotoxy(x + 2, y + 4);
		cout << "�������� ���Ⱑ �������� �ʽ��ϴ�";
	}
	else if (weapon->Level() == MIDDLE)
	{
		gotoxy(x + 5, y + 4);
		cout << "�ظ�";
		gotoxy(x + 7, y + 5);
		cout << "���ݷ�: 10";
	}
	else if (weapon->Level() == HIGH)
	{
		gotoxy(x + 5, y + 4);
		cout << "������";
		gotoxy(x + 7, y + 5);
		cout << "���ݷ�: 20";
	}
	else
	{
		gotoxy(x + 5, y + 4);
		cout << "�������� ���Ⱑ �������� �ʽ��ϴ�";
	}
	if (armor==NULL)
	{
		gotoxy(x + 2, y + 9);
		cout << "�������� ���� �������� �ʽ��ϴ�";
	}
	else if (armor->Level() == MIDDLE)
	{
		gotoxy(x + 5, y + 9);
		cout << "���װ���";
		gotoxy(x + 7, y + 10);
		cout << "����: 5";
	}
	else if (armor->Level() == HIGH)
	{
		gotoxy(x + 5, y + 9);
		cout << "��ź��";
		gotoxy(x + 7, y + 10);
		cout << "����: 10";
	}
	else
	{
		gotoxy(x + 5, y + 9);
		cout << "�������� ���Ⱑ �������� �ʽ��ϴ�.";
	}
	char ch;
	while (true)
	{
		ch = getKey();
		if (ch == 'b' || ch == 'B')
			break;
	}
	gotoxy(x, y); cout << "                                              ";
	gotoxy(x, y + 1); cout << "                                              ";
	gotoxy(x, y + 2); cout << "                                              ";
	gotoxy(x, y + 3); cout << "                                              ";
	gotoxy(x, y + 4); cout << "                                              ";
	gotoxy(x, y + 5); cout << "                                              ";
	gotoxy(x, y + 6); cout << "                                              ";
	gotoxy(x, y + 7); cout << "                                              ";
	gotoxy(x, y + 8); cout << "                                              ";
	gotoxy(x, y + 9); cout << "                                              ";
	gotoxy(x, y + 10); cout << "                                              ";
	gotoxy(x, y + 11); cout << "                                              ";
	gotoxy(x, y + 12); cout << "                                              ";
	gotoxy(x, y + 13); cout << "                                              ";
	gotoxy(x, y + 14); cout << "                                              ";
}
void Player::view_skills(){
	int x=92, y=3 , i=0;
	gotoxy(x, y); cout << "��������������������������������";
	gotoxy(x, y + 1); cout << "��                            ��";
	gotoxy(x, y + 2); cout << "��                            ��";
	gotoxy(x, y + 3); cout << "��                            ��";
	gotoxy(x, y + 4); cout << "��                            ��";
	gotoxy(x, y + 5); cout << "��                            ��";
	gotoxy(x, y + 6); cout << "��                            ��";
	gotoxy(x, y + 7); cout << "��                            ��";
	gotoxy(x, y + 8); cout << "��                            ��";
	gotoxy(x, y + 9); cout << "��                            ��";
	gotoxy(x, y + 10); cout << "��                            ��";
	gotoxy(x, y + 11); cout << "��                            ��";
	gotoxy(x, y + 12); cout << "��                            ��";
	gotoxy(x, y + 13); cout << "��                            ��";
	gotoxy(x, y + 14); cout << "��                            ��";
	gotoxy(x, y + 15); cout << "��                            ��";
	gotoxy(x, y + 16); cout << "��                            ��";
	gotoxy(x, y + 17); cout << "��                            ��";
	gotoxy(x, y + 18); cout << "��                            ��";
	gotoxy(x, y + 19); cout << "��                            ��";
	gotoxy(x, y + 20); cout << "��                            ��";
	gotoxy(x, y + 21); cout << "��                            ��";
	gotoxy(x, y + 22); cout << "��                            ��";
	gotoxy(x, y + 23); cout << "��������������������������������";
	if (sk_list[0] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "��Ÿ Lv1       �Ҹ�ap:  10";
		gotoxy(x + 6, y + 2 + i);
		cout << "������: 100 ~ 120";
		i += 2;
	}
	if (sk_list[1] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "��Ÿ Lv2       �Ҹ�ap:  20";
		gotoxy(x + 6, y + 2 + i);
		cout << "������: 200 ~ 240";
		i += 2;
	}if (sk_list[2] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "��Ÿ Lv3       �Ҹ�ap:  30";
		gotoxy(x + 6, y + 2 + i);
		cout << "������: 300 ~ 360";
		i += 2;
	}if (sk_list[3] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "����ġ�� Lv1   �Ҹ�ap:  10";
		gotoxy(x + 6, y + 2 + i);
		cout << "������: �Ϲݰ��ݷ� X 1.5";
		i += 2;
	}if (sk_list[4] != 0)
	{
		gotoxy(x + 6, y + 1 + i);
		cout << "����ġ�� Lv2   �Ҹ�ap:  50";
		gotoxy(x + 6, y + 2 + i);
		cout << "������: �Ϲݰ��ݷ� X 1.5";
		i += 2;
	}if (sk_list[5] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "����ġ�� Lv3   �Ҹ�ap: 120";
		gotoxy(x + 6, y + 2 + i);
		cout << "������: �Ϲݰ��ݷ� X 1.5";
		i += 2;
	}if (sk_list[6] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "ȸ�� Lv1       �Ҹ�ap:  15";
		gotoxy(x + 6, y + 2 + i);
		cout << "ȸ����: 30 ";
		i += 2;
	}if (sk_list[7] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "ȸ�� Lv2       �Ҹ�ap:  30";
		gotoxy(x + 6, y + 2 + i);
		cout << "ȸ����: 60";
		i += 2;
	}if (sk_list[8] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "ȸ�� Lv3       �Ҹ�ap:  45";
		gotoxy(x + 6, y + 2 + i);
		cout << "ȸ����: 90";
		i += 2;
	}if (sk_list[9] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "����           �Ҹ�ap: ??";
		gotoxy(x + 6, y + 2 + i);
		cout << "������: ??? ";
		i += 2;
	}
	char ch;
	while (true)
	{
		ch = getKey();
		if (ch == 'b' || ch == 'B')
			break;
	}
	gotoxy(x, y + 23); cout << "                                           ";
}