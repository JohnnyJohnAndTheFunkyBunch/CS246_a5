#include "game.h"
#include "board.h"
#include "block.h"
#include "blocks.h"
#include "textdisplay.h"
#include "scoreboard.h"
#include "level.h"
#include "levels.h"
#include "window.h"
#include <string>

// Chagne variable State, conflicts with Scorebaord

//////////////// CONSTRUCTOR DESTRUCTOR ///////////////

Game::Game(int level, std::string filename, bool graphics, int seed) : 
								curr(0), 
								next(0), 
								hold(0),
								b(new Board),
								t(TextDisplay::getInstance()), 
								s(ScoreBoard::getInstance()),
								w(0),
								x(0),
								y(14),
								graphics(graphics),
								alive(true),
								held(false)
{
	//init levels;
	Level::initLevels(level, filename, seed);
	l = Level::levels[level];
	curr = l->getBlock();
	next = l->getBlock();
	t->place(*curr, x, y);
	if(graphics) {
		w = Xwindow::getInstance();
		w->init();
		w->drawNext(*next);
		w->place(*curr, x, y);
		w->drawLevel();
		w->drawScore();
	}
		
}

Game::~Game() {
	delete b;
	t->clearGrid();
	s->resetScore();
	delete curr;
	delete next;
	delete hold;
	Level::levels[0]->restart();
	// reopen the file?
}

/////////////////// LEVEL METHODS ////////////////

void Game::increaseLevel() {
	Level::increaseLevel();
	l = Level::levels[Level::getLevel()];
	if (graphics) {
		w->drawLevel();
	}
}

void Game::decreaseLevel() {
	Level::decreaseLevel();
	l = Level::levels[Level::getLevel()];
	if (graphics) {
		w->drawLevel();
	}
}

////////////////// BLOCK METHODS //////////////

void Game::move(Direction d) {
	State st;
	if (d == Left) {
		st = b->place(*curr, x - 1, y);
		switch(st)
		{
			case OK:
				t->unplace(*curr, x, y);
				if (graphics) {
					w->unplace(*curr, x, y);
				}

				
				x--;
				t->place(*curr, x, y);
				if (graphics) {
					w->place(*curr, x, y);
				}
				break;
			case BAD:
				break;
			case OUT:
				break;
		}
	}
	else if (d == Right) {
		st = b->place(*curr, x + 1, y);
		switch(st)
		{
			case OK:
				t->unplace(*curr, x, y);
				if (graphics) {
					w->unplace(*curr, x, y);
				}

				x++;
				t->place(*curr, x, y);
				if (graphics) {
					w->place(*curr, x, y);
				}
				break;
			case BAD:
				break;
			case OUT:
				break;
		}
	}
	else if (d == Down) {
		st = b->place(*curr, x , y - 1);
		switch(st)
		{
			case OK:
				t->unplace(*curr, x, y);
				if (graphics) {
					w->unplace(*curr, x, y);
				}
	//			redraw(*curr, x, y);
				//redraw	
				y--;
				t->place(*curr, x, y);
				if (graphics) {
					w->place(*curr, x, y);
				}
				break;
			case BAD:
				break;
			case OUT:
				break;
		}
	}
}

void Game::drop(){
	// calculate fall
	int fall = b->dropHeight(*curr, x); //faster algo
	if (fall > y) {
		std::cout << "ASDFASDF" <<std::endl;
		fall = b->dropHeight(*curr, x, y); // less fast
	}
	// update fall graphics
	t->unplace(*curr, x, y);
	if (graphics) {
		w->unplace(*curr, x, y);
	}
	y = fall;
	b->set(*curr, x, y);
	t->place(*curr, x, y);
	if (graphics) {
		w->place(*curr, x, y);
	}
	if (b->clearRows() && graphics) {
		w->refresh();
		w->drawScore();
	}
	// change pieces
	delete curr;
	curr = next;
	next = l->getBlock();
	if (graphics) {
		w->undrawNext(*curr); //since the previous next is this curr
		w->drawNext(*next);
	}
	x = 0;
	y = 14;
	if (b->place(*curr, x, y) == BAD) {
		alive = false;
		t->printDead();
		if (graphics) {
			w->drawDead();
		} // change to state management // DEAD
	}
	else {
		t->place(*curr, x, y);
		if (graphics) {
			w->place(*curr, x, y);
		}
	}
	held = false;
}

void Game::rotateC() {
	State st;
	curr->rotateC();
	st = b->place(*curr, x, y);
	if (st == BAD || st == OUT) { // back to original position
		curr->rotateCC();
	}
	else {
		curr->rotateCC();
		t->unplace(*curr, x, y);
		if (graphics) {
			w->unplace(*curr, x, y);
		}
		curr->rotateC();
		t->place(*curr, x, y);
		if (graphics) {
			w->place(*curr, x, y);
		}
	}
}

void Game::rotateCC() {
	State st;
	curr->rotateCC();
	st = b->place(*curr, x, y);
	if (st == BAD || st == OUT) { // back to original position
		curr->rotateC();
	}
	else {
		curr->rotateC();
		t->unplace(*curr, x, y);
		if (graphics) {
			w->unplace(*curr, x, y);
		}
		curr->rotateCC();
		t->place(*curr, x, y);
		if (graphics) {
			w->place(*curr, x, y);
		}
	}
}

void Game::holdBlock() {
	if ((hold == NULL || b->place(*hold, 0, 14) == OK) && held == false) {
		t->unplace(*curr, x, y);
		if (graphics) {
			w->unplace(*curr, x ,y);
		}
		curr->rotateO();
		if (hold) {
			if (graphics) {
				w->undrawHold(*hold);
			}
			Block *tmp = curr;
			curr = hold;
			hold = tmp;
		}
		else {
			hold = curr;
			curr = next;
			next = l->getBlock();
			if (graphics) {
				w->undrawNext(*curr);
				w->drawNext(*next);
			}
		}
		x = 0;
		y = 14;
	
		t->place(*curr, x, y);
		if (graphics) {
			w->place(*curr, x, y);
			w->drawHold(*hold);
		}
		held = true;
	}
}

void Game::skipBlock() {
	if (curr->getSkip()) {
		t->unplace(*curr, x, y);
		if (graphics) {
			w->unplace(*curr, x, y);
		}
		delete curr;
		curr = next;
		next = l->getBlock();
		if (graphics) {
			w->undrawNext(*curr);
			w->drawNext(*next);
		}
		x = 0;
		y = 14;
		t->place(*curr, x, y);
		if (graphics) {
			w->place(*curr, x, y);
		}
	}
}

//////////////// Display ///////////////////

void Game::display() {
	t->printAll(next, hold);
}
	
/////////////// Const Functions ///////////////


bool Game::amIAlive() const {
	return alive;
}







