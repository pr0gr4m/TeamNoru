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
				Battlelog("ÀÌ¾å! ÆòÅ¸!");
				Battlelog("%y%s%wÀº/´Â %r%d%w µ¥¹ÌÁö¸¦ %y%s%w¿¡°Ô ÁÖ¾ú´Ù!", p.name, damage, monster.name);
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
			Battlelog("%y%s%wÀº/´Â %r%s%wÀÇ ÀüÅõ¿¡¼­ ½Â¸®Çß´Ù!",p.name,monster.name);
			p.Getexp(monster.Exp());
			Battlelog("%y%s%wÀº/´Â %r%d%wÀÇ °æÇèÄ¡¸¦ ¾ò¾ú´Ù!",p.name,monster.Exp());
			return;
		}
		AIBattle();
		if (p.nHp <= 0) {
			Battlelog("%r%sÀº/´Â ÆÐ¹èÇß´Ù.....%w",p.name);
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
			cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "¦¢  ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                                    ¦¢                    ¦¢" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "¦¢  ¦¢ »¡ °£  Æ÷ ¼Ç  X  n°³: 1¦¢                                    ¦¢    E x i t :  4    ¦¢" << endl;
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
			cout << "¦¢  ¦¢ ÇÏ ¾á  Æ÷ ¼Ç  X  n°³: 2¦¢                                    ¦§<Monster> ¦¡¦¡¦¡¦¡¦¡¦©" << endl;
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
			cout << "¦¢  ¦¢ ÆÄ ¶õ  Æ÷ ¼Ç  X  n°³: 3¦¢                                    ¦¢  Çà µ¿  ¼± ÅÃ :  n ¦¢" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "¦¢  ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥A P ¸¦  3 0 ¸¸ Å­  È¸ º¹ ÇÑ ´Ù.     ¦¢                    ¦¢" << endl;
			gotoxy(30, 10 + colm);
			colm++;
			cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
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
				//¾ÆÀÌÅÛ »ç¿ë
				if (p.item_list[inp] > 0) {
					Battlelog("%y%s%wÀº/´Â %r%s%wÀ»/¸¦ »ç¿ëÇß´Ù!", p.name, item_name[inp]);
					
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
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤" << endl;
		cout << "¦¢                                                                                        ¦¢" << endl;
		cout << "¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©" << endl;
		gotoxy(35, 11);
		cout << p.name << "      HP   " << p.nHp << " / " << p.getMaxHp() << "      AP   " << p.nAP << " / " << p.getMaxHp();
		int garo = 2;
		for (int i = 0; i < SKILL_NUM; i++) {
			if (p.sk_list[i]) {
				garo++;
				gotoxy(30, 10 + garo);
				cout << "¦¢                                                                                        ¦¢" << endl;
				gotoxy(31, 10 + garo);
				cout << garo - 2 << ". " << sk_name[i] << "L v " <</*½ºÅ³ ·¹º§<<*/"         A  P: "/*½ºÅ³ ÄÚ½ºÆ®*/;
			}
		}
		gotoxy(30, 11 + garo);
		cout << "¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©" << endl;
		cout << "¦¢                                                                                        ¦¢" << endl;
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥" << endl;
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
			//½ºÅ³ ÀÖ´Â ¹øÈ£ ¸®ÅÏ
			counter += p.sk_list[num];
			if (counter == inp)
				break;
			else {
				return false;
			}
		}
		int damage = 0;
		if (p.nAP < 1/*AP »ç¿ë*/) {
			return false;
			Battlelog("AP°¡ ºÎÁ·ÇÕ´Ï´Ù!");
		}
		//½ºÅ³ »ç¿ë ÇÔ¼ö[num];
		//½ºÅ³ AP ¼Ò¸ð
		Battlelog("%y%s%wÀº/´Â %y%s%wÀ»/¸¦ »ç¿ëÇß´Ù!",p.name,sk_name[num]);
		return true;
	}
	
}
void Battle::Boxscreen() {
	gotoxy(0, 0);
	monster.printASCII();
	gotoxy(0, 52);
	cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
	cout << "¦¢                                                                        ¦¢                                                                        ¦¢";
	cout << "¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©";
	cout << "¦¢                                                                                                                                                  ¦¢";
	cout << "¦¢                                                                                                                                                  ¦¢";
	cout << "¦¢                                                                                                                                                  ¦¢";
	cout << "¦¢                                                                                                                                                  ¦¢";
	cout << "¦¢                                                                                                                                                  ¦¢";
	cout << "¦¢                                                                                                                                                  ¦¢";
	cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";
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
			//¸ó½ºÅÍ ÆòÅ¸
			p.beatenDamage(monsterdmg);
			Battlelog("/*PlayerName*/Àº/´Â %r%d%wÀÇ µ¥¹ÌÁö¸¦ ÀÔ¾ú´Ù!", monsterdmg);
			break;
		}
		else {
			//¸ó½ºÅÍ½ºÅ³
			for (int i = 0; i < SKILL_NUM; i++) {
				if (monster.sk_list[i]) {//½ºÅ³ ÀÖÀ»¶§
					if (monster.getAP() >1 ) {//½ºÅ³»ç¿ëap°¡ ÇöÀçAPº¸´Ù ³ôÀ¸¸é
						int damage = monster.sk_list[i];
						Battlelog("%y%s%wÀº/´Â%y%s%wÀ»/¸¦ »ç¿ëÇß´Ù!", monster.name, monster.sk_list[i]);
						Battlelog("%y%s%wÀº/´Â %r%d%wÀÇ µ¥¹ÌÁö¸¦ ÀÔ¾ú´Ù!", p.name, damage);
						p.beatenDamage(damage);
						break;
					}
				}
			}
		}
	}
}
bool Battle::Run() {
	if (RandInt(3)) {
		Battlelog("%y&s%wÀº/´Â %y%s%w¿¡°Ô¼­ ¹«»çÈ÷ µµ¸ÁÃÆ´Ù!", p.name, monster.name);
		return true;
	}
	else
		Battlelog("%y%s%wÀº/´Â %y%s%w¿¡°Ô¼­ µµ¸ÁÄ¡´Âµ¥ ½ÇÆÐÇß´Ù!", p.name, monster.name);
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
			case 'd':     // int Çü ¸Å°³º¯¼ö Ãâ·Â  
				strcat(Log[0], (char*)idx);
				cout<<*(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'c':     // char Çü ¸Å°³º¯¼ö Ãâ·Â
				strcat(Log[0], (char*)idx);
				cout << *(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'f':     // double Çü ¸Å°³º¯¼ö Ãâ·Â  
				strcat(Log[0], (char*)idx);
				cout << *(int*)idx;
				idx++;    // double ÇüÀº 8byte¸¦ Â÷ÁöÇÏ±â ¶§¹®¿¡ 4byte¾¿ 2¹ø ¶Ù¾î ³Ñ´Â´Ù.
				idx++;
				Format += 2;
				break;
			case 's':     // ¹®ÀÚ¿­ ¸Å°³º¯¼ö Ãâ·Â
				strcat(Log[0], (char*)idx);
				cout << *(int*)idx;
				idx++;
				Format += 2;
				break;
			case 'y':     // ¿»·Î¿ì »ö
				setColor(YELLOW);
				Format += 2;
				break;
			case 'w':     // »ö Á¶Àý È­¾ÆÀÌÆ®
				setColor(WHITE);
				Format += 2;
				break;
			case 'r':     // »ö Á¶Àý ·¹µå 
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
		cout << "¡å";
	}
	getchar();
}
int Battle::BattleMenu() {
	while (1) {
		monster.printASCII();
		gotoxy(0, 52);
		cout << "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
		cout << "¦¢ ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                                           ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤      ¦¢";
		cout << "¦¢ ¦¢      ¢º     1.    ÀÏ ¹Ý  °ø °Ý             ¦¢                                           ¦¢        ¢º     2.    °¡ ¹æ  ¿­ ±â           ¦¢      ¦¢";
		cout << "¦¢ ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥                                           ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥      ¦¢";
		cout << "¦¢ ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤                                           ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤      ¦¢";
		cout << "¦¢ ¦¢      ¢º     3.    ½º Å³  °ø °Ý             ¦¢                                           ¦¢        ¢º     4.    Àü Åõ  µµ ÁÖ           ¦¢      ¦¢";
		cout << "¦¢ ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥             Çà µ¿  ¼± ÅÃ :                ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥      ¦¢";
		cout << "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";
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