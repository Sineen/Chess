
CXX = g++
OBJECTS = Bishop.o Board.o King.o Queen.o Knight.o Pawn.o Piece.o Rook.o
FLAGS = -Wextra -Wall -Wvla -std=c++17 -pthread -g -DNDEBUG
TARFILES1= chess.cpp Bishop.cpp Bishop.h Board.cpp Board.h King.cpp King.h Knight.cpp Knight.h
TARFILES2= Pawn.cpp Pawn.h Piece.cpp Piece.h Queen.cpp Queen.h Rook.cpp Rook.h Makefile README
LC_F = --leak-check=full
SPL_Y = --show-possibly-lost=yes
SR_Y = --show-reachable=yes
UVE_Y = --undef-value-errors=yes

all: chess

chess: $(OBJECTS)
	$(CXX) $(FLAGS) -c chess.cpp -o chess.o
	$(CXX) $(FLAGS) $(OBJECTS) chess.o -o ex2

Bishop.o: Bishop.cpp Bishop.h
	$(CXX) $(FLAGS) -c Bishop.cpp

Board.o: Board.cpp Board.h
	$(CXX) $(FLAGS) -c Board.cpp

Queen.o: Queen.cpp Queen.h
	$(CXX) $(FLAGS) -c Queen.cpp 

Knight.o: Knight.cpp Knight.h
	$(CXX) $(FLAGS) -c Knight.cpp

Pawn.o: Pawn.cpp Pawn.h
	$(CXX) $(FLAGS) -c Pawn.cpp

Piece.o: Piece.cpp Piece.h
	$(CXX) $(FLAGS) -c Piece.cpp

Rook.o: Rook.cpp Rook.h
	$(CXX) $(FLAGS) -c Rook.cpp

King.o: King.cpp King.h
	$(CXX) $(FLAGS) -c King.cpp

tar:
	tar cvf ex2.tar $(TARFILES1) $(TARFILES2)

valdbg: chess
	valgrind $(LC_F) $(SPL_Y) $(SR_Y) $(UVE_Y) ex2

clean:
	rm -f *.o ex2

