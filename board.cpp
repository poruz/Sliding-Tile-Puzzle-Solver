#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}


Board::Board(const Board& b)
{
  if(&b != this)
  {
    size_ = b.size_;
    tiles_ = new int[size_];
    for(int i=0; i < size_; i++)
      tiles_[i] = b.tiles_[i];
  }
}

Board::~Board()
{
  //if(tiles_ != NULL)
  delete [] tiles_;
}

Board& Board::operator=(const Board& b)
{
  if(&b == this)
  {
    return *this;
  }
  else
  {
    size_ = b.size_;
    delete [] tiles_;
    tiles_ = new int[size_];
    for(int i=0; i < size_; i++)
      tiles_[i] = b.tiles_[i];
  }
  return *this;
}

bool Board::solved() const
{
  for(int i = 0; i < size_; i++)
  {
    if(tiles_[i] != i)
      return false;
  }
  return true;
}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> moveMap;

  //Find the blank tile
  int side_dim = dim();

  int j=-1; //tile with 0
  while(tiles_[++j] != 0);

 // cout << j << endl;

  int northTile = j - side_dim;
  int westTile = j - 1;
  int southTile = j + side_dim;
  int eastTile = j + 1;
  /*
  cout << northTile << ' ' << westTile << ' ' <<southTile << ' '
  << eastTile << endl;// << size_ << endl; //*/

  //Check for potential moves N, W, S, E
  if((northTile >= 0)) //if can go North
  {
    Board* northMoveBoard = new Board(*this);
    northMoveBoard->move(northMoveBoard->tiles_[northTile]);
    moveMap.insert(make_pair(this->tiles_[northTile],northMoveBoard));
  }

  if((westTile >= 0 && j%side_dim != 0)) //can go West
  {
    Board* westMoveBoard = new Board(*this);
    westMoveBoard->move(westMoveBoard->tiles_[westTile]);
    moveMap.insert(make_pair(this->tiles_[westTile],westMoveBoard));
  }

  if((southTile < size_)) //can go South
  {
    Board* southMoveBoard = new Board(*this);
    southMoveBoard->move(southMoveBoard->tiles_[southTile]);
    moveMap.insert(make_pair(this->tiles_[southTile],southMoveBoard));
  }

  if((eastTile < size_ && (j+1)%side_dim != 0)) //can go East
  {
    Board* eastMoveBoard = new Board(*this);
    eastMoveBoard->move(eastMoveBoard->tiles_[eastTile]);
    moveMap.insert(make_pair(this->tiles_[eastTile],eastMoveBoard));
  }

  return moveMap;
}

bool Board::operator<(const Board& rhs) const
{
  for(int i = 0; i < size_; i++)
  {
    if(tiles_[i] < rhs.tiles_[i])
      return true;
    else if(tiles_[i] > rhs.tiles_[i])
      return false;
  }
  return false;
}

const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}

std::ostream& operator<<(std::ostream &os, const Board &b)
{
  b.printRowBanner(os);
  int t = 0;
  for(int i = 0; i < b.dim(); i++)
  {
    for(int j = 0; j < b.dim(); j++, t++)
    {
      os << "|" << setw(2);
      if(b[t] != 0)
        os << b[t];
      else
        os << ' ';
    }
    os << "|" << endl;
    b.printRowBanner(os);
  }
  return os;
}

/*
int main()
{
  Board b(3, 198, 1);

  cout << b << endl << "----------\n\n";

  map<int, Board*> mapp = b.potentialMoves();jjm

  cout << mapp.size() << endl;
  for(map<int, Board*>::iterator it = mapp.begin();
        it!=mapp.end(); ++it)
    cout << *(it->second);

  //cout << b;

  return 0;
}*/