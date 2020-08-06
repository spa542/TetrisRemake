main: main.o TetrisGame.o
	g++ -o main main.o TetrisGame.o -lncurses -std=c++11 -g 
main.o: main.cpp TetrisGame.h
	g++ -c main.cpp -std=c++11 -g
TetrisGame.o: TetrisGame.h TetrisGame.cpp
	g++ -c TetrisGame.cpp -std=c++11 -g
clean:
	rm -f *.o main
