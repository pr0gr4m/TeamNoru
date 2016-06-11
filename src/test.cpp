#include <iostream>
#include <ctime>
#include "monster.h"
#include "map.h"
#include "lib.h"
#include "game.h"
#include "player.h"

using namespace std;

Player p("player");

int main()
{
	p.Lvup();
	gameScreen();
	return 0;
}