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
                break;
            case 'd':
                printw("Pressed the d key\n");
                game.moveRight();
                break;
            case 'a':
                printw("Pressed the a key\n");
                game.moveLeft();
                break;
            case 'e': 
                printw("Pressed the e key, exiting the loop\n");
                break;
        }
        if ( ch == 'e' ) {
            break;
        }
        getch();
        clear();
        refresh();
    }
    getch();
    endwin();
    return 0;
}
