#ifndef LEVEL0_H
#define LEVEL0_H

#include "level.h"
#include <fstream>
#include <string>

class Block;
class Level0 : public Level
{
			 std::ifstream *in;    // the actual input stream
			 std::string filename; // the filename of the input stream
    public:
        Level0(std::string filename);
				Block * getBlock();
        virtual ~Level0();
        void restart();
				
    protected:
    private:
				void changeIn(std::ifstream *in);
};

#endif // LEVEL0_H
