#pragma once

class player
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
	char buf[BUF_SIZE];
public:
	player();
	~player();
	void initializig();
	int nHp;//���� hp
	int nAP;//���� ap
	int nexp;//���� ����ġ
	void Setstr(int nstr);//���߰�
	void Setluck(int nluck);//���߰�
	void Setdex(int ndex);//dex�߰�
	void Sethealth(int nhealth);//ü���߰�
	void Sethp();//�� hp��ȭ+ hp��ȭ����ŭ ���� hp�߰�
	void Setap();//�� ap��ȭ + ap ��ȭ����ŭ ���� ap �߰�
	void Lvup();//������
	int pattack();//�������ݷ�
	int pdefense();//��������
	bool critical();//ũ��Ƽ��Ȯ��
	void statuschange();//�������� ���ݺй�
	virtual int attackDamage();// ������ ������ ���
	int beatenDamage(int dmg);// ���� ������ ���
	int HealHP(int hp);// ȸ���� hp���
	int HealAP(int ap);//ȸ���� ap���
	void Getexp(int pexp);//exp���
	enum { SKILL_NUM = 10, ITEM_NUM=10 };
	int sk_list[SKILL_NUM];
	int item_list[ITEM_NUM];
};

