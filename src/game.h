/*
 * ���� : game.h
 * ���� : ���� ���� �Լ� ����
 * ���� : �ڰ���
 */

#pragma once
#ifndef _GAME_H
#define _GAME_H

// ���� ���� �Լ�
void gameScreen(void);

// ����Ű �̵� �Լ�
void Move(int dir);

extern int nx, ny;
extern int nStage;

#endif