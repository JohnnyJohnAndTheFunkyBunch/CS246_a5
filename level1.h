#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"

class Block;
class Level1 : public Level
{
    public:
        Level1();
				Block * getBlock();
        virtual ~Level1();
    protected:
    private:
};

#endif // LEVEL1_H
