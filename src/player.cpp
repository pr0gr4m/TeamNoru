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
	// 로드용 디폴트 생성자
}

Player::Player(const char *n)
{
	strcpy(name, n);
	initializig();
	Sethp();
	Setap();
}

void Player::initializig(){
	str = 3;
	luck = 1;
	dex = 3;
	health = 3;
	Lv = 1;
	exp = 30;
	sp = 0;
	weapon = NULL;
	armor = NULL;
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
	int dmg = pattack()+(weapon->Amount());
	if (critical())
		return dmg * 2;
	else
		return dmg;
}

int Player::beatenDamage(int dmg){
	int defensivePower = pdefense()+ (armor->Amount());
	int calDmg = dmg - defensivePower;
	if (nHp <= calDmg)
		nHp = 0;
	else
		nHp -= calDmg;
	return nHp;
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

void Player::statuschange(){//gotoxy넣고 좌표조정부탁드립니다.
	int nstr = 0, ndex = 0, nhealth = 0, nluck = 0, xp = 0, yp = 0, off = 0;
	int x = 92, y = 3;
	while (off == 0)
	{
		gotoxy(x, y);		cout << "                              ";
		gotoxy(x, y);		cout << "┌─────────────┐";
		gotoxy(x, y + 1);	cout << "│STATUS CHANG              │";
		gotoxy(x, y + 2);	cout << "│Strength : " << setw(3) << setfill(' ') << str << "   + -   " << nstr << "  │";
		gotoxy(x, y + 3);	cout << "│Dex      : " << setw(3) << setfill(' ') << dex << "   + -   " << ndex << "  │";
		gotoxy(x, y + 4);	cout << "│Health   : " << setw(3) << setfill(' ') << health << "   + -   " << nhealth << "  │";
		gotoxy(x, y + 5);	cout << "│Luck     : " << setw(3) << setfill(' ') << luck << "   + -   " << nluck << "  │";
		gotoxy(x, y + 6);	cout << "│남은 스테이터스포인트: " << setw(2) << setfill(' ') << sp << " │";
		gotoxy(x, y + 7);	cout << "└─────────────┘";

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
						gotoxy(90, 15); cout << "┌────────────────┐";
						gotoxy(90, 16); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(90, 17); cout << "└────────────────┘";
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
						gotoxy(90, 15); cout << "┌────────────────┐";
						gotoxy(90, 16); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(90, 17); cout << "└────────────────┘";
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
						gotoxy(90, 15); cout << "┌────────────────┐";
						gotoxy(90, 16); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(90, 17); cout << "└────────────────┘";
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
						gotoxy(90, 15); cout << "┌────────────────┐";
						gotoxy(90, 16); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(90, 17); cout << "└────────────────┘";
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
				xp = 1;		// 여기 왜 == 였음?//멘탈이 나간상태라 그랬나봅니다
			break;
		case 10: case 13:
			if (sp != 0)
			{
				gotoxy(90, 15); cout << "┌────────────────┐";
				gotoxy(90, 16); cout << "│남은 스테이터스포인트가 있습니다│";
				gotoxy(90, 17); cout << "│정말로 종료하시겠습니까?  (Y/N) │";
				gotoxy(90, 18); cout << "└────────────────┘";
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
						gotoxy(90, 15); cout << "┌─────────┐";
						gotoxy(90, 16); cout << "│종료를 취소합니다 │";
						gotoxy(90, 17); cout << "└─────────┘";
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
			// 그 외
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

void Player::Lvup(){//좌표조정필요
	gotoxy(10, 30); cout << "┌──────────┐";
	gotoxy(10, 31); cout << "│     Level Up! ▼   │";
	gotoxy(10, 32); cout << "└──────────┘";
	ClearReadBuff();
	getKey();//아무거나 넣으면 되게 해놓은거에요 바꾸셔도 됩니다.
	Lv++;
	nexp -= exp;
	exp *= 2;
	sp += 5;
	// 스탯은 메뉴에서 찍음
}
void Player::view_itemlist(){
	int x = 92, y = 3;
	int i=1;
	gotoxy(x, y); cout << "┌──────────────┐";
	if (item_list[0] != 0)
	{
		gotoxy(x, y + i); 
		cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[0] << " X " << setw(2) << setfill(' ') << item_list[0] << "│";
		i++;
	}
	if (item_list[1] != 0)
	{
		gotoxy(x, y +i);
		cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[1] << " X " << setw(2) << setfill(' ') << item_list[1] << "│";
		i++;
	}
	if (item_list[2] != 0)
	{
		gotoxy(x, y + i);
		cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[2] << " X " << setw(2) << setfill(' ') << item_list[2] << "│";
		i++;
	}
	if (item_list[3] != 0)
	{
		gotoxy(x, y +  i);
		cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[3] << " X " << setw(2) << setfill(' ') << item_list[3] << "│";
		i++;
	}
	if (item_list[4] != 0)
	{
		gotoxy(x, y +  i);
		cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[4] << " X " << setw(2) << setfill(' ') << item_list[4] << "│";
		i++;
	}
	if (item_list[5] != 0)
	{
		gotoxy(x, y  + i);
		cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[5] << " X " << setw(2) << setfill(' ') << item_list[5] << "│";
		i++;
	}
	if (item_list[6] != 0)
	{
		gotoxy(x, y  + i);
		cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[6] << " X " << setw(2) << setfill(' ') << item_list[6] << "│";
		i++;
	}
	gotoxy(x, y  + i);
	cout << "└──────────────┘";
}
void Player::item_mount(){
	int yp = 0, i, j = 0, off=0;
	int x = 94, y = 4;
	int ion[7];
	for (i = 0; i < ITEM_NUM; i++)
	{
		if (item_list[i] != 0)
		{
			ion[j] = i;
			j++;
		}
	}
	while (off==0)
	{
		view_itemlist();
		if (yp == 0)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y);
			cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[ion[0]] << " X " << setw(2) << setfill(' ') << item_list[ion[0]] << "│";
			setColor();
		}
		else if (yp == 1)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y);
			cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[ion[1]] << " X " << setw(2) << setfill(' ') << item_list[ion[1]] << "│";
			setColor();
		}
		else if (yp == 2)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y);
			cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[ion[2]] << " X " << setw(2) << setfill(' ') << item_list[ion[2]] << "│";
			setColor();
		}
		else if (yp == 3)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y);
			cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[ion[3]] << " X " << setw(2) << setfill(' ') << item_list[ion[3]] << "│";
			setColor();
		}
		else if (yp == 4)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y);
			cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[ion[4]] << " X " << setw(2) << setfill(' ') << item_list[ion[4]] << "│";
			setColor();
		}
		else if (yp == 5)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y);
			cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[ion[5]] << " X " << setw(2) << setfill(' ') << item_list[ion[5]] << "│";
			setColor();
		}
		else if (yp == 6)
		{
			setColor(BLACK, LIGHTGRAY);
			gotoxy(x, y);
			cout << "│ " << setiosflags(ios::left) << setw(9) << setfill(' ') << item_name[ion[6]] << " X " << setw(2) << setfill(' ') << item_list[ion[6]] << "│";
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
			if (yp > j)
				yp = j;
			break;
		case 10: case 13:
			if (ion[yp] == 0 || ion[yp] == 1)
				weapon = (Weapon*)itList[yp];
			else if (ion[yp] == 2 || ion[yp] == 3)
				armor = (Armor *)itList[yp];
			/*else
				//포션*/
				break;
		
		case 'b': case 'B':
			off++;
		default:
			break;
		}
	}
	//여기에 메뉴로 돌아가는걸 넣어야 합니다.
}