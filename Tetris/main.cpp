#include"TetrisGame.h" // TetrisGame
#include<time.h>
#include<stdlib.h>
#include<ncurses.h> // Game window library

int main() {
    srand(time(NULL));

    TetrisGame game;
    initscr();
    noecho();
    cbreak();

    int ch;
    game.generatePiece();
    while(true) {
        game.printBoard();
        ch = getch();
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
