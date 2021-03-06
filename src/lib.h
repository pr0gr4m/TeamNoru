/*
 * 파일 : lib.h
 * 내용 : 라이브러리 함수 선언 및 정의
 * 제작 : 박강민
 */

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

enum { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77 };

enum { ATTK, DEF, HEAL };

enum CURSOR_TYPE { NOCURSOR, SOLIDCURSOR, NORMALCURSOR };

static const int BUF_LEN = 256;

// 콘솔 화면에서 커서 x, y 좌표로 이동
void gotoxy(int x, int y);

// 콘솔 사이즈 140 * 52으로 변경
void setConsoleSize(void);

// 콘솔 사이즈 130 * 60으로 지정
void bigConsoleSize(void);

// 화면 지움
void clrscr(void);

// 버퍼 없이 키 입력 받음
int getKey(void);

// 커서 타입 지정 (디폴트시 안보임)
void setCursorType(CURSOR_TYPE type = NOCURSOR);

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

void Delay(int n);

#endif