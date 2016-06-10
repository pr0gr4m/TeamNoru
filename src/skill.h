<<<<<<< HEAD
#pragma once
#ifndef _SKILL_H
#define _SKILL_H

enum { ATTK, HEAL };

class Skill
{
public:
	Skill(const char *n, short t, short lev = 1);
	virtual int Amount() const;
	virtual int Cost() const;
	short Type() const { return type; }
	short Level() const { return level; }
private:
	enum { NAME_LEN = 20 };
	char name[NAME_LEN];
	short type, level;
};

class Smite : public Skill
{
public:
	Smite(short lev = 1)
		: Skill("강타", ATTK, lev) { }
};

class Super : public Skill
{
public:
	Super(short lev = 1)
		: Skill("몰아치기", ATTK, lev) { }
	int Amount(int dmg) const;
	int Cost() const;
};

class Heal : public Skill
{
public:
	Heal(short lev = 1)
		: Skill("회복", HEAL, lev) { }
	int Amount() const;
	int Cost() const;
};

class Gamble : public Skill
{
public:
	Gamble(short lev = 1)
		: Skill("도박", ATTK, lev) { }
	int Amount() const;
	int Cost() const;
};

=======
#pragma once
#ifndef _SKILL_H
#define _SKILL_H

class SKILL
{
public:
private:
	enum { NAME_LEN = 20 };
	char name[NAME_LEN];
	short type, level;
	int amount, cost;
};

>>>>>>> min
#endif