#include "Pawn.h"

#define MAX_X 2

/*
	Pawn's Constructor
*/
Pawn::Pawn(bool playerColor, int x, int y, char type) : Piece(playerColor, x, y, type)
{
	_hasWalked = false;
}

/*
	Pawn's Destructor
*/
Pawn::~Pawn()
{
}

/*
	This function checks if the pawn can move to the entered location
	Input: x & y: The 'x' and 'y' coordinates of the tile
		   Piece*** board: The board of the game
	Output: 0 if the move succeeded, 6 otherwise.
*/
int Pawn::checkMove(int x, int y, Piece*** board) 
{
	int result = ERROR_SIX;
	
	if (board[x][y] == nullptr)
	{
		// Moving one tile
		if (_y == y)
		{
			if ((_playerColor == true && _x - x == 1) || (_playerColor == false && _x - x == -1))
			{
				result = 0;
				_hasWalked = true;
			}
		}

		// Moving two tiles
		if (_hasWalked == false)
		{
			if ((_playerColor == true && _x - x == 2))
			{
				if (_y == y && board[x + 1][y] == nullptr)
				{
					result = 0;
					_hasWalked = true;
				}
			}
			else if ((_playerColor == false && _x - x == -2))
			{
				if (_y == y && board[x - 1][y] == nullptr)
				{
					result = 0;
					_hasWalked = true;
				}
			}
		}
	}


	else // Attack
	{
		if ((_playerColor == true) && (_x - x == 1) || (_playerColor == false) && (_x - x == -1))
		{
			if (_y - y == 1 || _y - y == -1)
			{
				result = 0;
			}
		}
	}

	return result;
}

