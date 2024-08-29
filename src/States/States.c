#include "States.h"
#include "../Core.h"

#include "Menu.h"
#include "Gameplay.h"
#include "Pause.h"
#include "End.h"

void States_Initialize(void)
{
    GameData* game = GameData_Get();
    game->gameStates[GAMESTATE_MENU].Start = _Menu_Start;
    game->gameStates[GAMESTATE_MENU].Update = _Menu_Update;
    game->gameStates[GAMESTATE_MENU].Draw = _Menu_Draw;

    game->gameStates[GAMESTATE_GAMEPLAY].Start = _Gameplay_Start;
    game->gameStates[GAMESTATE_GAMEPLAY].Update = _Gameplay_Update;
    game->gameStates[GAMESTATE_GAMEPLAY].Draw = _Gameplay_Draw;

    game->gameStates[GAMESTATE_PAUSE].Start = _Pause_Start;
    game->gameStates[GAMESTATE_PAUSE].Update = _Pause_Update;
    game->gameStates[GAMESTATE_PAUSE].Draw = _Pause_Draw;
    Pause_Initialize();

    game->gameStates[GAMESTATE_END].Start = _End_Start;
    game->gameStates[GAMESTATE_END].Update = _End_Update;
    game->gameStates[GAMESTATE_END].Draw = _End_Draw;
    End_Initialize();
}

void States_Change(const unsigned char newState)
{
    GameData* game = GameData_Get();
    game->gameStates[newState].Start(game->stateIndex);
    game->stateIndex = newState;
}

GameState States_Get(void)
{
    GameData* game = GameData_Get();
    return game->gameStates[game->stateIndex];
}