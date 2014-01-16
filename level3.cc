#include "level3.h"

#include <cstdlib>
#include "block.h"
#include "blocks.h"
#include "PRNG.h"

Level3::Level3(){}

Block * Level3::getBlock(){
	int n = prng() % 9;
	switch(n) {
		case 0:
			return new IBlock();
		case 1:
			return new JBlock();
		case 2:
			return new LBlock();
		case 3: case 4:
			return new SBlock();
		case 5: case 6:
			return new ZBlock();
		case 7:
			return new OBlock();
		case 8:
			return new TBlock();
	}
	
}
Level3::~Level3(){}
