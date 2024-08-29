#include "States.h"
#include "../Core.h"

#include "Menu.h"
#include "Gameplay.h"
#include "Pause.h"
#include "End.h"

void States_Initialize(void)
{
    g_gameData->gameStates[GAMESTATE_MENU].Start = _Menu_Start;
    g_gameData->gameStates[GAMESTATE_MENU].Update = _Menu_Update;
    g_gameData->gameStates[GAMESTATE_MENU].Draw = _Menu_Draw;

    g_gameData->gameStates[GAMESTATE_GAMEPLAY].Start = _Gameplay_Start;
    g_gameData->gameStates[GAMESTATE_GAMEPLAY].Update = _Gameplay_Update;
    g_gameData->gameStates[GAMESTATE_GAMEPLAY].Draw = _Gameplay_Draw;

    g_gameData->gameStates[GAMESTATE_PAUSE].Start = _Pause_Start;
    g_gameData->gameStates[GAMESTATE_PAUSE].Update = _Pause_Update;
    g_gameData->gameStates[GAMESTATE_PAUSE].Draw = _Pause_Draw;
    Pause_Initialize();

    g_gameData->gameStates[GAMESTATE_END].Start = _End_Start;
    g_gameData->gameStates[GAMESTATE_END].Update = _End_Update;
    g_gameData->gameStates[GAMESTATE_END].Draw = _End_Draw;
    End_Initialize();
}

void States_Change(const unsigned char newState)
{
    g_gameData->gameStates[newState].Start(g_gameData->stateIndex);
    g_gameData->stateIndex = newState;
}

GameState States_Get(void)
{
    return g_gameData->gameStates[g_gameData->stateIndex];
}