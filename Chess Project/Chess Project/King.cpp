#include "King.h"

/*
	King's Constructor
*/
King::King(bool color, int x, int y, char type) : Piece(color, x, y, type)
{
	if (_playerColor)
	{
		_kingLocationW[0] = x;
		_kingLocationW[1] = y;
	}
	else
	{
		_kingLocationB[0] = x;
		_kingLocationB[1] = y;
	}
}

/*
	King's Destructor
*/
King::~King()
{
}

/*
	This function checks if the king can move to the entered location
	Input: x & y: The 'x' and 'y' coordinates of the tile
		   Piece*** board: The board of the game
	Output: 0 if the move succeeded, 6 otherwise.
*/
int King::checkMove(int x, int y, Piece*** board) //Should work as intended now
{
	int result = ERROR_SIX;
	if (((_x - x == 0) || (_x - x == -1) || (_x - x == 1)) && ((_y - y == 0) || (_y - y == -1) || (_y - y == 1)))
	{
		result = 0;
		if (_playerColor)
		{
			_kingLocationW[0] = x;
			_kingLocationW[1] = y;
		}
		else
		{
			_kingLocationB[0] = x;
			_kingLocationB[1] = y;
		}
	}
	return result;
}
