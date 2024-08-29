#pragma once

typedef struct GameData GameData;

#define GAMESTATE_MENU 0
#define GAMESTATE_GAMEPLAY 1
#define GAMESTATE_PAUSE 2
#define GAMESTATE_END 3
#define GAMESTATE_COUNT 4

typedef struct GameState
{
    void (*Start)(const unsigned char prevState);
    void (*Update)();
    void (*Draw)();
} GameState;

void States_Initialize(void);
void States_Change(const unsigned char newState);
GameState States_Get(void);