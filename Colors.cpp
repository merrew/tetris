#include "Colors.h"

Color DarkGray = { 40, 40, 40, 255 };
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
Color BeigeGray = { 80, 73, 69, 255 };


std::vector<Color> SetColor()
{
	return { DarkGray, DeepPink, Cyan, Yellow, Lime, BrightPurple, Orange, Blue, White, LightGray, DarkGray };
}

std::vector<Texture2D> SetTexture()
{
	std::vector<Texture2D> textures(8);
	textures[1] = LoadTexture("texture1.png");
	textures[2] = LoadTexture("texture2.png");
	textures[3] = LoadTexture("texture3.png");
	textures[4] = LoadTexture("texture4.png");
	textures[5] = LoadTexture("texture5.png");
	textures[6] = LoadTexture("texture6.png");
	textures[7] = LoadTexture("texture7.png");
	return textures;
}
