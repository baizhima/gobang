#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H


#include "player.h"

class HumanPlayer: public Player
{
public:
    HumanPlayer(int);
    void play(ChessBoard &);

};

#endif // HUMANPLAYER_H
