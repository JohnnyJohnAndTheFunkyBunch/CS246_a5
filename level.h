#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "PRNG.h"

class Block;
class Level
{
    public:
				static int currLevel;   // The current level
				static PRNG prng;       // The ranomizer
				static Level **levels;  // Array of pointers to each level, [1..4]
				
				Level();
				static void initLevels(int n, std::string s, int seed); // Initialzie the levels
				static void cleanUp();                                  // Call when exit, to delete levels
				static void increaseLevel();
				static void decreaseLevel();
				static int getLevel();
				virtual void restart();
        virtual ~Level();
				virtual Block * getBlock()=0;
    protected:
    private:
};

#endif // LEVEL_H
