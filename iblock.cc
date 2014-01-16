#include "iblock.h"

IBlock::IBlock()
{
		this->setBlock('I', 2);
    rotation = new Point*[cycle];
		for (int i = 0 ; i < cycle ; i++) {
			rotation[i] = new Point[4];
		}
		
		rotation[0][0].setPoint(0, 0);
    rotation[0][1].setPoint(1, 0);
    rotation[0][2].setPoint(2, 0);
    rotation[0][3].setPoint(3, 0);

		rotation[1][0].setPoint(0, 0);
    rotation[1][1].setPoint(0, 1);
    rotation[1][2].setPoint(0, 2);
    rotation[1][3].setPoint(0, 3);
		
		this->calWidth();
		this->calHeight();
		this->calSkirt();
}
IBlock::~IBlock()
{
    //dtor
}
