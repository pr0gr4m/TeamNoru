#pragma once
#ifndef _LIB_H
#define _LIB_H

#include <iostream>
#include <ctime>

enum {
	BLACK = 0, BLUE, GREEN, CYAN, RED, MAGENTA = 5, PURPLE = 5,
	BROWN = 6, LIGHTGRAY, GRAY, LIGHTBLUE, 
	LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTMAGENTA = 13, LIGHTPURPLE = 13, YELLOW = 14, WHITE = 15
};

// �ܼ� ȭ�鿡�� Ŀ�� x, y ��ǥ�� �̵�
void gotoxy(int x, int y);

// �ܼ� ������ 200 * 60���� ����
void setConsoleSize(void);

// ȭ�� ����
void clrscr(void);

// ù ��° ���� ���� ��, �� ��° ���� ��� �� ����
void setColor(int colFrt = LIGHTGRAY, int colBck = BLACK);

// �Է� ���� ���
void ClearReadBuff(void);

// ���� �ѹ� �õ�
inline void SetRand(void) { srand((unsigned int)time(NULL)); }

// 0 �̻� n �̸��� ���� ���� ����
inline int RandInt(int n) { return rand() % n; }

// 0 ~ n ������ ���� �Ǽ� ����
inline double RandDouble(double n) { return (double)rand() / RAND_MAX * n; }

#endif