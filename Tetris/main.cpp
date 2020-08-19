#include"TetrisGame.h" // TetrisGame
#include<time.h> // For timing
#include<stdlib.h>
#include<ncurses.h> // Game window library
#include"./TimerLibrary/timercpp.h" // External timer library

#define WAIT_TIME 5000 // Wait time for game loop (milliseconds)

void startMenu(); // Start Menu for the game
void directions(); // Printable directions for the game

int main(int argc, char** argv) {
    srand(time(NULL));
    Timer t = Timer();

    TetrisGame game;
    initscr();
    noecho();
    cbreak();

    startMenu();

    int garb = getch();
    clear();
    refresh();

    int ch;
    game.generatePiece();
    while(true) {
        game.printBoard();

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

        ch = getch();

        switch(ch) {
            case 's':
                game.fall();
                break;
            case 'd':
                game.moveRight();
                break;
            case 'a':
                game.moveLeft();
                break;
            case 'e': 
                break;
            case 'z':
                game.rotateLeft();
                break;
            case 'x':
                game.rotateRight();
                break;
            case 'q':
                clear();
                refresh();
                directions();
                garb = getch();
                break;
        }
        if ( ch == 'e' ) {
            break;
        }
        if (game.isPieceSet()) { 
            game.convertSetPieces();
            RowData stuff = game.fullRows();
            if (stuff.isRowFull) {
                game.clearRows(stuff.fullRows);
            }
            game.generatePiece();
        }
        if (game.isMaxColumnLoss()) {
            clear();
            refresh();
            game.lost();
            garb = getch();
            break;
        }
        clear();
        refresh();
    }

    endwin();
    return 0;
}

// Start menu for the game
void startMenu() {
    printw("Welcome to Tetris Remake!\n");
    printw("Author: Ryan Rosiak\n\n");
    directions();
}

// Directions for the game
void directions() {
    printw("Directions:\n");
    printw("\t'a' - Move Left\n");
    printw("\t's' - Move Down\n");
    printw("\t'd' - Move Right\n");
    printw("\t'e' - Exit Game\n");
    printw("\t'z' - Rotate Left\n");
    printw("\t'x' - Rotate Right\n");
    printw("\t'q' - Print Directions\n");
    printw("\n\nPress any key to continue...\n");
}
