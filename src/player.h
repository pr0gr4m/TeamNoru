#pragma once

class player
{
private:
	int str=3;
	int luck=1;
	int dex=3;
	int health=3;
	int HP;//�����ִ� hp
	int AP;//���� �ִ�ap
	int item[7];
	int Lv=1;
	int exp=30;
	int sp=0;
protected:
	enum {SKILL_NUM = 10 };
	int sk_list[SKILL_NUM];
public:
	player();
	~player();
	int nHp;//���� hp
	int nAP;//���� ap
	int nexp;//���� ����ġ
	void Setstr(int nstr);//���߰�
	void Setluck(int nluck);//���߰�
	void Setdex(int ndex);//dex�߰�
	void Sethealth(int nhealth);//ü���߰�
	void Setitem(int *nitem);//������ ������ ��ȭ
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
	void checkSkill(int *ar) const;// ��ų ����Ʈ üũ
};

