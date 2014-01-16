#ifndef BLOCK_H
#define BLOCK_H

#include "point.h"
class Block
{

    public:
        Block();

        int getWidth() const;
        int getHeight() const;
        int *getSkirt() const;
				char getChar() const;
        Point *getBody() const;
        bool getSkip() const;

        void rotateC();           // rotate clockwise
        void rotateCC();          // rotate counterclockwise
        void rotateO();           // rotate back to orginal postiion
        
        void setSkip();           // set skip to true
        
        virtual ~Block() = 0;
        
        friend std::ostream& operator<< (std::ostream& os, const Block &b);
				
    protected:
		    Point **rotation;
				char c;
				int width;
				int height;
				int *skirt;
				int index;
				int cycle;
				bool skip;
				void calWidth();
				void calHeight();
				void calSkirt();
				void setBlock(char c, int cycle);
			
    private:

				
};



#endif // BLOCK_H
