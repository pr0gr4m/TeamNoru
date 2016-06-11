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
using std::endl;
player::player()
{
	while (true)
	{
		cout << "당신의 이름은 무었입니까? ";
		cin >> buf;
		if (strlen(buf) >= 20)
			cout << "이름이 너무 깁니다 영어1~19자, 한글과 특수문자는 1~9자 이내로 이름지어주세요.";
		else
			break;
	}
	initializig();
	Sethp();
	Setap();
}


player::~player()
{
}
void player::initializig(){
	str = 3;
	luck = 1;
	dex = 3;
	health = 3;
	Lv = 1;
	exp = 30;
	sp = 0;
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
void player::Sethp(){
	float hp = health * 4 + str*1.5;
	HealHP((int)hp-HP);
	HP = (int)hp;
}
void player::Setap(){
	float ap = str*1.5 + dex * 2;
	HealAP((int)ap - AP);
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
int player::attackDamage()
{
	int dmg = pattack();//+itemattack;
	if (critical())
		return dmg * 2;
	else
		return dmg;
}
int player::beatenDamage(int dmg){
	int defensivePower = pdefense();//+itemdefense;
	int calDmg = dmg - defensivePower;
	if (nHp <= calDmg)
		nHp = 0;
	else
		nHp -= calDmg;
	return nHp;
}
int player::HealHP(int hp){
	if (hp > HP - nHp)
		nHp = HP;
	else
		nHp += hp;
	return nHp;
}
int player::HealAP(int ap){
	if (ap > AP - nAP)
		nAP = AP;
	else
		nAP += ap;
	return nAP;
}
void player::Getexp(int pexp){
	nexp += pexp;
	if (nexp >= exp)
		Lvup();
}

void player::statuschange(){//gotoxy넣고 좌표조정부탁드립니다.
	int nstr = 0, ndex = 0, nhealth = 0, nluck = 0, xp = 0, yp = 0, off = 0;
	while (off == 0)
	{
		gotoxy(x, y);	cout << "┌────────────────────┐";
		gotoxy(x, y + 1);	cout << "│STATUS CHANGE│";
		gotoxy(x, y + 2);	cout << "│Strength : " << setw(3) << setfill(' ') << str << " + - " << nstr << "│";
		gotoxy(x, y + 3);	cout << "│Dex      : " << setw(3) << setfill(' ') << dex << " + - " << ndex << "│";
		gotoxy(x, y + 4);	cout << "│Health   : " << setw(3) << setfill(' ') << health << " + - " << nhealth << "│";
		gotoxy(x, y + 5);	cout << "│Luck     : " << setw(3) << setfill(' ') << luck << " + - " << nluck << "│";
		gotoxy(x, y + 6); cout << "│  남은 스테이터스포인트: " << setw(2) << setfill(' ') << sp << "│";
		gotoxy(x, y + 7); cout << "└────────────────────┘";

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
						gotoxy(); cout << "┌────────────────┐";
						gotoxy(); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(); cout << "└────────────────┘";
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
						gotoxy(); cout << "┌────────────────┐";
						gotoxy(); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(); cout << "└────────────────┘";
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
						gotoxy(); cout << "┌────────────────┐";
						gotoxy(); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(); cout << "└────────────────┘";
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
						gotoxy(); cout << "┌────────────────┐";
						gotoxy(); cout << "│남은 스테이터스포인트가 없습니다│";
						gotoxy(); cout << "└────────────────┘";
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
				gotoxy(); cout << "┌────────────────┐";
				gotoxy(); cout << "│남은 스테이터스포인트가 있습니다│";
				gotoxy(); cout << "│정말로 종료하시겠습니까?  (Y/N) │";
				gotoxy(); cout << "└────────────────┘";
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
						gotoxy(); cout << "┌─────────┐";
						gotoxy(); cout << "│종료를 취소합니다 │";
						gotoxy(); cout << "└─────────┘";
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
				gotoxy(); cout << "┌────────────────┐";
				gotoxy(); cout << "│남은 스테이터스포인트가 있습니다│";
				gotoxy(); cout << "│다음 레벨업까지 스테이터스포인트│";
				gotoxy(); cout << "│분배는 불가능합니다             │";
				gotoxy(); cout << "│정말로 종료하시겠습니까?  (Y/N) │";
				gotoxy(); cout << "└────────────────┘";
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
						gotoxy(); cout << "┌─────────┐";
						gotoxy(); cout << "│종료를 취소합니다 │";
						gotoxy(); cout << "└─────────┘";
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
void player::Lvup(){//좌표조정필요
	gotoxy(); cout << "┌─────────┐";
	gotoxy(); cout << "│     Level Up! ▼ │";
	gotoxy(); cout << "└─────────┘";
	ClearReadBuff();
	getch();//아무거나 넣으면 되게 해놓은거에요 바꾸셔도 됩니다.
	Lv++;
	nexp -= exp;
	exp *= 2;
	sp += 5;
	statuschange();
}