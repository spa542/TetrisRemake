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
            printw("%c", board[i][j]);     
        }
        printw("\n");
    }
}

void TetrisGame::generatePiece() {
    int randomPiece = rand() % 7;
    int randomStartSpot = 3 + rand() % 33;
    //std::cout << "RandomPiece Number generated was " << randomPiece << std::endl;
    //std::cout << "RandomStartSpot Number generated was " << randomStartSpot << std::endl;

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
        if (board[row + 3][column] == '=' || board[row + 3][column] == '#') {
            return;
        }
        board[row][column] = ' ';
        board[row + 3][column] = '*';
        return;
    }

    if (currentPiece == HoriLine) {
        if (board[row + 1][column] == '=' || board[row + 1][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#' ||
                board[row + 1][column + 2] == '=' || board[row + 1][column + 2] == '#') {
            return;
        }
        board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
        board[row + 1][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = '*';
        return;
    }

    if (currentPiece == Box) {
        if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column + 1] == '=' || board[row + 2][column + 1] == '#') {
            return;
        }
        board[row][column] = board[row][column + 1] = ' ';
        board[row + 2][column] = board[row + 2][column + 1] = '*';
        return;
    }
    
    if (currentPiece == LShape) {
        if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column + 1] == '=' || board[row + 3][column + 1] == '#' ||
                board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
            return;
        }
        board[row][column] = board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
        board[row + 3][column] = board[row + 3][column + 1] = board[row + 3][column + 2] = '*';
        return;
    }

    if (currentPiece == LShapeRev) {
        if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column - 1] == '=' || board[row + 3][column - 1] == '#' ||
                board[row + 3][column - 2] == '=' || board[row + 3][column - 2] == '#') {
            return;
        }
        board[row][column] = board[row + 2][column - 1] = board[row + 2][column - 2] = ' ';
        board[row + 3][column] = board[row + 3][column - 1] = board[row + 3][column - 2] = '*';
        return;
    }
    
    if (currentPiece == ZigZag) {
        if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column - 1] == '=' || board[row + 2][column - 1] == '#' ||
                board[row + 3][column - 2] == '=' || board[row + 3][column - 2] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column - 1] = board[row + 1][column - 2] = ' ';
        board[row + 2][column - 1] = board[row + 2][column] = board[row + 3][column - 2] = '*';
        return;
    }

    if (currentPiece == ZigZagRev) {
        if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column + 1] == '=' || board[row + 2][column + 1] == '#' ||
                board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = ' ';
        board[row + 2][column + 1] = board[row + 2][column] = board[row + 3][column + 2] = '*';
        return;
    }
}

void TetrisGame::moveLeft() {
    int row, column;
    try {
        row = findRow();
        column = findColumn(row);
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    if (currentPiece == VertLine) {
        if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' ||
                board[row + 1][column - 1] == '|' || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
        board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
        return;
    }

    if (currentPiece == HoriLine) {
        if (board[row][column - 1] == '|' || board[row][column - 1] == '#') {
            return;
        }
        board[row][column + 2] = ' ';
        board[row][column - 1] = '*';
        return;
    }

    if (currentPiece == Box) {
        if (board[row][column - 1] == '|' || board[row][column - 1] == '#' || board[row + 1][column - 1] == '|' ||
                board[row + 1][column - 1] == '#') {
            return;
        }
        board[row][column + 1] = board[row + 1][column + 1] = ' ';
        board[row][column - 1] = board[row + 1][column - 1] = '*';
        return;
    }
    
    if (currentPiece == LShape) {
        if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' ||
                board[row + 1][column - 1] == '|' || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column + 2] = ' ';
        board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
        return;
    }

    if (currentPiece == LShapeRev) {
        if (board[row + 2][column - 3] == '|' || board[row + 2][column - 3] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
        board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 3] = '*';
        return;
    }
    
    if (currentPiece == ZigZag) {
        if (board[row][column - 1] == '|' || board[row][column - 1] == '#' || board[row + 1][column - 3] == '|' || board[row + 1][column - 3] == '#'
                || board[row + 2][column - 3] == '|' || board[row + 2][column - 3] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column - 2] = ' ';
        board[row][column - 1] = board[row + 1][column - 3] = board[row + 2][column - 3] = '*';
        return;
    }

    if (currentPiece == ZigZagRev) {
        if (board[row][column - 1] == '|' || board[row][column - 1] == '#' || board[row + 1][column - 1] == '|' || board[row + 1][column - 1] == '#'
                || board[row + 2][column + 1] == '|' || board[row + 2][column + 1] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
        board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column + 1] = '*';
    }
}

void TetrisGame::moveRight() {
    int row, column;
    try {
        row = findRow();
        column = findColumn(row);
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    if (currentPiece == VertLine) {
        if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#'
                || board[row + 2][column + 1] == '|' || board[row + 2][column + 1] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
        board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
        return;
    }

    if (currentPiece == HoriLine) {
        if (board[row][column + 3] == '|' || board[row][column + 3] == '#') {
            return;
        }
        board[row][column] = ' ';
        board[row][column + 3] = '*';
        return;
    }

    if (currentPiece == Box) {
        if (board[row][column + 2] == '|' || board[row][column + 2] == '#' || board[row + 1][column + 2] == '|' || board[row + 1][column + 2] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column] = ' ';
        board[row][column + 2] = board[row + 1][column + 2] = '*';
        return;
    }
    
    if (currentPiece == LShape) {
        if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#' ||
                board[row + 2][column + 3] == '|' || board[row + 2][column + 3] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
        board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 3] = '*';
        return;
    }

    if (currentPiece == LShapeRev) {
        if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#' ||
                board[row + 2][column + 1] == '|' || board[row + 2][column + 1] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column - 2] = ' ';
        board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
        return;
    }
    
    if (currentPiece == ZigZag) {
        if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#' ||
                board[row + 2][column - 1] == '|' || board[row + 2][column - 1] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column - 2] = board[row + 2][column - 2] = ' ';
        board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column - 1] = '*';
        return;
    }

    if (currentPiece == ZigZagRev) {
        if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 3] == '|' || board[row + 1][column + 3] == '#' ||
                board[row + 2][column + 3] == '|' || board[row + 2][column + 3] == '#') {
            return;
        }
        board[row][column] = board[row + 1][column] = board[row + 2][column + 2] = ' ';
        board[row][column + 1] = board[row + 1][column + 3] = board[row + 2][column + 3] = '*';
        return;
    }
}

bool TetrisGame::isPieceSet() {
    int row, column;
    try {
        row = findRow();
        column = findColumn(row);
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    if (currentPiece == VertLine) {
        if (board[row + 3][column] == '=' || board[row + 3][column] == '#') {
            return true;
        }
        return false;
    }

    if (currentPiece == HoriLine) {
        if (board[row + 1][column] == '=' || board[row + 1][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#' ||
                board[row + 1][column + 2] == '=' || board[row + 1][column + 2] == '#') {
            return true;
        }
        return false;
    }

    if (currentPiece == Box) {
        if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column + 1] == '=' || board[row + 2][column + 1] == '#') {
            return true;
        }
        return false;
    }
    
    if (currentPiece == LShape) {
        if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column + 1] == '=' || board[row + 3][column + 1] == '#' ||
                board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
            return true;
        }
        return false;
    }

    if (currentPiece == LShapeRev) {
        if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column - 1] == '=' || board[row + 3][column - 1] == '#' ||
                board[row + 3][column - 2] == '=' || board[row + 3][column - 2] == '#') {
            return true;
        }
        return false;
    }
    
    if (currentPiece == ZigZag) {
        if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column - 1] == '=' || board[row + 2][column - 1] == '#' ||
                board[row + 3][column - 2] == '=' || board[row + 3][column - 2] == '#') {
            return true;
        }
        return false;
    }

    if (currentPiece == ZigZagRev) {
        if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column + 1] == '=' || board[row + 2][column + 1] == '#' ||
                board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
            return true;
        }
        return false;
    }
    return false;
}

void TetrisGame::convertSetPieces() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            if (board[i][j] == '*') {
                board[i][j] = '#';
            }
        }
    }
}

RowData TetrisGame::fullRows() {
    RowData stuff;
    bool isFull = false;
    for (int i = 0; i < 39; i++) {
        for (int j = 1; j < 39; j++) {
            if (board[i][j] != '#') {
                isFull = false;
                break;
            }
            isFull = true;
        }
        if (isFull) {
            stuff.fullRows.push_back(i);
            isFull = false;
        }
    }
    return stuff;
}

void TetrisGame::clearRows(std::vector<int> rowsToDel) {
    for (std::vector<int>::iterator i = rowsToDel.begin(); i != rowsToDel.end(); ++i) {
        for (int j = 1; j < 39; j++) {
            board[*i][j] = ' ';
        }
    }

    // Still need to reformat the array to make up for lost row
}
