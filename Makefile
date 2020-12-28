main: main.o TetrisGame.o
	g++ -o main main.o TetrisGame.o -lncurses -pthread -std=c++17 -g 
main.o: main.cpp TetrisGame.h
	g++ -c main.cpp -std=c++17 -g
TetrisGame.o: TetrisGame.h TetrisGame.cpp
	g++ -c TetrisGame.cpp -std=c++17 -g
clean:
	rm -f *.o main
