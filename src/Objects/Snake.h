#pragma once
#include "raylib.h"

#define UPDATE_TIME (1.0f / 8.0f)

typedef struct Snake
{
    unsigned char position[2];
    unsigned char length;
    unsigned char travel[253];
    Image image;;
    Texture2D texture;
} Snake;

void Snake_Update(Snake* snake);
void Snake_GetPositions(const Snake* const snake, unsigned char* positionBuffer);
void Snake_Draw(const Snake* const snake);