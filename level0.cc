
#include "level0.h"
#include "block.h"
#include "blocks.h"
#include <cstring>

///////////// Constructor Destructor ////////////////////

Level0::Level0(std::string filename):in(0), filename(filename) {
	in = new std::ifstream;
	in->open(filename.c_str());
}

Level0::~Level0() {
	in->close();
	delete in;
}

//////////////// File handler ///////////////////

void Level0::restart() {
	in->close();
	in->open(filename.c_str());
}

////////////// Block Methods ////////////////////

Block * Level0::getBlock() {
	char c;

	*in >> c;
	if (in->eof()) {
		in->close();
		delete in;
		in = new std::ifstream;
		in->open(filename.c_str());
		*in >> c;
	}
	switch(c) {
		case 'I':
			return new IBlock();
		case 'J':
			return new JBlock();
		case 'L':
			return new LBlock();
		case 'S':
			return new SBlock();
		case 'Z':
			return new ZBlock();
		case 'O':
			return new OBlock();
		case 'T':
			return new TBlock();
	}
}
