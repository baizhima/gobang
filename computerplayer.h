#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.h"


class ComputerPlayer: public Player
{
public:
    ComputerPlayer(int, bool);
    void play(ChessBoard &);


private:

    bool ai;

    void decision(ChessBoard &, int &, int &);
    void randomDecision(ChessBoard &, int &, int &);
    void aiDecision(ChessBoard &, int &, int &);
    int horizontalVal(ChessBoard &, int, int);
    int verticalVal(ChessBoard &, int, int);
    int majorDiagonalVal(ChessBoard &, int, int);
    int minorDiagonalVal(ChessBoard &, int, int);
    int calculateScore(int, int, int);
};

#endif // COMPUTERPLAYER_H
