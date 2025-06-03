#pragma once
#include "Colors.h"
#include "Header.h"
#include <map>

struct Position
{
	int row;
	int col;
};

class Block
{
public:
	std::map<int, std::vector<Position>> cells;
	int RotationState;
	int ID;

	int offset_x;
	int offset_y;

	std::vector<Color> colors;

	bool drop;

	Block();
	void Draw();

	void Draw(Color color);

	void Move(int rows, int cols);

	std::vector<Position> GetCellPosition();

	int row_offset;
	int col_offset;

private:
	int cellSize;

	
	


};

class LBlock : public Block
{
public:
	LBlock()
	{
		ID = 1;
		cells[0] = { Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0) };
		cells[3] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1) };
		this->Move(0, 3);
	}
};

class JBlock : public Block
{
public:
	JBlock()
	{
		ID = 2;
		cells[0] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2) };
		cells[3] = { Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1) };
		this->Move(0, 3);
	}
};

class IBlock : public Block
{
public:
	IBlock()
	{
		ID = 3;
		cells[0] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) };
		cells[1] = { Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) };
		cells[2] = { Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) };
		cells[3] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) };
		this->Move(-1, 3);
	}
};

class OBlock : public Block
{
public:
	OBlock()
	{
		ID = 4;
		cells[0] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		//cells[1] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		//cells[2] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		//cells[3] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
		this->Move(0, 4);
	}
};

class SBlock : public Block
{
public:
	SBlock()
	{
		ID = 5;
		cells[0] = { Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1) };
		cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2) };
		cells[2] = { Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1) };
		cells[3] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1) };
		this->Move(0, 3);
	}
};

class TBlock : public Block
{
public:
	TBlock()
	{
		ID = 6;
		cells[0] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1) };
		cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1) };
		this->Move(0, 3);
	}
};

class ZBlock : public Block
{
public:
	ZBlock()
	{
		ID = 7;
		cells[0] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2) };
		cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0) };
		this->Move(0, 3);
	}
};