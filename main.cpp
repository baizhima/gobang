
#include <iostream>
#include "chessboard.h"
#include "humanplayer.h"
#include "computerplayer.h"
using namespace std;

int main(int argc, char *argv[])
{
    ChessBoard chessBoard;
    HumanPlayer human(1);
    ComputerPlayer computer(2);

    while (true) {
        chessBoard.printBoard();
        int winner = chessBoard.getWinner();
        if (winner > 0) {
            cout << "Game Ends! The winner is Player #" << winner << endl;
            break;
        }
        chessBoard.printPrompt(human.getPlayerId());
        human.play(chessBoard);
        chessBoard.printBoard();
        chessBoard.printPrompt(computer.getPlayerId());
        computer.play(chessBoard);
    }

    return 0;
}
