
#include <iostream>
#include <string>
#include <cstring>
#include "game.h"
#include "inputhandler.h"
#include <sstream>

using namespace std;


//for levels, make an array of multiple levels, and just point at 
// differnet ones

// Note : Restart, restart the file, also for the level

// IMPLEMENT YOURE DEAD



int main(int argc, char *argv[]) {
	string scriptFile = "sequence.txt"; // initialized with main
	int startLevel = 0;
	int seed = 1;
	////////////
	

	// maybe change this to a heap storage, and bring the adress the input handler
	///////////
	string s;
	char c;
	char k;
	bool multi = false;
	int n = 0; // multiplier
	bool graphics = true;
	
	string line;
	
	string orig;
	string fresh;
	
	InputHandler *l = new InputHandler();
	// Initializing comand line arguments
	
	for(int i = 0 ; i < argc ; i++) {
	string flag = argv[i];
		if(flag == "-text") {
			graphics = false;
		}
		if(flag == "-scriptfile") {
			i++;
			
			scriptFile = argv[i];
		}
		if(flag == "-startlevel") {
			i++;
			int j = 0;
			int num = 0;
			while(argv[i][j] != '\0') {
				if (argv[i][j] < '0' || argv[i][j] > '9') { // if invalid number, then level0
					num = 0;
					break;
				}
				num = num * 10 + argv[i][j] - 48;
				j++;
			}
			startLevel = num;
		}
		if (flag == "-rename") {
			l->rename(argv[i + 1], argv[i + 2]);
			i = i + 2;
		}
		if (flag == "-seed") {
			i++;
			int j = 0;
			int num = 0;
			while(argv[i][j] != '\0') {
				if (argv[i][j] < '0' || argv[i][j] > '9') { // if invalid number, then level0
					num = 0;
					break;
				}
				num = num * 10 + argv[i][j] - 48;
				j++;
			}
			seed = num;
		}
	}
	
	Game *g = new Game(startLevel, scriptFile, graphics, seed); // this can be changed in command line
	g->display();

// Game loop, with cin
	while (cin >> s){
		for(int i = 0 ; i < s.length() ; i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				multi = true;
				n = n * 10 + s[i] - 48;
			}
			else {
				s = s.substr(i);
				break;
			}
			if (i == s.length() - 1) {
				cin >> s;
				break;
			}
		}
		if (!multi) {
			n = 1;
		}
				
// List of Commands 
		// If dead, skip commands
			if (l->getCommand(s) != 8 && !g->amIAlive()) {
				continue;
			}

			if (l->getCommand(s) == 0) {
				for (int i = 0 ; i < n ; i++) {
					g->move(Left);
				}
			}
			else if (l->getCommand(s) == 1) {
				for (int i = 0 ; i < n ; i++) {
					g->move(Right);
				}
			}
			else if (l->getCommand(s) == 2) {
				for (int i = 0 ; i < n ; i++) {
					g->move(Down);
				}
			}
			else if (l->getCommand(s) == 3) {
				for (int i = 0 ; i < n ; i++) {
					g->rotateC();
				}
			}
			else if (l->getCommand(s) == 4) {
				for (int i = 0 ; i < n ; i++) {
					g->rotateCC();
				}
			}
			else if (l->getCommand(s) == 5) {
				for (int i = 0 ; i < n ; i++) {
					g->drop();
					if(!g->amIAlive()) { break; };
				}
			}
			else if (l->getCommand(s) == 6) {
				for (int i = 0 ; i < n ; i++) {
					g->increaseLevel();
				}
			}
			else if (l->getCommand(s) == 7) {
				for (int i = 0 ; i < n ; i++) {
					g->decreaseLevel();
				}
			}
			else if (l->getCommand(s) == 8) {
				delete g;
				g = new Game(startLevel, scriptFile, graphics, seed);
			}
			else if (l->getCommand(s) == 9) {
				g->holdBlock();
			}
			else if (l->getCommand(s) == 10) {
				g->skipBlock();
			}
			else if (l->getCommand(s) == 11) {
				cin >> orig;
				cin >> fresh;
				l->rename(orig, fresh);
				// rename
			}
			g->display(); // should it display even for invalid commands?
			multi = false;
			n = 0;
		}
	delete g;
	delete l;
	return 0;
}
