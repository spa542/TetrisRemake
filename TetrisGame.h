#ifndef _TETRIS_H_
#define _TETRIS_H_
#include<iostream> // Used for error logging
#include<string> // Used for binding char array
#include<time.h> // Used for timing in tetris
#include<cstdlib> // Used for cstd lib functions
#include<ncurses.h> // Used for printing the board to the screen
#include<vector> // Used to hold rows that are full 

enum Pieces { VertLine, HoriLine, Box, LShape, LShapeRev, ZigZag, ZigZagRev };

struct RowData {
    bool isRowFull;
    std::vector<int> fullRows;
};

class TetrisGame {
    private:
        char board[40][40]; // Board
        int currentPiece; // Holds the integer value (enum val) for what piece is currently being moved
        bool isRotatedLeft; // To know if the shape is rotated left
        bool isRotatedRight; // To know if the shape is rotated right
        bool isUpsideDown; // To know if the shape is upside down
        int score;

        int findRow(); // Finds the star of the current moving block
        int findColumn(int); // Uses the row to find the column of the first block
    public:
        TetrisGame(); // Default Constructor
        TetrisGame(const TetrisGame&); // Copy Constructor
        ~TetrisGame(); // Destructor
        void printBoard(); // Prints the board to the screen
        void generatePiece(); // Generates a new piece to be used by the user
        void fall(); // Facilitates the handling of the down command
        void moveLeft(); // Facilitates the handling of the left command
        void moveRight(); // Facilitates the handling of the right command
        void rotateLeft(); // Rotates the piece to the left
        void rotateRight(); // Rotates the piece to the right
        bool isPieceSet(); // Checks to see if the piece has hit the "bottom"
        void convertSetPieces(); // Converts set pieces into # signs
        RowData fullRows(); // Checks to see if the row is full or not
        void clearRows(std::vector<int>); // Clears the rows by specified number in the vector
        bool isMaxColumnLoss(); // Checks to see if 'tower' reaches specified level on game map
        void lost(); // Game lost screen
};

#endif
