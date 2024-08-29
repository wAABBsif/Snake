#include "States.h"
#include "../Core.h"

#include "Menu.h"
#include "Gameplay.h"
#include "Pause.h"

void States_Initialize(GameData* game)
{
    game->gameStates[GAMESTATE_MENU].Start = _Menu_Start;
    game->gameStates[GAMESTATE_MENU].Update = _Menu_Update;
    game->gameStates[GAMESTATE_MENU].Draw = _Menu_Draw;

    game->gameStates[GAMESTATE_GAMEPLAY].Start = _Gameplay_Start;
    game->gameStates[GAMESTATE_GAMEPLAY].Update = _Gameplay_Update;
    game->gameStates[GAMESTATE_GAMEPLAY].Draw = _Gameplay_Draw;

    game->gameStates[GAMESTATE_PAUSE].Start = _Pause_Start;
    game->gameStates[GAMESTATE_PAUSE].Update = _Pause_Update;
    game->gameStates[GAMESTATE_PAUSE].Draw = _Pause_Draw;
    Pause_Initialize(game);
}

void States_Change(GameData* game, const unsigned char newState)
{
    game->gameStates[newState].Start(game, game->stateIndex);
    game->stateIndex = newState;
}

GameState States_Get(const GameData* game)
{
    return game->gameStates[game->stateIndex];
}