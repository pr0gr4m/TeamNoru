/*
 * ���� : menu.cpp
 * ���� : �޴� ��� �� �˰���
 * ���� : �����, �ڰ���
 */

#pragma once
#ifndef _MENU_H
#define _MENU_H

enum { STAT = 0, WITEM, HITEM, HSKILL, SAVE, EXIT };

// �޴� ��� �Լ�
void printMenu();

// �޴� ���� �Լ�
void chooseMenu();

#endif