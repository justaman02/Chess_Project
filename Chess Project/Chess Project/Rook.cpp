#include "Rook.h"
#include <algorithm>

/*
	Rook's Constructor
*/
Rook::Rook(bool color, int x, int y, char type) : Piece(color, x, y, type)
{
}

/*
	Rook's Destructor
*/
Rook::~Rook()
{
}

/*
	This function checks if the rook can move to the entered location
	Input: x & y: The 'x' and 'y' coordinates of the tile
		   Piece*** board: The board of the game
	Output: 0 if the move succeeded, 6 otherwise.
*/
int Rook::checkMove(int x, int y, Piece*** board)
{
	return checkAxises(x, y, board);
}