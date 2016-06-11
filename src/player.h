#pragma once

class player
{
private:
	int str=3;
	int luck=1;
	int dex=3;
	int health=3;
	int HP;//현재최대 hp
	int AP;//현재 최대ap
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
	int nHp;//현재 hp
	int nAP;//현재 ap
	int nexp;//현재 경험치
	void Setstr(int nstr);//힘추가
	void Setluck(int nluck);//운추가
	void Setdex(int ndex);//dex추가
	void Sethealth(int nhealth);//체력추가
	void Setitem(int *nitem);//아이템 소지양 변화
	void Sethp();//총 hp변화+ hp변화량만큼 현재 hp추가
	void Setap();//총 ap변화 + ap 변화량만큼 현재 ap 추가
	void Lvup();//레벨업
	int pattack();//순수공격력
	int pdefense();//순수방어력
	bool critical();//크리티컬확인
	void statuschange();//레벨업시 스텟분배
	virtual int attackDamage();// 공격할 데미지 계산
	int beatenDamage(int dmg);// 받을 데미지 계산
	int HealHP(int hp);// 회복할 hp계산
	int HealAP(int ap);//회복할 ap계산
	void Getexp(int pexp);//exp계산
	void checkSkill(int *ar) const;// 스킬 리스트 체크
};

