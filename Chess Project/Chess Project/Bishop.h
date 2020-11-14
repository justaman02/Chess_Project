#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(bool color, int x, int y, char type);
	~Bishop();
	int checkMove(int x, int y, Piece*** board);

};