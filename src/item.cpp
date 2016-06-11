#include "item.h"
#include <cstring>

ITEM::ITEM(const char *n, short t, short lev) 
	:type(t), level(lev)
{
	std::strcpy(name, n);
}

int Weapon1::Amount() const
{
	return dmg;
}

int Weapon2::Amount() const
{
	return dmg;
}

int Armor1::Amount() const
{
	return def;
}

int Armor2::Amount() const
{
	return def;
}

int HPPotion1::Amount() const
{
	return heal;
}

int HPPotion2::Amount() const
{
	return heal;
}

int APPotion::Amount() const
{
	return heal;
}