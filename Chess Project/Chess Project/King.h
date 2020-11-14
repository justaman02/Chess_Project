#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(bool color, int x, int y, char type);
	~King();
	int checkMove(int x, int y, Piece*** board);
};

