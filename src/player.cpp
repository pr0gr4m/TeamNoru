#include "player.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "lib.h"
#include <iomanip>
using std::cout;
using std::cin;
using std::setfill;
using std::setw;
using std::endl;
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
	int dmg = pattack();//+itemattack;
	if (critical())
		return dmg * 2;
	else
		return dmg;
}

int Player::beatenDamage(int dmg){
	int defensivePower = pdefense();//+itemdefense;
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
				xp = 1;		// 여기 왜 == 였음?
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