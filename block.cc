#include "block.h"
#include <iostream>

////////////////////// Constructor Destructor //////////////////
Block::Block(): 
	rotation(NULL), 
	c(' '),
	width(0),
	height(0),
	skirt(0),
	index(0),
	cycle(0),
	skip(false)
{
}

Block::~Block()
{
	for (int i = 0 ; i < cycle ; i++) {
		delete [] rotation[i];
	}
	delete [] rotation;
	delete [] skirt;
}

////////////////// Const Functions ///////////////////////////

int Block::getWidth() const{ return width; }

int Block::getHeight() const{ return height; }

int * Block::getSkirt() const{ return skirt; }

char Block::getChar() const{ return c; }

Point * Block::getBody() const{ 
	return rotation[(index % cycle + cycle) % cycle]; } 
	
bool Block::getSkip() const {return skip; }
	
////////////////// ROTATION ///////////////////////

void Block::rotateC() { 
	index--; 
	int tmp;
	tmp = height;
	height = width;
	width = tmp;
	calSkirt();
}

void Block::rotateCC() { 
	index++; 
	int tmp;
	tmp = height;
	height = width;
	width = tmp;
	calSkirt();
}

void Block::rotateO() {
	index = 0;
	calWidth();
	calHeight();
	calSkirt();
}


//////////////////// PROTECTED //////////////////////

////////// INIT Functions /////////////

void Block::calWidth() {
	Point *p = getBody();
	int max = 0;
	for (int i = 0 ; i < 4 ; i++) {
		if (p[i].x > max) {
			max = p[i].x;
		}
	}
	width = max + 1;
}

void Block::calHeight() {
	Point *p = getBody();
	int max = 0;
	for (int i = 0 ; i < 4 ; i++) {
		if (p[i].y > max) {
			max = p[i].y;
		}
	}
	height = max + 1;
}

void Block::calSkirt() {
	if(skirt) {
		delete [] skirt;
	}
	int *skirt_array = new int[width];
	Point *p = getBody();
	for (int i = 0 ; i < width ; i++) {
		int min = 4;
		for (int j = 0; j < 4 ; j++) {
			if (p[j].x == i && p[j].y < min) {
				min = p[j].y;
			}
		}
		skirt_array[i] = min;
	}
	skirt = skirt_array;
}


void Block::setBlock(char c, int cycle) {
	this->c = c;
	this->cycle = cycle;
}

void Block::setSkip() {
	this->skip = true;
	this->c = this->c + 32;
}


////////// DEBUG FRIENDS /////////////////////
	

std::ostream& operator<< (std::ostream& os, const Block &b) {
	Point *p = b.getBody();
	bool wtv = false;
	
	for (int i = 4 ; i >= 0 ; i--) {
		for (int j = 0 ; j < 4 ; j++) {
			for (int k = 0 ; k < 4 ; k++) {
				if (p[k].y == i && p[k].x == j) {
					wtv = true;
				}
			}
			if (wtv) {os << b.c;}
			else {os << ' ';}
			wtv = false;
		}
		os << std::endl;
	}
	os << "Width = " << b.width << " Height = " << b.height;
	os << " Skirt = [";
	for (int i = 0 ; i < b.width ; i++) {
		os << b.skirt[i] << ',';
	}
	os << "]" << std::endl;
	os << "____";
	return os;
}

