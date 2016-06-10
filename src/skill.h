#pragma once
#ifndef _SKILL_H
#define _SKILL_H

enum { ATTK, HEAL };

class Skill
{
public:
	Skill(const char *n, short t, short lev = 1);
private:
	enum { NAME_LEN = 20 };
	char name[NAME_LEN];
	short type, level;
};

class Smite : public Skill
{

};

class Super : public Skill
{

};

class Heal : public Skill
{

};

class Gamble : public Skill
{

};

#endif