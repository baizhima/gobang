#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "chessboard.h"

class HumanPlayer
{
public:
    HumanPlayer(int);
    void play(ChessBoard &);
    int getPlayerId();
private:
    int playerId;
};

#endif // HUMANPLAYER_H
