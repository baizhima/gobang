#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(int id, bool aiStatus)
{
    playerId = id;
    ai = aiStatus;
}




void ComputerPlayer::play(ChessBoard &chessBoard) {
    int i,j;
    decision(chessBoard, i, j);
    char ch = 'A' + i;
    cout << ch << j+1 << endl;
    chessBoard.setChess(playerId, i, j);
}


int ComputerPlayer::getPlayerId() {
    return playerId;
}

void ComputerPlayer::decision(ChessBoard &chessBoard, int &i, int &j) {
    if (ai)
        aiDecision(chessBoard, i, j);
    else
        randomDecision(chessBoard, i, j);
}

void ComputerPlayer::randomDecision(ChessBoard &chessBoard, int &iOpt, int &jOpt) {
    int x, y;
    srand(time(NULL)); // set random seed
    do {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
    } while (!chessBoard.isEmpty(x,y));
    iOpt = x;
    jOpt = y;
}

/* Artificial Intelligence Algorithm
 * 1. Iterate through the whole chess board finding all places that are empty (grid[i][j] == '.')
 * 2. In each case, set the total consecutive number of pieces of computer(o by default)
 *    and human(x by default) to count1 and count2
 * 3. Add bonus points with respect to following rules:
 * (a) human 3 pieces in a row (bonus: 20)
 * (b) computer 3 pieces in a row (bonus: 10)
 * (c) human 4 pieces in a row (bonus: 100)
 * (d) computer 4 pieces in a row (bonus: 70)
 * 4. set variable sideBlock recording the blocking pieces at each side
 * 5. Compute the overall score by formula: score = (count1+count2)*5-sideBlock
 * 6. Return the coordinate (i,j) which holds the maximum overall score
 */

void ComputerPlayer::aiDecision(ChessBoard &chessBoard, int &iOpt, int &jOpt) {
    int maxVali = -1, maxValj = -1;
    int maxValue = -1;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!chessBoard.isEmpty(i,j)) continue; // non-empty grid, cannot set piece here
            int score = horizontalVal(chessBoard, i, j) + verticalVal(chessBoard, i, j)
                    + majorDiagonalVal(chessBoard, i, j) + minorDiagonalVal(chessBoard, i, j);
            if (score > maxValue) {
                maxVali = i;
                maxValj = j;
                maxValue = score;
            }
        }
    iOpt = maxVali;
    jOpt = maxValj;
}


int ComputerPlayer::horizontalVal(ChessBoard &chessBoard, int i, int j) {
    int count1 = 0, count2 = 0;
    int sideBlock = 0;
    char selfPiece, rivalPiece;
    getPlayerId() == 1 ? selfPiece = 'x' : selfPiece = 'o';
    getPlayerId() == 1 ? rivalPiece = 'o' : rivalPiece = 'x';

    // rightward search, self piece
    int j1 = j + 1;
    while (j1 < BOARD_SIZE && chessBoard.getChess(i, j1) == selfPiece) {
        j1 += 1;
        count1 += 1;
    }
    if (j1 == BOARD_SIZE || chessBoard.getChess(i, j1) == rivalPiece)
        sideBlock += 1;
    j1 = j - 1;
    // leftward search, self piece
    while (j1 >= 0 && chessBoard.getChess(i, j1) == selfPiece) {
        j1 -= 1;
        count1 += 1;
    }
    if (j1 < 0 || chessBoard.getChess(i, j1) == rivalPiece)
        sideBlock += 1;
    // rightward search, rival piece
    int j2 = j + 1;
    while (j2 < BOARD_SIZE && chessBoard.getChess(i, j2) == rivalPiece) {
        j2 += 1;
        count2 += 1;
    }
    j2 = j - 1;
    // leftward search, rival piece
    while (j2 >= 0 && chessBoard.getChess(i, j2) == rivalPiece) {
        j2 -= 1;
        count2 += 1;
    }
    return calculateScore(count1, count2, sideBlock);
}

int ComputerPlayer::verticalVal(ChessBoard &chessBoard, int i, int j) {
    int count1 = 0, count2 = 0;
    int sideBlock = 0;
    char selfPiece, rivalPiece;
    getPlayerId() == 1 ? selfPiece = 'x' : selfPiece = 'o';
    getPlayerId() == 1 ? rivalPiece = 'o' : rivalPiece = 'x';

    // downward search, self piece
    int i1 = i + 1;
    while (i1 < BOARD_SIZE && chessBoard.getChess(i1, j) == selfPiece) {
        i1 += 1;
        count1 += 1;
    }
    if (i1 == BOARD_SIZE || chessBoard.getChess(i1, j) == rivalPiece)
        sideBlock += 1;
    i1 = i - 1;
    // upward search, self piece
    while (i1 >= 0 && chessBoard.getChess(i1, j) == selfPiece) {
        i1 -= 1;
        count1 += 1;
    }
    if (i1 < 0 || chessBoard.getChess(i1, j) == rivalPiece)
        sideBlock += 1;
    // downward search, rival piece
    int i2 = i + 1;
    while (i2 < BOARD_SIZE && chessBoard.getChess(i2, j) == rivalPiece) {
        i2 += 1;
        count2 += 1;
    }
    i2 = i - 1;
    // upward search, rival piece
    while (i2 >= 0 && chessBoard.getChess(i2, j) == rivalPiece) {
        i2 -= 1;
        count2 += 1;
    }
    return calculateScore(count1, count2, sideBlock);
}

int ComputerPlayer::majorDiagonalVal(ChessBoard &chessBoard, int i, int j) {
    int count1 = 0, count2 = 0;
    int sideBlock = 0;
    char selfPiece, rivalPiece;
    getPlayerId() == 1 ? selfPiece = 'x' : selfPiece = 'o';
    getPlayerId() == 1 ? rivalPiece = 'o' : rivalPiece = 'x';

    // SouthEastward search, self piece
    int delta = 1;
    while (i+delta < BOARD_SIZE && j+delta < BOARD_SIZE && chessBoard.getChess(i+delta,j+delta) == selfPiece) {
        delta += 1;
        count1 += 1;
    }
    if (i+delta == BOARD_SIZE || j+delta == BOARD_SIZE || chessBoard.getChess(i+delta, j+delta) == rivalPiece)
        sideBlock += 1;
    delta = -1;
    // NorthWestward search, self piece
    while (i+delta >= 0 && j+delta >= 0 && chessBoard.getChess(i+delta,j+delta) == selfPiece) {
        delta -= 1;
        count1 += 1;
    }
    if (i+delta < 0 || j+delta < 0 || chessBoard.getChess(i+delta,j+delta) == rivalPiece)
        sideBlock += 1;
    // SouthEastward search, rival piece
    delta = 1;
    while (i+delta < BOARD_SIZE && j+delta < BOARD_SIZE && chessBoard.getChess(i+delta,j+delta) == rivalPiece) {
        delta += 1;
        count2 += 1;
    }
    delta = -1;
    // NorthWestward search, rival piece
    while (i+delta >= 0 && j+delta >= 0 && chessBoard.getChess(i+delta,j+delta) == rivalPiece) {
        delta -= 1;
        count2 += 1;
    }
    return calculateScore(count1, count2, sideBlock);
}

int ComputerPlayer::minorDiagonalVal(ChessBoard &chessBoard, int i, int j) {
    int count1 = 0, count2 = 0;
    int sideBlock = 0;
    char selfPiece, rivalPiece;
    getPlayerId() == 1 ? selfPiece = 'x' : selfPiece = 'o';
    getPlayerId() == 1 ? rivalPiece = 'o' : rivalPiece = 'x';

    // NorthEastward search, self piece
    int delta = 1;
    while (i-delta >= 0 && j+delta < BOARD_SIZE && chessBoard.getChess(i-delta,j+delta) == selfPiece) {
        delta += 1;
        count1 += 1;
    }
    if (i-delta < 0 || j+delta == BOARD_SIZE || chessBoard.getChess(i-delta, j+delta) == rivalPiece)
        sideBlock += 1;
    delta = 1;
    // SouthWestward search, self piece
    while (i+delta < BOARD_SIZE && j-delta >= 0 && chessBoard.getChess(i+delta,j-delta) == selfPiece) {
        delta += 1;
        count1 += 1;
    }
    if (i+delta == BOARD_SIZE || j-delta < 0 || chessBoard.getChess(i+delta,j-delta) == rivalPiece)
        sideBlock += 1;
    // NorthEastward search, rival piece
    delta = 1;
    while (i-delta >= 0 && j+delta < BOARD_SIZE && chessBoard.getChess(i-delta,j+delta) == rivalPiece) {
        delta += 1;
        count2 += 1;
    }
    delta = 1;
    // SouthWestward search, rival piece
    while (i+delta < BOARD_SIZE && j-delta >= 0 && chessBoard.getChess(i+delta,j-delta) == rivalPiece) {
        delta += 1;
        count2 += 1;
    }
    return calculateScore(count1, count2, sideBlock);
}



int ComputerPlayer::calculateScore(int count1, int count2, int sideBlock) {
    if (count2 == 3) count2 += 40;
    if (count1 == 3) count1 += 25;
    if (count2 >= 4) count2 += 100;
    if (count1 >= 4) count1 += 120;
    return (count1 + count2) * 5 - sideBlock;
}
