#include "Colors.h"

Color DarkGray = { 12, 23, 45, 255 };
Color DeepPink = { 255, 20, 147, 255 };
Color Cyan = { 0, 255, 255, 255 };
Color Yellow = { 255, 255, 0, 255 };
Color Lime = { 124, 252, 0, 255 };
Color BrightPurple = { 190, 3, 253, 255 };
Color Orange = { 255, 140, 0, 255 };
Color Blue = { 0, 0, 255, 255 };
Color White = { 255, 255, 255, 255 };
Color LightGray = { 0, 0, 0, 255 };
Color Gray = { 0, 0, 0, 79 };

std::vector<Color> SetColor()
{
	return { DarkGray, DeepPink, Cyan, Yellow, Lime, BrightPurple, Orange, Blue, White, LightGray };
}