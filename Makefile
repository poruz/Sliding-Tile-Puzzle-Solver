CC = g++
CPPFLAGS = -g -Wall

OBJS = board.o puzzle_heur.o puzzle_solver.o puzzle_move.o

all: puzzle

board.o: board.h board.cpp
	$(CC) $(CPPFLAGS) -c board.cpp -o $@

puzzle_heur.o: puzzle_heur.cpp board.h puzzle_heur.h
	$(CC) $(CPPFLAGS) -c puzzle_heur.cpp -o $@

puzzle_move.o: puzzle_move.cpp board.h puzzle_move.h 
	$(CC) $(CPPFLAGS) -c puzzle_move.cpp -o $@

puzzle_solver.o: puzzle_solver.cpp puzzle_move.h puzzle_solver.h board.h heap.h puzzle_heur.h
	$(CC) $(CPPFLAGS) -c puzzle_solver.cpp -o $@

puzzle: puzzle.cpp $(OBJS)
	$(CC) $(CPPFLAGS) puzzle.cpp $(OBJS) -o $@

heap_test: heap.h heap_test.cpp
	$(CC) $(CPPFLAGS) heap_test.cpp -o $@	
	
clean:
	rm -rf board.o
	rm -rf puzzle_solver.o
	rm -rf puzzle_heur.o
	rm -rf puzzle_move.o
	rm -rf puzzle
	rm -rf heap_test