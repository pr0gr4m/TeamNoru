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

// 콘솔 화면에서 커서 x, y 좌표로 이동
void gotoxy(int x, int y);

// 콘솔 사이즈 200 * 60으로 변경
void setConsoleSize(void);

// 화면 지움
void clrscr(void);

// 첫 번째 인자 글자 색, 두 번째 인자 배경 색 지정
void setColor(int colFrt = LIGHTGRAY, int colBck = BLACK);

// 입력 버퍼 비움
void ClearReadBuff(void);

// 랜덤 넘버 시드
inline void SetRand(void) { srand((unsigned int)time(NULL)); }

// 0 이상 n 미만의 랜덤 정수 생성
inline int RandInt(int n) { return rand() % n; }

// 0 ~ n 사이의 랜덤 실수 생성
inline double RandDouble(double n) { return (double)rand() / RAND_MAX * n; }

#endif