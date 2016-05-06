#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H

#include <iostream>

class Monster
{
public:
	Monster(int level);
	bool isDie() { return ((HP > 0) ? false : true); }
	int attackDamage();
	int beatenDamage(int dmg);
	void printStatus();

private:
	int STM, STR, DEX, LUK;
	int HP, AP;

private:
	bool isCritical();
	int defensivePower() { return int(STR * 1.5); }
};

#endif