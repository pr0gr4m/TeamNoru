#pragma once
#ifndef _LIB_H
#define _LIB_H

enum {
	BLACK = 0, BLUE, GREEN, CYAN, RED, MAGENTA = 5, PURPLE = 5,
	BROWN = 6, LIGHTGRAY, GRAY, LIGHTBLUE, 
	LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTMAGENTA = 13, LIGHTPURPLE = 13, YELLOW = 14, WHITE = 15
};

void gotoxy(int x, int y);
void setConsoleSize(void);
void clrscr(void);
void setColor(int colFrt = LIGHTGRAY, int colBck = BLACK);
void ClearReadBuff(void);

#endif