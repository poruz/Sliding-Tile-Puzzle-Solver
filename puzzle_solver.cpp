#include "puzzle_solver.h"

using namespace std;

// Constructor (makes a copy of the Board and stores it in b_)
//  Also takes a PuzzleHeuristic which will score boards
PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph)
:b_(b), expansions_(0) ,ph_(ph)
{ }

// Destructor
PuzzleSolver::~PuzzleSolver()
{ }

// Run the A* search and builds the solution and tracks
// the number of expansions
void PuzzleSolver::run()
{
	Board* initialBoard = new Board(b_);
	PuzzleMove* initialMove = new PuzzleMove(initialBoard);
	int heur = ph_->compute(*initialBoard);
	initialMove->h = heur;

	PuzzleMoveSet closedList; //set<PuzzleMove*, PuzzleMoveBoardComp>
	Heap<PuzzleMove*, PuzzleMoveScoreComp> openList(2);

	closedList.insert(initialMove);
	openList.push(initialMove);

	while(!openList.empty())
	{
		PuzzleMove* s = openList.top();
		closedList.insert(s);
		openList.pop();

		if(s->b->solved())
		{ //Trace back
			
			while(s->tileMove != -1)
			{
				solution_.push_front(s->tileMove);
				s = s->prev;
			}

			//release memory
			for(PuzzleMoveSet::iterator itr = closedList.begin();
				itr != closedList.end(); ++itr)
			{
				delete *itr;
			}

			return;
		}
			
		//Get all potential moves.
		map<int, Board*> successor = s->b->potentialMoves();
		for(map<int, Board*>::iterator it = successor.begin();
				it!=successor.end(); ++it)
		{
		
			PuzzleMove *newMove = new PuzzleMove(it->first, it->second, s);
			//If not in closed list already
			if(closedList.find(newMove) == closedList.end()) //not in the closedlist
			{
				expansions_++;
				heur = ph_->compute(*(newMove->b));
				newMove->h = heur;
				newMove->g = s->g + 1;
				openList.push(newMove);
				closedList.insert(newMove);
			}
			else
				delete newMove;
		
		}
	}
	delete initialBoard;
	delete initialMove;
}

// Return the solution deque
std::deque<int> PuzzleSolver::getSolution()
{
	return solution_;
}

// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions()
{
	return expansions_;
}
/*
int main()
{
	Board *b= new Board(3,3,0);
	cout << "HI" << endl;
	PuzzleOutOfPlaceHeuristic* pp = new PuzzleOutOfPlaceHeuristic;
	PuzzleSolver p (*b, pp);
	return 0;
} */