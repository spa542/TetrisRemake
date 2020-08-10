#include"TetrisGame.h" // TetrisGame
#include<time.h> // For timing
#include<stdlib.h>
#include<ncurses.h> // Game window library
#include"./TimerLibrary/timercpp.h" // External timer library

#define WAIT_TIME 2.0 // Wait time for game loop

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

        ch = getch();

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
        }, 5000);

        switch(ch) {
            case 's':
                printw("Pressed the s key\n");
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
                printw("Pressed the d key\n");
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
                printw("Pressed the a key\n");
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
                printw("Pressed the e key, exiting the loop\n");
                break;
        }
        if ( ch == 'e' ) {
            break;
        }
        clear();
        refresh();
    }
    getch();
    endwin();
    return 0;
}
