#include "player.h"
#include <fstream>
#include <iostream>
#include "npc.h"
#include "map.h"
#include "game.h"
#include "fileIO.h"

bool SaveGame()
{
	using std::ios;
	using std::ofstream;

	ofstream fo(fileName, ios::out | ios::binary);

	if (!fo.is_open())
		return false;

	fo.write((char*)&p, sizeof(p));
	fo.write((char*)&nx, sizeof(nx));
	fo.write((char*)&ny, sizeof(ny));
	fo.write((char*)&nStage, sizeof(nStage));
	fo.write((char*)&n1, sizeof(n1));
	fo.write((char*)&n2, sizeof(n2));
	fo.write((char*)&n3, sizeof(n3));
	fo.write((char*)&n4, sizeof(n4));
	fo.write((char*)&n5, sizeof(n5));
	fo.write((char*)&n6, sizeof(n6));
	fo.write((char*)&n7, sizeof(n7));
	fo.write((char*)map, sizeof(map));

	fo.close();
	return true;
}

bool LoadGame()
{
	using std::ios;
	using std::ifstream;

	ifstream fi(fileName, ios::in | ios::binary);

	if (!fi.is_open())
		return false;

	fi.read((char*)&p, sizeof(p));
	if (p.getWeaponNum() != -1)		// setting pointer
		p.setWeapon();
	if (p.getArmorNum() != -1)
		p.setArmor();
	fi.read((char*)&nx, sizeof(nx));
	fi.read((char*)&ny, sizeof(ny));
	fi.read((char*)&nStage, sizeof(nStage));
	fi.read((char*)&n1, sizeof(n1));
	fi.read((char*)&n2, sizeof(n2));
	fi.read((char*)&n3, sizeof(n3));
	fi.read((char*)&n4, sizeof(n4));
	fi.read((char*)&n5, sizeof(n5));
	fi.read((char*)&n6, sizeof(n6));
	fi.read((char*)&n7, sizeof(n7));
	fi.read((char*)map, sizeof(map));

	fi.close();
	return true;
}