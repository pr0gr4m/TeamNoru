<<<<<<< HEAD
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

=======
#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H

#include <iostream>
#include "lib.h"

/*
 * Ŭ���� : Monster
 * ������ : �̸��� ������ ������ ���޹���
 *			������ �������� �����ϰ� ������ ���ڷ� ���� (����Ʈ 0�̸� �ڵ� ���)
 * ��� : ���� ���� Ŭ����
 */
class Monster
{
public:
	// ������
	Monster(const char *n, int lev,
		int dmg = 0, int dfs = 0);
	// �׾����� Ȯ��
	bool isDie() const { return ((HP > 0) ? false : true); }
	// ������ ������ ���
	virtual int attackDamage() const;
	// ���� ������ ���
	int beatenDamage(int dmg);
	// ���� ��� ���� ���� �Լ�
	virtual void printStatus() const = 0;
	// ũ��Ƽ�� Ȯ��
	virtual bool isCritical() const { return RandInt(8) == 0; }
	// �׾��� �� ����ġ ��
	int Exp() const;
private:
	enum { NAME_LEN = 20 };
	int defensivePower() { return DFS; }
private:
	char name[NAME_LEN];
	int level;
	int HP, AP, DMG, DFS;
};

class LowMonster : public Monster
{

};

class HighMonster : public Monster
{

};

class BossMonster : public Monster
{

};

>>>>>>> 17deda5118fcb09193b138e7a4a433c3e5a9407a
#endif