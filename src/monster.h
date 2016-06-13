#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H

#include <iostream>
#include "lib.h"

// ���� Ÿ��
enum { NORM, AGGR, DEFN };

static const int MON_TYPE = 7;
static const char *mon_name[MON_TYPE] = { "���Ͽ��", "�Ŵ�縶��", "���δ���", "����Ŭ��", "����Ʈ�ö��", "����", "������ü" };
static const int BOSS_LEVEL = 30;

/*
 * Ŭ���� : Monster
 * ������ : ������ ������ ���޹���
 *			Ÿ�� ������ �ϸ� ���� ���� �ο� ����
 * ��� : ���� ���� Ŭ����
 */
class Monster
{
public:
	enum { NAME_LEN = 20, SKILL_NUM = 10, FILE_LEN = 30 };
	// ������
	Monster(int lev, int val = 0, short type = NORM);
	// �׾����� Ȯ��
	bool isDie() const { return ((HP > 0) ? false : true); }
	// ������ ������ ���
	virtual int attackDamage() const;
	// ���� ������ ���
	int beatenDamage(int dmg);
	// ȸ���� ������ ���
	int HealHP(int hp);
	// ���� ��� ���� �Լ�
	virtual void printStatus() const;
	// ũ��Ƽ�� Ȯ�� ���� ���� �Լ�
	virtual bool isCritical() const = 0;
	// �׾��� �� ����ġ ��
	int Exp() const;
	// �ƽ�Ű ��Ʈ ���
	bool printASCII() const;
	// ���� HP ��ȯ
	int getHP() const { return HP; }
	// ���� AP ��ȯ
	int getAP() const { return AP; }
	// �ִ� HP ��ȯ
	int getMAXHP() const { return MAXHP; }
	// AP ����
	void subAP(int cost) { AP -= cost; }
	// ��ų ����Ʈ
	int sk_list[SKILL_NUM];
	// �̸�
	char name[NAME_LEN];
protected:
	int defensivePower() { return DFS; }
private:
	int level;
	int HP, AP, DMG, DFS;
	int MAXHP;
};

/*
 * Ŭ���� : LowMonster
 * ������ : ������ �ݵ�� �Է¹޾Ƽ� ���� Ŭ���� �ʱ�ȭ
 * �������̵� : ũ��Ƽ�� ���� �Լ� ���� ���ε�
 * ���� ���� : 1 ~ 10
 * �̸� : ���� Ÿ�Կ� ���� ������ (���Ͽ��, �Ŵ�縶��, ���δ���)
 */
class LowMonster : public Monster
{
public:
	// ������
	LowMonster(int lev, int val = 0, short type = NORM);
	bool isCritical() const { return RandInt(8) == 0; }
};

/*
 * Ŭ���� : HighMonster
 * ������ : ������ �ݵ�� �Է¹޾Ƽ� ���� Ŭ���� �ʱ�ȭ
 * �������̵� : �����Լ�, ũ��Ƽ�� �Լ�
 * �������� : 11 ~ 20
 * �̸� : ���� Ÿ�Կ� ���� ������ (����Ŭ��, ����Ʈ�ö��, ����)
 */
class HighMonster : public Monster
{
public:
	HighMonster(int lev, int val = 0, short type = NORM);
	int attackDamage() const;
	bool isCritical() const { return RandInt(7) == 0; }
};

/*
 * Ŭ���� : BossMonster
 * ������ : ����Ʈ ����
 * �������̵� : �����Լ�, ũ��Ƽ�� �Լ�
 * ���� ���� : 30
 * �̸� : ���� ��ü
 */
class BossMonster : public Monster
{
public:
	BossMonster();
	int attackDamage() const;
	bool isCritical() const { return RandInt(5) == 0; }
};

#endif