#include "sortvector.h"
#include "pathfinder.h"
#include <algorithm>
#include <stdlib.h>

//constructor sets start and end points for path
PathFinder::PathFinder(void) 
{
	start_a = 0;
	start_b = 0;
	end_a = 0;
	end_b = 0;
}

void PathFinder::SetUp(int a1, int b1, int a2, int b2) 
{
	start_a = a1;
	start_b = b1;
	end_a = a2;
	end_b = b2;
}

bool PathFinder::findThePath(void)
{
	Path startPos(start_a, start_b); //create a starting point for path
	startPos.parentPath = NULL; //starting point has no parent
	getHeuristic(startPos); //calculate heuristic to reach final path

	if(startPos.pathScore == 0) //if heuristic is 0, then start == end
	{
		return false; //no path
	}
	else
	{
		closedVector.reserve(320); //reserve space in the closed vector to avoid memory being reallocated and corrupting pointers
		addtoClosedVector(startPos); //add the starting point to the closed vector
		Path theMove = findNextMove(startPos);
		finalPath.push_back(theMove); //findNextMove will generate final move in the path. Add this to finalPath vector

		while(theMove.parentPath != NULL) //check that last move added is not the start of the path
		{
			theMove = *theMove.parentPath; //get the next move by tracing back through the parent path moves
			finalPath.push_back(theMove); //add this to the path
			
		}

		std::reverse(finalPath.begin(), finalPath.end()); //reverse the order so the path is going forwards instead of back
		return true;
	}
}

Path PathFinder::getNextMove(int it)
{
	return finalPath[it];
}


void PathFinder::ClearVectors(void)
{
	openVector.clear();
	closedVector.clear();
	finalPath.clear();	
}

//checks a set of coordinates to see if that set is already in the open vector
bool PathFinder::searchOpenVector(int aa, int bb) 
{
	for(int i = 0; i < openVector.size(); i++)
	{
		if(openVector[i].a==aa && openVector[i].b==bb)
			return true;

	}
	return false;
}

//adds a given move to the open vector
void PathFinder::addtoOpenVector(Path nextStep)
{
	openVector.push_back(nextStep);
}

//removes the last move from the open vector
void PathFinder::removefromOpenVector()
{
	openVector.pop_back();
}

//checks a set of coordinates to see if that set is already in the closed vectore
bool PathFinder::searchClosedVector(int aa, int bb)
{
	for(int i = 0; i < closedVector.size(); i++)
	{
		if(closedVector[i].a==aa && closedVector[i].b==bb)
			return true;

	}
	return false;
}

//adds a given move to the closed vector
void PathFinder::addtoClosedVector(Path nextStep)
{
	closedVector.push_back(nextStep);
}

//removes the last move from the closed vector (not used)
void PathFinder::removefromClosedVector()
{
	closedVector.pop_back();
}

//function that checks all possible moves from a given point. Recursively checks the moves with the best heuristics until the end point is reached
Path PathFinder::findNextMove(Path & currentPos)
{
	int xmin, xmax; //variables to find the adjacent squares on the grid
	int ymin, ymax;
	
	//checks to ensure it does not look at squares off the edge of the grid
	if(currentPos.a == 0)
		xmin = 0;
	else
	{
		xmin = currentPos.a - 1;
	}
	if(currentPos.a == 19)
		xmax = 20;
	else
	{
		xmax = currentPos.a + 2;
	}
	if(currentPos.b == 0)
		ymin = 0;
	else
	{
		ymin = currentPos.b - 1;
	}
	if(currentPos.b == 15)
		ymax = 16;
	else
	{
		ymax = currentPos.b + 2;
	}
	
	for(int y = ymin; y<ymax; y++)
	{
		for(int x = xmin; x<xmax; x++)
		{
			if(!Grid[y][x].blocked)  //checks if the move is blocked on the game grid (not checking for diagonal blocks yet)
			{
				if(!searchClosedVector(x,y) && !searchOpenVector(x,y)) //checks if the move is has been made or is already on the moves Vector
				{
					//create new move using these coord   inates
					Path nextMove(x, y);
					nextMove.parentPath = &currentPos;
					getHeuristic(nextMove);
					if(x==end_a && y==end_b) //check if this move is the final one
					{
						return nextMove;
					}
					else
					{	
						addtoOpenVector(nextMove);  //add this move to the open Vector
					}
				}
			}			
		}
	}
	std::sort(openVector.begin(), openVector.end(), Compare_pathScores());
	addtoClosedVector(openVector.back()); //add the move with best heuristic to the closed vector (will be last one in the vector)
	removefromOpenVector(); //remove it from the open vector so we don't try it twice
	return findNextMove(closedVector.back()); //find next possible moves from this move (recursive call)
}

void PathFinder::getHeuristic(Path & aMove)
{	
	//variables
	int a_dest, b_dest;
	int diag_dest, hori_dest;
	
	a_dest = abs(end_a-aMove.a);
	b_dest = abs(end_b-aMove.b);
	
	diag_dest = a_dest < b_dest ? a_dest*14 : b_dest*14;
	hori_dest = abs(a_dest-b_dest)*10;
	
	aMove.destScore = diag_dest + hori_dest;
	
	if(aMove.parentPath != NULL)
	{
		if(aMove.a==aMove.parentPath->a || aMove.b==aMove.parentPath->b)
			aMove.moveScore = 10 + aMove.parentPath->moveScore;
		else
		{
			aMove.moveScore = 14 + aMove.parentPath->moveScore;
		}
	}
	else
	{
		aMove.moveScore = 0;
	}
	
	aMove.pathScore = aMove.destScore + aMove.moveScore;
}


 


