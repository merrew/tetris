#include "Grid.h"

Grid::Grid()
{
	numRows = numberRows;
	numCols = numberCols;
	cellSize = ScreenWeight / numCols;
	colors = SetColor();
	textures = SetTexture();

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
			
			if (now_color > 0 && now_color <= 7)
			{
				Rectangle source = { 0, 0, this->textures[now_color].width, this->textures[now_color].height };
				Rectangle dest = { col * cellSize + 1,
									row* cellSize + 1,
									cellSize - 1, cellSize - 1 };
				Vector2 origin = { 0, 0 };

				DrawTexturePro(this->textures[now_color], source, dest, origin, 0.0f, WHITE);

			}

			else DrawRectangle(col * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[now_color]);
		}
	}
	DrawRectangleLines(1, 1, grid[0].size() * cellSize + 2, grid.size() * cellSize - 2, WHITE);
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