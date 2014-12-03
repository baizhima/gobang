#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(int id)
{
    playerId = id;
}




void ComputerPlayer::play(ChessBoard &chessBoard) {
    int i,j;
    decision(chessBoard, i, j);
    char ch = 'A' + i;
    cout << ch << j+1 << endl;
    chessBoard.setChess(playerId, i, j);
}

void ComputerPlayer::decision(ChessBoard &chessBoard, int &i, int &j) {
    int x, y;
    srand(time(NULL)); // set random seed
    do {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
    } while (!chessBoard.isEmpty(x,y));
    i = x;
    j = y;
}

int ComputerPlayer::getPlayerId() {
    return playerId;
}
