#pragma once
#ifndef _ITEM_H
#define _ITEM_H	//아이템의 요소 (수치, 착용레벨제한)

#include "lib.h"

static const int ITEM_NUM = 7;
static const char *item_name[ITEM_NUM] = { "해머", "전기톱", "가죽갑옷", "방탄복", "빨간포션", "하얀포션", "파란포션" };

class ITEM
{
public:
	ITEM(const char *n, short t, short lev);
	virtual int Amount() const = 0;
	short Type() const { return type; }
	short Level() const { return level; }
private:
	enum { NAME_LEN = 20 };
	char name[NAME_LEN];
	short type, level;
};

class Weapon1 :public ITEM
{
public:
	Weapon1(short lev = 3) :
		ITEM(item_name[0], ATTK, lev), dmg(10) {}
	int Amount() const;
private:
	int dmg;
};

class Weapon2 :public ITEM
{
public:
	Weapon2(short lev = 5) :
		ITEM(item_name[1], ATTK, lev), dmg(20) {}
	int Amount() const;
private:
	int dmg;
};

class Armor1 :public ITEM
{
public:
	Armor1(short lev = 3) :
		ITEM(item_name[2], DEF, lev), def(5) {}
	int Amount() const;
private:
	int def;
};

class Armor2 :public ITEM
{
public:
	Armor2(short lev = 5) :
		ITEM(item_name[3], DEF, lev), def(10) {}
	int Amount() const;
private:
	int def;
};

class HPPotion1 :public ITEM
{
public:
	HPPotion1(short lev = 1) :
		ITEM(item_name[4], HEAL, lev), heal(50) {}
	int Amount() const;
private:
	int heal;
};

class HPPotion2 :public ITEM
{
public:
	HPPotion2(short lev = 1) :
		ITEM(item_name[5], HEAL, lev), heal(100) {}
	int Amount() const;
private:
	int heal;
};

class APPotion :public ITEM
{
public:
	APPotion(short lev = 1) :
		ITEM(item_name[6], HEAL, lev), heal(30) {}
	int Amount() const;
private:
	int heal;
};

#endif