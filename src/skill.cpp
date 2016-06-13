#include "skill.h"
#include "lib.h"
#include "player.h"
#include <cstring>

extern Skill * skList[10];

int SkillDamage(int i)
{
	if (i >= 6 && i <= 8)
	{
		p.HealAP(skList[i]->Amount(0));
		return 0;
	}
	return skList[i]->Amount(p.attackDamage());
}

Skill::Skill(const char *n, short t, short lev)
	: type(t), level(lev)
{
	std::strcpy(name, n);
}

// 데미지 : (100 * 스킬 레벨) * (1 ~ 1.2)
int Skill::Amount(int tmp) const
{
	return (100 * level) * (RandDouble(0.2) + 1);
}

// 코스트 : 레벨 * 10
int Skill::Cost() const
{
	return level * 10;
}

// 데미지 : 스킬 레벨 * 일반 공격 데미지
int Super::Amount(int dmg) const
{
	double pow = Level() == 1 ? 1.5 : Level();
	return dmg * pow;
}

int Super::Cost() const
{
	int pow;

	if (Level() == 1)
		pow = 10;
	else if (Level() == 2)
		pow = 25;
	else if (Level() == 3)
		pow = 40;
	return Level() * pow;
}

// 회복량 : 스킬레벨 * 30
int Heal::Amount(int tmp) const
{
	return Level() * 30;
}

int Heal::Cost() const
{
	return Level() * 15;
}

// 데미지 : 0 ~ 199
int Gamble::Amount(int tmp) const
{
	return RandInt(200);
}

// 소모량 : 0 ~ 49
int Gamble::Cost() const
{
	return RandInt(50);
}