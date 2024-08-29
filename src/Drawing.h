#pragma once
#include "Core.h"

#define FADE_TIME 0.175f

void CheckerboardDraw(const Vector2 position, const unsigned char squareSize, const char countX, const char countY, const Color color1, const Color color2);
void ScoreToString(const unsigned char score, char* str);
void DrawFade();