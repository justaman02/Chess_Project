#include "Board.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include <iostream>

#define LOCATION_ARR 2
#define CHESS 1
#define MAXIMUM_INDEX_VALUE 7
#define SOURCE_AND_DESTINATION_EQUAL 7
#define INVALID_INDEX_VALUE 5
#define CHESS_ON_SELF 4
#define SOURCE_IS_EMPTY 2
#define DESTINATION_CONTAINS_PLAYERS_PIECE 3

/*
	This function initializes the board with each piece in it's default position.
	Input: startingPositions: The initialization string representing the starting positions of each piece.
*/
Board::Board(string startingPositions)
{
	int i = 0, j = 0, k = 0;
	char c = 0;
	_pieces = new Piece **[DIMENSION];
	_turn = true, _chess = false;
	for (i = 0, k = i; i < DIMENSION; i++)
	{
		_pieces[i] = new Piece *[DIMENSION];
		for (j = 0; j < DIMENSION; j++)
		{
			c = startingPositions[k];
			switch (c)
			{
			case 'R':
				_pieces[i][j] = new Rook(true, i, j, c);
				break;
			case 'r':
				_pieces[i][j] = new Rook(false, i, j, c);
				break;
			case 'K':
				_pieces[i][j] = new King(true, i, j, c);
				break;
			case 'k':
				_pieces[i][j] = new King(false, i, j, c);
				break;
			case 'P':
				_pieces[i][j] = new Pawn(true, i, j, c);
				break;
			case 'p':
				_pieces[i][j] = new Pawn(false, i, j, c);
				break;
			case 'N':
				_pieces[i][j] = new Knight(true, i, j, c);
				break;
			case 'n':
				_pieces[i][j] = new Knight(false, i, j, c);
				break;
			case 'B':
				_pieces[i][j] = new Bishop(true, i, j, c);
				break;
			case 'b':
				_pieces[i][j] = new Bishop(false, i, j, c);
				break;
			case 'Q':
				_pieces[i][j] = new Queen(true, i, j, c);
				break;
			case 'q':
				_pieces[i][j] = new Queen(false, i, j, c);
				break;
			default:
				_pieces[i][j] = nullptr;
				break;
			}
			k++;
		}
	}
}

/*
	Board's Destructor
*/
Board::~Board()
{
	int i = 0, j = 0;
	for (i = 0; i < DIMENSION; i++)
	{
		for (j = 0; j < DIMENSION; j++)
		{
			delete _pieces[i][j];
		}
	}
	delete[] _pieces; //Notice that it might result problems
}

/*
	This function returns the X and Y indexes of the entered position in the board.
	Input: A position in the board ( For example: "E3", "A6" and so on )
	Output: A pointer to an array that contains the X and Y positions of the entered location.
*/
int* Board::getLocation(string location)
{
	int* locationOnBoard = new int[LOCATION_ARR];
	locationOnBoard[0] = '8' - location[1];
	locationOnBoard[1] = location[0] - 'a';
	return locationOnBoard;
}

/*
	This function checks if the piece in "currentLocation" can move to "newLocation". if so, it moves the piece and returns either 0 ( Move is legal ), 1 ( Move is legal and chessed the opponent ) or 8 ( Move is legal and checkmated the opponent ).
	If not, it returns the corresponding error to the condition that happend when moving the piece.
	Error List: 2: Source tile doesn't contain a player's piece.
				3: Destination tile contains a player's piece.
				4: Moving the piece results in chess on the player.
				5: Indexes of one of the tiles are out of bounds ( less then 0 or bigger then 8 )
				6: Illegal move ( The piece cannot move in such way )
				7: Source and Destination tiles are the same
	Input: Two strings, one contains the source tile and one contains the destination tile ( Represented in the formal chess format: "E4", "A5" and so on )
	Output: The result of the move ( 1 - 8 )
*/
int Board::move(string currentLocation, string newLocation)
{
	int result = 0, i = 0, j = 0;
	bool errorAlreadyRaised = false;
	int* currentLocationIndexes = getLocation(currentLocation), * newLocationIndexes = getLocation(newLocation), * kingLocationIndexes = {};
	if (0 > currentLocationIndexes[0] || currentLocationIndexes[0] > MAXIMUM_INDEX_VALUE || 0 > currentLocationIndexes[1] || currentLocationIndexes[1] > MAXIMUM_INDEX_VALUE || 0 > newLocationIndexes[0] || newLocationIndexes[0] > MAXIMUM_INDEX_VALUE || 0 > newLocationIndexes[1] || newLocationIndexes[1] > MAXIMUM_INDEX_VALUE)
	{
		result = INVALID_INDEX_VALUE;
		errorAlreadyRaised = true;
	}
	if (errorAlreadyRaised == false && currentLocationIndexes[0] == newLocationIndexes[0] && currentLocationIndexes[1] == newLocationIndexes[1])
	{
		result = SOURCE_AND_DESTINATION_EQUAL;
		errorAlreadyRaised = true;
	}
	if (errorAlreadyRaised == false && _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]] == nullptr || _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]]->getPlayerColor() != _turn)//need to change// not correct!
	{
		result = SOURCE_IS_EMPTY;
		errorAlreadyRaised = true;
	}
	if (errorAlreadyRaised == false && _pieces[newLocationIndexes[0]][newLocationIndexes[1]] != nullptr && _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]] && _pieces[newLocationIndexes[0]][newLocationIndexes[1]]->getPlayerColor() == _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]]->getPlayerColor())
	{
		result = DESTINATION_CONTAINS_PLAYERS_PIECE;
		errorAlreadyRaised = true;
	}
	if (errorAlreadyRaised == false && _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]] != nullptr && _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]]->getPlayerColor() == _turn && _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]]->checkMove(newLocationIndexes[0], newLocationIndexes[1], _pieces) == 0)
	{
		_pieces[newLocationIndexes[0]][newLocationIndexes[1]] = _pieces[currentLocationIndexes[0]][currentLocationIndexes[1]];
		_pieces[currentLocationIndexes[0]][currentLocationIndexes[1]] = nullptr;
		_pieces[newLocationIndexes[0]][newLocationIndexes[1]]->setX(newLocationIndexes[0]);
		_pieces[newLocationIndexes[0]][newLocationIndexes[1]]->setY(newLocationIndexes[1]);
		
		//Check for chess on self.
		kingLocationIndexes = Piece::getKingLocation(_turn);
		result = checkForChess(kingLocationIndexes);
		result = result != CHESS ? 0 : CHESS_ON_SELF;
		/*
			CR: Dror Malinsky
			This comment can be modifed to be more informative as it's using part of code itself to explain
			that this if statement checks if the move does chess on the player itself.

			Consider changing this comment to something a bit more informative without using the code itself to explain this part of the code.

			Suggested changes:
				Change line to -> "//If the move results on check on self, rewind the move"
		*/
		//rewind the move if result == CHESS_ON_SELF <-- CR on this comment
		/*
			CR: Dror Malinsky
			This comment is not informative and is also not very professional. Consider removing this comment
			as it's not providing any helpful information for future developers nor explaining hard to understand code.

			Suggested changes:
				Remove -> "//This check also helps preventing stupid moves that dont stop"
		*/
		//This check also helps preventing stupid moves that dont stop <-- CR on this comment
		if (result == CHESS_ON_SELF)
		{
			_pieces[currentLocationIndexes[0]][currentLocationIndexes[1]] = _pieces[newLocationIndexes[0]][newLocationIndexes[1]];
			_pieces[newLocationIndexes[0]][newLocationIndexes[1]] = nullptr;
			_pieces[currentLocationIndexes[0]][currentLocationIndexes[1]]->setX(currentLocationIndexes[0]);
			_pieces[currentLocationIndexes[0]][currentLocationIndexes[1]]->setY(currentLocationIndexes[1]);
		}
		
		else
		{
			_chess = false;
		}

		//Check for normal chess.
		if (result != CHESS_ON_SELF)
		{
			cout << "HEIL" << endl;
			kingLocationIndexes = Piece::getKingLocation(!_turn);
			result = checkForChess(kingLocationIndexes);
			_chess = result == CHESS ? true : false;
		}

		// Switch The Turn
		if (_turn && result != CHESS_ON_SELF)
		{
			_turn = false;
		}
		else if (!_turn && result != CHESS_ON_SELF)
		{
			_turn = true;
		}
	}
	else if (errorAlreadyRaised == false)
	{
		result = ERROR_SIX;
	}
	return result;
}

/*
	This function prints the board.
	Input: None
	Output: None
*/
void Board::printBoard()
{
	int i = 0, j = 0;

	for (i = 0; i < DIMENSION; i++)
	{
		cout << DIMENSION - i << " ";
		for (j = 0; j < DIMENSION; j++)
		{

			if (_pieces[i][j] != nullptr)
			{
				cout << _pieces[i][j]->getType() << " ";
			}
			else
			{
				cout << "#" << " ";
			}
		}
		cout << endl;
	}
	cout << "  a b c d e f g h" << endl;

}

/*
	This function checks if the tile in the cordinates 'x' and 'y' is empty or not.
	Input: The 'x' and 'y' of the tile
	Output true if the tile is empty, false otherwise.
*/
bool Board::isEmpty(int x, int y)
{
	bool result = false;
	if (_pieces[x][y] == nullptr)
	{
		result = true;
	}
	return result;
}

/*
	This function checks if there is chess on the king in "kingLocationIndexes".
	Input: An array containing the x and y coordinates of the king.
	Output: CHESS (1) if there is chess on the king, 0 otherwise.
*/
int Board::checkForChess(int* kingLocationIndexes)
{
	int i = 0, j = 0, result = 0;
	for (i = 0; i < DIMENSION; i++)
	{
		for (j = 0; j < DIMENSION; j++)
		{
			if (_pieces[i][j] != nullptr && _pieces[i][j]->getPlayerColor() != _pieces[kingLocationIndexes[0]][kingLocationIndexes[1]]->getPlayerColor() && _pieces[i][j]->getType() != 'k' && _pieces[i][j]->getType() != 'K' && _pieces[i][j]->checkMove(kingLocationIndexes[0], kingLocationIndexes[1], _pieces) == 0)
			{
				cout << i << " " << j << endl;
				result = CHESS;
			}
		}
	}
	return result;
}