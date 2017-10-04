#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int n = atoi(argv[1]);
  int initMoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heur = atoi(argv[4]);

  PuzzleHeuristic *ph;
  if(heur == 2)
 	ph = new PuzzleManhattanHeuristic;
  else if(heur == 1 )
  	ph = new PuzzleOutOfPlaceHeuristic;
  else if(heur == 0)
  	ph = new PuzzleBFSHeuristic;

  Board myBoard(n, initMoves, seed); 

  //cout << myBoard << endl;
  int choice = 1;
  while (choice!=0 && !myBoard.solved())
  {
    cout << endl << myBoard << endl;
  	cout << "Enter tile number to move or -1 for a cheat: ";
  	cin >> choice;
    //cout << endl;
  	if(choice == -1)
  	{
  		cout << "Try this sequence: \n";
  		PuzzleSolver pz(myBoard, ph);
  		pz.run();
  		std::deque<int> sol = pz.getSolution();
  		for(unsigned int i = 0; i < sol.size(); i++)
  		{
  			cout << sol[i] << ' ';
  		} cout << endl;
  		cout << "(Expansions = " << pz.getNumExpansions() <<")" << endl;
  	}
  	else if(choice != 0)
  	{
  		myBoard.move(choice);
  	}
    
    //cout << myBoard<< endl;

  }

  if(myBoard.solved())
  {
  	cout << endl << myBoard << endl;
  }

  delete ph;
  return 0;
}
