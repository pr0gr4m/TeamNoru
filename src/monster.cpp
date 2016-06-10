<<<<<<< HEAD
#include <iostream>
#include <cstring>
#include "lib.h"
#include "monster.h"

Monster::Monster(const char *n, int lev,
	int dmg, int dfs)	: level(lev)
{
	strcpy(name, n);
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
<<<<<<< HEAD
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
=======
>>>>>>> min
	cout << "DMG : " << DMG << ", DFS : " << DFS << endl;
}

int Monster::Exp() const
{
	int exp = level * 10;
	return exp * (RandDouble(0.4) + 0.8);
<<<<<<< HEAD
>>>>>>> 17deda5118fcb09193b138e7a4a433c3e5a9407a
=======
>>>>>>> min
}