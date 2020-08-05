#include"TetrisGame.h"

TetrisGame::TetrisGame() {
    currentPiece = -1; // No current piece when game board is created
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
           if (j == 0 || j == 39) {
               board[i][j] = '|';
           } else {
               board[i][j] = ' ';
           }
        }
        if (i == 39) {
            for (int j = 0; j < 40; j++) {
                board[i][j] = '=';
            }
            break;
        }
    }
}

TetrisGame::TetrisGame(const TetrisGame& old) {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            board[i][j] = old.board[i][j];
        }
    }
}

TetrisGame::~TetrisGame() {
    
}

void TetrisGame::printBoard() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            std::cout << board[i][j];     
        }
        std::cout << std::endl; 
    }
}

void TetrisGame::generatePiece() {
    int randomPiece = rand() % 7;
    int randomStartSpot = 3 + rand() % 33;
    std::cout << "RandomPiece Number generated was " << randomPiece << std::endl;
    std::cout << "RandomStartSpot Number generated was " << randomStartSpot << std::endl;

    if (randomPiece == VertLine) {
        for (int i = 0; i < 3; i++) {
            board[i][randomStartSpot] = '*';
        }
        currentPiece = VertLine;
    }

    if (randomPiece == HoriLine) {
        for (int i = 0, start = randomStartSpot; i < 3; i++, start++) {
            board[2][start] = '*';
        }
        currentPiece = HoriLine;
    }

    if (randomPiece == Box) {
        for (int i = 1, column = randomStartSpot; i < 3; i++) {
            board[i][column] = '*';
            board[i][++column] = '*';
            column--;
        }
        currentPiece = Box;
    }

    if (randomPiece == LShape) {
        for (int i = 0, column = randomStartSpot; i < 3; i++) {
            board[i][column] = '*';
            if (i == 2) {
                board[i][column + 1] = '*';
                board[i][column + 2] = '*';
            }
        }
        currentPiece = LShape;
    }

    if (randomPiece == LShapeRev) {
        for (int i = 0, column = randomStartSpot; i < 3; i++) {
            board[i][column] = '*';
            if (i == 2) {
                board[i][column - 1] = '*';
                board[i][column - 2] = '*';
            }
        }
        currentPiece = LShapeRev;
    }

    if (randomPiece == ZigZag) {
        for (int i = 0, column = randomStartSpot; i < 3; i++) {
            if (i == 0) {
                board[i][column + 2] = '*';
            }
            if (i == 1) {
                board[i][column] = board[i][column + 1] = board[i][column + 2] = '*';
            }
            if (i == 2) {
                board[i][column] = '*';
            }
        }
        currentPiece = ZigZag;
    }

    if (randomPiece == ZigZagRev) {
        for (int i = 0, column = randomStartSpot; i < 3; i++) {
            if (i == 0) {
                board[i][column - 2] = '*';
            }
            if (i == 1) {
                board[i][column] = board[i][column - 1] = board[i][column - 2] = '*';
            }
            if (i == 2) {
                board[i][column] = '*';
            }
        }
        currentPiece = ZigZagRev;
    }
}

int TetrisGame::findRow() {
    for (int i = 0; i < 39; i++) {
        for (int j = 1; j < 39; j++) {
            if (board[i][j] == '*') {
                return i;
            }
        }
    }
    throw "This shouldn't happen";
}

int TetrisGame::findColumn(int row) {
    for (int i = 0; i < 39; i++) {
        if (board[row][i] == '*') {
            return i;
        }
    }

    throw "This shouldn't happen either";
}

void TetrisGame::fall() {
    int row, column;
    try {
        row = findRow();
        column = findColumn(row);
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    if (currentPiece == VertLine) {
        board[row][column] = ' ';
        board[row + 3][column] = '*';
        return;
    }

    if (currentPiece == HoriLine) {
        board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
        board[row + 1][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = '*';
        return;
    }

    if (currentPiece == Box) {
        board[row][column] = board[row][column + 1] = ' ';
        board[row + 2][column] = board[row + 2][column + 1] = ' ';
        return;
    }
    
    if (currentPiece == LShape) {
        board[row][column] = board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
        board[row + 3][column] = board[row + 3][column + 1] = board[row + 3][column + 2] = '*';
        return;
    }

    if (currentPiece == LShapeRev) {
        board[row][column] = board[row + 2][column - 1] = board[row + 2][column - 2] = ' ';
        board[row + 3][column] = board[row + 3][column - 1] = board[row + 3][column - 2] = '*';
        return;
    }
    
    if (currentPiece == ZigZag) {
        board[row][column] = board[row + 1][column - 1] = board[row + 1][column - 2] = ' ';
        board[row + 2][column - 1] = board[row + 2][column] = board[row + 3][column - 2] = '*';
        return;
    }

    if (currentPiece == ZigZagRev) {
        board[row][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = ' ';
        board[row + 2][column + 1] = board[row + 2][column] = board[row + 3][column + 2] = '*';
        return;
    }
}
