#include <iostream>
#include <cstring>
#include "lib.h"
#include "monster.h"

Monster::Monster(int lev, int val, short type)	
	: level(lev)
{
	int base = level / 10 + 1;
	MAXHP = HP = base * 30 + level * 10;
	AP = base * 10 + level * 5;
	DMG = type == AGGR ? val : base * 20 + level * 5;
	DFS = type == DEFN ? val : base * 10 + level * 3;
	for (int i = 0; i < SKILL_NUM; i++)
		sk_list[i] = 0;
}

int Monster::attackDamage() const
{ 
	double dmg = DMG * (RandDouble(0.5) + 0.7);

	// 순수 가상함수 isCritical
	if (isCritical())
		return dmg * 2;
	else
		return dmg;
}

// 회복 스킬을 사용할 때 회복하고 회복한 HP 반환
int Monster::HealHP(int hp)
{
	if (hp > MAXHP - HP)
		HP = MAXHP;
	else
		HP += hp;
	return HP;
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

// 상태 출력 임시 함수
void Monster::printStatus() const
{
	using std::cout;
	using std::endl;
	cout << "이름 : " << name << endl;
	cout << "HP : " << HP << ", AP : " << AP << endl;
	cout << "DMG : " << DMG << ", DFS : " << DFS << endl;
}

// 경험치 반환
int Monster::Exp() const
{
	int exp = level * 10;
	return exp * (RandDouble(0.4) + 0.8);
}

// 전달받은 배열에 보유중인 스킬 리스트 복사
void Monster::checkSkill(int *arr) const
{
	for (int i = 0; i < SKILL_NUM; i++)
		arr[i] = sk_list[i];
}

LowMonster::LowMonster(int lev, int val, short type) : Monster(lev, val, type)
{
	for (int i = 0; i < SKILL_NUM; i += 3)
	{
		if (RandInt(2))
			sk_list[i] = 1;
	}

	if (type == NORM)
		std::strcpy(name, mon_name[0]);
	else if (type == AGGR)
		std::strcpy(name, mon_name[1]);
	else if (type == DEFN)
		std::strcpy(name, mon_name[2]);
	else
	{
		std::cerr << "잘 못된 타입 인자" << std::endl;
		exit(EXIT_FAILURE);
	}
}

HighMonster::HighMonster(int lev, int val, short type) 
	: Monster(lev, val, type)
{
	for (int i = 1; i < SKILL_NUM; i += 3)
	{
		if (RandInt(2))
			sk_list[i] = 1;
	}

	if (type == NORM)
		std::strcpy(name, mon_name[3]);
	else if (type == AGGR)
		std::strcpy(name, mon_name[4]);
	else if (type == DEFN)
		std::strcpy(name, mon_name[5]);
	else
	{
		std::cerr << "잘 못된 타입 인자" << std::endl;
		exit(EXIT_FAILURE);
	}
}

int HighMonster::attackDamage() const
{
	return Monster::attackDamage() * 1.2;
}

BossMonster::BossMonster()
	: Monster(BOSS_LEVEL)
{
	for (int i = 2; i < SKILL_NUM; i += 3)
		sk_list[i] = 1;
	std::strcpy(name, mon_name[6]);
}

int BossMonster::attackDamage() const
{
	return Monster::attackDamage() * 1.5;
}