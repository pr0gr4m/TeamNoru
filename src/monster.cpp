<<<<<<< HEAD
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
=======
#include <iostream>
#include <cstring>
#include "lib.h"
#include "monster.h"

Monster::Monster(const char *n, int lev,
	int dmg, int dfs)	: level(lev)
{
	std::strcpy(name, n);
	int base = level / 10 + 1;
	HP = base * 30 + level * 10;
	AP = base * 10 + level * 5;
	DMG = dmg == 0 ? base * 20 + level * 5 : dmg;
	DFS = dfs == 0 ? base * 10 + level * 3 : dfs;
}

int Monster::attackDamage() const
{ 
	double dmg = DMG * (RandDouble(0.5) + 0.7);
	if (isCritical())
		return dmg * 2;
	else
		return dmg;
}

// 데미지 입는 수치를 받아서 남은 HP를 반환
int Monster::beatenDamage(int dmg)
{
	int calDmg = dmg - defensivePower();
	if (HP <= calDmg)
		HP = 0;
	else
		HP -= calDmg;
	return HP;
}

void Monster::printStatus() const
{
	using std::cout;
	using std::endl;
	cout << "이름 : " << name << endl;
	cout << "HP : " << HP << ", AP : " << AP << endl;
	cout << "DMG : " << DMG << ", DFS : " << DFS << endl;
}

int Monster::Exp() const
{
	int exp = level * 10;
	return exp * (RandDouble(0.4) + 0.8);
>>>>>>> 17deda5118fcb09193b138e7a4a433c3e5a9407a
}