#include "skill.h"
#include "lib.h"
#include <cstring>

Skill::Skill(const char *n, short t, short lev)
	: type(t), level(lev)
{
	std::strcpy(name, n);
}

int Skill::Amount() const
{
	return (100 * level) * (RandDouble(0.2) + 1);
}

int Skill::Cost() const
{
	return level * 10;
}

int Super::Amount(int dmg) const
{
	double pow = Level() == 1 ? 1.5 : Level();
	return dmg * pow;
}

int Super::Amount() const
{
	double pow;

	if (Level() == 1)
		pow = 
}

