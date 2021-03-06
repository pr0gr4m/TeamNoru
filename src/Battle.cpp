/*
 * だ橾 : Battle.cpp
 * 頂辨 : 瞪癱 檣攪む檜蝶 掘⑷
 * 薯濛 : 瞪撩遵
 */

#include "Battle.h"
#include "player.h"
#include "skill.h"
#include "item.h"
#include <sstream>
#include <stdarg.h>
#include <conio.h>
#include <fstream>
using namespace std;

extern Skill * skList[10];
extern ITEM * itList[7];
static const char *over_file = "ASCII\\gameover.txt";

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
			ClearReadBuff();
			bool isCheck = false;
			int damage = 0;
			switch (battleget) {
			case 1:
				damage = p.attackDamage();
				_gotoxy();
				cout << "檜曉! ゎ顫!";
				getKey();
				monsterbeaten();
				_gotoxy();
				cout << p.name << "擎(朝) " << monster.beatenDamage(damage) << " 等嘐雖蒂 " << monster.name << "縑啪 輿歷棻!";
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
			cout << p.name << "擎(朝) " << monster.name << "曖 瞪癱縑憮 蝓葬ц棻!";
			getKey();
			p.Getexp(monster.Exp());
			_gotoxy();
			cout << p.name << "擎(朝) " << monster.Exp() << "曖 唳я纂蒂 橢歷棻!";
			getKey();
			return;
		}
		AIBattle();
		if (p.nHp <= 0) {
			_gotoxy();
			cout << p.name << "擎(朝) ぬ寡ц棻.....";
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
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式成式式式式式式式式式式忖" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  忙式式式式式式式式式式式式忖                                    弛                    弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  弛 說 除  ん 暮  X  " << p.item_list[4] << "偃: 1弛                                    弛    E x i t :  4    弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  戌式式式式式式式式式式式式戎H P 蒂  5 0 虜 躑  �� 犒 и 棻.     弛                    弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛                                                                  戍<Player>式式式式式式扣" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  忙式式式式式式式式式式式式忖                                    弛 000/000    000/000 弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  弛 ж 擔  ん 暮  X  " << p.item_list[5] << "偃: 2弛                                    戍<Monster> 式式式式式扣" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  戌式式式式式式式式式式式式戎H P 蒂  1 0 0 虜 躑  �� 犒 и 棻.   弛 000/000      000   弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛                                                                  戍式式式式式式式式式式扣" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  忙式式式式式式式式式式式式忖                                    弛                    弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  弛 だ 塢  ん 暮  X  " << p.item_list[6] << "偃: 3弛                                    弛    璋  濠  摹 鷗   弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "弛  戌式式式式式式式式式式式式戎A P 蒂  3 0 虜 躑  �� 犒 и 棻.     弛                    弛" << endl;
	gotoxy(30, 10 + colm);
	colm++;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扛式式式式式式式式式式戎" << endl;

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
				//嬴檜蠱 餌辨
				if (p.item_list[inp + 3] > 0) {
					_gotoxy();
					cout << p.name << "擎(朝) " << item_name[inp + 3] << "擊(蒂) 餌辨ц棻!";
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
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
		gotoxy(20, 11);
		cout << "弛                                                                                    弛";
		gotoxy(25, 11);
		cout << p.name << "      HP   " << p.nHp << " / " << p.getMaxHp() << "      AP   " << p.nAP << " / " << p.getMaxAp();
		gotoxy(20, 12);
		cout << "戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣";
		gotoxy(20, 13);
		cout << "弛                                                                                    弛";
		gotoxy(20, 14);
		cout << "弛                                                                                    弛";
		gotoxy(20, 15);
		cout << "弛                                                                                    弛";
		gotoxy(20, 16);
		cout << "弛                                                                                    弛";
		gotoxy(20, 17);
		cout << "弛                                                                                    弛";
		gotoxy(20, 18);
		cout << "弛                                                                                    弛";
		gotoxy(20, 19);
		cout << "弛                                                                                    弛";
		gotoxy(20, 20);
		cout << "弛                                                                                    弛";
		gotoxy(20, 21);
		cout << "弛                                                                                    弛";
		gotoxy(20, 22);
		cout << "戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣";
		gotoxy(20, 23);
		cout << "弛                                                                                    弛";
		gotoxy(20, 24);
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";
		gotoxy(25, 23);
		cout << "Exit: 0             Get Number: n" << endl;
		int ypos = 13;
		for (int i = 0; i < SKILL_NUM; i++)
		{
			if (p.sk_list[i] && i != 9)	// 蝶鑒 襄營 ж賊
			{
				gotoxy(25, ypos++);
				cout << i + 1 << ". " << skList[i]->name << "  Lv." << skList[i]->Level() << "    AP : " << skList[i]->Cost();
			}
			else if (p.sk_list[i] && i == 9)
			{
				gotoxy(25, ypos++);
				cout << "G. " << skList[i]->name << "  Lv." << skList[i]->Level() << "    AP : " << skList[i]->Cost();
			}
		}

	SKILL_INPUT:
		int input = getKey();
		if (input == 'g' || input == 'G')
		{
			input = 10;
		}
		else
			input -= '0';
		if (!input) {
			return false;
		}
		input--;
		if (input < 0 || input > 9 || !p.sk_list[input])
			goto SKILL_INPUT;

		if (p.nAP < skList[input]->Cost())
		{	// ap 睡褶
			_gotoxy();
			cout << "AP陛 睡褶м棲棻!";
			getKey();
			return false;
		}
		else
		{
			int dmg = skList[input]->Amount();
			_gotoxy();
			cout << p.name << "擎(朝) " << skList[input]->name << "擊(蒂) 餌辨ц棻!";
			getKey();
			monsterbeaten();
			int cdmg = monster.beatenDamage(SkillDamage(input));
			p.nAP -= skList[input]->Cost();
			if (input >= 6 && input <= 8)
			{
				_gotoxy();
				cout << p.name << "擎(朝) " << dmg << "擊(蒂) �蛹嘎葧�!";
				getKey();
			}
			else
			{
				_gotoxy();
				cout << monster.name << "擎(朝) " << cdmg << "曖 等嘐雖蒂 殮歷棻!";
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
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛                                                            弛                                                            弛" << endl;
	cout << "戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣" << endl;
	cout << "弛                                                                                                                          弛" << endl;
	cout << "弛                                                                                                                          弛" << endl;
	cout << "弛                                                                                                                          弛" << endl;
	cout << "弛                                                                                                                          弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
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
			cout << monster.name << "擎(朝) " << p.name << " 擊(蒂) 奢問ц棻!";
			getKey();
			_gotoxy();
			cout << p.name << "擎(朝) " << p.beatenDamage(monsterdmg) << "曖 等嘐雖蒂 殮歷棻!";
			getKey();
			break;
		}
		else 
		{
			int num = RandInt(9);	// 蝶鑒 楠渾 雖薑
			if (monster.sk_list[num])
			{	// 蝶鑒 氈擊 陽
				if (monster.getAP() >= skList[num]->Cost())	// AP 醱碟 ж賊
				{
					if (num >= 0 && num <= 2)
					{
						_gotoxy();
						cout << monster.name << "擎(朝) 鬼顫蒂 餌辨ц棻!";
						getKey();
					}
					else if (num >= 3 && num <= 5)
					{
						_gotoxy();
						cout << monster.name << "擎(朝) 路嬴纂晦蒂 餌辨ц棻!";
						getKey();
					}
					else
					{
						_gotoxy();
						cout << monster.name << "擎(朝) �蛹嘛� 餌辨ц棻!";
						getKey();
						monster.HealHP(skList[num]->Amount());
						monster.subAP(skList[num]->Cost());
						return;
					}
					playerbeaten();
					int dmg = skList[num]->Amount();
					_gotoxy();
					cout << p.name << "擎(朝) " << p.beatenDamage(dmg) << "曖 等嘐雖蒂 殮歷棻!";
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
	if (!strcmp(monster.name, mon_name[6]))
	{
		_gotoxy();
		cout << "掘羹煎睡攪朝 紫蜂艦 熱 橈棻!";
		getKey();
		return false;
	}
	if (RandInt(3)) {
		_gotoxy();
		cout << p.name << "擎(朝) 鼠餌�� 紫蜂蟻棻!";
		getKey();
		return true;
	}
	else
	{
		_gotoxy();
		cout << "紫蜂纂朝等 褒ぬц棻!";
		getKey();
		return false;
	}
}

int Battle::BattleMenu() {
	ClearReadBuff();
	monster.printASCII();
	gotoxy(0, 42);
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
	cout << "弛 忙式式式式式式式式式式式式式式式式式式式式式式忖                    忙式式式式式式式式式式式式式式式式式式式式式式忖   弛" << endl;
	cout << "弛 弛      Ⅱ     1.    橾 奩  奢 問             弛                    弛        Ⅱ     2.    陛 寞  翮 晦           弛   弛" << endl;
	cout << "弛 戌式式式式式式式式式式式式式式式式式式式式式式戎                    戌式式式式式式式式式式式式式式式式式式式式式式戎   弛" << endl;
	cout << "弛 忙式式式式式式式式式式式式式式式式式式式式式式忖                    忙式式式式式式式式式式式式式式式式式式式式式式忖   弛" << endl;
	cout << "弛 弛      Ⅱ     3.    蝶 鑒  奢 問             弛                    弛        Ⅱ     4.    瞪 癱  紫 輿           弛   弛" << endl;
	cout << "弛 戌式式式式式式式式式式式式式式式式式式式式式式戎   ч 翕  摹 鷗 :   戌式式式式式式式式式式式式式式式式式式式式式式戎   弛" << endl;
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
	while (1) 
	{
		int num = getKey();
		if (num >= '1' && num <= '4')
			return num - '0';
	}
}

void Battle::GAMEOVER() {
	char buf[BUF_LEN];
	std::ifstream op(over_file, ios::in | ios::binary);
	if (!op.is_open())
	{
		std::cerr << "だ橾 螃Ъ 褒ぬ." << endl << "ASCII ィ渦諦 臢蝶お だ橾擊 �挫恉� 輿褊衛螃." << endl;
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
	exit(100);
}

void Battle::playerbeaten(){
	system("color 4F");
	Delay(100);
	system("color 0F");
	Delay(100);
	system("color 4F");
	Delay(100);
	system("color 0F");
	Delay(100);
}

void Battle::monsterbeaten(){
	setColor(RED);
	gotoxy(0, 0);
	monster.printASCII();
	Delay(100);
	setColor();
	gotoxy(0, 0);
	monster.printASCII();	
	setColor(RED);
	gotoxy(0, 0);
	monster.printASCII();
	Delay(100);
	setColor();
	gotoxy(0, 0);
	monster.printASCII();
}