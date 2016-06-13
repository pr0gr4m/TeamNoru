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

class NPC2
{
private:
	char str[STR_NUM][MAX_LEN];
	int flag;
public:
	NPC2();
	void Dialogue();
};

class NPC3
{
private:
	char str[STR_NUM][MAX_LEN];
	int flag;
public:
	NPC3();
	void Dialogue();
};

class NPC4
{
private:
	char str[STR_NUM][MAX_LEN];
	int flag;
public:
	NPC4();
	void Dialogue();
};

class NPC5
{
private:
	char str[STR_NUM][MAX_LEN];
	int flag;
public:
	NPC5();
	void Dialogue();
};

class NPC6
{
private:
	char str[STR_NUM][MAX_LEN];
	int flag;
public:
	NPC6();
	void Dialogue();
};

class NPC7
{
private:
	char str[STR_NUM][MAX_LEN];
	int flag;
public:
	NPC7();
	void Dialogue();
};

#endif