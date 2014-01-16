#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
class Block;
#include "window.h"

class TextDisplay
{
			char ** grid;
			
    public:
        TextDisplay();
				static TextDisplay *instance;
				static TextDisplay *getInstance();
				static void cleanup();
				
				void place(const Block &b, int x, int y);   // place a block in the grid
				void place(const char c, int x, int y);     // place a character in the grid
				void unplace(const Block &b, int x, int y); // unplace a block in the grid
				
				void clearRow(int n);                       // clear the n'th row, and pull down
				void clearGrid();                           // clear the grid -> empty grid
				
				void printAll(const Block *next, const Block *holt) const; // print in cout
				void printDead();                                          // print to notify game over
				
        ~TextDisplay();
				friend std::ostream& operator<< (std::ostream& os, const TextDisplay &t);
				friend void Xwindow::refresh();
    protected:
    private:
    		void printScore() const;
				void printBoard() const;
				void printNext(const Block *b) const;
				void printHold(const Block *b) const;
};

#endif // TEXTDISPLAY_H
