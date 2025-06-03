#pragma once
#include "Block.h"
#include "Grid.h"
#include "string"

class Game
{
public:
	Grid grid;

	//bool time_check();
	int level;
	double speed = 0.5;
	int deleted_rows = 0;
	int score = 0;
	int best_score;

	Texture2D pause;
	Texture2D play;
	Rectangle pauseRect;
	bool pause_st = false;

	Texture2D reload;
	Rectangle reloadRect;
	bool reload_st = false;

	Texture2D sound;
	Texture2D soundOff;
	Rectangle soundRect;
	Sound fallSound;
	Sound gameoverSound;
	Sound clear_line;
	//Sound rotate;
	Sound menu;
	Sound new_level;
	Sound new_best;

	bool sound_on = true;

	bool gameOver = false;
	bool eventTriggered(double interval);

	Game();
	void Check_Keyboard_Click();

	void Check_Mouse_Click();

	bool Collision_Wall_Down();
	bool Collision_Wall_Down(Block block);
	bool Collision_Wall_Up();
	bool Collision_Wall_Left();
	bool Collision_Wall_Right();

	void Flicker_Fill();

	bool Destroy_Row(std::vector<int> rows);

	void Offset_DelRows(int row);

	void CheckLevel(int rows);

	void GameOver();

	bool Collision_AnotherBlock_Right();
	bool Collision_AnotherBlock_Left();
	bool Collision_AnotherBlock_Down();
	bool Collision_AnotherBlock_Down(Block block);
	bool Collision_AnotherBlock_Up();

	void Pause();
	void Draw();
	~Game();

private:
	std::vector<int> flicker;
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;

	void FillBlocks();
	Block GetRandBlock();

};