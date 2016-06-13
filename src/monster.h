#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H

#include <iostream>
#include "lib.h"

// 몬스터 타입
enum { NORM, AGGR, DEFN };

static const int MON_TYPE = 7;
static const char *mon_name[MON_TYPE] = { "블랙하운드", "거대사마귀", "방사두더지", "데스클로", "뮤턴트플라워", "구울", "검은구체" };
static const int BOSS_LEVEL = 30;

/*
 * 클래스 : Monster
 * 생성자 : 레벨을 무조건 전달받음
 *			타입 지정을 하면 고정 스탯 부여 가능
 * 비고 : 순수 가상 클래스
 */
class Monster
{
public:
	enum { NAME_LEN = 20, SKILL_NUM = 10, FILE_LEN = 30 };
	// 생성자
	Monster(int lev, int val = 0, short type = NORM);
	// 죽었는지 확인
	bool isDie() const { return ((HP > 0) ? false : true); }
	// 공격할 데미지 계산
	virtual int attackDamage() const;
	// 받을 데미지 계산
	int beatenDamage(int dmg);
	// 회복할 데미지 계산
	int HealHP(int hp);
	// 상태 출력 가상 함수
	virtual void printStatus() const;
	// 크리티컬 확인 순수 가상 함수
	virtual bool isCritical() const = 0;
	// 죽었을 때 경험치 량
	int Exp() const;
	// 아스키 아트 출력
	bool printASCII() const;
	// 현재 HP 반환
	int getHP() const { return HP; }
	// 현재 AP 반환
	int getAP() const { return AP; }
	// 최대 HP 반환
	int getMAXHP() const { return MAXHP; }
	// AP 깎임
	void subAP(int cost) { AP -= cost; }
	// 스킬 리스트
	int sk_list[SKILL_NUM];
	// 이름
	char name[NAME_LEN];
protected:
	int defensivePower() { return DFS; }
private:
	int level;
	int HP, AP, DMG, DFS;
	int MAXHP;
};

/*
 * 클래스 : LowMonster
 * 생성자 : 레벨을 반드시 입력받아서 기초 클래스 초기화
 * 오버라이딩 : 크리티컬 여부 함수 동적 바인딩
 * 레벨 제한 : 1 ~ 10
 * 이름 : 몬스터 타입에 따라 정해짐 (블랙하운드, 거대사마귀, 방사두더지)
 */
class LowMonster : public Monster
{
public:
	// 생성자
	LowMonster(int lev, int val = 0, short type = NORM);
	bool isCritical() const { return RandInt(8) == 0; }
};

/*
 * 클래스 : HighMonster
 * 생성자 : 레벨을 반드시 입력받아서 기초 클래스 초기화
 * 오버라이딩 : 공격함수, 크리티컬 함수
 * 레벨제한 : 11 ~ 20
 * 이름 : 몬스터 타입에 따라 정해짐 (데스클로, 뮤턴트플라워, 구울)
 */
class HighMonster : public Monster
{
public:
	HighMonster(int lev, int val = 0, short type = NORM);
	int attackDamage() const;
	bool isCritical() const { return RandInt(7) == 0; }
};

/*
 * 클래스 : BossMonster
 * 생성자 : 디폴트 생성
 * 오버라이딩 : 공격함수, 크리티컬 함수
 * 보스 레벨 : 30
 * 이름 : 검은 구체
 */
class BossMonster : public Monster
{
public:
	BossMonster();
	int attackDamage() const;
	bool isCritical() const { return RandInt(5) == 0; }
};

#endif