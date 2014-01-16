#include "textdisplay.h"
#include <iostream>
#include <cstdlib>

#include "block.h"
#include "point.h"
#include "scoreboard.h"
#include "level.h"

TextDisplay *TextDisplay::instance = 0;

TextDisplay *TextDisplay::getInstance() {
	if (!instance) {
		instance = new TextDisplay;
		atexit(cleanup);
	}
	return instance;
}

////////////////////// PUBLIC //////////////////
TextDisplay::TextDisplay() {
	grid = new char*[18];
	for (int i = 0 ; i < 18 ; i++) {
		grid[i] = new char[10];
	}
	for (int i = 0 ; i < 18 ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			grid[i][j] = ' ';
		}
	}
}

void TextDisplay::place(const char c, int x, int y) {
	grid[y][x] = c;
}

void TextDisplay::place(const Block &b, int x, int y) {
	Point *p = b.getBody();
	char c = b.getChar();
	for (int i = 0 ; i < 4 ; i++) {
		place(c, p[i].x + x, p[i].y + y);
	}
	
		
}
void TextDisplay::unplace(const Block &b, int x, int y) {
	Point *p = b.getBody();
	for (int i = 0 ; i < 4 ; i++) {
		place(' ', p[i].x + x, p[i].y + y);
	}
}

void TextDisplay::clearRow(int n) {
	delete [] grid[n];
	int i;
	for (i = n ; i < 17 ; i++) {
		grid[i] = grid[i + 1];
	}
	grid[i] = new char[10];
	for (int j = 0 ; j < 10 ; j++) {
		grid[i][j] = ' ';
	}
}

void TextDisplay::clearGrid() {
	for (int i = 0 ; i < 18 ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			grid[i][j] = ' ';
		}
	}
}
	
	


void TextDisplay::printAll(const Block *next, const Block *hold) const{
	printScore();
	printBoard();
	printNext(next);
	printHold(hold);
}
	
void TextDisplay::cleanup() {
	delete instance;
}

void TextDisplay::printDead() {
	for (int i = 0 ; i < 15 ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			grid[i][j] = 'X';
		}
	}
	grid[6][2] = ' ';
	grid[6][3] = ' ';
	grid[6][4] = ' ';
	grid[6][5] = ' ';
	grid[6][6] = ' ';
	grid[6][7] = ' ';

	grid[8][2] = ' ';
	grid[8][3] = ' ';
	grid[8][4] = ' ';
	grid[8][5] = ' ';
	grid[8][6] = ' ';
	grid[8][7] = ' ';
	
	grid[7][2] = ' ';
	grid[7][7] = ' ';
	
	grid[7][3] = 'D';
	grid[7][4] = 'E';
	grid[7][5] = 'A';
	grid[7][6] = 'D';
	
}
	
TextDisplay::~TextDisplay()
{
	for (int i = 0 ; i < 18 ; i++) {
		delete [] grid[i];
	}
	delete [] grid;
}

////////////// Private ///////////////

void TextDisplay::printScore() const{
	ScoreBoard *s = ScoreBoard::getInstance();
	std::cout << "Level:";// implement level
	for(int i = 10000000 ; ( i != 1 && Level::getLevel()/i == 0 ) ; i = i / 10) {
		std::cout << ' ';
	}
	std::cout << Level::getLevel() << std::endl;
	std::cout << "Score:";
	for(int i = 10000000 ; ( i != 1 && s->getScore()/i == 0 ) ; i = i / 10) {
		std::cout << ' ';
	}
	std::cout << s->getScore() << std::endl;
	std::cout << "Hi Score:";
	for(int i = 10000 ; (i != 1 && s->getHighscore()/i == 0) ; i = i / 10) {
		std::cout << ' ';
	}
	std::cout << s->getHighscore() << std::endl;
	std::cout << "----------" << std::endl;
}
		
void TextDisplay::printBoard() const{
	for (int i = 14 ; i >= 0 ; i--) {
		for (int j = 0 ; j < 10 ; j++) {
			std::cout << grid[i][j];
		}
		std::cout << std::endl;
	}
}

void TextDisplay::printNext(const Block *b) const{
	Point *p = b->getBody();
	char c = b->getChar();
	bool wtv = false;
	std::cout << "----------" << std::endl;
	std::cout << "Next:" << std::endl;
	for (int i = b->getHeight() - 1 ; i >= 0 ; i--) {
		for (int j = 0 ; j < b->getWidth() ; j++) {
			for (int k = 0 ; k < 4 ; k++) {
				if (p[k].y == i && p[k].x == j) {
					wtv = true;
				}
			}
			if (wtv) {std::cout << c;}
			else {std::cout << ' ';}
			wtv = false;
		}
		std::cout << std::endl;
	}
	if(c == 'I') { // add another line for prettiness
		std::cout << std::endl;
	}
}

void TextDisplay::printHold(const Block *b) const{
	std::cout << "----------" << std::endl;
	std::cout << "Hold:" << std::endl;
	if (b) {
		Point *p = b->getBody();
		char c = b->getChar();
		bool wtv = false;
		for (int i = b->getHeight() - 1 ; i >= 0 ; i--) {
			for (int j = 0 ; j < b->getWidth() ; j++) {
				for (int k = 0 ; k < 4 ; k++) {
					if (p[k].y == i && p[k].x == j) {
						wtv = true;
					}
				}
				if (wtv) {std::cout << c;}
				else {std::cout << ' ';}
				wtv = false;
			}
			std::cout << std::endl;
		}
		if(c == 'I') {
			std::cout << std::endl;
		}
	}
	else {
		// add 2 lines for symmetry
		std::cout << std::endl << std::endl;
	}
}

std::ostream& operator<< (std::ostream& os, const TextDisplay &t) {
	for (int i = 14 ; i >= 0 ; i--) {
		for (int j = 0 ; j < 10 ; j++) {
			os << t.grid[i][j];
		}
		os << i;
		os << std::endl;
	}
	return os;
}
