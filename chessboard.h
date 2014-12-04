#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <cstdlib>    /* srand, rand */
#include <cassert>    /* assert */
#include <ctime>      /* time */
using namespace std;


#define BOARD_SIZE 15

class ChessBoard
{
public:
    ChessBoard();
    bool isEmpty(int i, int j);
    void printBoard();
    void printPrompt(int playerId);
    void setChess(int playerId, int i, int j);
    char getChess(int i, int j);
    bool regret();
    int getWinner();
    void randomTest();

private:

    bool fiveInARow(int i, int j);
    void printBoardInfo();

    char grid[BOARD_SIZE][BOARD_SIZE];
    int nrounds;
    int nmoves;
    int lastMove[2][2]; // (lastMove[i][0],lastMove[i][1]) represents player #(i+1)'s last move coordinate
};

#endif // CHESSBOARD_H
