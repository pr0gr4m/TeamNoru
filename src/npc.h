/*
 * 파일 : npc.h
 * 내용 : NPC 클래스 선언
 * 제작 : 최세일
 */

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

extern NPC1 n1;
extern NPC2 n2;
extern NPC3 n3;
extern NPC4 n4;
extern NPC5 n5;
extern NPC6 n6;
extern NPC7 n7;

#endif