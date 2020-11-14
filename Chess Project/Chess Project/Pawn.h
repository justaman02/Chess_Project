#pragma once
#include "Piece.h"

class Pawn : public Piece
{
	bool _hasWalked;
public:
	Pawn(bool playerColor, int x, int y, char type);
	~Pawn();
	int checkMove(int x, int y, Piece*** board);
};

