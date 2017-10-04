#include "puzzle_heur.h"
#include <cmath>

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int count = 0;
	for(int i = 0; i < b.size(); i++)
		if(b[i] != i && b[i] != 0)
			count++;
	return count;
}

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int count = 0;
	int dim = b.dim();
	for(int i = 0; i < b.size(); i++)
	{
		if(b[i] != 0)
		{
			int goalr, goalc, tr, tc; //goalrow goalcol tilerow tilecol
			//Current row and col
			tr = i/dim;
			tc = i%dim;

			//Where was the value at current position supposed to be?
			goalr = b[i]/dim;
			goalc = b[i]%dim;
			int dist = std::abs(goalr-tr) + std::abs(goalc-tc);
			count += dist;
		}
	}
	return count;
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}