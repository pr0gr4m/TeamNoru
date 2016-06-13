#include "Battle.h"
#include "player.h"
#include "skill.h"
#include "item.h"
#include <sstream>
#include <stdarg.h>
#include <conio.h>
using namespace std;
Battle::Battle(Monster& _monster)
	: monster(_monster)
{
	BattleSystem();
}

Battle::~Battle()
{
}

void Battle::BattleSystem() {
	while (1) {
		int battleget = 0;
		clrscr();
		battleget = BattleMenu();
		while(1) {
			bool isCheck = false;
			int damage = 0;
			switch (battleget) {
			case 1:
				damage = p.attackDamage();
				Battlelog("檜曉! ゎ顫!");
				monsterbeaten();
				Battlelog("%y%s%w擎/朝 %r%d%w 等嘐雖蒂 %y%s%w縑啪 輿歷棻!", p.name, damage, monster.name);
				monster.beatenDamage(damage);
				isCheck = true;
				break;
			case 2:
				isCheck = ShowInventory();
				break;
			case 3:
				isCheck = ShowSkills();
				break;
			case 4:
				if (Run()) {
					return;
				}
				isCheck = true;
				break;
			default:
				break;
			}
			if (isCheck)
				break;
		}
		if (monster.isDie()) {
			Battlelog("%y%s%w擎/朝 %r%s%w曖 瞪癱縑憮 蝓葬ц棻!",p.name,monster.name);
			p.Getexp(monster.Exp());
			Battlelog("%y%s%w擎/朝 %r%d%w曖 唳я纂蒂 橢歷棻!",p.name,monster.Exp());
			return;
		}
		AIBattle();
		if (p.nHp <= 0) {
			Battlelog("%r%s擎/朝 ぬ寡ц棻.....%w",p.name);
			GAMEOVER();
		}
	}
}

bool Battle::ShowInventory() {
	char input = 0;
	while (1) {
		{
			int colm = 0;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式成式式式式式式式式式式忖" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "弛  忙式式式式式式式式式式式式忖                                    弛                    弛" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "弛  弛 說 除  ん 暮  X  n偃: 1弛                                    弛    E x i t :  4    弛" << endl;
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
			cout << "弛  弛 ж 擔  ん 暮  X  n偃: 2弛                                    戍<Monster> 式式式式式扣" << endl;
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
			cout << "弛  弛 だ 塢  ん 暮  X  n偃: 3弛                                    弛  ч 翕  摹 鷗 :  n 弛" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "弛  戌式式式式式式式式式式式式戎A P 蒂  3 0 虜 躑  �� 犒 и 棻.     弛                    弛" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扛式式式式式式式式式式戎" << endl;
			gotoxy(101, 15);
			cout << p.nHp << "/" << p.getMaxHp() << "    " << p.nAP << "/" << p.getMaxHp();
			gotoxy(101, 17);
			cout << monster.getHP() << "/" << monster.getMAXHP() << "      " << monster.getAP();
			gotoxy(54, 12);
			cout << p.item_list[4];
			gotoxy(54, 16);
			cout << p.item_list[5];
			gotoxy(54, 20);
			cout << p.item_list[6];
		}
		gotoxy(118, 20);
		input = getche();
		int inp = (int)input - 45;
		if (inp < 1 || inp>4)

			if (input == 4) {
				Boxscreen();
				return false;
			}
			else {
				//嬴檜蠱 餌辨
				if (p.item_list[inp] > 0) {
					Battlelog("%y%s%w擎/朝 %r%s%w擊/蒂 餌辨ц棻!", p.name, item_name[inp]);
					
					p.item_list[inp]--;
					return true;
				}
				else {
					return false;
				}
			}
	}
	
}
bool Battle::ShowSkills() {
	while (1) {
		gotoxy(30, 10);
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛                                                                                        弛" << endl;
		cout << "戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣" << endl;
		gotoxy(35, 11);
		cout << p.name << "      HP   " << p.nHp << " / " << p.getMaxHp() << "      AP   " << p.nAP << " / " << p.getMaxHp();
		int garo = 2;
		for (int i = 0; i < SKILL_NUM; i++) {
			if (p.sk_list[i]) {
				garo++;
				gotoxy(30, 10 + garo);
				cout << "弛                                                                                        弛" << endl;
				gotoxy(31, 10 + garo);
				cout << garo - 2 << ". " << sk_name[i] << "L v " <</*蝶鑒 溯漣<<*/"         A  P: "/*蝶鑒 囀蝶お*/;
			}
		}
		gotoxy(30, 11 + garo);
		cout << "戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣" << endl;
		cout << "弛                                                                                        弛" << endl;
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
		gotoxy(35, 12 + garo);
		cout << "Exit: 0             Get Number: n" << endl;
		gotoxy(68, 12 + garo);
		char input = getche();
		int inp = input - 48;
		if (!inp) {
			return false;
		}
		int counter = 0,num=0;
		for (num = 0; num < SKILL_NUM; num++) {
			//蝶鑒 氈朝 廓�� 葬欐
			counter += p.sk_list[num];
			if (counter == inp)
				break;
			else {
				return false;
			}
		}
		int damage = 0;
		if (p.nAP < 1/*AP 餌辨*/) {
			Battlelog("AP陛 睡褶м棲棻!");
			return false;
		}
		//damage=蝶鑒[num];
		//蝶鑒 AP 模賅
		Battlelog("%y%s%w擎/朝 %y%s%w擊/蒂 餌辨ц棻!",p.name,sk_name[num]);
		if (damage) {
			monsterbeaten();
			Battlelog("%y%s%w擎/朝 %r%d%w曖 等嘐雖蒂 %y%s%w縑啪 輿歷棻!", p.name, damage, monster.name);
		}
		else {
			Battlelog("%y%s%w擎/朝 跺擊 蹺蝶溜棻!", p.name);
		}
		return true;
	}
	
}
void Battle::Boxscreen() {
	gotoxy(0, 0);
	monster.printASCII();
	gotoxy(0, 52);
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
	cout << "弛                                                                        弛                                                                        弛";
	cout << "戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";
	gotoxy(8, 50);
	setColor(YELLOW);
	cout << p.name;
	setColor();
	gotoxy(28, 50);
	cout << p.nHp << "/" << p.getMaxHp();
	gotoxy(42, 50);
	cout << p.nAP << "/" << p.getMaxAp();
	gotoxy(94, 50);
	setColor(RED);
	cout << monster.name;
	setColor();
	gotoxy(112, 50);
	cout << monster.getHP() << "/" <<monster.getMAXHP();
	gotoxy(126, 50);
	cout << monster.getAP() << " A P";
}
void Battle::AIBattle(){
	while (1) {
		if (RandInt(2)) {
			int monsterdmg = monster.attackDamage();
			//跨蝶攪 ゎ顫
			p.beatenDamage(monsterdmg);
			Battlelog("%y%s%w擎/朝 %y%s%w擊/蒂 奢問ц棻!",monster.name,p.name);
			Battlelog("%y%s%w擎/朝 %r%d%w曖 等嘐雖蒂 殮歷棻!",p.name, monsterdmg);
			break;
		}
		else {
			//跨蝶攪蝶鑒
			for (int i = 0; i < SKILL_NUM; i++) {
				if (monster.sk_list[i]) {//蝶鑒 氈擊陽
					if (monster.getAP() >1 ) {//蝶鑒餌辨ap陛 ⑷營AP爾棻 堪戲賊
						int damage = monster.sk_list[i];
						Battlelog("%y%s%w擎/朝%y%s%w擊/蒂 餌辨ц棻!", monster.name, sk_name[i]);
						if (damage > 0) {
							playerbeaten();
							Battlelog("%y%s%w擎/朝 %r%d%w曖 等嘐雖蒂 殮歷棻!", p.name, damage);
							p.beatenDamage(damage);
							break;
						}
						else {
							Battlelog("%y%s%w擎/朝 跺擊 蹺蝶溜棻!", monster.name);
						}
					}
				}
			}
		}
	}
}
bool Battle::Run() {
	if (RandInt(3)) {
		Battlelog("%y&s%w擎/朝 %y%s%w縑啪憮 鼠餌�� 紫蜂蟻棻!", p.name, monster.name);
		return true;
	}
	else
		Battlelog("%y%s%w擎/朝 %y%s%w縑啪憮 紫蜂纂朝等 褒ぬц棻!", p.name, monster.name);
		return false;
}

void Battle::Battlelog(const char* Format, ...) {
	va_list list;
	clrscr();
	Boxscreen();
	int i;
	int* idx = (int*)&Format;
	idx++;
	for (int i = 0; i < 5; i++) {
		strcpy(Log[i + 1], Log[i]);
	}
	for (int i = 0; i < 6; i++) {
		gotoxy(2, 56 - i);
		setColor(LIGHTGRAY);
		cout << Log[i+1];
		setColor();
	}
	while (*Format != NULL) {
		if (*Format == '%') {
			switch (*(Format + 1))
			{
			case 'd':     // int ⑽ 衙偃滲熱 轎溘  
				strcat(Log[0], (char*)idx);
				cout<<*(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'c':     // char ⑽ 衙偃滲熱 轎溘
				strcat(Log[0], (char*)idx);
				cout << *(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'f':     // double ⑽ 衙偃滲熱 轎溘  
				strcat(Log[0], (char*)idx);
				cout << *(int*)idx;
				idx++;    // double ⑽擎 8byte蒂 離雖ж晦 陽僥縑 4byte噶 2廓 嗨橫 剩朝棻.
				idx++;
				Format += 2;
				break;
			case 's':     // 僥濠翮 衙偃滲熱 轎溘
				strcat(Log[0], (char*)idx);
				cout << *(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'y':     // 蕃煎辦 儀
				setColor(YELLOW);
				Format += 2;
				break;
			case 'w':     // 儀 褻瞰 �倌ぜ昄�
				setColor(WHITE);
				Format += 2;
				break;
			case 'r':     // 儀 褻瞰 溯萄 
				setColor(RED);
				Format += 2;
				break;
			default:
				break;
			}
		}
		else
		{
			strcat(Log[0], Format);
			cout << *Format;
			Format++;
		}
		cout << "∪";
	}
	getchar();
}
int Battle::BattleMenu() {
	while (1) {
		monster.printASCII();
		gotoxy(0, 52);
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
		cout << "弛 忙式式式式式式式式式式式式式式式式式式式式式式忖                                           忙式式式式式式式式式式式式式式式式式式式式式式忖      弛";
		cout << "弛 弛      Ⅱ     1.    橾 奩  奢 問             弛                                           弛        Ⅱ     2.    陛 寞  翮 晦           弛      弛";
		cout << "弛 戌式式式式式式式式式式式式式式式式式式式式式式戎                                           戌式式式式式式式式式式式式式式式式式式式式式式戎      弛";
		cout << "弛 忙式式式式式式式式式式式式式式式式式式式式式式忖                                           忙式式式式式式式式式式式式式式式式式式式式式式忖      弛";
		cout << "弛 弛      Ⅱ     3.    蝶 鑒  奢 問             弛                                           弛        Ⅱ     4.    瞪 癱  紫 輿           弛      弛";
		cout << "弛 戌式式式式式式式式式式式式式式式式式式式式式式戎             ч 翕  摹 鷗 :                戌式式式式式式式式式式式式式式式式式式式式式式戎      弛";
		cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";
		gotoxy(80, 57);
		char num=getche();
		gotoxy(0, 0);
		if (num< 49 || num>52) {
		}
		else {
			return (int)(num-48);
		}
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