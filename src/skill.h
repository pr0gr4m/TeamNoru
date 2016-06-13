#pragma once
#ifndef _SKILL_H
#define _SKILL_H

#include "lib.h"

static const int SK_TYPE = 4;
static const char *sk_name[SK_TYPE] = { "��Ÿ", "����ġ��", "ȸ��", "����" };
static const int SKILL_NUM = 10;

// ��ų ���
int SkillDamage(int i);

/*
 * Ŭ���� : Skill
 * ������ : ��ų �̸�, ��ų Ÿ��, ��ų ������ ���޹���
 * ��� : �θ� Ŭ����
 */
class Skill
{
public:
	Skill(const char *n, short t, short lev = 1);
	// ��ų ����/ȸ���� ��ġ. ���� dmg�� ��ø ������ ����
	virtual int Amount(int tmp = 0) const;
	// ��ų AP �ڽ�Ʈ
	virtual int Cost() const;
	// ��ų Ÿ��
	short Type() const { return type; }
	// ��ų ����
	short Level() const { return level; }
private:
	enum { NAME_LEN = 20 };
	char name[NAME_LEN];
	short type, level;
};

/*
 * Ŭ���� : Smite
 * ������ : ������ ���޹޾Ƽ� ���� Ŭ���� �ʱ�ȭ
 * ���� : ���� ������
 */
class Smite : public Skill
{
public:
	Smite(short lev = 1)
		: Skill(sk_name[0], ATTK, lev) { }
};

/*
 * Ŭ���� : Super
 * ������ : ������ ���޹޾Ƽ� ���� Ŭ���� �ʱ�ȭ
 * ���� : ��ø ������
 */
class Super : public Skill
{
public:
	Super(short lev = 1)
		: Skill(sk_name[1], ATTK, lev) { }
	// �Ϲ� ���� �������� ���ڷ� ���޹޾Ƽ� ��� �ٲ���
	int Amount(int dmg) const;
	int Cost() const;
};

/*
 * Ŭ���� : Heal
 * ������ : ������ ���޹޾Ƽ� ���� Ŭ���� Ÿ�� ȸ������ �ʱ�ȭ
 * ���� : ȸ�� ��ų
 */
class Heal : public Skill
{
public:
	Heal(short lev = 1)
		: Skill(sk_name[2], HEAL, lev) { }
	// ȸ����
	int Amount(int tmp = 0) const;
	int Cost() const;
};

/*
 * Ŭ���� : Gamble
 * ������ : ������ ���޹޾Ƽ� ���� Ŭ���� �ʱ�ȭ
 * ���� : ���� ������, ���� �ڽ�Ʈ
 */
class Gamble : public Skill
{
public:
	Gamble(short lev = 1)
		: Skill(sk_name[3], ATTK, lev) { }
	int Amount(int tmp = 0) const;
	int Cost() const;
};

#endif