#include "Core.h"

void ChangeState(GameData* game, const unsigned char newState)
{
    game->gameStates[newState].Start(game, game->stateIndex);
    game->stateIndex = newState;
}