/*
 * 파일 : map.h
 * 내용 : 맵 선언
 * 제작 : 최세일
 */

#pragma once
#ifndef _MAP_H
#define _MAP_H

enum { numOfMap = 8, y_size = 26, x_size = 41 };

// 맵 선언
extern char map[numOfMap][y_size][x_size];

// 맵 출력 함수
void mapDraw(int);
void testMap();

#endif