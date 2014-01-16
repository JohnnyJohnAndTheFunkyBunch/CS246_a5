#ifndef BOARD_H
#define BOARD_H

#include <iostream>
class BlockGraveyard;
class Block;

enum State {OK, BAD, OUT};

class Board
{
		bool **grid;
		int heights[10];
		int rows[18];
		BlockGraveyard *grave;
		
    public:
        Board();
				State place(const Block &b, int x, int y); // returns a state OK, BAD, OUT
				void set(const Block &b, int x, int y); // Actually set the block
				int dropHeight(const Block &b, int x) const; // Calculates the y coordinate it'll land
				int dropHeight(const Block &b, int x, int y) const; // calculate dropHeight if below heights
				bool clearRows(); // true if cleared a row
				
        ~Board();
				friend std::ostream& operator<< (std::ostream& os, const Board &b);
    protected:
    private:
};

#endif // BOARD_H
