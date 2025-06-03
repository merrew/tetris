#include <iostream>
#include "Grid.h"
#include "Block.h"
#include "Game.h"

int main()
{
	InitWindow(ScreenWeight + frame, ScreenHeight, "Tetris");
	SetTargetFPS(60);

	Color DarkBlue = { 44, 44, 127, 255 };

	//Game game;
	Game* game = new Game();
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DarkBlue);

		game->GameOver();

		while (game->gameOver)
		{
			BeginDrawing();
			ClearBackground(DarkBlue);

			if (game->reload_st)
			{
				bool sound = game->sound_on;
				game->~Game();
				game = new Game();
				game->sound_on = sound;
				break;
			}

			game->Pause();
			DrawRectangle(ScreenWeight / 2 - ScreenWeight / numberCols * 3.5, ScreenHeight / 9 + 250, ScreenWeight / numberCols * 8, ScreenWeight / numberCols * 2, { 44, 44, 127, 255 });
			DrawText("GAME OVER", ScreenWeight / 2 - ScreenWeight / numberCols * 3.5 + 10, ScreenHeight / 9 + 280, 60, White);
			DrawText("(Press Enter to restart)", ScreenWeight / 2 - ScreenWeight / numberCols * 4, ScreenHeight / 9 + 380, 35, White);

			if (IsKeyPressed(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), game->reloadRect)))
			{
				bool sound = game->sound_on;
				game->~Game();
				game = new Game();
				game->sound_on = sound;
				break;
			}

			EndDrawing();
			if (WindowShouldClose())
			{
				return 0;
			}

		}

		if (game->reload_st)
		{
			bool sound = game->sound_on;
			game->~Game();
			game = new Game();
			game->sound_on = sound;
			continue;
		}

		while (game->pause_st)
		{
			if (game->reload_st)
			{
				bool sound = game->sound_on;
				game->~Game();
				game = new Game();
				game->sound_on = sound;
				break;
			}

			BeginDrawing();
			ClearBackground(DarkBlue);
			game->Check_Mouse_Click();
			game->Pause();
			EndDrawing();
			if (WindowShouldClose())
			{
				return 0;
			}
			//continue;
		}

		game->Draw();
		game->Check_Keyboard_Click();
		game->Check_Mouse_Click();
		
		auto delete_lines = game->grid.Check_FillLine();
		int count_delete_lines = delete_lines.size();
		game->CheckLevel(count_delete_lines);
		if (count_delete_lines != 0)
		{
			if(game->sound_on)
				PlaySound(game->clear_line);
			while (game->Destroy_Row(delete_lines) != true)
			{
				BeginDrawing();
				ClearBackground(DarkBlue);
				game->Pause();
				EndDrawing();
			}
			for (auto line : delete_lines)
			{
				BeginDrawing();
				ClearBackground(DarkBlue);
				game->Pause();
				game->Offset_DelRows(line);
				EndDrawing();
			}

		}

		EndDrawing();
	}

	CloseWindow();
}
