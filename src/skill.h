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

#endif