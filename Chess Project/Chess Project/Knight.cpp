#include "Knight.h"

/*
	Knight's Constructor
*/
Knight::Knight(bool color, int x, int y, char type) : Piece(color, x, y, type)
{
}

/*
	Knight's Destructor
*/
Knight::~Knight()
{
}

/*
	This function checks if the knight can move to the entered location
	Input: x & y: The 'x' and 'y' coordinates of the tile
		   Piece*** board: The board of the game
	Output: 0 if the move succeeded, 6 otherwise.
*/
int Knight::checkMove(int x, int y, Piece*** board)
{
	int result = ERROR_SIX;
	if ((_x - x == 2 && _y - y == 1) ||
		(_x - x == 2 && _y - y == -1) ||
		(_x - x == -2 && _y - y == 1) ||
		(_x - x == -2 && _y - y == -1) ||
		(_x - x == 1 && _y - y == 2) ||
		(_x - x == 1 && _y - y == -2) ||
		(_x - x == -1 && _y - y == 2) ||
		(_x - x == -1 && _y - y == -2))
	{
		result = 0;
	}
	return result;
}
