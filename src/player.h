#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "skill.h"
#include "item.h"

class Player
{
private:
	int str;
	int luck;
	int dex;
	int health;
	int HP;//�����ִ� hp
	int AP;//���� �ִ�ap
	int item[7];
	int Lv;
	int exp;
	int sp;
	enum{ NAME_LEN = 20, BUF_SIZE = 256 };
	char name[NAME_LEN];

	void initializig();

public:
	Player();	// �ҷ������ ����Ʈ ������
	Player(const char *n);	// �̸� �Է¹޴� ������
	int nHp;	//���� hp
	int nAP;	//���� ap
	int nexp;	//���� ����ġ
	void Setstr(int nstr);	// ���ڷ� ���޹��� ���ڸ�ŭ ���߰�
	void Setluck(int nluck);	// ���ڷ� ���޹��� ���ڸ�ŭ ���߰�
	void Setdex(int ndex);	// dex�߰�
	void Sethealth(int nhealth);	// ü���߰�
	void Sethp();	//�� hp��ȭ + hp��ȭ����ŭ ���� hp�߰�
	void Setap();	//�� ap��ȭ + ap ��ȭ����ŭ ���� ap �߰�
	void Lvup();//������
	int pattack();//�������ݷ�
	int pdefense();//��������
	bool critical();//ũ��Ƽ��Ȯ��
	void statuschange();//�������� ���ݺй�
	int attackDamage();// ������ ������ ���
	int beatenDamage(int dmg);// ���� ������ ���
	int HealHP(int hp);// ȸ���� hp���
	int HealAP(int ap);//ȸ���� ap���
	void Getexp(int pexp);//exp���

	int sk_list[SKILL_NUM];
	int item_list[ITEM_NUM];
};

#endif