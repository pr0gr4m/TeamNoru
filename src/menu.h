/*
 * 파일 : menu.cpp
 * 내용 : 메뉴 출력 및 알고리즘
 * 제작 : 김민주, 박강민
 */

#pragma once
#ifndef _MENU_H
#define _MENU_H

enum { STAT = 0, WITEM, HITEM, HSKILL, SAVE, EXIT };

// 메뉴 출력 함수
void printMenu();

// 메뉴 선택 함수
void chooseMenu();

#endif