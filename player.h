#ifndef PLAYER_H
#define PLAYER_H

#include "chessboard.h"

class Player
{
public:
    Player(int);
    int getPlayerId();
    virtual void play(ChessBoard &){};
protected:
    int playerId;
};

#endif // PLAYER_H
