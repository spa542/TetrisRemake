#include"TetrisGame.h" // TetrisGame
#include<time.h> // For timing
#include<stdlib.h>
#include<ncurses.h> // Game window library
#include"./TimerLibrary/timercpp.h" // External timer library

#define WAIT_TIME 5000 // Wait time for game loop (milliseconds)

int main() {
    srand(time(NULL));
    Timer t = Timer();

    TetrisGame game;
    initscr();
    noecho();
    cbreak();

    int ch;
    game.generatePiece();
    while(true) {
        game.printBoard();
/*
        // Set the time interval that will run in the main game loop
        t.setTimeout([&]() {
            game.fall();
            if (game.isPieceSet()) {
                game.convertSetPieces();
                RowData stuff = game.fullRows();
                if (stuff.isRowFull) {
                    game.clearRows(stuff.fullRows);
                }
                game.generatePiece();
            }
            t.stop();
        }, WAIT_TIME);
*/
        ch = getch();

        switch(ch) {
            case 's':
                game.fall();
                if (game.isPieceSet()) {
                    game.convertSetPieces();
                    RowData stuff = game.fullRows();
                    if (stuff.isRowFull) {
                        game.clearRows(stuff.fullRows); 
                    }
                    game.generatePiece();
                }
                break;
            case 'd':
                game.moveRight();
                if (game.isPieceSet()) {
                    game.convertSetPieces();
                    RowData stuff = game.fullRows();
                    if (stuff.isRowFull) {
                        game.clearRows(stuff.fullRows); 
                    }
                    game.generatePiece();
                }
                break;
            case 'a':
                game.moveLeft();
                if (game.isPieceSet()) { 
                    game.convertSetPieces();
                    RowData stuff = game.fullRows();
                    if (stuff.isRowFull) {
                        game.clearRows(stuff.fullRows);
                    }
                    game.generatePiece();
                }
                break;
            case 'e': 
                break;
            case 'z':
                game.rotateLeft();
                if (game.isPieceSet()) { 
                    game.convertSetPieces();
                    RowData stuff = game.fullRows();
                    if (stuff.isRowFull) {
                        game.clearRows(stuff.fullRows);
                    }
                    game.generatePiece();
                }
                break;
            case 'x':
                game.rotateRight();
                if (game.isPieceSet()) { 
                    game.convertSetPieces();
                    RowData stuff = game.fullRows();
                    if (stuff.isRowFull) {
                        game.clearRows(stuff.fullRows);
                    }
                    game.generatePiece();
                }
                break;
        }
        if ( ch == 'e' ) {
            break;
        }
        clear();
        refresh();
    }
    endwin();
    return 0;
}
