#include "Grid.h"

Grid::Grid()
{
	numRows = numberRows;
	numCols = numberCols;
	cellSize = ScreenWeight / numCols;
	colors = SetColor();

	for (int i = 0; i < numRows; i++)
	{
		grid.push_back(std::vector<int>());
		for (int j = 0; j < numCols; j++)
		{
			grid[i].push_back(0);
		}
	}
}

void Grid::Draw()
{
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[0].size(); col++)
		{
			auto now_color = grid[row][col];

			DrawRectangle(col * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[now_color]);
		}
	}
}

std::vector<int> Grid::Check_FillLine()
{
	std::vector<int> delete_lines;
	for (int row = 0; row < grid.size(); row++)
	{
		int fill_cell = 0;
		for (int col = 0; col < grid[0].size(); col++)
		{
			if (grid[row][col] != 0)
			{
				fill_cell += 1;
			}
		}
		if (fill_cell == numberCols)
			delete_lines.push_back(row);
	}
	return delete_lines;
}

Grid::~Grid()
{

}