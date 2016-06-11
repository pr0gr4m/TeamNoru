#include <iostream>
#include <ctime>
#include "monster.h"
#include "map.h"
#include "lib.h"
#include "game.h"
#include "player.h"

using namespace std;

int main()
{
	setConsoleSize();
	Player p("¿Ã∏ß");
	p.Lvup();
	p.statuschange();

	return 0;
}