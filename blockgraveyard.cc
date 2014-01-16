
#include "blockgraveyard.h"
#include <vector>
#include <iostream>

/////////////// Debug Functions ///////////////////

std::ostream& operator<< (std::ostream& os,  BlockGhost &b) {
	
	std::cout << '(' << b.level << ',' << b.yBot << ',' << b.yTop << ')';
	return os;
}

////////////// Contruct Destruct ///////////////////

BlockGraveyard::BlockGraveyard() {}


BlockGraveyard::~BlockGraveyard(){
	lst.clear();
}

////////////// Ghost Handlers /////////////////////

void BlockGraveyard::addGhost(BlockGhost b) {
	lst.push_back(b);
}

int BlockGraveyard::notifyGhosts(int n) {
	std::vector<BlockGhost>::iterator it = lst.begin();
	int sumPoints = 0;
	while(it != lst.end() && !lst.empty()) {
		// if n smaller than yBot
		if (n < it->yBot) {
			it->yBot--;
			it->yTop--;
		}
		// if n [yBot , yTop]
		else if (n >= it->yBot && n <= it->yTop) {
			it->yTop--;
		}
		if (it->yTop < it->yBot) {
			sumPoints += (it->level + 1) * (it->level + 1);
			lst.erase(it);
		}
		else {
			it++;
		}
	}
	return sumPoints;
}

///////////////// Debug Friend ////////////////////////
	


std::ostream& operator<< (std::ostream& os,  BlockGraveyard &g) {
	for (std::vector<BlockGhost>::iterator it = (g.lst).begin() ; it != (g.lst).end() ; it++) {
		std::cout << '(' << it->level << ',' << it->yBot << ',' << it->yTop << ')';
	}

	return os;
}



