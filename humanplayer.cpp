#include "humanplayer.h"

HumanPlayer::HumanPlayer(int id):Player(id)
{

}

void HumanPlayer::play(ChessBoard &chessBoard) {
    char ch;
    int i,j;
    while (true) {
        cin >> ch >> j;
        if (ch >= 'a' && ch <= 'z')
            ch = ch + 'A' - 'a';
        if (ch == 'A' && j == 0) { // regret option
            bool success = chessBoard.regret();
            if (success)
                chessBoard.printBoard();
            chessBoard.printPrompt(playerId);
            continue;
        }
        if (ch < 'A' || ch > 'Z' || j <= 0 || j > BOARD_SIZE) {
            cout << "invalid input, please enter another coordinate" << endl;
            chessBoard.printPrompt(playerId);
            continue;
        }
        i = ch - 'A';
        j = j - 1; // translate from 1 based to 0 based
        if (!chessBoard.isEmpty(i,j)) {
            cout << ch << j+1 << " has been filled, please enter another coordinate" << endl;
            chessBoard.printPrompt(playerId);
            continue;
        }
        break;

    }

    chessBoard.setChess(playerId, i, j);

}
/*
int HumanPlayer::getPlayerId() {
    return playerId;
}
*/
