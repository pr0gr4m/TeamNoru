#include "Battle.h"
#include "player.h"
#include "skill.h"
#include "item.h"
#include <stdarg.h>
#include <conio.h>
using namespace std;
Battle::Battle(Monster& monster)
{
	BattleSystem(monster);
}


Battle::~Battle()
{
}

void Battle::BattleSystem(Monster& monster) {
	while (1) {
		int battleget = 0;
		clrscr();
		battleget = BattleMenu(monster);
		while(1) {
			bool isCheck = false;
			int damage = 0;
			switch (battleget) {
			case 1:
				damage = p.attackDamage();
				Battlelog(monster,"檜曉! ゎ顫!");
				Battlelog(monster,"%y%s%w擎/朝 %r%d%w 等嘐雖蒂 %y%s%w縑啪 輿歷棻!", p.name, damage, monster.name);
				monster.beatenDamage(damage);
				isCheck = true;
				break;
			case 2:
				isCheck = ShowInventory(monster);
				break;
			case 3:
				isCheck = ShowSkills(monster);
				break;
			case 4:
				if (Run(monster)) {
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
		AIBattle(monster);
	}
}

bool Battle::ShowInventory(Monster& monster) {
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
			cout << p.nHp << "/" << p.getMAXHP() << "    " << p.nAP << "/" << p.getMAXAP();
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
				Boxscreen(monster);
				return false;
			}
			else {
				//嬴檜蠱 餌辨
				if (p.item_list[inp] > 0) {
					Battlelog(monster, "%y%s%w擎/朝 %r%s%w擊/蒂 餌辨ц棻!", p.name, item_name[inp]);
					//嬴檜蠱 餌辨 л熱 褒ч
					p.item_list[inp]--;
					return true;
				}
				else {
					_beep(523, 200);
					_beep(523, 200);
				}
			}
	}
	
}
bool Battle::ShowSkills(Monster& monster) {
	while (1) {
		gotoxy(30, 10);
		//cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		//cout << "弛                                                                                        弛" << endl;
		//cout << "弛                                                                                        弛" << endl;
		//cout << "弛                                                                                        弛" << endl;
		//cout << "弛                                                                                        弛" << endl;
		//cout << "弛                                                                                        弛" << endl;
		//cout << "弛                                                                                        弛" << endl;
		//cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎" << endl;
		//gotoxy(31, 11);
		//return true;
		cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖" << endl;
		cout << "弛                                                                                        弛" << endl;
		cout << "戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣" << endl;
		gotoxy(35, 11);
		cout << p.name << "      HP   " << p.nHp << " / " << p.getMAXHP << "      AP   " << p.nAP << " / " << p.getMAXAP;
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
		if (p.nAP < 1/*蝶鑒 餌辨 AP爾棻 雪棻賊*/) {
			return false;
			Battlelog(monster, "AP陛 睡褶м棲棻!");
		}
		//蝶鑒 餌辨 л熱[num];
		//蝶鑒 AP 模賅
		Battlelog(monster,"%y%s%w擎/朝 %y%s%w擊/蒂 餌辨ц棻!",p.name,sk_name[num]);
		return true;
	}
	
}
void Battle::Boxscreen(Monster& monster) {
	gotoxy(0, 0);
	monster.printASCII();
	gotoxy(0, 52);
	cout << "忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "弛                                                                                                                                                  弛";
	cout << "戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎";
	gotoxy(0, 0);
}
void Battle::AIBattle(Monster& monster){
	while (1) {
		if (RandInt(2)) {
			int monsterdmg = monster.attackDamage();
			//跨蝶攪 ゎ顫
			p.beatenDamage(monsterdmg);
			Battlelog(monster,"/*PlayerName*/擎/朝 %r%d%w曖 等嘐雖蒂 殮歷棻!", monsterdmg);
			break;
		}
		else {
			//跨蝶攪蝶鑒
			for (int i = 0; i < SKILL_NUM; i++) {
				if (monster.sk_list[i]) {//蝶鑒 氈擊陽
					if (monster.getAP() >1 ) {//蝶鑒餌辨ap陛 ⑷營AP爾棻 堪戲賊
						int damage = 0;
						Battlelog(monster,"%y%s%w擎/朝%y%s%w擊/蒂 餌辨ц棻!", monster.name, monster.sk_list[i]);
						Battlelog(monster,"%y%s%w擎/朝 %r%d%w曖 等嘐雖蒂 殮歷棻!", p.name, damage);
						p.beatenDamage(damage);
						break;
					}
				}
			}
		}
	}
}
bool Battle::Run(Monster& monster) {
	if (RandInt(3)) {
		Battlelog(monster, "%y&s%w擎/朝 %y%s%w縑啪憮 鼠餌�� 紫蜂蟻棻!", p.name, monster.name);
		return true;
	}
	else
		Battlelog(monster, "%y%s%w擎/朝 %y%s%w縑啪憮 紫蜂纂朝等 褒ぬц棻!", p.name, monster.name);
		return false;
}

void Battle::Battlelog(Monster& monster,const char* Format, ...) {
	va_list list;
	clrscr();
	//嬴蝶酈 轎溘
	Boxscreen(monster);
	int i;
	int* idx = (int*)&Format;
	idx++;
	while (*Format != NULL) {
		if (*Format == '%') {
			switch (*(Format + 1))
			{
			case 'd':     // int ⑽ 衙偃滲熱 轎溘  
				cout<<*(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'c':     // char ⑽ 衙偃滲熱 轎溘  
				cout << *(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'f':     // double ⑽ 衙偃滲熱 轎溘  
				cout << *(int*)idx;
				idx++;    // double ⑽擎 8byte蒂 離雖ж晦 陽僥縑 4byte噶 2廓 嗨橫 剩朝棻.
				idx++;
				Format += 2;
				break;
			case 's':     // 僥濠翮 衙偃滲熱 轎溘  
				cout << *(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'y':     // 蕃煎辦 儀
				setColor(YELLOW,BLACK);
				Format += 2;
				break;
			case 'w':     // 儀 褻瞰 綰楷  
				setColor(WHITE, BLACK);
				Format += 2;
				break;
			case 'r':     // 儀 褻瞰 溯萄 
				setColor(RED, BLACK);
				Format += 2;
				break;

			default:
				break;
			}
		}
		else
		{
			cout << *Format;
			Format++;
		}
	}
}
int Battle::BattleMenu(Monster& monster) {
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