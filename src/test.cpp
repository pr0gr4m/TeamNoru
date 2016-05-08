#include <iostream>
#include <ctime>
#include "monster.h"

using namespace std;

int main()
{
	Monster mon1(10), mon2(11);

	srand((unsigned int)time(NULL));

	while (true)
	{
		cout << endl;
		cout << "***** mon1's status *****" << endl;
		mon1.printStatus();
		cout << "***** mon2's status *****" << endl;
		mon2.printStatus();

		cout << "***** attack each other *****" << endl;
		mon2.beatenDamage(mon1.attackDamage());
		if (mon2.isDie()) {
			cout << "mon2 is dead" << endl;
			break;
		}
		mon1.beatenDamage(mon2.attackDamage());
		if (mon1.isDie()) {
			cout << "mon1 is dead" << endl;
			break;
		}
	}

	return 0;
}