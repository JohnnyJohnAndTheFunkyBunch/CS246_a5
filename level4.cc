#include "level4.h"

#include <cstdlib>
#include "block.h"
#include "blocks.h"
#include "PRNG.h"
Level4::Level4(){}

Block * Level4::getBlock(){
	Block *b = NULL;
	int n = prng() % 9;
	switch(n) {
		case 0:
			b = new IBlock();
			break;
		case 1:
			b = new JBlock();
			break;
		case 2:
			b = new LBlock();
			break;
		case 3: case 4:
			b = new SBlock();
			break;
		case 5: case 6:
			b = new ZBlock();
			break;
		case 7:
			b = new OBlock();
			break;
		case 8:
			b = new TBlock();
			break;
	}
	int skip = prng() % 3;
	if(!skip) {
		b->setSkip();
	}
	return b;
}


Level4::~Level4(){}
