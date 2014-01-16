#include <iostream>
#include "point.h"
using namespace std;

int main(){
	Point p = {1, 3};
	cout << p << endl;
	p.setPoint(3, 4);
		cout << p << endl;
	return 0;
}
