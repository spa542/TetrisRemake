#ifndef _TETRIS_H_
#define _TETRIS_H_
#include<iostream> // Used for error logging
#include<string> // Used for binding char array
#include<time.h> // Used for timing in tetris
#include<cstdlib> // Used for cstd lib functions
#include<ncurses.h> // Used for printing the board to the screen

enum Pieces { VertLine, HoriLine, Box, LShape, LShapeRev, ZigZag, ZigZagRev };

class TetrisGame {
    private:
        char board[40][40];
        int currentPiece;

        int findRow(); // Finds the star of the current moving block
        int findColumn(int); // Uses the row to find the column of the first block
    public:
        TetrisGame();
        TetrisGame(const TetrisGame&);
        ~TetrisGame();
        void printBoard();
        void generatePiece();
        void fall(); 
        void moveLeft();
        void moveRight();
};

#endif
