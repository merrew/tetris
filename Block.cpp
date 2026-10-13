#include "Block.h"
#include "Colors.h"

Block::Block()
{
	cellSize = ScreenWeight / numberCols;
	RotationState = 0;
	colors = SetColor();
	textures = SetTexture();
	

	row_offset = 0;
	col_offset = 0;

	offset_x = 0;
	offset_y = 0;

	drop = false;


}

void Block::Draw()
{
	for (auto item : GetCellPosition())
	{
		
		
		Rectangle source = { 0, 0, this->textures[ID].width, this->textures[ID].height};
		Rectangle dest = { item.col * cellSize + 1 + offset_x,
							item.row * cellSize + 1 + offset_y,
							cellSize - 1, cellSize - 1 };
		Vector2 origin = { 0, 0 };

		DrawTexturePro(this->textures[ID], source, dest, origin, 0.0f, WHITE);
		
		//DrawRectangle(item.col * cellSize + 1 + offset_x, item.row * cellSize + 1 + offset_y, cellSize - 1, cellSize - 1, colors[ID]);
	}

}

void Block::Draw(Color color, int ID)
{
	for (auto item : GetCellPosition())
	{
		//DrawRectangle(item.col * cellSize + 1 + offset_x, item.row * cellSize + 1 + offset_y, cellSize - 1, cellSize - 1, color);
		DrawRectangle(item.col * cellSize + 2 + offset_x,
			item.row * cellSize + 2 + offset_y,
			cellSize - 3, cellSize - 3, color);

		// Внешний контур (обводка)
		DrawRectangleLines(item.col * cellSize + 1 + offset_x,
			item.row * cellSize + 1 + offset_y,
			cellSize - 1, cellSize - 1, colors[ID]);
	}

}

void Block::Move(int rows, int cols)
{
	row_offset += rows;
	col_offset += cols;
}

std::vector<Position> Block::GetCellPosition()
{
	std::vector<Position> new_Pos;
	for (auto item : cells[RotationState])
	{
		Position new_position = { item.row + row_offset, item.col + col_offset };
		new_Pos.push_back(new_position);
	}

	for (auto i = 0; i < new_Pos.size(); i++)
	{
		while (new_Pos[i].row < 0)
		{
			for (auto j = 0; j < new_Pos.size(); j++)
				new_Pos[j].row += 1;
		}
			
		while (new_Pos[i].col < 0)
		{
			for (auto j = 0; j < new_Pos.size(); j++)
				new_Pos[j].col += 1;
		}
	}

	return new_Pos;
}
