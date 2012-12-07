#ifndef _SORTVECTOR_H_
#define _SORTVECTOR_H_

//class for finding the fastest route between two given sets of coordinates on a grid
#include <vector>
#include "path.h"

//struct used to return the class object with the highest pathscore - we want to sort the open vector so that the lowest (best score) is last
//in order to push it to select it next for finding path
struct Compare_pathScores 
{
	inline bool operator() (const Path & a, const Path & b)
	{
		return a.pathScore > b.pathScore;
	}
};



#endif