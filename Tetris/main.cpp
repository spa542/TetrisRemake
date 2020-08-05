#include"TetrisGame.h"
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
    srand(time(NULL));

    TetrisGame game;

    game.printBoard();

    game.generatePiece();

    game.printBoard();

    std::cout << "Time for the fall..." << std::endl;

    game.fall();
    game.fall();
    game.fall();
    game.fall();

    game.printBoard();

    return 0;
}
