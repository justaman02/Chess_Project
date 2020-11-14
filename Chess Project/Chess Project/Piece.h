#pragma once
#include <iostream>
#include "Board.h"
using std::string;

#define LOCATION_ARRAY_SIZE 2

class Board;
class Piece
{
public:
	Piece(bool playerColor, int x, int y, char type);
	~Piece();
	virtual int checkMove(int x, int y, Piece*** board);
	const bool& getPlayerColor() const;
	const char& getType() const;
	const int& getX() const;
	const int& getY() const;
	static int* getKingLocation(bool color);
	int checkDiagonal(int x, int y, Piece*** board);
	int checkAxises(int x, int y, Piece*** board);
	void setX(int x);
	void setY(int y);

protected:
	static int* _kingLocationW;
	static int* _kingLocationB;
	bool _playerColor;
	int _x;
	int _y;
	char _type;
};

