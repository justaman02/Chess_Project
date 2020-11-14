#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(bool color, int x, int y, char type);
	~Rook();
	int checkMove(int x, int y, Piece*** board);
};

