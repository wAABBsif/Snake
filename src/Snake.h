#pragma once
#include "raylib.h"

#define UPDATE_TIME (1.0f / 10.0f)

typedef struct Snake
{
    unsigned char position[2];
    unsigned char length;
    Image image;;
    Texture2D texture;
    unsigned char travel[256];
} Snake;

void Snake_Update(Snake* snake);
void Snake_GetPositions(const Snake* const snake, unsigned char* positionBuffer);
bool Snake_CheckForHit(const Snake* const snake, unsigned char position[]);
void Snake_Draw(const Snake* const snake);