#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(bool color, int x, int y, char type);
	~Knight();
	int checkMove(int x, int y, Piece*** board);
};

