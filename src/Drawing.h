#pragma once
#include "Core.h"

#define FADE_TIME 0.175f

typedef struct TextureEntry
{
	const char name[32];
	Image image;
	Texture2D texture;
} TextureEntry;

void Drawing_Initialize();
void _Drawing_Load(const char* name);
Texture2D* Drawing_GetTexture(const char* name);
void Drawing_Free();
void Drawing_Checkerboard(const Vector2 position, const unsigned char squareSize, const char countX, const char countY, const Color color1, const Color color2);
void Drawing_ScoreToString(const unsigned char score, char* str);
void Drawing_Fade();
void Drawing_SetWindowMode(const int mode);