#pragma once
#ifndef _ITEM_H
#define _ITEM_H	//�������� ��� (��ġ, ���뷹������)

#include "lib.h"

static const int ITEM_NUM = 7;
static const char *item_name[ITEM_NUM] = { "�ظ�", "������", "���װ���", "��ź��", "��������", "�Ͼ�����", "�Ķ�����" };
enum itemLv { START = 1, LOW = 3, MIDDLE = 5, HIGH = 10 };

class ITEM
{
public:
	enum { NAME_LEN = 20 };
	ITEM(short t, itemLv lev) : type(t), level(lev) { }
	virtual int Amount() const = 0;
	short Type() const { return type; }
	short Level() const { return level; }
protected:
	char name[NAME_LEN];
private:
	short type;
	itemLv level;
};

class Weapon : public ITEM
{
public:
	Weapon(itemLv lev = MIDDLE);
	int Amount() const;
private:
	int dmg;
};

class Armor : public ITEM
{
public:
	Armor(itemLv lev = MIDDLE);
	int Amount() const;
private:
	int def;
};

class HPPotion : public ITEM
{
public:
	HPPotion(itemLv lev = LOW);
	int Amount() const;
private:
	int heal;
};

class APPotion : public ITEM
{
public:
	APPotion(itemLv lev = MIDDLE);
	int Amount() const;
private:
	int heal;
};

#endif