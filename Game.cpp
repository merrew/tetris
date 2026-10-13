#include "Game.h"
#include <random>
#include <ctime>
#include <fstream>
#include <iostream>

auto last_time = time(NULL);
//bool Game::time_check()
//{
//	auto now_time = time(NULL);
//	if (now_time - last_time >= 1)
//	{
//		last_time = time(NULL);
//		return true;
//	}
//	return false;
//}

double lastUpdateTime = 0;
bool Game::eventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	else
	{
		return false;
	}
}

Game::Game()
{
	customFont = LoadFont("font.ttf");

	FillBlocks();
	currentBlock = GetRandBlock();

	nextBlock = GetRandBlock();
	nextBlock.offset_x = ScreenWeight - frame/ 3;
	nextBlock.offset_y = ScreenHeight / 8;

	flicker = { 8, 9 };
	level = 1;

	std::ifstream in("best.txt", std::ios_base::in);
	if (in.is_open())
	{
		in >> best_score;
	}
	in.close();

	Image image = LoadImage("pause.png");
	this->pause = LoadTextureFromImage(image);
	pauseRect = Rectangle{ ScreenWeight + 10, ScreenHeight / 9 + 830, (float)image.width, (float)image.height };
	UnloadImage(image);

	image = LoadImage("play.png");
	this->play = LoadTextureFromImage(image);
	UnloadImage(image);

	soundRect = Rectangle{ ScreenWeight + 140, ScreenHeight / 9 + 830, (float)image.width, (float)image.height };
	image = LoadImage("sound_on.png");
	this->sound = LoadTextureFromImage(image);
	UnloadImage(image);

	image = LoadImage("sound_off.png");
	this->soundOff = LoadTextureFromImage(image);
	UnloadImage(image);

	reloadRect = Rectangle{ ScreenWeight + 75, ScreenHeight / 9 + 830, (float)image.width, (float)image.height };
	image = LoadImage("reload.png");
	this->reload = LoadTextureFromImage(image);
	UnloadImage(image);

	InitAudioDevice();
	fallSound = LoadSound("fall.mp3");
	gameoverSound = LoadSound("game_over.mp3");
	clear_line = LoadSound("line_clear.mp3");
	//rotate = LoadSound("rotate.mp3");
	menu = LoadSound("menu.mp3");
	new_level = LoadSound("level.mp3");
	new_best = LoadSound("best_score.mp3");

}

void Game::FillBlocks()
{
	blocks = { LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

Block Game::GetRandBlock()
{
	srand(time(NULL));
	if (blocks.size() == 0)
		FillBlocks();
	int rand_ind = rand() % blocks.size();
	auto randBlock = blocks[rand_ind];
	blocks.erase(blocks.begin() + rand_ind);
	return randBlock;
}

void Game::DrawTextWithOutline(Font font, const char* text, Vector2 position,
	float fontSize, float spacing, Color textColor, Color outlineColor, int outlineSize)
{
	// Рисуем обводку
	for (int x = -outlineSize; x <= outlineSize; x++) {
		for (int y = -outlineSize; y <= outlineSize; y++) {
			if (x == 0 && y == 0) continue;
			DrawTextEx(font, text, { position.x + x, position.y + y },
				fontSize, spacing, outlineColor);
		}
	}

	// Основной текст
	DrawTextEx(font, text, position, fontSize, spacing, textColor);
}

void Game::Pause()
{
	grid.Draw();

	Block copy_block = currentBlock;
	copy_block.row_offset = 3;

	while (!Collision_Wall_Down(copy_block) && !Collision_AnotherBlock_Down(copy_block))
		copy_block.Move(1, 0);
	copy_block.Draw(Gray, 8);

	currentBlock.Draw();


	DrawTextWithOutline(customFont, "Next",
		{
		ScreenWeight + 5 + ScreenWeight / numberCols * 3 / 2,
			ScreenHeight / 9 - 40
		},
		30,
		0,
		WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 20 - 1,
		ScreenHeight / 9 - 1,
		ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 3 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 3, DarkGray);
	nextBlock.Draw();

	DrawTextWithOutline(customFont, "Score", {
		ScreenWeight + ScreenWeight / numberCols * 3 / 2,  ScreenHeight / 9 + 210 }, 30, 0, WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 30 - 1,
		ScreenHeight / 9 + 250 - 1,
		ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 2 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9 + 250, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 2, DarkGray);
	
	std::string score_str = std::to_string(score);
	DrawTextEx(customFont, score_str.c_str(), {ScreenWeight + 30, ScreenHeight / 9 + 280}, 25, 0, White);

	DrawTextWithOutline(customFont, "Level", {
		ScreenWeight + ScreenWeight / numberCols * 3 / 2, ScreenHeight / 9 + 410 }, 30, 0, WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 30, ScreenHeight / 9 + 450 - 1, ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 2 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9 + 450, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 2, DarkGray);
	std::string level_str = std::to_string(level);
	DrawTextEx(customFont, level_str.c_str(), { ScreenWeight + 30, ScreenHeight / 9 + 480 }, 25, 0, White);

	DrawTextWithOutline(customFont, "Best", {
		ScreenWeight + 5 + ScreenWeight / numberCols * 3 / 2, ScreenHeight / 9 + 610 }, 30, 0, WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 30 - 1, ScreenHeight / 9 + 650 - 1, ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 2 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9 + 650, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 2, DarkGray);
	std::string best_str = std::to_string(best_score);
	DrawTextEx(customFont, best_str.c_str(), { ScreenWeight + 30, ScreenHeight / 9 + 680 }, 25, 0, White);

	DrawTexture(play, ScreenWeight + 10, ScreenHeight / 9 + 830, WHITE);

	DrawTexture(reload, ScreenWeight + 75, ScreenHeight / 9 + 830, WHITE);

	if (sound_on)
		DrawTexture(sound, ScreenWeight + 140, ScreenHeight / 9 + 830, WHITE);
	else
		DrawTexture(soundOff, ScreenWeight + 140, ScreenHeight / 9 + 830, WHITE);

}

void Game::Draw()
{
	grid.Draw();
	

	Block copy_block = currentBlock;
	copy_block.row_offset = 3;

	while(!Collision_Wall_Down(copy_block) && !Collision_AnotherBlock_Down(copy_block))
		copy_block.Move(1, 0);
	copy_block.Draw(Gray, 8);
	// !!!!
	currentBlock.Draw();
	
		DrawTextWithOutline(customFont, "Next",
		{
		ScreenWeight + 5 + ScreenWeight / numberCols * 3 / 2,
			ScreenHeight / 9 - 40
		},
		30,
		0,
		WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 20 - 1,
		ScreenHeight / 9 - 1,
		ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 3 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 3, DarkGray);
	nextBlock.Draw();

	DrawTextWithOutline(customFont, "Score", {
		ScreenWeight + ScreenWeight / numberCols * 3 / 2,  ScreenHeight / 9 + 210 }, 30, 0, WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 30 - 1,
		ScreenHeight / 9 + 250 - 1,
		ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 2 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9 + 250, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 2, DarkGray);
	
	std::string score_str = std::to_string(score);
	DrawTextEx(customFont, score_str.c_str(), {ScreenWeight + 30, ScreenHeight / 9 + 280}, 25, 0, White);

	DrawTextWithOutline(customFont, "Level", {
		ScreenWeight + ScreenWeight / numberCols * 3 / 2, ScreenHeight / 9 + 410 }, 30, 0, WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 30, ScreenHeight / 9 + 450 - 1, ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 2 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9 + 450, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 2, DarkGray);
	std::string level_str = std::to_string(level);
	DrawTextEx(customFont, level_str.c_str(), { ScreenWeight + 30, ScreenHeight / 9 + 480 }, 25, 0, White);

	DrawTextWithOutline(customFont, "Best", {
		ScreenWeight + 5 + ScreenWeight / numberCols * 3 / 2, ScreenHeight / 9 + 610 }, 30, 0, WHITE, DarkGray, 1);
	/*
	DrawRectangleLines(ScreenWeight + 30 - 1, ScreenHeight / 9 + 650 - 1, ScreenWeight / numberCols * 5 + 2, ScreenWeight / numberCols * 2 + 2, WHITE);
	*/
	DrawRectangle(ScreenWeight + 15, ScreenHeight / 9 + 650, ScreenWeight / numberCols * 5, ScreenWeight / numberCols * 2, DarkGray);
	std::string best_str = std::to_string(best_score);
	DrawTextEx(customFont, best_str.c_str(), { ScreenWeight + 30, ScreenHeight / 9 + 680 }, 25, 0, White);

	DrawTexture(pause, ScreenWeight + 10, ScreenHeight / 9 + 830, WHITE);

	DrawTexture(reload, ScreenWeight + 75, ScreenHeight / 9 + 830, WHITE);

	if (sound_on)
		DrawTexture(sound, ScreenWeight + 140, ScreenHeight / 9 + 830, WHITE);
	else
		DrawTexture(soundOff, ScreenWeight + 140, ScreenHeight / 9 + 830, WHITE);

	if (!Collision_Wall_Down())
	{
		if (!currentBlock.drop)
		{
			if (eventTriggered(speed) == true)
			{
				if (!Collision_AnotherBlock_Down())
					currentBlock.Move(1, 0);
			}
		}
		else
		{
			if (!Collision_AnotherBlock_Down())
				currentBlock.Move(1, 0);
		}		
	}

	if(Collision_Wall_Down() || Collision_AnotherBlock_Down())
	{
		if (eventTriggered(0) == true)
		{
			//currentBlock.drop = true;
			if (sound_on) { PlaySound(fallSound); };

			for (auto item : currentBlock.GetCellPosition())
			{
				grid.grid[item.row][item.col] = currentBlock.ID;
			}
			currentBlock = nextBlock;
			currentBlock.offset_x = 0;
			currentBlock.offset_y = 0;

			nextBlock = GetRandBlock();
			nextBlock.offset_x = ScreenWeight - frame / 3;
			nextBlock.offset_y = ScreenHeight / 8;
			
			
		}
		else
		{
			if (IsKeyPressed(KEY_RIGHT))
			{
				if (Collision_Wall_Right())
					currentBlock.Move(0, -1);
				if (!Collision_AnotherBlock_Right())
					currentBlock.Move(0, 1);
			}
			else if (IsKeyPressed(KEY_LEFT))
			{
				if (Collision_Wall_Left())
					currentBlock.Move(0, 1);
				if (!Collision_AnotherBlock_Left())
					currentBlock.Move(0, -1);
			}
			else if (IsKeyPressed(KEY_DOWN))
			{
				if (Collision_Wall_Down())
					currentBlock.Move(-1, 0);
				if (!Collision_AnotherBlock_Down())
					currentBlock.Move(1, 0);
			}
			else if (IsKeyPressed(KEY_UP))
			{

				while (Collision_Wall_Right() && Collision_AnotherBlock_Right())
					currentBlock.Move(0, -1);
				while (Collision_Wall_Left() && Collision_AnotherBlock_Left())
					currentBlock.Move(0, 1);
				while (Collision_Wall_Down() && Collision_AnotherBlock_Down())
					currentBlock.Move(-1, 0);
				while (Collision_Wall_Up() && Collision_AnotherBlock_Up())
					currentBlock.Move(1, 0);


				if (!Collision_AnotherBlock_Right() && !Collision_AnotherBlock_Left() && !Collision_AnotherBlock_Up() 
					&& !Collision_Wall_Right() && !Collision_Wall_Left() && !Collision_Wall_Up())
				{
					currentBlock.Move(-3, 0);
					currentBlock.RotationState += 1;
					if (currentBlock.RotationState >= currentBlock.cells.size())
						currentBlock.RotationState = 0;

				}

			}
			
		}
		
	}
}

void Game::Check_Keyboard_Click()
{
	if (currentBlock.drop) return;
	if (IsKeyPressed(KEY_RIGHT))
	{
		if (Collision_Wall_Right())
			currentBlock.Move(0, -1);
		if(!Collision_AnotherBlock_Right())
			currentBlock.Move(0, 1);
	}
	else if (IsKeyPressed(KEY_LEFT))
	{
		if (Collision_Wall_Left())
			currentBlock.Move(0, 1);
		if (!Collision_AnotherBlock_Left())
			currentBlock.Move(0, -1);
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		if (Collision_Wall_Down())
			currentBlock.Move(-1, 0);
		if (!Collision_AnotherBlock_Down())
			currentBlock.Move(1, 0);
	}
	else if (IsKeyPressed(KEY_UP))
	{
		
		while (Collision_Wall_Right())
			currentBlock.Move(0, -1);
		while (Collision_Wall_Left())
			currentBlock.Move(0, 1);
		while (Collision_Wall_Down())
			currentBlock.Move(-1, 0);
		while (Collision_Wall_Up())
			currentBlock.Move(1, 0);

		
		if (!Collision_AnotherBlock_Right() && !Collision_AnotherBlock_Left() && !Collision_AnotherBlock_Down() && !Collision_AnotherBlock_Up())
		{
			currentBlock.RotationState += 1;
			if (currentBlock.RotationState >= currentBlock.cells.size())
				currentBlock.RotationState = 0;
			
		}
	}
	else if (IsKeyPressed(KEY_SPACE))
	{
		currentBlock.drop = true;
	}
	else if (IsKeyPressed(KEY_RIGHT_SHIFT))
	{
		if (sound_on)
			PlaySound(menu);
		pause_st = !pause_st;
	}
	else if (IsKeyPressed(KEY_LEFT_SHIFT))
	{
		if (sound_on)
			PlaySound(menu);
		reload_st = !reload_st;
	}
	/*if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePosition = GetMousePosition();

		if (CheckCollisionPointRec(mousePosition, pauseRect)) {
			if (sound_on)
				PlaySound(menu);
			pause_st = !pause_st;
		}
		if (CheckCollisionPointRec(mousePosition, soundRect)) {
			if (sound_on)
				PlaySound(menu);
			sound_on = !sound_on;
		}
		if (CheckCollisionPointRec(mousePosition, reloadRect)) {
			if (sound_on)
				PlaySound(menu);
			reload_st = true;
		}
	}*/
}

void Game::Check_Mouse_Click()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePosition = GetMousePosition();

		if (CheckCollisionPointRec(mousePosition, pauseRect)) {
			if (sound_on)
				PlaySound(menu);
			pause_st = !pause_st;
		}
		if (CheckCollisionPointRec(mousePosition, soundRect)) {
			if (sound_on)
				PlaySound(menu);
			sound_on = !sound_on;
		}
		if (CheckCollisionPointRec(mousePosition, reloadRect)) {
			if (sound_on)
				PlaySound(menu);
			reload_st = true;
		}
	}
}

bool Game::Collision_AnotherBlock_Down()
{
	for (auto item : currentBlock.GetCellPosition())
	{
		if (!Collision_Wall_Down())
		{
			if (item.row + 1 <= grid.numRows - 1)
			{
				if (grid.grid[item.row + 1][item.col] != 0)
					return true;
			}
		}
	}
	return false;
}

bool Game::Collision_AnotherBlock_Down(Block block)
{
	for (auto item : block.GetCellPosition())
	{
		if (!Collision_Wall_Down())
		{
			if (item.row + 1 <= grid.numRows - 1)
			{
				if (grid.grid[item.row + 1][item.col] != 0)
					return true;
			}
		}
	}
	return false;
}

bool Game::Collision_AnotherBlock_Up()
{
	for (auto item : currentBlock.GetCellPosition())
	{
		
		if (!Collision_Wall_Up())
		{
			if (grid.grid[item.row - 1][item.col] != 0)
				return true;
		}
	}
	return false;
}

bool Game::Collision_AnotherBlock_Left()
{
	for (auto item : currentBlock.GetCellPosition())
	{
		
		if (item.col - 1 >= 0)
		{
			if (grid.grid[item.row][item.col - 1] != 0)
				return true;
		}
	}
	return false;
}

bool Game::Collision_AnotherBlock_Right()
{
	for (auto item : currentBlock.GetCellPosition())
	{
		
		if (item.col + 1 <= grid.numCols - 1)
		{
			if (grid.grid[item.row][item.col + 1] != 0)
				return true;
		}
	}
	return false;
}

bool Game::Collision_Wall_Down()
{
	for (auto item : currentBlock.GetCellPosition())
	{

		if (item.row >= grid.numRows - 1)
			return true;
	}
	return false;
}

bool Game::Collision_Wall_Down(Block block)
{
	for (auto item : block.GetCellPosition())
	{

		if (item.row >= grid.numRows - 1)
			return true;
	}
	return false;
}

bool Game::Collision_Wall_Up()
{
	for (auto item : currentBlock.GetCellPosition())
	{
		if (item.row <= 0)
			return true;
	}
	return false;
}

bool Game::Collision_Wall_Left()
{
	for (auto item : currentBlock.GetCellPosition())
	{
		if (item.col <= 0)
			return true;
	}
	return false;
}

bool Game::Collision_Wall_Right()
{
	for (auto item : currentBlock.GetCellPosition())
	{
		if (item.col >= grid.numCols - 1)
			return true;
	}
	return false;
}

void Game::Flicker_Fill()
{
	flicker = {8, 9, 10};
}

bool Game::Destroy_Row(std::vector<int> rows)
{
	if (flicker.size() == 0)
	{
		Flicker_Fill();
	}
	
	auto color = flicker.back();
	flicker.pop_back();

	if (eventTriggered(1) == true)
	{
		color = 0;
	}

	for (int row : rows)
	{
		for (int col = 0; col < grid.grid[row].size(); col++)
		{
			grid.grid[row][col] = color;
		}
	}

	if (score > best_score)
	{
		if (sound_on)
			PlaySound(new_best);
		std::ofstream out;
		out.open("best.txt");

		out << score;
		best_score = score;
		out.close();
	}

	if (color == 10 || color == 8 || color == 9)
		return false;
	else
		return true;
}

void Game::Offset_DelRows(int row)
{
	if (row <= 0)
		return;

	for (int i = row - 1; i > 0; i--)
	{
		for (int col = 0; col < grid.grid[row].size(); col++)
		{
			if (grid.grid[i][col] != 0)
			{
				grid.grid[i + 1][col] = grid.grid[i][col];
			}
			grid.grid[i][col] = 0;
		}
	}
}

void Game::CheckLevel(int rows)
{
	if (rows == 0)
		return;
	deleted_rows += rows;
	if (deleted_rows >= level * 10)
	{
		if (sound_on)
			PlaySound(new_level);
		level += 1;
		if(speed > 0.25)
			speed -= 0.05;
	}

	switch (rows)
	{
	case(1):
		score += 40 * (level + 1);
		break;
	case(2):
		score += 100 * (level + 1);
		break;
	case(3):
		score += 300 * (level + 1);
		break;
	case(4):
		score += 1200 * (level + 1);
		break;
	}

}

void Game::GameOver()
{
	if (Collision_Wall_Up() && Collision_AnotherBlock_Down())
	{
		if (sound_on) { PlaySound(gameoverSound); };
		gameOver = true;
	}
}

Game::~Game()
{
	UnloadTexture(pause);
	UnloadTexture(play);
	UnloadTexture(reload);

	UnloadTexture(sound);
	UnloadTexture(soundOff);

	UnloadSound(fallSound);
	UnloadSound(gameoverSound);
	UnloadSound(clear_line);
	//UnloadSound(rotate);
	UnloadSound(menu);
	UnloadSound(new_level);
	UnloadSound(new_best);
	CloseAudioDevice();
}