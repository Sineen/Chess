
CXX = g++
OBJECTS = Board.o Piece.o Square.o
FLAGS = -Wextra -Wall -Wvla -std=c++17 -pthread -g -DNDEBUG
TARFILES1 = enums.h Game.cpp Game.h Board.cpp Board.h Piece.cpp Piece.h Square.cpp Square.h
TARFILES2 = Makefile
LC_F = --leak-check=full
SPL_Y = --show-possibly-lost=yes
SR_Y = --show-reachable=yes
UVE_Y = --undef-value-errors=yes

all: Game

Game: $(OBJECTS)
	$(CXX) $(FLAGS) -c Game.cpp -o Game.o
	$(CXX) $(FLAGS) $(OBJECTS) Game.o -o ex2

Game.o: Game.cpp Game.h enums.h
	$(CXX) $(FLAGS) -c Game.cpp

Board.o: Board.cpp Board.h enums.h
	$(CXX) $(FLAGS) -c Board.cpp

Piece.o: Piece.cpp Piece.h enums.h
	$(CXX) $(FLAGS) -c Piece.cpp

Square.o: Square.cpp Square.h enums.h
	$(CXX) $(FLAGS) -c Square.cpp


tar:
	tar cvf ex2.tar $(TARFILES1) $(TARFILES2)

valdbg: chess
	valgrind $(LC_F) $(SPL_Y) $(SR_Y) $(UVE_Y) ex2

clean:
	rm -f *.o ex2

