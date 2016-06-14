#include "Battle.h"
#include "player.h"
#include "skill.h"
#include "item.h"
#include <sstream>
#include <stdarg.h>
#include <conio.h>
using namespace std;

extern Skill * skList[10];
extern ITEM * itList[7];

void Battle::_gotoxy()
{
	Boxscreen();
	gotoxy(4, 46);
}

Battle::Battle(Monster& _monster)
	: monster(_monster)
{
	ClearReadBuff();
	BattleSystem();
}

Battle::~Battle()
{
}

void Battle::BattleSystem() {
	while (1) {
	BAT_START:
		int battleget = 0;
		clrscr();
		ClearReadBuff();
		battleget = BattleMenu();
		while (1) {
			bool isCheck = false;
			int damage = 0;
			switch (battleget) {
			case 1:
				damage = p.attackDamage();
				_gotoxy();
				cout << "ÀÌ¾å! ÆòÅ¸!";
				getKey();
				monsterbeaten();
				_gotoxy();
				cout << p.name << "Àº(´Â) " << monster.beatenDamage(damage) << " µ¥¹ÌÁö¸¦ " << monster.name << "¿¡°Ô ÁÖ¾ú´Ù!";
				getKey();
				isCheck = true;
				break;
			case 2:
				isCheck = ShowInventory();
				break;
			case 3:
				isCheck = ShowSkills();
				break;
			case 4:
				if (Run())
					return;
				isCheck = true;
				break;
			default:
				break;
			}
			if (isCheck)
				break;
			else
				goto BAT_START;
		}
		if (monster.isDie()) {
			_gotoxy();
			cout << p.name << "Àº(´Â) " << monster.name << "ÀÇ ÀüÅõ¿¡¼­ ½Â¸®Çß´Ù!";
			getKey();
			p.Getexp(monster.Exp());
			_gotoxy();
			cout << p.name << "Àº(´Â) " << monster.Exp() << "ÀÇ °æÇèÄ¡¸¦ ¾ò¾ú´Ù!";
			getKey();
			return;
		}
		AIBattle();
		if (p.nHp <= 0) {
			_gotoxy();
			cout << p.name << "Àº(´Â) ÆÐ¹èÇß´Ù.....";
			getKey();
			GAMEOVER();
		}
	}
}

bool Battle::ShowInventory() {
	char input = 0;
	int colm = 0;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                                    ¦¢                    ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦¢ »¡ °£  Æ÷ ¼Ç  X  " << p.item_list[4] << "°³: 1¦¢                                    ¦¢    E x i t :  4    ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥H P ¸¦  5 0 ¸¸ Å­  È¸ º¹ ÇÑ ´Ù.     ¦¢                    ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢                                                                  ¦§<Player>¦¡¦¡¦¡¦¡¦¡¦¡¦©" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                                    ¦¢ 000/000    000/000 ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦¢ ÇÏ ¾á  Æ÷ ¼Ç  X  " << p.item_list[5] << "°³: 2¦¢                                    ¦§<Monster> ¦¡¦¡¦¡¦¡¦¡¦©" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥H P ¸¦  1 0 0 ¸¸ Å­  È¸ º¹ ÇÑ ´Ù.   ¦¢ 000/000      000   ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢                                                                  ¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                                    ¦¢                    ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦¢ ÆÄ ¶õ  Æ÷ ¼Ç  X  " << p.item_list[6] << "°³: 3¦¢                                    ¦¢    ¼ý  ÀÚ  ¼± ÅÃ   ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¢  ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥A P ¸¦  3 0 ¸¸ Å­  È¸ º¹ ÇÑ ´Ù.     ¦¢                    ¦¢" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;

	while (1) 
	{
	ITEM_SELECT:
		input = getKey();
		int inp = input - '0';
		if (inp >= 1 && inp <= 4) 
		{
			if (input == '4') {
				return false;
			}
			else 
			{
				//¾ÆÀÌÅÛ »ç¿ë
				if (p.item_list[inp + 3] > 0) {
					_gotoxy();
					cout << p.name << "Àº(´Â) " << item_name[inp + 3] << "À»(¸¦) »ç¿ëÇß´Ù!";
					getKey();
					(p.item_list[inp + 3])--;
					return true;
				}
				else {
					goto ITEM_SELECT;
				}
			}
		}
	}
}

bool Battle::ShowSkills() {
	while (1) {
		gotoxy(20, 10);
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
		gotoxy(20, 11);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(25, 11);
		cout << p.name << "      HP   " << p.nHp << " / " << p.getMaxHp() << "      AP   " << p.nAP << " / " << p.getMaxHp();
		gotoxy(20, 12);
		cout << "¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©";
		gotoxy(20, 13);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 14);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 15);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 16);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 17);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 18);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 19);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 20);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 21);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 22);
		cout << "¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©";
		gotoxy(20, 23);
		cout << "¦¢                                                                                    ¦¢";
		gotoxy(20, 24);
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";
		gotoxy(25, 23);
		cout << "Exit: 0             Get Number: n" << endl;
		int ypos = 13;
		for (int i = 0; i < SKILL_NUM; i++)
		{
			if (p.sk_list[i])	// ½ºÅ³ Á¸Àç ÇÏ¸é
			{
				gotoxy(25, ypos++);
				cout << i + 1 << ". " << skList[i]->name << "  Lv." << skList[i]->Level() << "    AP : " << skList[i]->Cost();
			}
		}

		int input = getKey() - '0';
		if (!input) {
			return false;
		}
		input--;

		if (p.nAP < skList[input]->Cost())
		{	// ap ºÎÁ·
			_gotoxy();
			cout << "AP°¡ ºÎÁ·ÇÕ´Ï´Ù!";
			getKey();
			return false;
		}
		else
		{
			int dmg = skList[input]->Amount();
			_gotoxy();
			cout << p.name << "Àº(´Â) " << skList[input]->name << "À»(¸¦) »ç¿ëÇß´Ù!";
			getKey();
			monsterbeaten();
			int cdmg = monster.beatenDamage(SkillDamage(input));
			p.nAP -= skList[input]->Cost();
			if (input >= 6 && input <= 8)
			{
				_gotoxy();
				cout << p.name << "Àº(´Â) " << dmg << "À»(¸¦) È¸º¹Çß´Ù!";
				getKey();
			}
			else
			{
				_gotoxy();
				cout << monster.name << "Àº(´Â) " << cdmg << "ÀÇ µ¥¹ÌÁö¸¦ ÀÔ¾ú´Ù!";
				getKey();
			}
			return true;
		}
	}
}

void Battle::Boxscreen() {
	clrscr();
	gotoxy(0, 0);
	monster.printASCII();
	gotoxy(0, 42);
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢                                                            ¦¢                                                            ¦¢" << endl;
	cout << "¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©" << endl;
	cout << "¦¢                                                                                                                          ¦¢" << endl;
	cout << "¦¢                                                                                                                          ¦¢" << endl;
	cout << "¦¢                                                                                                                          ¦¢" << endl;
	cout << "¦¢                                                                                                                          ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	gotoxy(3, 43);
	setColor(YELLOW);
	cout << p.name;
	setColor();
	gotoxy(15, 43);
	cout << "HP : " << p.nHp << "/" << p.getMaxHp();
	gotoxy(30, 43);
	cout << "AP : " << p.nAP << "/" << p.getMaxAp();
	gotoxy(70, 43);
	setColor(RED);
	cout << monster.name;
	setColor();
	gotoxy(82, 43);
	cout << "HP : " << monster.getHP() << "/" << monster.getMAXHP();
	gotoxy(97, 43);
	cout << "AP : " << monster.getAP() << "/??";
}

void Battle::AIBattle(){
	while (1) 
	{
		if (!RandInt(3)) 
		{
		NORMAL_ATTACK:
			int monsterdmg = monster.attackDamage();
			_gotoxy();
			cout << monster.name << "Àº(´Â) " << p.name << " À»(¸¦) °ø°ÝÇß´Ù!";
			getKey();
			_gotoxy();
			cout << p.name << "Àº(´Â) " << p.beatenDamage(monsterdmg) << "ÀÇ µ¥¹ÌÁö¸¦ ÀÔ¾ú´Ù!";
			getKey();
			break;
		}
		else 
		{
			int num = RandInt(9);	// ½ºÅ³ ·£´ý ÁöÁ¤
			if (monster.sk_list[num])
			{	// ½ºÅ³ ÀÖÀ» ¶§
				if (monster.getAP() >= skList[num]->Cost())	// AP ÃæºÐ ÇÏ¸é
				{
					if (num >= 0 && num <= 2)
					{
						_gotoxy();
						cout << monster.name << "Àº(´Â) °­Å¸¸¦ »ç¿ëÇß´Ù!";
						getKey();
					}
					else if (num >= 3 && num <= 5)
					{
						_gotoxy();
						cout << monster.name << "Àº(´Â) ¸ô¾ÆÄ¡±â¸¦ »ç¿ëÇß´Ù!";
						getKey();
					}
					else
					{
						_gotoxy();
						cout << monster.name << "Àº(´Â) È¸º¹À» »ç¿ëÇß´Ù!";
						getKey();
						monster.HealHP(skList[num]->Amount());
						monster.subAP(skList[num]->Cost());
						return;
					}
					playerbeaten();
					int dmg = skList[num]->Amount();
					_gotoxy();
					cout << p.name << "Àº(´Â) " << p.beatenDamage(dmg) << "ÀÇ µ¥¹ÌÁö¸¦ ÀÔ¾ú´Ù!";
					getKey();
					break;
				}
				else
					goto NORMAL_ATTACK;
			}
			else
				goto NORMAL_ATTACK;
		}
	}
}

bool Battle::Run() {
	if (RandInt(3)) {
		_gotoxy();
		cout << p.name << "Àº(´Â) ¹«»çÈ÷ µµ¸ÁÃÆ´Ù!";
		getKey();
		return true;
	}
	else
	{
		_gotoxy();
		cout << "µµ¸ÁÄ¡´Âµ¥ ½ÇÆÐÇß´Ù!";
		getKey();
		return false;
	}
}

int Battle::BattleMenu() {
	monster.printASCII();
	gotoxy(0, 42);
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
	cout << "¦¢ ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                    ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤   ¦¢" << endl;
	cout << "¦¢ ¦¢      ¢º     1.    ÀÏ ¹Ý  °ø °Ý             ¦¢                    ¦¢        ¢º     2.    °¡ ¹æ  ¿­ ±â           ¦¢   ¦¢" << endl;
	cout << "¦¢ ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥                    ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥   ¦¢" << endl;
	cout << "¦¢ ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                    ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤   ¦¢" << endl;
	cout << "¦¢ ¦¢      ¢º     3.    ½º Å³  °ø °Ý             ¦¢                    ¦¢        ¢º     4.    Àü Åõ  µµ ÁÖ           ¦¢   ¦¢" << endl;
	cout << "¦¢ ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥   Çà µ¿  ¼± ÅÃ :   ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥   ¦¢" << endl;
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
	while (1) 
	{
		int num = getKey();
		if (num >= '1' && num <= '4')
			return num - '0';
	}
}

void Battle::GAMEOVER() {
	exit(100);
}

void Battle::playerbeaten(){
	system("color 4F");
	_beep(532, 150);
	_sleep(100);
	system("color 0F");
	_sleep(100);
	system("color 4F");
	_beep(532, 250);
	_sleep(100);
	system("color 0F");
	_sleep(100);
}

void Battle::monsterbeaten(){
	setColor(RED);
	gotoxy(0, 0);
	monster.printASCII();
	_beep(532, 200);
	_sleep(100);
	setColor();
	gotoxy(0, 0);
	monster.printASCII();	
	setColor(RED);
	gotoxy(0, 0);
	monster.printASCII();
	_beep(532, 200);
	_sleep(100);
	setColor();
	gotoxy(0, 0);
	monster.printASCII();
}