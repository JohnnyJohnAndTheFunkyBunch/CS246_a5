#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
    int x;
    int y;
		void setPoint(int x, int y) {
			this->x = x;
			this->y = y;
		}
};

std::ostream& operator<< (std::ostream& os, const Point &p);


#endif
