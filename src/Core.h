#pragma once
#include "Orb.h"
#include "raylib.h"
#include "SaveData.h"
#include "Snake.h"

typedef struct Snake Snake;
typedef struct Orb Orb;

typedef struct GameData
{
    unsigned char score;
    Snake snake;
    Orb orb;
    SaveData saveData;
} GameData;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256