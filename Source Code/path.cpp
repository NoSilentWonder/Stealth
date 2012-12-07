#include "path.h"
#include <stdlib.h>


Path::Path(int a1, int b1)
{
	a = a1;
	b = b1;
	parentPath = NULL;
	destScore = moveScore = pathScore = 0;
}