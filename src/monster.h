#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H

#include <iostream>
#include "lib.h"

/*
 * 클래스 : Monster
 * 생성자 : 이름과 레벨을 무조건 전달받음
 *			스탯을 고정으로 조정하고 싶으면 인자로 전달 (디폴트 0이면 자동 계산)
 * 비고 : 순수 가상 클래스
 */
class Monster
{
public:
	// 생성자
	Monster(const char *n, int lev,
		int dmg = 0, int dfs = 0);
	// 죽었는지 확인
	bool isDie() const { return ((HP > 0) ? false : true); }
	// 공격할 데미지 계산
	virtual int attackDamage() const;
	// 받을 데미지 계산
	int beatenDamage(int dmg);
	// 상태 출력 순수 가상 함수
	virtual void printStatus() const = 0;
	// 크리티컬 확인
	virtual bool isCritical() const { return RandInt(8) == 0; }
	// 죽었을 때 경험치 량
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

#endif