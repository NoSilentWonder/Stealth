#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_

//class for finding the fastest route between two given sets of coordinates on a grid
#include <vector>
#include "gridspace.h"
#include "path.h"

class PathFinder
{
public:
	PathFinder(void);
	void SetUp(int a1, int b1, int a2, int b2);
	bool findThePath(void);
	int getPathSize(void)
	{ 
		return finalPath.size(); 
	}
	Path getNextMove(int it);
	void ClearVectors(void);	
	
private:
	//prototypes
	bool searchOpenVector(int aa, int bb);
	void addtoOpenVector(Path nextStep);
	void removefromOpenVector();

	bool searchClosedVector(int aa,int bb);
	void addtoClosedVector(Path nextStep);
	void removefromClosedVector();

	Path findNextMove(Path & currentPos);
	void getHeuristic(Path  & aMove);

	//vector for pathfinding
	std::vector<Path> openVector;
	std::vector<Path> closedVector;
	std::vector<Path> finalPath;
	
	//start and end points
	int start_a;
	int start_b;
	int end_a;
	int end_b;
};

#endif