#include "inputhandler.h"
#include <iostream>
#include <string>


//// Make Input Handler RENAME function
const int nbOfCommands = 12;
///////////////// Constructor Destructor ///////////////////////

InputHandler::InputHandler() { // have initial intialization, with default, with strings as parameters
	lofc = new std::string[nbOfCommands];
	
	lofc[0] = "left";
	lofc[1] = "right";
	lofc[2] = "down";
	lofc[3] = "clockwise";
	lofc[4] = "counterclockwise";
	lofc[5] = "drop";
	lofc[6] = "levelup";
	lofc[7] = "leveldown";
	lofc[8] = "restart";
	lofc[9] = "hold";
	lofc[10] = "skip";
	lofc[11] = "rename";
		
}





InputHandler::~InputHandler(){
	delete [] lofc;
}

///////////////// Get Command //////////////////////////


int InputHandler::getCommand(std::string input) {
	
	int index[nbOfCommands] = {};
	int valid = 0;
	for(int i = 0 ; i < input.length() ; i++) {
		valid = 0;
		for(int j = 0 ; j < nbOfCommands ; j++) {
			if (i < lofc[j].length() && lofc[j][i] == input[i] && index[j] == i) { // same letter and same index
			// if run behind, stop incrementing
				index[j]++; 
				valid++;
			}

		}
	}
	if (valid == 1) {
		for(int j = 0 ; j < nbOfCommands ; j++) {
			if(index[j] == input.length()) {
				return j;
			}
		}
	}
	else {
		return -1;
	}
}
	

void InputHandler::rename(std::string orig, std::string fresh) {
	for(int i = 0 ; i < nbOfCommands ; i++) {
		if (orig == lofc[i]) {
			lofc[i] = fresh;
		}
	}
}
	
	
	
	
	
	
	


