#include "player.h"
#include <ctime>
#include <cstdlib>

player::player()
{
}


player::~player()
{
}
void player::Setstr(int nstr){
	str += nstr;
}
void player::Setluck(int nluck){
	luck += nluck;
}
void player::Setdex(int ndex){
	dex += ndex;
}
void player::Sethealth(int nhealth){
	health += nhealth;
}
void player::Setitem(int *nitem){//변경사항만 처리
	for (int i = 0; i < 7; i++)
		item[i] += nitem[i];
}
void player::Sethp(){
	float hp = health * 4 + str*1.5;
	HP = (int)hp;
}
void player::Setap(){
	float ap = str*1.5 + dex * 2;
	AP = (int)ap;
}
int player::pattack(){
	srand(time(NULL));
	float pattack = str*2.5 - (rand() % str + 1);
	return (int)pattack;
}
int player::pdefense(){
	float pdefense = str*1.5;
	return (int)pdefense;
}
bool player::critical(){
	if ((dex*1.5 + luck * 2) > (rand() % 100 + 1))
		return true;
}