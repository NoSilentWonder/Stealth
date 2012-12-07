#ifndef _GRIDSPACE_H_
#define _GRIDSPACE_H_

#include "sprites.h"

class GridSpace
{
public:
	GridSpace();
	~GridSpace();
	void SetCoordinates(int a, int b);
	int GetX(void) {return x;}
	int GetY(void) {return y;}
	bool blocked;
private:
	int x, y, z;
	
};

extern GridSpace Grid[16][20];


#endif