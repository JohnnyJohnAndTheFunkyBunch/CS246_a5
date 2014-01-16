#include "level1.h"

#include "block.h"
#include "blocks.h"
#include <cstdlib>
#include "PRNG.h"


Level1::Level1(){}

Block * Level1::getBlock(){
	int n = prng() % 12;
	switch(n) {
		case 0: case 1:
			return new IBlock();
		case 2: case 3:
			return new JBlock();
		case 4: case 5:
			return new LBlock();
		case 6:
			return new SBlock();
		case 7:
			return new ZBlock();
		case 8: case 9:
			return new OBlock();
		case 10: case 11:
			return new TBlock();
	}
}
Level1::~Level1(){}
