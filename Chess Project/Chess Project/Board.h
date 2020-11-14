#pragma once
#include "Piece.h"
#include <string>
#include <vector>

#define DIMENSION 8
#define ERROR_SIX 6

using namespace std;

class Piece;
class Board
{
private:
	Piece*** _pieces;
	bool _turn, _chess;

public:
	Board(string startingPositions);
	~Board();
	void printBoard();
	int* getLocation(string location);
	bool isEmpty(int x, int y);
	int move(string currentLocation, string newLocation);
	int checkForChess(int* kingLocationIndexes);
};

