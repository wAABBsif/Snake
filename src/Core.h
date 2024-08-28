#pragma once
#include "Objects/Orb.h"
#include "raylib.h"
#include "SaveData.h"
#include "Objects/Snake.h"

#define GAMESTATE_MENU 0
#define GAMESTATE_GAMEPLAY 1
#define GAMESTATE_PAUSE 2
#define GAMESTATE_COUNT 3

typedef struct Snake Snake;
typedef struct Orb Orb;
typedef struct GameData GameData;

typedef struct GameState
{
    void (*Start)(GameData* game, const unsigned char prevState);
    void (*Update)(GameData* game);
    void (*Draw)(const GameData* game);
} GameState;

typedef struct GameData
{
    GameState gameStates[GAMESTATE_COUNT];
    Snake snake;
    Orb orb;
    SaveData saveData;
    unsigned char score;
    unsigned char stateIndex;
} GameData;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256

void ChangeState(GameData* game, const unsigned char newState);