#include "Piece.h"
#include <algorithm>

int* Piece::_kingLocationW = new int[2];
int* Piece::_kingLocationB = new int[2];

/*
	Piece's Constructor
*/
Piece::Piece(bool playerColor, int x, int y, char type)
{
	this->_playerColor = playerColor;
	this->_x = x;
	this->_y = y;
	this->_type = type;
}

/*
	Piece's Destructor
*/
Piece::~Piece()
{

}

/*
	Returns the color of the current piece ( Either black or white )
*/
const bool& Piece::getPlayerColor() const
{
	return _playerColor;
}

/*
	returns the type of the piece ( K/k for king, R/r for rook ect... )
*/
const char& Piece::getType() const
{
	return _type;
}

/*
	
*/
int Piece::checkMove(int x, int y, Piece*** board)
{
	return 6;
}

/*
	Returns the X coordinate of a tile
*/
const int& Piece::getX() const
{
	return _x;
}

/*
	Returns the Y coordinate of a tile
*/
const int& Piece::getY() const
{
	return _y;
}

/*
	Returns the location of the king with the entered color as an array
*/
int* Piece::getKingLocation(bool color) 
{
	if (color)
	{
		return _kingLocationW;
	}
	else
	{
		return _kingLocationB;
	}
}

/*
	
*/
int Piece::checkDiagonal(int x, int y, Piece*** board)
{
	int result = 0, i = 0, j = 0;
	if (_x == x || _y == y || (_y - _x != y - x && _y + _x != y + x))
	{
		result = ERROR_SIX;
	}

	//Main Diagonal
	if (_y - _x == y - x)
	{
		if (x > _x && y > _y)
		{
			for (i = 1; i < y - _y && result != ERROR_SIX; i++)
			{
				if (board[_x + i][_y + i] != nullptr)
				{
					result = ERROR_SIX;
				}
			}
		}

		if (x < _x && y < _y) //check
		{
			for (i = 1; i < _y - y && result != ERROR_SIX; i++)
			{
				if (board[_x - i][_y - i] != nullptr)
				{
					result = ERROR_SIX;
				}
			}
		}
	}

	//Secondary Diagonal
	else if (_y + _x == y + x)
	{
		if (x < _x && y > _y)
		{
			for (i = 1; i < y - _y && result != ERROR_SIX; i++)
			{
				if (board[_x - i][_y + i] != nullptr)
				{
					result = ERROR_SIX;
				}
			}
		}

		if (x > _x && y < _y)
		{
			for (i = 1; i < _y - y && result != ERROR_SIX; i++)
			{
				if (board[_x + i][_y - i] != nullptr)
				{
					result = ERROR_SIX;
				}
			}
		}
	}

	else
	{
		result = ERROR_SIX;
	}
	return result;
}

int Piece::checkAxises(int x, int y, Piece*** board)
{
	int maxY = 0, maxX = 0, minY = 0, minX = 0, i = 0, result = 0;
	if ((_y != y) && (_x != x) || (_y == y) && (_x == x))
	{
		result = ERROR_SIX;
	}

	if (_x == x)
	{
		maxY = std::max(_y, y);
		minY = std::min(_y, y);
		for (i = minY + 1; i < maxY; i++)
		{
			if (board[_x][i] != nullptr)
			{
				result = ERROR_SIX;
			}
		}
	}
	else if (_y == y)
	{
		maxX = std::max(_x, x);
		minX = std::min(_x, x);
		for (i = minX + 1; i < maxX; i++)
		{
			if (board[i][_y] != nullptr)
			{
				result = ERROR_SIX;
			}
		}
	}

	else
	{
		result = ERROR_SIX;
	}
	return result;
}

/*
	Sets the Y coordinate to the given value
	Input: y: The new y value
	Output: None
*/
void Piece::setY(int y)
{
	_y = y;
}

/*
	Sets the X coordinate to the given value
	Input: x: The new x value
	Output: None
*/
void Piece::setX(int x)
{
	_x = x;
}
