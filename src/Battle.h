#pragma once
#include "monster.h"
//already included iostream and lib.h!
class Battle
{
public:
	Battle(Monster&);
	void BattleSystem();
	~Battle();
	bool ShowInventory();
	bool ShowSkills();
	void AIBattle();
	void Boxscreen();
	void Battlelog(const char* Format, ...);
	int BattleMenu();
	bool Run();
	void GAMEOVER();
	void playerbeaten();
	void monsterbeaten();
private:
	char* Log[6];
	int m_logcounter = 0;
	Monster& monster;
};

