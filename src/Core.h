#pragma once
#include "raylib.h"
#include "SaveData.h"
#include "Snake.h"

typedef struct Snake Snake;

typedef struct GameData
{
    Snake snake;
    SaveData saveData;
} GameData;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256