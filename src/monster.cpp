#include <iostream>
#include "monster.h"

Monster::Monster(int level)
{
	STM = level * 5;
	STR = level * 3;
	DEX = level * 2;
	LUK = level * 2;

	HP = STM * 2 + STR * 1.5;
	AP = STM * 1.5 + DEX * 2;
}

bool Monster::isCritical()
{
	if ((DEX * 1.5 + LUK * 2) > (rand() % 100 + 1))
		return true;
}

int Monster::attackDamage() 
{ 
	double dmg = STR * ((double)rand() / RAND_MAX + 1);
	if (isCritical())
		return dmg * 2;
	else
		return dmg;
}

int Monster::beatenDamage(int dmg)
{
	HP -= dmg - defensivePower();
	return HP;
}

void Monster::printStatus()
{
	using std::cout;
	using std::endl;

	cout << "HP : " << HP << ", AP : " << AP << endl;
}