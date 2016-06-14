/*
 * 파일 : Battle.h
 * 내용 : 전투 클래스 선언
 * 제작 : 전성욱
 */

#pragma once
#ifndef _BATTLE_H
#define _BATTLE_H
#include "monster.h"
//already included iostream and lib.h!

enum { LOG_LEN = 256, LOG_NUM = 6 };

class Battle
{
public:
	Battle(Monster&);
	~Battle();
private:
	void BattleSystem();
	bool ShowInventory();
	bool ShowSkills();
	void AIBattle();
	void Boxscreen();
	int BattleMenu();
	bool Run();
	void GAMEOVER();
	void playerbeaten();
	void monsterbeaten();
	char Log[LOG_NUM][LOG_LEN];
	int m_logcounter = 0;
	void _gotoxy();
	Monster& monster;
};
#endif