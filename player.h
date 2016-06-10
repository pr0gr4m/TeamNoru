#pragma once

class player
{
private:
	int str=3;
	int luck=1;
	int dex=3;
	int health=3;
	int HP;
	int AP;
	int item[7];
public:
	player();
	~player();
	int nHp;
	int nAP;
	void Setstr(int nstr);
	void Setluck(int nluck);
	void Setdex(int ndex);
	void Sethealth(int nhealth);
	void Setitem(int *nitem);
	void Sethp();
	void Setap();
	int pattack();
	int pdefense();
	bool critical();
};

