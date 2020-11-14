#include "Queen.h"

/*
	Queen's Constructer
*/
Queen::Queen(bool color, int x, int y, char type) : Piece(color, x, y, type)
{
}

/*
	Queens Destructor
*/
Queen::~Queen()
{
}

/*
	This function checks if the queen can move to the entered location 
	Input: x & y: The 'x' and 'y' coordinates of the tile
		   Piece*** board: The board of the game
	Output: 0 if the move succeeded, 6 otherwise.
*/
int Queen::checkMove(int x, int y, Piece*** board)
{
	int result = ERROR_SIX;
	result = checkAxises(x, y, board);
	if (result != 0)
	{
		result = checkDiagonal(x, y, board);
	}
	return result;
}