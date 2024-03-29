#include "gridspace.h"

//GRIDSPACE CONSTRUCTOR///////////////////////////////////////////////////////////////////////////////////////
GridSpace::GridSpace()
{
	x = 0; 
	y = 0;
	z = 0;
	bool blocked = false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//EMPTY DESTRUCTOR/////////////////////////////////////////////////////////////////////////////////////////////
GridSpace::~GridSpace()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SETCOORDINATES(a, b) FUNCTION////////////////////////////////////////////////////////////////////////////////
void GridSpace::SetCoordinates(int a, int b)
{
	x = a*32; //sets the x and y coordinates for the centre of the grid space in grid array Grid[b][a].
	y = b*32;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GridSpace Grid[16][20]; //global game grid