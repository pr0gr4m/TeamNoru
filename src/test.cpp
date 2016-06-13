#include <iostream>
#include <ctime>
#include "monster.h"
#include "map.h"
#include "lib.h"
#include "game.h"
#include "player.h"
#include "skill.h"

using namespace std;

Player p("player");

Skill * skList[10];
ITEM * itList[7];

void initSkill()
{
	skList[0] = new Smite(1);
	skList[1] = new Smite(2);
	skList[2] = new Smite(3);
	skList[3] = new Super(1);
	skList[4] = new Super(2);
	skList[5] = new Super(3);
	skList[6] = new Heal(1);
	skList[7] = new Heal(2);
	skList[8] = new Heal(3);
	skList[9] = new Gamble();
}

void initItem()
{
	itList[0] = new Weapon(MIDDLE);
	itList[1] = new Weapon(HIGH);
	itList[2] = new Armor(MIDDLE);
	itList[3] = new Armor(HIGH);
	itList[4] = new HPPotion(LOW);
	itList[5] = new HPPotion(MIDDLE);
	itList[6] = new APPotion();
}

int main()
{
	initSkill();
	initItem();
	//for (int i = 0; i < 15; i++)
		p.Lvup();

	//p.item_list[0] = 1;
	//p.item_list[5] = 2;
	//p.item_list[3] = 1;
	p.sk_list[1] = 1;
	p.sk_list[9] = 1;
	gameScreen();
	return 0;
}