#ifndef _TETRIS_H_
#define _TETRIS_H_
#include<iostream>
#include<string>
#include<time.h>
#include<cstdlib>

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
};

#endif
