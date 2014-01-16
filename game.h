#ifndef Game_H
#define Game_H

enum Direction { Left, Right, Down };

class Board;
class Block;
class TextDisplay;
class ScoreBoard;
class Level;
class Xwindow;

#include <string>


class Game
{
			Block *curr;
			Block *next;
			Block *hold;
			Board *b;
			TextDisplay *t;
			ScoreBoard *s;
			Level *l;
			Xwindow *w;
			int x;          // Position of Current block
			int y;
			bool graphics;  // If choose to display graphics
			bool alive;     // if game is lost
			bool held;      // if held a piece before
    public: 
				Game(int level, std::string filename, bool graphics, int seed);
				~Game();
				void increaseLevel();
				void decreaseLevel();
				void move(Direction d);
				void drop();
				void rotateC();
				void rotateCC();
				void holdBlock();
				void skipBlock();
				void display();
				bool amIAlive() const;
    protected:
    private:
};

#endif // Game_H
