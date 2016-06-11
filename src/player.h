#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "skill.h"
#include "item.h"

class Player
{
private:
	int str;
	int luck;
	int dex;
	int health;
	int HP;//현재최대 hp
	int AP;//현재 최대ap
	int item[7];
	int Lv;
	int exp;
	int sp;
	enum{ NAME_LEN = 20, BUF_SIZE = 256 };
	char name[NAME_LEN];

	void initializig();

public:
	Player();	// 불러오기용 디폴트 생성자
	Player(const char *n);	// 이름 입력받는 생성자
	int nHp;	//현재 hp
	int nAP;	//현재 ap
	int nexp;	//현재 경험치
	void Setstr(int nstr);	// 인자로 전달받은 숫자만큼 힘추가
	void Setluck(int nluck);	// 인자로 전달받은 숫자만큼 운추가
	void Setdex(int ndex);	// dex추가
	void Sethealth(int nhealth);	// 체력추가
	void Sethp();	//총 hp변화 + hp변화량만큼 현재 hp추가
	void Setap();	//총 ap변화 + ap 변화량만큼 현재 ap 추가
	void Lvup();//레벨업
	int pattack();//순수공격력
	int pdefense();//순수방어력
	bool critical();//크리티컬확인
	void statuschange();//레벨업시 스텟분배
	int attackDamage();// 공격할 데미지 계산
	int beatenDamage(int dmg);// 받을 데미지 계산
	int HealHP(int hp);// 회복할 hp계산
	int HealAP(int ap);//회복할 ap계산
	void Getexp(int pexp);//exp계산

	int sk_list[SKILL_NUM];
	int item_list[ITEM_NUM];
};

#endif