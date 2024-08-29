#pragma once
#include "raylib.h"
#include "SaveData.h"
#include "States/States.h"
#include "Objects/Orb.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0xFF}

#define WINDOW_MODE_DEFAULT 0
#define WINDOW_MODE_BORDERLESS 1
#define WINDOW_MODE_FULLSCREEN 2

void SetWindowMode(const int mode);

extern GameData* g_gameData;

typedef struct GameData
{
    RenderTexture2D prevRenderTexture;
    RenderTexture2D renderTexture;
    GameState gameStates[4];
    Snake snake;
    Orb orb;
    SaveData saveData;
    unsigned char score;
    unsigned char stateIndex;
    unsigned char prevStateIndex;
} GameData;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256