#include"TetrisGame.h"

TetrisGame::TetrisGame() {
    currentPiece = -1; // No current piece when game board is created
    isRotatedLeft = isRotatedRight = isUpsideDown = false; // Starts in normal position
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
    isRotatedLeft = isRotatedRight = isUpsideDown = false; // Starts in normal position
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
        // If rotated, will be a horizontal line (movement)
        if (isRotatedLeft || isRotatedRight) {
            // Rotation collision
            if (board[row + 1][column] == '=' || board[row + 1][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#'
                    || board[row + 1][column + 2] == '=' || board[row + 1][column + 2] == '#') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 1][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = '*';
            return;
        } else {
            // Default shape collision detected
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#') {
                return;
            }
            // Default shape movement
            board[row][column] = ' ';
            board[row + 3][column] = '*';
            return;
        }
    }

    if (currentPiece == HoriLine) {
        // If rotated, will be a vertical line (movement)
        if (isRotatedLeft || isRotatedRight) {
            // Rotation collision
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#') {
                return;
            }
            board[row][column] = ' ';
            board[row + 3][column] = '*';
            return;
        } else {
            // Default shape collision detection
            if (board[row + 1][column] == '=' || board[row + 1][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#' ||
                    board[row + 1][column + 2] == '=' || board[row + 1][column + 2] == '#') {
                return;
            }
            // Default shape movement
            board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 1][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = '*';
            return;
        }
    }

    if (currentPiece == Box) {
        if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column + 1] == '=' || board[row + 2][column + 1] == '#') {
            return;
        }
        /* Will never have rotation logic since the shape will always be the same */
        board[row][column] = board[row][column + 1] = ' ';
        board[row + 2][column] = board[row + 2][column + 1] = '*';
        return;
    }
    
    if (currentPiece == LShape) {
        // Right rotation movement
        if (isRotatedRight) {
            // Right rotation collision
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column - 1] == '=' || board[row + 3][column - 1] == '#'
                    || board[row + 3][column - 2] == '=' || board[row + 3][column - 2] == '#') {
                return;
            }
            board[row][column] = board[row + 2][column - 1] = board[row + 2][column - 2] = ' ';
            board[row + 3][column] = board[row + 3][column - 1] = board[row + 3][column - 2] = '*';
            return;
        }
        // Left rotation movement
        else if (isRotatedLeft) {
            // Left rotation collision
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#'
                    || board[row + 1][column + 2] == '=' || board[row + 1][column + 2] == '#') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 3][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = '*';
            return;
        }
        // Upside down rotation movement
        else if (isUpsideDown) {
            // Upside down collision
            if (board[row + 1][column] == '=' || board[row + 1][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#'
                    || board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 1][column] = board[row + 1][column + 1] = board[row + 3][column + 2] = '*';
            return;
        } else {
            // Default collsion
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column + 1] == '=' || board[row + 3][column + 1] == '#' ||
                    board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
                return;
            }
            // Default shape movement 
            board[row][column] = board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
            board[row + 3][column] = board[row + 3][column + 1] = board[row + 3][column + 2] = '*';
            return;
        }
    }

    if (currentPiece == LShapeRev) {
        // Right rotation movement
        if (isRotatedRight) {
            // Right rotation collision
            if (board[row + 1][column] == '=' || board[row + 1][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#'
                    || board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 1][column] = board[row + 1][column + 1] = board[row + 3][column + 2] = '*';
            return;
        }
        // Left rotation movement
        else if (isRotatedLeft) {
            // Left rotation collision
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column + 1] == '=' || board[row + 3][column + 1] == '#' ||
                    board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
                return;
            }
            board[row][column] = board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
            board[row + 3][column] = board[row + 3][column + 1] = board[row + 3][column + 2] = '*';
            return;
        }
        // Upside down rotation movement
        else if (isUpsideDown) {
            // Upside down collision
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#'
                    || board[row + 1][column + 2] == '=' || board[row + 1][column + 2] == '#') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 3][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = '*';
            return;
        } else {
            // Default collision
            if (board[row + 3][column] == '=' || board[row + 3][column] == '#' || board[row + 3][column - 1] == '=' || board[row + 3][column - 1] == '#' ||
                    board[row + 3][column - 2] == '=' || board[row + 3][column - 2] == '#') {
                return;
            }
            board[row][column] = board[row + 2][column - 1] = board[row + 2][column - 2] = ' ';
            board[row + 3][column] = board[row + 3][column - 1] = board[row + 3][column - 2] = '*';
            return;
        }
    }
    
    if (currentPiece == ZigZag) {
        // Will be the same shape on either rotation, rotational movement
        if (isRotatedLeft || isRotatedRight) {
            // Rotation collision
            if (board[row + 1][column] == '=' || board[row + 1][column] == '#' || board[row + 3][column + 1] == '=' || board[row + 3][column + 1] == '#'
                    || board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row + 2][column + 2] = ' ';
            board[row + 1][column] = board[row + 3][column + 1] = board[row + 3][column + 2] = '*';
            return;
        } else {
            // Default collision
            if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column - 1] == '=' || board[row + 2][column - 1] == '#' ||
                    board[row + 3][column - 2] == '=' || board[row + 3][column - 2] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column - 1] = board[row + 1][column - 2] = ' ';
            board[row + 2][column - 1] = board[row + 2][column] = board[row + 3][column - 2] = '*';
            return;
        }
    }

    if (currentPiece == ZigZagRev) {
        // Will be the same shape on either rotation, rotational movement
        if (isRotatedRight || isRotatedLeft) {
            // Rotation collision
            if (board[row + 1][column + 1] == '=' || board[row + 1][column + 1] == '#' || board[row + 3][column] == '=' || board[row + 3][column] == '#'
                    || board[row + 3][column - 1] == '=' || board[row + 3][column - 1] == '#') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row + 2][column - 1] = ' ';
            board[row + 1][column + 1] = board[row + 3][column] = board[row + 3][column - 1] = '*';
            return;
        } else {
            // Default collision
            if (board[row + 2][column] == '=' || board[row + 2][column] == '#' || board[row + 2][column + 1] == '=' || board[row + 2][column + 1] == '#' ||
                    board[row + 3][column + 2] == '=' || board[row + 3][column + 2] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column + 1] = board[row + 1][column + 2] = ' ';
            board[row + 2][column + 1] = board[row + 2][column] = board[row + 3][column + 2] = '*';
            return;
        }
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
        // Will be a horizontal line
        if (isRotatedLeft || isRotatedRight) {
            // Rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|') {
                return;
            }
            board[row][column + 2] = ' '; 
            board[row][column - 1] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' ||
                    board[row + 1][column - 1] == '|' || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
            return;
        }
    }

    if (currentPiece == HoriLine) {
        // Will be a vertical line
        if (isRotatedLeft || isRotatedRight) {
            // Rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|'
                    || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column - 1] == '|' || board[row][column - 1] == '#') {
                return;
            }
            // Default movement
            board[row][column + 2] = ' ';
            board[row][column - 1] = '*';
            return;
        }
    }

    if (currentPiece == Box) {
        if (board[row][column - 1] == '|' || board[row][column - 1] == '#' || board[row + 1][column - 1] == '|' ||
                board[row + 1][column - 1] == '#') {
            return;
        }
        // Will never have rotational logic because shape is never changed
        board[row][column + 1] = board[row + 1][column + 1] = ' ';
        board[row][column - 1] = board[row + 1][column - 1] = '*';
        return;
    }
    
    if (currentPiece == LShape) {
        // Left rotation movement
        if (isRotatedLeft) {
            // Left rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|'
                    || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
                return;
            }
            board[row][column + 2] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
            return;
        }
        // Right rotation movement
        else if (isRotatedRight) {
            // Right rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|'
                    || board[row + 2][column - 3] == '#' || board[row + 2][column - 3] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 3] = '*';
            return;
        }
        // Upside down rotation movement
        else if (isUpsideDown) {
            // Upside down collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|'
                    || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column + 2] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row][column - 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' ||
                    board[row + 1][column - 1] == '|' || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column + 2] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
            return;
        }
    }

    if (currentPiece == LShapeRev) {
        // Left rotation movement
        if (isRotatedLeft) {
            // Left rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' ||
                    board[row + 1][column - 1] == '|' || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column + 2] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
            return;
        }
        // Right rotation movement
        else if (isRotatedRight) {
            // Right rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|'
                    || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column + 2] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row][column - 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            return;
        }
        // Upside down rotation movement
        else if (isUpsideDown) {
            // Upside down collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|'
                    || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|') {
                return;
            }
            board[row][column + 2] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 1] = '*';
            return;
        } else {
            // Default collision
            if (board[row + 2][column - 3] == '|' || board[row + 2][column - 3] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 3] = '*';
            return;
        }
    }
    
    if (currentPiece == ZigZag) {
        // Will be the same shape on either rotation (movement) 
        if (isRotatedRight || isRotatedLeft) {
            // Rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column] == '#' || board[row + 1][column] == '|'
                    || board[row + 2][column] == '#' || board[row + 2][column] == '|') {
                return;
            }
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 2] = ' ';
            board[row][column - 1] = board[row + 1][column] = board[row + 2][column] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column - 1] == '|' || board[row][column - 1] == '#' || board[row + 1][column - 3] == '|' || board[row + 1][column - 3] == '#'
                    || board[row + 2][column - 3] == '|' || board[row + 2][column - 3] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column - 2] = ' ';
            board[row][column - 1] = board[row + 1][column - 3] = board[row + 2][column - 3] = '*';
            return;
        }
    }

    if (currentPiece == ZigZagRev) {
        // Will be the same shape on either rotation (movement)
        if (isRotatedRight || isRotatedLeft) {
            // Rotation collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|'
                    || board[row + 2][column - 2] == '#' || board[row + 2][column - 2] == '|') {
                return;
            }
            board[row][column + 1] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column - 2] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column - 1] == '|' || board[row][column - 1] == '#' || board[row + 1][column - 1] == '|' || board[row + 1][column - 1] == '#'
                    || board[row + 2][column + 1] == '|' || board[row + 2][column + 1] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 2][column + 1] = '*';
            return;
        }
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
        // Will be a horizontal line
        if (isRotatedRight || isRotatedLeft) {
            // Rotation collision
            if (board[row][column + 3] == '#' || board[row][column + 3] == '|') {
                return;
            }
            board[row][column] = ' ';
            board[row][column + 3] = '*';
            return;  
        } else {
            // Default collision
            if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#'
                    || board[row + 2][column + 1] == '|' || board[row + 2][column + 1] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            return;
        }
    }

    if (currentPiece == HoriLine) {
        // Will be a vertical line
        if (isRotatedRight || isRotatedLeft) {
            // Rotation collision
            if (board[row][column + 1] == '#' || board[row][column + 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|'
                    || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column + 3] == '|' || board[row][column + 3] == '#') {
                return;
            }
            // Default movement
            board[row][column] = ' ';
            board[row][column + 3] = '*';
            return;
        }
    }

    if (currentPiece == Box) {
        if (board[row][column + 2] == '|' || board[row][column + 2] == '#' || board[row + 1][column + 2] == '|' || board[row + 1][column + 2] == '#') {
            return;
        }
        // No rotational logic needed because shape will never change
        board[row][column] = board[row + 1][column] = ' ';
        board[row][column + 2] = board[row + 1][column + 2] = '*';
        return;
    }
    
    if (currentPiece == LShape) {
        // Left rotation movement
        if (isRotatedLeft) {
            // Left rotation collision
            if (board[row][column + 3] == '#' || board[row][column + 3] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|'
                    || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row + 1][column + 1] = board[row + 2][column + 1] = board[row][column + 3] = '*';
            return;
        }
        // Right rotation movement
        else if (isRotatedRight) {
            // Right rotation collision
            if (board[row][column + 1] == '#' || board[row][column + 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|'
                    || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column - 2] = ' ';
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            return;
        }
        // Upside down rotation movement
        else if (isUpsideDown) {
            // Upside down collision
            if (board[row][column + 3] == '#' || board[row][column + 3] == '|' || board[row + 1][column + 3] == '#' || board[row + 1][column + 3] == '|'
                    || board[row + 2][column + 3] == '#' || board[row + 2][column + 3] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row][column + 3] = board[row + 1][column + 3] = board[row + 2][column + 3] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#' ||
                    board[row + 2][column + 3] == '|' || board[row + 2][column + 3] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 3] = '*';
            return;
        }
    }

    if (currentPiece == LShapeRev) {
        // Left rotation movement
        if (isRotatedLeft) {
            // Left rotation collision
            if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#' ||
                    board[row + 2][column + 3] == '|' || board[row + 2][column + 3] == '#') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 3] = '*';
            return;
        }
        // Right rotation movement
        else if (isRotatedRight) {
            // Right rotation collision
            if (board[row][column + 3] == '#' || board[row][column + 3] == '|' || board[row + 1][column + 3] == '#' || board[row + 1][column + 3] == '|'
                    || board[row + 2][column + 3] == '#' || board[row + 2][column + 3] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row][column + 3] = board[row + 1][column + 3] = board[row + 2][column + 3] = '*';
            return;
        }
        // Upside down rotation movement
        else if (isUpsideDown) {
            // Upside down collision
            if (board[row][column + 3] == '#' || board[row][column + 3] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|'
                    || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column] = ' ';
            board[row + 1][column + 1] = board[row + 2][column + 1] = board[row][column + 3] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#' ||
                    board[row + 2][column + 1] == '|' || board[row + 2][column + 1] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column - 2] = ' ';
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            return;
        }
    }
    
    if (currentPiece == ZigZag) {
        // Will be the same shape regardless of rotation (movement)
        if (isRotatedLeft || isRotatedRight) {
            // Rotation collision
            if (board[row][column + 2] == '#' || board[row][column + 2] == '|' || board[row + 1][column + 2] == '#' || board[row + 1][column + 2] == '|'
                    || board[row + 3][column + 3] == '#' || board[row + 2][column + 3] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column + 1] = board[row + 2][column + 1] = ' ';
            board[row][column + 2] = board[row + 1][column + 2] = board[row + 2][column + 3] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 1][column + 1] == '#' ||
                    board[row + 2][column - 1] == '|' || board[row + 2][column - 1] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column - 2] = board[row + 2][column - 2] = ' ';
            board[row][column + 1] = board[row + 1][column + 1] = board[row + 2][column - 1] = '*';
            return;
        }
    }

    if (currentPiece == ZigZagRev) {
        // Will be the same shape regardless of rotation (movement)
        if (isRotatedLeft || isRotatedRight) {
            // Rotation collision
            if (board[row][column + 2] == '#' || board[row][column + 2] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|'
                    || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 2][column - 1] = ' ';
            board[row][column + 2] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            return;
        } else {
            // Default collision
            if (board[row][column + 1] == '|' || board[row][column + 1] == '#' || board[row + 1][column + 3] == '|' || board[row + 1][column + 3] == '#' ||
                    board[row + 2][column + 3] == '|' || board[row + 2][column + 3] == '#') {
                return;
            }
            // Default movement
            board[row][column] = board[row + 1][column] = board[row + 2][column + 2] = ' ';
            board[row][column + 1] = board[row + 1][column + 3] = board[row + 2][column + 3] = '*';
            return;
        }
    }
}

void TetrisGame::rotateLeft() {
    int row, column;
    try {
        row = findRow();
        column = findColumn(row);
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    if (currentPiece == VertLine) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 2][column] = ' ';
            board[row + 1][column - 1] = board[row + 1][column + 1] = '*';
            isRotatedLeft = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row - 1][column + 1] == '#' || board[row - 1][column + 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 2] = ' ';
            board[row - 1][column + 1] = board[row + 1][column + 1] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
    }

    if (currentPiece == HoriLine) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row - 1][column + 1] == '#' || board[row - 1][column + 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 2] = ' ';
            board[row - 1][column + 1] = board[row + 1][column + 1] = '*';
            isRotatedLeft = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 2][column] = ' ';
            board[row + 1][column - 1] = board[row + 1][column + 1] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
    }

    if (currentPiece == Box) {
        return;
    }
    
    if (currentPiece == LShape) {
        if (!isRotatedLeft && !isRotatedRight && !isUpsideDown) {
            // Collision
            if (board[row][column + 1] == '#' || board[row][column + 1] == '|' || board[row][column + 2] == '#' || board[row][column + 2] == '|') {
                return;
            }
            board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
            board[row][column + 1] = board[row][column + 2] = '*';
            isRotatedLeft = true;
            return;
        }
        if (isRotatedRight) {
            // Collision
            if (board[row][column - 2] == '#' || board[row][column - 2] == '|' || board[row + 1][column - 2] == '#' || board[row + 1][column - 2] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = ' ';
            board[row][column - 2] = board[row + 1][column - 2] = '*';
            isRotatedRight = false;
            return;
        }
        if (isRotatedLeft) {
            // Collision
            if (board[row + 1][column + 2] == '#' ||  board[row + 1][column + 2] == '|' || board[row + 2][column + 2] == '#' || board[row + 2][column + 2] == '|') {
                return;
            }
            board[row + 1][column] = board[row + 2][column] = ' ';
            board[row + 1][column + 2] = board[row + 2][column + 2] = '*';
            isUpsideDown = true;
            isRotatedLeft = false;
            return;
        }
        if (isUpsideDown) {
            // Collision
            if (board[row + 1][column] == '#' || board[row + 1][column] == '|' || board[row + 2][column] == '#' || board[row + 2][column] == '|') {
                return;
            }
            board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row + 1][column] = board[row + 2][column] = '*';
            isUpsideDown = false;
            isRotatedLeft = true;
            return;
        }
    }

    if (currentPiece == LShapeRev) {
        if (!isRotatedLeft && !isRotatedRight && !isUpsideDown) {
            // Collision 
            if (board[row][column - 2] == '#' || board[row][column - 2] == '|' || board[row + 1][column - 2] == '#' || board[row + 1][column - 2] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = ' ';
            board[row][column - 2] = board[row + 1][column - 2] = '*';
            isRotatedLeft = true;
            return;
        }
        if (isRotatedLeft) {
            // Collision
            if (board[row][column + 1] == '#' || board[row][column + 1] == '|' || board[row][column + 2] == '#' || board[row][column + 2] == '|') {
                return;
            }
            board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
            board[row][column + 1] = board[row][column + 2] = '*';
            isUpsideDown = true;
            isRotatedLeft = false;
            return;
        }
        if (isRotatedRight) {
            // Collision
            if (board[row + 2][column] == '#' || board[row + 2][column] == '|' || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 1] = ' ';
            board[row + 2][column] = board[row + 2][column + 1] = '*';
            isRotatedRight = false;
            return;
        }
        if (isUpsideDown) {
            // Collision
            if (board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|' || board[row + 2][column + 2] == '#' || board[row + 2][column + 2] == '|') {
                return;
            }
            board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 2][column + 1] = board[row + 2][column + 2] = '*';
            isUpsideDown = false;
            isRotatedLeft = true;
            return;
        }
    }
    
    if (currentPiece == ZigZag) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row + 2][column] == '#' || board[row + 2][column] == '|' || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|'
                    || board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row][column - 2] == '#' || board[row][column - 2] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 1][column - 2] = board[row + 2][column - 2] = ' ';
            board[row + 2][column] = board[row + 2][column - 1] = board[row][column - 1] = board[row][column - 2] = '*';
            isRotatedLeft = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row][column + 2] == '#' || board[row][column + 2] == '|' || board[row + 1][column + 2] == '#' || board[row + 1][column + 2] == '|'
                    || board[row + 1][column] == '#' || board[row + 1][column] == '|' || board[row + 2][column] == '#' || board[row + 2][column] == '|') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
            board[row][column + 2] = board[row + 1][column + 2] = board[row + 1][column] = board[row + 2][column] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
    }

    if (currentPiece == ZigZagRev) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row][column + 1] == '#' || board[row][column + 1] == '|' || board[row][column + 2] == '#' || board[row][column + 2] == '|'
                    || board[row + 2][column] == '#' || board[row + 2][column] == '|' || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row][column + 1] = board[row][column + 2] = board[row + 2][column] = board[row + 2][column + 1] = '*';
            isRotatedLeft = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|'
                    || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row + 2][column] = board[row + 2][column - 1] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
    }
}

void TetrisGame::rotateRight() {
    int row, column;
    try {
        row = findRow();
        column = findColumn(row);
    } catch(const char* e) {
        std::cout << e << std::endl;
    }

    if (currentPiece == VertLine) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row + 1][column - 1] == '#' ||  board[row + 1][column - 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 2][column] = ' ';
            board[row + 1][column - 1] = board[row + 1][column + 1] = '*';
            isRotatedRight = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row - 1][column + 1] == '#' || board[row - 1][column + 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 2] = ' ';
            board[row - 1][column + 1] = board[row + 1][column + 1] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
    }

    if (currentPiece == HoriLine) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row - 1][column + 1] == '#' || board[row - 1][column + 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 2] = ' ';
            board[row - 1][column + 1] = board[row + 1][column + 1] = '*';
            isRotatedRight = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|' || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 2][column] = ' ';
            board[row + 1][column - 1] = board[row + 1][column + 1] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
    }

    if (currentPiece == Box) {
        return;
    }
    
    if (currentPiece == LShape) {
        if (!isRotatedRight && !isRotatedLeft && !isUpsideDown) {
            // Collision
            if (board[row][column + 2] == '#' || board[row][column + 2] == '|' || board[row + 1][column + 2] == '#' || board[row + 1][column + 2] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = ' ';
            board[row][column + 2] = board[row + 1][column + 2] = '*';
            isRotatedRight = true;
            return;
        }
        if (isRotatedRight) {
            // Collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row][column - 2] == '#' || board[row][column - 2] == '|') {
                return;
            }
            board[row + 2][column - 1] = board[row + 2][column - 2] = ' ';
            board[row][column - 1] = board[row][column - 2] = '*';
            isRotatedRight = false;
            isUpsideDown = true;
            return;
        }
        if (isRotatedLeft) {
            // Collision
            if (board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|' || board[row + 2][column + 2] == '#' || board[row + 2][column + 2] == '|') {
                return;
            }
            board[row][column + 1] = board[row][column + 2] = ' ';
            board[row + 2][column + 1] = board[row + 2][column + 2] = '*';
            isRotatedLeft = false;
            return;
        }
        if (isUpsideDown) {
            // Collision
            if (board[row + 2][column] == '#' || board[row + 2][column] == '|' || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 1] = ' ';
            board[row + 2][column] = board[row + 2][column + 1] = '*';
            isUpsideDown = false;
            isRotatedRight = true;
            return;
        }
    }

    if (currentPiece == LShapeRev) {
        if (!isRotatedLeft && !isRotatedRight && !isUpsideDown) {
            // Collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row][column - 2] == '#' || board[row][column - 2] == '|') {
                return;
            }
            board[row + 2][column - 1] = board[row + 2][column - 2] = ' ';
            board[row][column - 1] = board[row][column - 2] = '*';
            isRotatedRight = true;
            return;
        }
        if (isRotatedRight) {
            // Collision
            if (board[row + 1][column] == '#' || board[row + 1][column] == '|' || board[row + 2][column] == '#' || board[row + 2][column] == '|') {
                return;
            }
            board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row + 1][column] = board[row + 2][column] = '*';
            isUpsideDown = true;
            isRotatedRight = false;
            return;
        }
        if (isRotatedLeft) {
            // Collision
            if (board[row][column + 2] == '#' || board[row][column + 2] == '|' || board[row + 1][column + 2] == '#' || board[row + 1][column + 2] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = ' ';
            board[row][column + 2] = board[row + 1][column + 2] = '*';
            isRotatedLeft = false;
            return;
        }
        if (isUpsideDown) {
            // Collision
            if (board[row + 1][column + 2] == '#' || board[row + 1][column + 2] == '|' || board[row + 2][column + 2] == '#' || board[row + 2][column + 2] == '|') {
                return;
            }
            board[row + 1][column] = board[row + 2][column] = ' ';
            board[row + 1][column + 2] = board[row + 2][column + 2] = '*';
            isUpsideDown = false;
            isRotatedRight = true;
            return;
        }
    }
    
    if (currentPiece == ZigZag) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row + 2][column] == '#' || board[row + 2][column] == '|' || board[row + 2][column - 1] == '#' || board[row + 2][column - 1] == '|'
                    || board[row][column - 1] == '#' ||  board[row][column - 1] == '|' || board[row][column - 2] == '#' || board[row][column - 2] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 1][column - 2] = board[row + 2][column - 2] = ' ';
            board[row + 2][column] = board[row + 2][column - 1] = board[row][column - 1] = board[row][column - 2] = '*';
            isRotatedRight = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row][column + 2] == '#' || board[row][column + 2] == '|' || board[row + 1][column + 2] == '#' || board[row + 1][column + 2] == '|'
                    || board[row + 1][column] == '#' || board[row + 1][column] == '|' || board[row + 2][column] == '#' || board[row + 2][column] == '|') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row + 2][column + 1] = board[row + 2][column + 2] = ' ';
            board[row][column + 2] = board[row + 1][column + 2] = board[row + 1][column] = board[row + 2][column] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
    }

    if (currentPiece == ZigZagRev) {
        if (!isRotatedLeft && !isRotatedRight) {
            // Collision
            if (board[row][column + 1] == '#' || board[row][column + 1] == '|' || board[row][column + 2] == '#' || board[row][column + 2] == '|'
                    || board[row + 2][column] == '#' || board[row + 2][column] == '|' || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row + 1][column] = board[row + 1][column + 2] = board[row + 2][column + 2] = ' ';
            board[row][column + 1] = board[row][column + 2] = board[row + 2][column] = board[row + 2][column + 1] = '*';
            isRotatedRight = true;
            return;
        }
        if (isRotatedLeft || isRotatedRight) {
            // Collision
            if (board[row][column - 1] == '#' || board[row][column - 1] == '|' || board[row + 1][column - 1] == '#' || board[row + 1][column - 1] == '|'
                    || board[row + 1][column + 1] == '#' || board[row + 1][column + 1] == '|' || board[row + 2][column + 1] == '#' || board[row + 2][column + 1] == '|') {
                return;
            }
            board[row][column] = board[row][column + 1] = board[row + 2][column] = board[row + 2][column - 1] = ' ';
            board[row][column - 1] = board[row + 1][column - 1] = board[row + 1][column + 1] = board[row + 2][column + 1] = '*';
            isRotatedLeft = isRotatedRight = false;
            return;
        }
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
        for (int above = --(*i), curr = *i; above >= 0; above--, curr--) {
            for (int col = 1; col < 39; col++) {
                board[curr][col] = board[above][col];
            }
        }
    }
}
