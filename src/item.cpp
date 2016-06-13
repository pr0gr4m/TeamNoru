#include "item.h"
#include "lib.h"
#include <cstring>

using namespace std;

Weapon::Weapon(itemLv lev)
	: ITEM(ATTK, lev)
{
	if (lev == MIDDLE) {
		std::strcpy(name, item_name[0]);
		dmg = 10;
	}
	else if (lev == HIGH) {
		std::strcpy(name, item_name[1]);
		dmg = 20;
	}
	else
	{
		cerr << "아이템 오류!" << endl;
		exit(EXIT_FAILURE);
	}
}

int Weapon::Amount() const
{
	return dmg;
}

Armor::Armor(itemLv lev)
	: ITEM(DEF, lev)
{
	if (lev == MIDDLE) {
		std::strcpy(name, item_name[2]);
		def = 5;
	}
	else if (lev == HIGH) {
		std::strcpy(name, item_name[3]);
		def = 10;
	}
	else
	{
		cerr << "아이템 오류!" << endl;
		exit(EXIT_FAILURE);
	}
}

int Armor::Amount() const
{
	return def;
}

HPPotion::HPPotion(itemLv lev)
	: ITEM(HEAL, lev)
{
	if (lev == LOW) {
		std::strcpy(name, item_name[4]);
		heal = 50;
	}
	else if (lev == MIDDLE) {
		std::strcpy(name, item_name[5]);
		heal = 100;
	}
	else
	{
		cerr << "아이템 오류!" << endl;
		exit(EXIT_FAILURE);
	}
}

int HPPotion::Amount() const
{
	return heal;
}

APPotion::APPotion(itemLv lev)
	: ITEM(HEAL, lev)
{
	if (lev == MIDDLE)
	{
		std::strcpy(name, item_name[6]);
		heal = 30;
	}
	else
	{
		cerr << "아이템 오류!" << endl;
		exit(EXIT_FAILURE);
	}
}

int APPotion::Amount() const
{
	return heal;
}