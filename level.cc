#include "level.h"
#include "levels.h"
#include <cstdlib>
#include <iostream> // delete later
#include "PRNG.h"

///////////////// GLOBAL Variables /////////////

const int maxLevel = 4;
const int minLevel = 0;

int Level::currLevel = 0;

PRNG Level::prng;

Level** Level::levels = new Level*[maxLevel + 1];

bool init = false;

//////////////// STATIC FUNCTIONS ////////////////

void Level::increaseLevel() {
	currLevel++;
	if (currLevel > maxLevel) {
		currLevel--;
	}
}

void Level::decreaseLevel() {
	currLevel--;
	if (currLevel < 0) {
		currLevel++;
	}
}


void Level::initLevels(int n, std::string s, int seed) {
	if (n > maxLevel) {
		currLevel = maxLevel;
	}
	else if ( n < minLevel) {
		currLevel = minLevel;
	}
	else {
		currLevel = n;
	}
	if (!init) {
		levels[0] = new Level0(s);
		levels[1] = new Level1;
		levels[2] = new Level2;
		levels[3] = new Level3;
		levels[4] = new Level4;
		atexit(cleanUp);
	}
	Level::prng.seed(seed);
	init = true;
}

void Level::cleanUp() {
		delete levels[0];
		delete levels[1];
		delete levels[2];
		delete levels[3];
		delete levels[4];

	delete [] levels;
}

void Level::restart() {}

int Level::getLevel() {
	return currLevel;
}

//////////////// VIRTUAL METHODS ///////////////
Level::Level() {}


Level::~Level() {}


Block * Level::getBlock() {}



