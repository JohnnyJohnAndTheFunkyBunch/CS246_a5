#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"

class Block;
class Level2 : public Level
{
    public:
        Level2();
				Block * getBlock();
        virtual ~Level2();
    protected:
    private:
};

#endif // LEVEL2_H
