#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board* board)
:tileMove(-1), b(board), g(0), prev(NULL)
{

}

// Constructor for subsequent search boards 
// (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
:tileMove(tile), b(board), prev(parent)
{
	//What about g and h - We do them later in other files
}

// Destructor
PuzzleMove::~PuzzleMove()
{
	delete b;
}