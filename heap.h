#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename Comparator = std::less<T> >
class Heap //0-based indexing
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c = Comparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  void printHeap() const;

 private:
  /// Add whatever helper functions and data members you need below
 
 void heapify(int loc); //used by pop(), trickle down approach
 void trickleUp(int loc); //used by push()

 int m_;
 std::vector<T> myItems_;
 Comparator compare_;


};


//Alternate constructor
template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(int m, Comparator c)
: m_(m), compare_(c)
{ }

//Alternate constructor
template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap()
{ }

//Return true for empty heap, else false
template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const
{
	return myItems_.size() == 0;
}

//Check for empty heap too
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty())
  {
    throw std::logic_error("can't top an empty heap");
  }
  else
  {
  	return myItems_[0]; //0-based indexing
  }
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  else
  {
  	if(myItems_.size() == 1)
  		myItems_.pop_back(); //no need to heapify
  	else //size greater than 1
  	{
  		//Swap 1st and last
  		T temp = myItems_[0];
  		myItems_[0] = myItems_[myItems_.size()-1];
  		myItems_[myItems_.size()-1] = temp;

  		//Remove last
  		myItems_.pop_back();

  		//Heapify now
  		if(myItems_.size() == 1) //No need to heapify
  			return;
  		else
  		{
  			heapify(0);
  		}
  	}
  }
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::heapify(int loc)
{
  if(empty()){
    throw std::logic_error("can't heapify an empty heap");
  }
  else
  {
  	//Check if loc is a leaf node
  	//A leaf node has no child, a node
  	//which has a left-most child cannot be leaf.
  	
  	if( !(m_*loc + 1 < myItems_.size()) ) //has no left child, so is leaf
  		return;
  	int currIndex = m_*loc + 1; //left-most
  	int bestIndex = currIndex; //Assume
  	currIndex++;
  	
  	//Now go through all children in search for the best to swap with
  	while(currIndex <= m_*loc + m_ 
  		&& currIndex < myItems_.size())
  	{
  		if(compare_(myItems_[currIndex], myItems_[bestIndex]))
  		{
  			bestIndex = currIndex;
  		}
  		currIndex++;
  	}

  	//swap and heapify is condition satisfied
  	if(compare_(myItems_[bestIndex],myItems_[loc]))
  	{
  		T temp = myItems_[bestIndex];
  		myItems_[bestIndex] = myItems_[loc];
  		myItems_[loc] = temp;
  		heapify(bestIndex);
  	}

  }


}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item)
{
	//pushback and then trickle up
	myItems_.push_back(item);
	if(myItems_.size() > 1)
		trickleUp(myItems_.size()-1);
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleUp(int loc)
{
	if(empty())
	{
    	throw std::logic_error("can't trickle up an empty heap");
  	}
  	else
  	{
  		int parent = (loc-1)/m_;
  		while(parent >= 0 && 
  			compare_(myItems_[loc], myItems_[parent]) )
  		{
  			//Swap
  			T temp = myItems_[parent];
  			myItems_[parent] = myItems_[loc];
  			myItems_[loc] = temp;

  			//Update loc and parent
  			loc = parent;
  			parent = (loc-1)/m_;
  			
  		}
  	}
}

//Print heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::printHeap() const
 {
  	for(unsigned int i = 0; i < myItems_.size(); i++)
  		std::cout << myItems_[i] << ' ';
  	std::cout << std::endl;
 }

 

#endif
