/*
 * だ橾 : player.cpp
 * 頂辨 : Ы溯檜橫 贗楚蝶 掘⑷
 * 薯濛 : 梯團輿
 */

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
	// 煎萄辨 蛤ィお 儅撩濠
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
	nAP += ap;
	if (nAP >= AP)
		nAP = AP;
	return nAP;
}

void Player::Getexp(int pexp){
	nexp += pexp;
	if (nexp >= exp)
		Lvup();
}

void Player::statuschange(){//gotoxy厥堅 謝ル褻薑睡饕萄董棲棻.
	int nstr = 0, ndex = 0, nhealth = 0, nluck = 0, xp = 0, yp = 0, off = 0;
	int x = 92, y = 3;
	while (off == 0)
	{
		gotoxy(x, y);		cout << "                              ";
		gotoxy(x, y);		cout << "忙式式式式式式式式式式式式式忖";
		gotoxy(x, y + 1);	cout << "弛STATUS CHANG              弛";
		gotoxy(x, y + 2);	cout << "弛Strength : " << setw(3) << setfill(' ') << str << "   + -" << setw(4) << nstr << setw(3) << "  弛";
		gotoxy(x, y + 3);	cout << "弛Dex      : " << setw(3) << setfill(' ') << dex << "   + -" << setw(4)<< ndex << setw(3) << "  弛";
		gotoxy(x, y + 4);	cout << "弛Health   : " << setw(3) << setfill(' ') << health << "   + -" << setw(4) << nhealth << setw(3) << "  弛";
		gotoxy(x, y + 5);	cout << "弛Luck     : " << setw(3) << setfill(' ') << luck << "   + -" << setw(4) << nluck << setw(3) << "  弛";
		gotoxy(x, y + 6);	cout << "弛陴擎 蝶纔檜攪蝶ん檣お: " << setw(2) << setfill(' ') << sp << " 弛";
		gotoxy(x, y + 7);	cout << "戌式式式式式式式式式式式式式戎";

		if (xp ==0 && yp == 0){
			gotoxy(x + 2, y + 2);
			setColor(BLACK, LIGHTGRAY);
			cout << "Strength : " << setw(3) << setfill(' ') << str << "   + -" << setw(4) << nstr;
			setColor();
		}
		else if (xp == 0 && yp == 1){
			gotoxy(x + 2, y + 3);
			setColor(BLACK, LIGHTGRAY);
			cout << "Dex      : " << setw(3) << setfill(' ') << dex << "   + -" << setw(4) << ndex;
			setColor();
		}
		else if (xp == 0 && yp == 2){
			gotoxy(x + 2, y + 4);
			setColor(BLACK, LIGHTGRAY);
			cout << "Health   : " << setw(3) << setfill(' ') << health << "   + -" << setw(4) << nhealth;
			setColor();
		}
		else if (xp == 0 && yp == 3){
			gotoxy(x + 2, y + 5);
			setColor(BLACK, LIGHTGRAY);
			cout << "Luck     : " << setw(3) << setfill(' ') << luck << "   + -" << setw(4) << nluck;
			setColor();
		}
		else if (xp == 1 && yp == 0){
			gotoxy(x + 18, y + 2);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -" << setw(4) << nstr;
			setColor();
		}
		else if (xp == 1 && yp == 1){
			gotoxy(x + 18, y + 3);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -" << setw(4) << ndex;
			setColor();
		}
		else if (xp == 1 && yp == 2){
			gotoxy(x + 18, y + 4);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -" << setw(4) << nhealth;
			setColor();
		}
		else if (xp == 1 && yp == 3){
			gotoxy(x + 18, y + 5);
			setColor(BLACK, LIGHTGRAY);
			cout << " + -" << setw(4) << nluck;
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
						gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
						gotoxy(90, 16); cout << "弛陴擎 蝶纔檜攪蝶ん檣お陛 橈蝗棲棻弛";
						gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式戎";
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
						gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
						gotoxy(90, 16); cout << "弛陴擎 蝶纔檜攪蝶ん檣お陛 橈蝗棲棻弛";
						gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式戎";
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
						gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
						gotoxy(90, 16); cout << "弛陴擎 蝶纔檜攪蝶ん檣お陛 橈蝗棲棻弛";
						gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式戎";
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
						gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
						gotoxy(90, 16); cout << "弛陴擎 蝶纔檜攪蝶ん檣お陛 橈蝗棲棻弛";
						gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式戎";
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
				xp = 1;		// 罹晦 謁 == 艘擠?//詮驍檜 釭除鼻鷓塭 斜楊釭瑣棲棻
			break;
		case 10: case 13:
			if (sp != 0)
			{
				gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
				gotoxy(90, 16); cout << "弛陴擎 蝶纔檜攪蝶ん檣お陛 氈蝗棲棻弛";
				gotoxy(90, 17); cout << "弛薑蜓煎 謙猿ж衛啊蝗棲梱?  (Y/N) 弛";
				gotoxy(90, 18); cout << "戌式式式式式式式式式式式式式式式式戎";
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
						gotoxy(90, 15); cout << "忙式式式式式式式式式忖";
						gotoxy(90, 16); cout << "弛謙猿蒂 鏃模м棲棻 弛";
						gotoxy(90, 17); cout << "戌式式式式式式式式式戎";
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
			// 斜 諼
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

void Player::Lvup(){//謝ル褻薑в蹂
	gotoxy(10, 30); cout << "忙式式式式式式式式式式忖";
	gotoxy(10, 31); cout << "弛     Level Up! ∪   弛";
	gotoxy(10, 32); cout << "戌式式式式式式式式式式戎";
	ClearReadBuff();
	getKey();//嬴鼠剪釭 厥戲賊 腎啪 п場擎剪縑蹂 夥紱敷紫 腌棲棻.
	Lv++;
	nexp -= exp;
	exp *= 2;
	sp += 5;
	HealHP(1000);
	HealAP(1000);
	// 蝶囌擎 詭景縑憮 鎰擠
}
void Player::view_itemlist(){
	int x = 92, y = 3;
	int i=1;
	gotoxy(x, y);cout << "忙式式式式式式式式式式式式式式忖";
	gotoxy(x, y+1); cout << "弛                            弛";
	gotoxy(x, y+2); cout << "弛                            弛";
	gotoxy(x, y+3); cout << "弛                            弛";
	gotoxy(x, y+4); cout << "弛                            弛";
	gotoxy(x, y+5); cout << "弛                            弛";
	gotoxy(x, y+6); cout << "弛                            弛";
	gotoxy(x, y+7); cout << "弛                            弛";
	gotoxy(x, y+8); cout << "弛                            弛";
	gotoxy(x, y+9); cout << "弛                            弛";
	gotoxy(x, y + 10); cout << "弛                            弛";
	gotoxy(x, y + 11); cout << "弛                            弛";
	gotoxy(x, y + 12); cout << "弛                            弛";
	gotoxy(x, y + 13); cout << "弛                            弛";
	gotoxy(x, y + 13); cout << "弛                            弛";
	gotoxy(x, y + 14); cout << "弛                            弛";
	gotoxy(x, y + 15); cout << "弛                            弛";
	gotoxy(x, y+16); cout << "戌式式式式式式式式式式式式式式戎";
	if (item_list[0] != 0)
	{
		gotoxy(x+3, y +1 +i); 
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[0] << " X " << setw(5) << setfill(' ') << item_list[0] ;
		i+=2;
	}
	else
	{
		gotoxy(x + 3, y + 1 + i);
		cout << setiosflags(ios::left) << "-";
		i += 2;
	}
	if (item_list[1] != 0)
	{
		gotoxy(x+3, y+1 +i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[1] << " X " << setw(5) << setfill(' ') << item_list[1] ;
		i+=2;
	}
	else
	{
		gotoxy(x + 3, y + 1 + i);
		cout << setiosflags(ios::left) << "-";
		i += 2;
	}
	if (item_list[2] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[2] << " X " << setw(5) << setfill(' ') << item_list[2] ;
		i+=2;
	}
	else
	{
		gotoxy(x + 3, y + 1 + i);
		cout << setiosflags(ios::left) << "-";
		i += 2;
	}
	if (item_list[3] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[3] << " X " << setw(5) << setfill(' ') << item_list[3] ;
		i+=2;
	}
	else
	{
		gotoxy(x + 3, y + 1 + i);
		cout << setiosflags(ios::left) << "-";
		i += 2;
	}
	if (item_list[4] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[4] << " X " << setw(5) << setfill(' ') << item_list[4] ;
		i+=2;
	}
	else
	{
		gotoxy(x + 3, y + 1 + i);
		cout << setiosflags(ios::left) << "-";
		i += 2;
	}
	if (item_list[5] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[5] << " X " << setw(5) << setfill(' ') << item_list[5] ;
		i+=2;
	}
	else
	{
		gotoxy(x + 3, y + 1 + i);
		cout << setiosflags(ios::left) << "-";
		i += 2;
	}
	if (item_list[6] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout <<  setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[6] << " X " << setw(5) << setfill(' ') << item_list[6] ;
		i+=2;
	}
	else
	{
		gotoxy(x + 3, y + 1 + i);
		cout << setiosflags(ios::left) << "-";
		i += 2;
	}
	
}
void Player::item_mount(){
	int yp = 0, i, j = 0, off=0;
	int x = 95, y = 4;
	for (i = 0; i < ITEM_NUM; i++)
	{
		j++;
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
			if (item_list[0]) {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 1);
				cout << setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[0] << " X " << setw(5) << setfill(' ') << item_list[0];
				setColor();
			}
			else {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 1);
				cout << setiosflags(ios::left) << setw(19) << setfill(' ') << "-";
				setColor();
			}
		}
		else if (yp == 1)
		{
			if (item_list[1]) {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 2 + 1);
				cout << setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[1] << " X " << setw(5) << setfill(' ') << item_list[1];
				setColor();
			}
			else {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 2 + 1);
				cout << setiosflags(ios::left) << setw(19) << setfill(' ') << "-";
				setColor();
			}
		}
		else if (yp == 2)
		{
			if (item_list[2]) {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 4 + 1);
				cout << setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[2] << " X " << setw(5) << setfill(' ') << item_list[2];
				setColor();
			}
			else {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 4 + 1);
				cout << setiosflags(ios::left) << setw(19) << setfill(' ') << "-";
				setColor();
			}
		}
		else if (yp == 3)
		{
			if (item_list[3]) {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 6 + 1);
				cout << setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[3] << " X " << setw(5) << setfill(' ') << item_list[3];
				setColor();
			}
			else {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 6 + 1);
				cout << setiosflags(ios::left) << setw(19) << setfill(' ') << "-";
				setColor();
			}
		}
		else if (yp == 4)
		{
			if (item_list[4]) {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 8 + 1);
				cout << setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[4] << " X " << setw(5) << setfill(' ') << item_list[4];
				setColor();
			}
			else {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 8 + 1);
				cout << setiosflags(ios::left) << setw(19) << setfill(' ') << "-";
				setColor();
			}
		}
		else if (yp == 5)
		{
			if (item_list[5]) {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 10 + 1);
				cout << setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[5] << " X " << setw(5) << setfill(' ') << item_list[5];
				setColor();
			}
			else {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 10 + 1);
				cout << setiosflags(ios::left) << setw(19) << setfill(' ') << "-";
				setColor();
			}
		}
		else if (yp == 6)
		{
			if (item_list[6]) {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 12 + 1);
				cout << setiosflags(ios::left) << setw(11) << setfill(' ') << item_name[6] << " X " << setw(5) << setfill(' ') << item_list[6];
				setColor();
			}
			else {
				setColor(BLACK, LIGHTGRAY);
				gotoxy(x, y + 12 + 1);
				cout << setiosflags(ios::left) << setw(19) << setfill(' ') << "-";
				setColor();
			}
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
			if (yp > 6)
				yp = j-1;
			break;
		case 10: case 13:
			if (yp == 0 || yp == 1)
			{
				gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
				gotoxy(90, 16); cout << "弛鼠晦蒂 濰雜ж衛啊 蝗棲梱? (Y/N) 弛";
				gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式戎";
				while (true)
				{
					int yn = getKey();
					if (yn == 'y' || yn == 'Y')
					{
						if (Lv < itList[yp]->Level())
						{
							gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
							gotoxy(90, 16); cout << "弛溯漣檜 賅濠塭 濰雜й 熱 橈蝗棲棻弛";
							gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式戎";
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
			else if (yp == 2 || yp == 3)
			{
				gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式式忖";
				gotoxy(90, 16); cout << "弛寞橫掘蒂 濰雜ж衛啊 蝗棲梱? (Y/N) 弛";
				gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式式戎";
				while (true)
				{
					int yn = getKey();
					if (yn == 'y' || yn == 'Y')
					{
						if (Lv < itList[yp]->Level())
						{
							gotoxy(90, 15); cout << "忙式式式式式式式式式式式式式式式式忖";
							gotoxy(90, 16); cout << "弛溯漣檜 賅濠塭 濰雜й 熱 橈蝗棲棻弛";
							gotoxy(90, 17); cout << "戌式式式式式式式式式式式式式式式式戎";
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
			else if (yp == 4 || yp == 5)
			{
				p.HealAP(itList[yp]->Amount());
				(p.item_list[yp])--;
			}
			else if (yp == 6)
			{
				p.HealAP(itList[yp]->Amount());
				(p.item_list[yp])--;
			}
			break;
		
		case 'b': case 'B':
			off++;
		default:
			break;
		}
	}
	//罹晦縑 詭景煎 給嬴陛朝勘 厥橫撿 м棲棻.
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
	gotoxy(x, y); cout << "忙式式式式式式式式式式式式式式式式式式忖";
	gotoxy(x, y + 1); cout << "弛                                    弛";
	gotoxy(x, y + 2); cout << "弛 Weapon                             弛";
	gotoxy(x, y + 3); cout << "弛                                    弛";
	gotoxy(x, y + 4); cout << "弛                                    弛";
	gotoxy(x, y + 5); cout << "弛                                    弛";
	gotoxy(x, y + 6); cout << "弛                                    弛";
	gotoxy(x, y + 7); cout << "弛 Armor                              弛";
	gotoxy(x, y + 8); cout << "弛                                    弛";
	gotoxy(x, y + 9); cout << "弛                                    弛";
	gotoxy(x, y + 10); cout << "弛                                    弛";
	gotoxy(x, y + 11); cout << "弛                                    弛";
	gotoxy(x, y + 12); cout << "弛                                    弛";
	gotoxy(x, y + 13); cout << "弛                                    弛";
	gotoxy(x, y + 14); cout << "戌式式式式式式式式式式式式式式式式式式戎";
	if (weapon==NULL)
	{
		gotoxy(x + 2, y + 4);
		cout << "雜辨醞檣 鼠晦陛 襄營ж雖 彊蝗棲棻";
	}
	else if (weapon->Level() == MIDDLE)
	{
		gotoxy(x + 5, y + 4);
		cout << "п該";
		gotoxy(x + 7, y + 5);
		cout << "奢問溘: 10";
	}
	else if (weapon->Level() == HIGH)
	{
		gotoxy(x + 5, y + 4);
		cout << "瞪晦體";
		gotoxy(x + 7, y + 5);
		cout << "奢問溘: 20";
	}
	else
	{
		gotoxy(x + 5, y + 4);
		cout << "雜辨醞檣 鼠晦陛 襄營ж雖 彊蝗棲棻";
	}
	if (armor==NULL)
	{
		gotoxy(x + 2, y + 9);
		cout << "雜辨醞檣 寞橫掘陛 襄營ж雖 彊蝗棲棻";
	}
	else if (armor->Level() == MIDDLE)
	{
		gotoxy(x + 5, y + 9);
		cout << "陛避骨褡";
		gotoxy(x + 7, y + 10);
		cout << "寞橫溘: 5";
	}
	else if (armor->Level() == HIGH)
	{
		gotoxy(x + 5, y + 9);
		cout << "寞驕犒";
		gotoxy(x + 7, y + 10);
		cout << "寞橫溘: 10";
	}
	else
	{
		gotoxy(x + 5, y + 9);
		cout << "雜辨醞檣 鼠晦陛 襄營ж雖 彊蝗棲棻.";
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
	gotoxy(x, y); cout << "忙式式式式式式式式式式式式式式忖";
	gotoxy(x, y + 1); cout << "弛                            弛";
	gotoxy(x, y + 2); cout << "弛                            弛";
	gotoxy(x, y + 3); cout << "弛                            弛";
	gotoxy(x, y + 4); cout << "弛                            弛";
	gotoxy(x, y + 5); cout << "弛                            弛";
	gotoxy(x, y + 6); cout << "弛                            弛";
	gotoxy(x, y + 7); cout << "弛                            弛";
	gotoxy(x, y + 8); cout << "弛                            弛";
	gotoxy(x, y + 9); cout << "弛                            弛";
	gotoxy(x, y + 10); cout << "弛                            弛";
	gotoxy(x, y + 11); cout << "弛                            弛";
	gotoxy(x, y + 12); cout << "弛                            弛";
	gotoxy(x, y + 13); cout << "弛                            弛";
	gotoxy(x, y + 14); cout << "弛                            弛";
	gotoxy(x, y + 15); cout << "弛                            弛";
	gotoxy(x, y + 16); cout << "弛                            弛";
	gotoxy(x, y + 17); cout << "弛                            弛";
	gotoxy(x, y + 18); cout << "弛                            弛";
	gotoxy(x, y + 19); cout << "弛                            弛";
	gotoxy(x, y + 20); cout << "弛                            弛";
	gotoxy(x, y + 21); cout << "弛                            弛";
	gotoxy(x, y + 22); cout << "弛                            弛";
	gotoxy(x, y + 23); cout << "戌式式式式式式式式式式式式式式戎";
	if (sk_list[0] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "鬼顫 Lv1       模賅ap:  10";
		gotoxy(x + 6, y + 2 + i);
		cout << "等嘐雖: 100 ~ 120";
		i += 2;
	}
	if (sk_list[1] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "鬼顫 Lv2       模賅ap:  20";
		gotoxy(x + 6, y + 2 + i);
		cout << "等嘐雖: 200 ~ 240";
		i += 2;
	}if (sk_list[2] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "鬼顫 Lv3       模賅ap:  30";
		gotoxy(x + 6, y + 2 + i);
		cout << "等嘐雖: 300 ~ 360";
		i += 2;
	}if (sk_list[3] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "路嬴纂晦 Lv1   模賅ap:  10";
		gotoxy(x + 6, y + 2 + i);
		cout << "等嘐雖: 橾奩奢問溘 X 1.5";
		i += 2;
	}if (sk_list[4] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "路嬴纂晦 Lv2   模賅ap:  50";
		gotoxy(x + 6, y + 2 + i);
		cout << "等嘐雖: 橾奩奢問溘 X 1.5";
		i += 2;
	}if (sk_list[5] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "路嬴纂晦 Lv3   模賅ap: 120";
		gotoxy(x + 6, y + 2 + i);
		cout << "等嘐雖: 橾奩奢問溘 X 1.5";
		i += 2;
	}if (sk_list[6] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "�蛹� Lv1       模賅ap:  15";
		gotoxy(x + 6, y + 2 + i);
		cout << "�蛹僩�: 30 ";
		i += 2;
	}if (sk_list[7] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "�蛹� Lv2       模賅ap:  30";
		gotoxy(x + 6, y + 2 + i);
		cout << "�蛹僩�: 60";
		i += 2;
	}if (sk_list[8] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "�蛹� Lv3       模賅ap:  45";
		gotoxy(x + 6, y + 2 + i);
		cout << "�蛹僩�: 90";
		i += 2;
	}if (sk_list[9] != 0)
	{
		gotoxy(x + 3, y + 1 + i);
		cout << "健綰           模賅ap: ??";
		gotoxy(x + 6, y + 2 + i);
		cout << "等嘐雖: ??? ";
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