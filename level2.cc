#include "level2.h"

#include <cstdlib>
#include "block.h"
#include "blocks.h"
#include "PRNG.h"

Level2::Level2(){}

Block * Level2::getBlock(){
	int n = prng() % 7;
	switch(n) {
		case 0:
			return new IBlock();
		case 1:
			return new JBlock();
		case 2:
			return new LBlock();
		case 3:
			return new SBlock();
		case 4:
			return new ZBlock();
		case 5:
			return new OBlock();
		case 6:
			return new TBlock();
	}
	
}
Level2::~Level2(){}
