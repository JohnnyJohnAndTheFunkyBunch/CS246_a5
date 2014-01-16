#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

#include <string>


 
class InputHandler {
  std::string *lofc; // list of commands;
  

 public:
	InputHandler();
	void rename(std::string orig, std::string fresh); // rename the original command to fresh
	int getCommand(std::string input);                // outputs the command according to string
	~InputHandler();

};

#endif
