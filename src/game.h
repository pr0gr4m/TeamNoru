/*
 * 파일 : game.h
 * 내용 : 게임 구현 함수 선언
 * 제작 : 박강민
 */

#pragma once
#ifndef _GAME_H
#define _GAME_H

// 게임 진행 함수
void gameScreen(void);

// 방향키 이동 함수
void Move(int dir);

extern int nx, ny;
extern int nStage;

#endif