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

	// ���� �����Լ� isCritical
	if (isCritical())
		return dmg * 2;
	else
		return dmg;
}

// ȸ�� ��ų�� ����� �� ȸ���ϰ� ȸ���� HP ��ȯ
int Monster::HealHP(int hp)
{
	if (hp > MAXHP - HP)
		HP = MAXHP;
	else
		HP += hp;
	return HP;
}

// ������ �Դ� ��ġ�� �޾Ƽ� ���� HP�� ��ȯ
int Monster::beatenDamage(int dmg)
{
	int calDmg = dmg - defensivePower();
	if (HP <= calDmg)
		HP = 0;
	else
		HP -= calDmg;
	return HP;
}

// ���� ��� �ӽ� �Լ�
void Monster::printStatus() const
{
	using std::cout;
	using std::endl;
	cout << "�̸� : " << name << endl;
	cout << "HP : " << HP << ", AP : " << AP << endl;
	cout << "DMG : " << DMG << ", DFS : " << DFS << endl;
}

// ����ġ ��ȯ
int Monster::Exp() const
{
	int exp = level * 10;
	return exp * (RandDouble(0.4) + 0.8);
}

// ���޹��� �迭�� �������� ��ų ����Ʈ ����
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
		std::cerr << "�� ���� Ÿ�� ����" << std::endl;
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
		std::cerr << "�� ���� Ÿ�� ����" << std::endl;
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