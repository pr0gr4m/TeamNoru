/*
 * ���� : map.h
 * ���� : �� ����
 * ���� : �ּ���
 */

#pragma once
#ifndef _MAP_H
#define _MAP_H

enum { numOfMap = 8, y_size = 26, x_size = 41 };

// �� ����
extern char map[numOfMap][y_size][x_size];

// �� ��� �Լ�
void mapDraw(int);
void testMap();

#endif