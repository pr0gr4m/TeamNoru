#pragma once
#ifndef _SKILL_H
#define _SKILL_H

#include "lib.h"

static const int SK_TYPE = 4;
static const char *sk_name[SK_TYPE] = { "강타", "몰아치기", "회복", "도박" };
static const int SKILL_NUM = 10;

// 스킬 사용
int SkillDamage(int i);

/*
 * 클래스 : Skill
 * 생성자 : 스킬 이름, 스킬 타입, 스킬 레벨을 전달받음
 * 비고 : 부모 클래스
 */
class Skill
{
public:
	Skill(const char *n, short t, short lev = 1);
	// 스킬 공격/회복력 수치. 인자 dmg는 중첩 공격을 위함
	virtual int Amount(int tmp = 0) const;
	// 스킬 AP 코스트
	virtual int Cost() const;
	// 스킬 타입
	short Type() const { return type; }
	// 스킬 레벨
	short Level() const { return level; }
private:
	enum { NAME_LEN = 20 };
	char name[NAME_LEN];
	short type, level;
};

/*
 * 클래스 : Smite
 * 생성자 : 레벨을 전달받아서 기초 클래스 초기화
 * 설명 : 고정 데미지
 */
class Smite : public Skill
{
public:
	Smite(short lev = 1)
		: Skill(sk_name[0], ATTK, lev) { }
};

/*
 * 클래스 : Super
 * 생성자 : 레벨을 전달받아서 기초 클래스 초기화
 * 설명 : 중첩 데미지
 */
class Super : public Skill
{
public:
	Super(short lev = 1)
		: Skill(sk_name[1], ATTK, lev) { }
	// 일반 공격 데미지를 인자로 전달받아서 배로 바꿔줌
	int Amount(int dmg) const;
	int Cost() const;
};

/*
 * 클래스 : Heal
 * 생성자 : 레벨을 전달받아서 기초 클래스 타입 회복으로 초기화
 * 설명 : 회복 스킬
 */
class Heal : public Skill
{
public:
	Heal(short lev = 1)
		: Skill(sk_name[2], HEAL, lev) { }
	// 회복량
	int Amount(int tmp = 0) const;
	int Cost() const;
};

/*
 * 클래스 : Gamble
 * 생성자 : 레벨을 전달받아서 기초 클래스 초기화
 * 설명 : 랜덤 데미지, 랜덤 코스트
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