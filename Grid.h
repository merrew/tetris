#pragma once
#include "Header.h"
#include "Colors.h"
#include <raylib.h>

class Grid
{
public:
	std::vector<std::vector<int>> grid;
	int numRows;
	int numCols;

	Grid();

	void Draw();
	//int Check_Fill_Line();
	std::vector<int> Check_FillLine();
	~Grid();
private:
	int cellSize;

	std::vector<Color> colors;
	std::vector<Texture2D> textures;
};
