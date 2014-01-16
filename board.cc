#include "board.h"
#include "block.h"
#include "blocks.h"
#include "scoreboard.h"
#include "textdisplay.h"
#include "level.h"
#include "blockgraveyard.h"
#include "window.h"


///////////////// CONSTRUCTOR DESTROCTOR /////////////////

Board::Board() : grave(new BlockGraveyard){
	grid = new bool*[18];
	for (int i = 0 ; i < 18 ; i++) {
		grid[i] = new bool[10];
	}
	for (int i = 0 ; i < (15 + 3) ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			grid[i][j] = false;
		}
	}
	for (int i = 0 ; i < 10 ; i++) {
		heights[i] = 0;
	}
	for (int i = 0 ; i < 18 ; i++) {
		rows[i] = 0;
	}
}

Board::~Board(){
	for(int i = 0 ; i < 18 ; i++) {
		delete [] this->grid[i];
	}
	delete [] grid;
	delete grave;
}


///////////////// BLOCK PLACING METHODS //////////////////

State Board::place(const Block &b, int x, int y) { // 0 is false 1 is true
	Point *p = b.getBody();
	if (x < 0 || y < 0 || x > 10 || y > 17) { // out of bounds
		return OUT;
	}
	if (b.getWidth() + x > 10) {
		return OUT;
	}
	for (int i = 0 ; i < 4 ; i++) {
		if (grid[p[i].y + y][p[i].x + x]) {
			return BAD;
		}
	}
	//	std::cout << *this <<std::endl; // delete this
	return OK;
}

void Board::set(const Block &b, int x, int y) { 
	Point *p = b.getBody();
	for (int i = 0 ; i < 4 ; i++) {
		grid[p[i].y + y][p[i].x + x] = true;
		// update heights
		if (p[i].y + y + 1> heights[p[i].x + x]) {
			heights[p[i].x + x] = p[i].y + y + 1;
		}
		// update rows
		rows[p[i].y + y]++;
	}
	BlockGhost h = {Level::getLevel(), y, y + b.getHeight() - 1};
	grave->addGhost(h);
//	std::cout << *this; // delete this
}

int Board::dropHeight(const Block &b, int x) const{
	int max = 0;
	int *skirt = b.getSkirt();
	for (int i = 0 ; i < b.getWidth() ; i++) {
		if (heights[x + i] - skirt[i] > max ) {
			max = heights[x + i] - skirt[i];
		}
	}
	std::cout << "MAX is " << max << std::endl;
	return max;
}

int Board::dropHeight(const Block &b, int x, int y) const {
	int max = 0;
	int *skirt = b.getSkirt();
	for (int i = 0 ; i < b.getWidth() ; i++) {
		for (int j = y ; j >= 0 ; j--) {
//			std::cout << "J is:" << j << std::endl;
			if (grid[j][x + i]) {
				std::cout << "HELLO : " << j + 1 - skirt[i] << std::endl; 
				if (j + 1 - skirt[i] > max) {
					max = j + 1 - skirt[i];
				}
				break;
			}
		}
	}
	std::cout << "MAX is " << max << std::endl;
	return max;
}


bool Board::clearRows() {
	// for all rows, find filled rows;
	// notify graveyard, notify displays
	bool cleared = false;
	ScoreBoard *s;
	TextDisplay *t;
	int i = 0;
	while ( i < 18 ) {
		if (rows[i] == 10) {
			cleared = true;
			delete [] grid[i];
			// update score
			s = ScoreBoard::getInstance();
			s->addScore((Level::getLevel() + 1) * (Level::getLevel() + 1));
			// notify graveyard
			s->addScore(grave->notifyGhosts(i));
 			// update display
			t = TextDisplay::getInstance();
			t->clearRow(i);
			int j = i;
			for (j = i ; j < 17 ; j++) {
				// for grid
				grid[j] = grid[j+1];
				// for rows
				rows[j] = rows[j + 1];
			}
			// new top row
			grid[j] = new bool[10];
			rows[j] = 0;
			// initialzie new row and change heights
			for (int k = 0 ; k < 10 ; k++) {
				// set new row
				grid[j][k] = false;
				// change height
				if (heights[k] > i) { // if higher then just - 1
					heights[k]--;
				}
				else { // if the summit is exactly the row of clear, then recalculate
					int l = i;
					for (l = i ; l > 0 ; l--) { // goes down to see when it hits true
						if (grid[l][k] == true) {
							break;
						}
					}
					heights[k] = l;
				}
			}
		}
		else {
			i++;
		}
	}
	return cleared;
	
}

//////////////////////// CONST FUNCTIONS ///////////////////


//////////////////// DEBUGGING METHODS /////////////////////
		

std::ostream& operator<< (std::ostream& os, const Board &b) {
	for (int i = 17 ; i >= 0 ; i--) {
		os << b.rows[i];
		for (int j = 0 ; j < 10 ; j++) {
			if (b.grid[i][j]) {
				os << 'X';
			}
			else {
				os << '.';
			}
		}
		os << i << std::endl;
	}
	os << "Heights : ";
	for (int i = 0 ; i < 10; i++) {
		os << b.heights[i] << ',';
	}
	os << std::endl;
	
	return os;
}


