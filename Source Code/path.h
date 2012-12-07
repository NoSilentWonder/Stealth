#ifndef _PATH_H_
#define _PATH_H_

//class for pathfinding moves
class Path
{
public:
	Path(int a1, int b1);
	int a, b;
	Path * parentPath;
	int moveScore, destScore, pathScore;
};

#endif