#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"

class Block;
class Level3 : public Level
{
    public:
        Level3();
				Block * getBlock();
        virtual ~Level3();
    protected:
    private:
};

#endif // LEVEL3_H
