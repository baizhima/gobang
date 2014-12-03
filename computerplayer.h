#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "chessboard.h"

class ComputerPlayer
{
public:
    ComputerPlayer(int);
    void play(ChessBoard &);
    int getPlayerId();
private:
    int playerId;
    void decision(ChessBoard &, int &, int &);
};

#endif // COMPUTERPLAYER_H
