#pragma once
#ifndef _NPC_H
#define _NPC_H

static const int MAX_LEN = 80;
static const int STR_NUM = 5;

class NPC1
{
private:
	char str[STR_NUM][MAX_LEN];
	int flag;
public:
	NPC1();
	void Dialogue();
};

#endif