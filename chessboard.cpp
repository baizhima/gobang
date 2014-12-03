#include "chessboard.h"



ChessBoard::ChessBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            grid[i][j] = '.';
    nrounds = 0;
    nmoves = 0;
    lastMove[0][0] = lastMove[0][1] = lastMove[1][0] = lastMove[1][1] = -1;
}

bool ChessBoard::isEmpty(int i, int j) {
    return grid[i][j] == '.';
}

void ChessBoard::printBoard() {
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i+1 << " ";
        if (i < 9)
            cout << " ";
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        char letter = 'A' + i;
        cout << letter << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << grid[i][j];
            if (j == BOARD_SIZE - 1)
                cout << endl;
            else
                cout << "  ";
        }
    }

    printBoardInfo();
}


void ChessBoard::printPrompt(int playerId) {
    cout << "Please enter a valid coordinate, i.e. type 'A5' will place your piece at (A,5)" << endl;
    cout << "To regret, type 'A0'" << endl;
    cout << "Player #" << playerId << " chooses: ";
}

/* Function: setChess(int playerId, int i, int j)
 * Set the grid[i][j] to corresponding symbol based on playerId
 * playerId: 0 - chessBoard(regret), 1 - player #1, 2 - player #2
 * input (i,j) ranges from (0,0) to (BOARD_SIZE-1, BOARD_SIZE-1)
 **/

void ChessBoard::setChess(int playerId, int i, int j) {
    if (playerId > 0 && !isEmpty(i,j)) {
        cout << "[setChess]ERROR: cannot set the chess" << endl;
        return;
    }
    if (playerId == 1)
        grid[i][j] = 'x';       // player #1's piece is marked as 'x'
    else if (playerId == 2)
        grid[i][j] = 'o';       // player #2's piece is marked as 'o'
    else
        grid[i][j] = '.';       // default empty place is marked as '.'

    if (playerId > 0) {
        nmoves += 1;
        nrounds = nmoves / 2;
        lastMove[playerId - 1][0] = i;
        lastMove[playerId - 1][1] = j;
    }

    if (playerId == 0) {
        if (nmoves > 0)
            nmoves -= 1;
        nrounds = nmoves / 2;
    }

}

bool ChessBoard::regret() {
    if (nrounds == 0) {
        cout << "The game has not started. No previous move will be removed" << endl;
        return false;
    }
    if (lastMove[0][0] == -1) {
        cout << "Unable to regret more than 1 time." << endl;
        return false;
    }
    setChess(0, lastMove[0][0], lastMove[0][1]);
    setChess(0, lastMove[1][0], lastMove[1][1]);
    lastMove[0][0] = lastMove[0][1] = lastMove[1][0] = lastMove[1][1] = -1; // erase lastMove
    return true;
}

/* Function getWinner()
 * return the playerId if either player wins, else return 0
 *
 */

int ChessBoard::getWinner() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (fiveInARow(i,j)) {
                if (grid[i][j] == '.')
                    cout << "[checkWinner]bugs here. cannot win at an empty place" << endl;
                if (grid[i][j] == 'x')
                    return 1;
                else
                    return 2;
            }
        }
    return 0;
}

/* Function: randomTest
 * Simulate two players randomly setting their pieces on grid. Test overall functionality
 */

void ChessBoard::randomTest() {
    int currentPlayer = 1;
    srand(time(NULL));
    while (true) {
        int winner = getWinner();
        if (winner > 0) {
            cout << "Game Ends! The winner is Player #" << winner << endl;
            break;
        }
        int i,j;
        do {
            i = rand() % BOARD_SIZE;
            j = rand() % BOARD_SIZE;
        } while (!isEmpty(i,j));
        setChess(currentPlayer, i, j);
        printBoard();
        currentPlayer = -currentPlayer + 3; // mapping from 1 to 2 or 2 to 1 (f(x)=-x+3)
    }
}


/* Function: fiveInARow
 *   Return true if any of following 3 cases occurs
 *   input (i,j) ranges from (0,0) to (BOARD_SIZE-1, BOARD_SIZE-1)
 *   case 1: x x x x x   case 2:  x      case 3:  x                 x
 *                                x                x               x
 *                                x                 x     or      x
 *                                x                  x           x
 *                                x                   x         x
 */

bool ChessBoard::fiveInARow(int i, int j) {
    char currentPiece = grid[i][j];
    if (currentPiece == '.')
        return false;
    // 1. five pieces located horizontally  xxxxx
    if (j - 2 >= 0 && j + 2 <= BOARD_SIZE - 1) {
        int count = 0;
        for (int t = j-2; t <= j+2; t++)
            if (grid[i][t] == currentPiece)
                count += 1;
        if (count == 5)
            return true;
    }
    // 2. five pieces located vertically
    if (i - 2 >= 0 && i + 2 <= BOARD_SIZE - 1) {
        int count = 0;
        for (int t = i-2; t <= i+2; t++)
            if (grid[t][j] == currentPiece)
                count += 1;
        if (count == 5)
            return true;
    }
    // 3. five pieces located diagonally
    if (j-2 >= 0 && j+2 <= BOARD_SIZE-1 && i-2 >= 0 && i+2 <= BOARD_SIZE-1) {
        int lcount = 0,rcount = 0;
        int startRow = i-2;
        int startCol = j-2;
        for (int t = 0; t < 5; t++)
            if (grid[startRow+t][startCol+t] == currentPiece)
                lcount += 1;
        if (lcount == 5)
            return true;
        startCol = j+2;
        for (int t = 0; t < 5; t++)
            if (grid[startRow+t][startCol-t] == currentPiece)
                rcount += 1;
        if (rcount == 5)
            return true;
    }
    return false;
}

void ChessBoard::printBoardInfo() {
    cout << "nmoves: " << nmoves << ", nrounds: " << nrounds << endl;
    char ch1 = 'A' + lastMove[0][0];
    char ch2 = 'A' + lastMove[1][0];
    if (ch1 == 'A' - 1) {
        cout << "last move player #1 (N/A)" << endl;
        cout << "last move player #2 (N/A)\n" << endl;
    }
    else {
        cout << "last move player #1 (" << ch1 << "," << lastMove[0][1]+1 << ")" << endl;
        cout << "last move player #2 (" << ch2 << "," << lastMove[1][1]+1 << ")\n" << endl;
    }
}
