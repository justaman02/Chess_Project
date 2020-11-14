#include "Bishop.h"

/*
	Bishop's Constructor
*/
Bishop::Bishop(bool color, int x, int y, char type) : Piece(color, x, y, type)
{
}

/*
	Bishop's Destructor
*/
Bishop::~Bishop()
{
}

/*
	This function checks if the bishop can move to the entered location
	Input: x & y: The 'x' and 'y' coordinates of the tile
		   Piece*** board: The board of the game
	Output: 0 if the move succeeded, 6 otherwise.
*/
int Bishop::checkMove(int x, int y, Piece*** board) // Should work as intended now
{
	return checkDiagonal(x, y, board);
}