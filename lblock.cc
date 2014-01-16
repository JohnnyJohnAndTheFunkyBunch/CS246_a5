#include "lblock.h"

LBlock::LBlock()
{
		this->setBlock('L', 4);
    rotation = new Point*[cycle];
		for (int i = 0 ; i < cycle ; i++) {
			rotation[i] = new Point[4];
		}
    rotation[0][0].setPoint(0, 0);
    rotation[0][1].setPoint(2, 1);
    rotation[0][2].setPoint(1, 0);
    rotation[0][3].setPoint(2, 0);

		rotation[1][0].setPoint(0, 2);
    rotation[1][1].setPoint(1, 0);
    rotation[1][2].setPoint(1, 1);
    rotation[1][3].setPoint(1, 2);
		
		rotation[2][0].setPoint(0, 1);
    rotation[2][1].setPoint(1, 1);
    rotation[2][2].setPoint(2, 1);
    rotation[2][3].setPoint(0, 0);

		rotation[3][0].setPoint(0, 0);
    rotation[3][1].setPoint(0, 1);
    rotation[3][2].setPoint(0, 2);
    rotation[3][3].setPoint(1, 0);

		this->calWidth();
		this->calHeight();
		this->calSkirt();
}
LBlock::~LBlock()
{
    //dtor
}
