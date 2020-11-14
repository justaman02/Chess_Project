#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(bool color, int x, int y, char type);
	~Queen();
	int checkMove(int x, int y, Piece*** board);
};

