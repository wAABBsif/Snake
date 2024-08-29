#pragma once

typedef struct GameData GameData;

#define GAMESTATE_MENU 0
#define GAMESTATE_GAMEPLAY 1
#define GAMESTATE_PAUSE 2
#define GAMESTATE_END 3
#define GAMESTATE_COUNT 4

typedef struct GameState
{
    void (*Start)(GameData* game, const unsigned char prevState);
    void (*Update)(GameData* game);
    void (*Draw)(const GameData* game);
} GameState;

void States_Initialize(GameData* game);
void States_Change(GameData* game, const unsigned char newState);
GameState States_Get(const GameData* game);