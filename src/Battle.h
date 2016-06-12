#pragma once
#include "monster.h"
//already included iostream and lib.h!
class Battle
{
public:
	Battle(Monster&);
	void BattleSystem(Monster&);
	~Battle();
	bool ShowInventory(Monster& monster);
	bool ShowSkills(Monster& monster);
	void AIBattle(Monster&);
	void Boxscreen(Monster& monster);
	void Battlelog(Monster&monster,const char* Format, ...);
	int BattleMenu(Monster& monster);
	bool Run(Monster& monster);
private:
	const char* Log[6][100];
	int m_logcounter = 0;
};

