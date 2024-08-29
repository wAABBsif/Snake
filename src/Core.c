#include "Core.h"

#include <stdio.h>

GameData* _gameData = NULL;

GameData* GameData_Get()
{
    return _gameData;
}

void GameData_Set(GameData* game)
{
    _gameData = game;
}

void SetWindowMode(const GameData* game, const int mode)
{
    static bool isFullscreen = false;
    static bool isBorderless = false;

    if (mode == WINDOW_MODE_BORDERLESS && !isBorderless)
    {
        ToggleBorderlessWindowed();
        isBorderless = true;
    }

    if (mode != WINDOW_MODE_BORDERLESS && isBorderless)
    {
        ToggleBorderlessWindowed();
        isBorderless = false;
    }

    if (mode == WINDOW_MODE_FULLSCREEN)
    {
        //does not work on some devices?
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
    }

    if (mode == WINDOW_MODE_FULLSCREEN && !isFullscreen)
    {
        ToggleFullscreen();
        isFullscreen = true;
    }

    if (mode != WINDOW_MODE_FULLSCREEN && isFullscreen)
    {
        ToggleFullscreen();
        isFullscreen = false;
    }

    if (mode != WINDOW_MODE_FULLSCREEN)
    {
        SetWindowSize(SCREEN_WIDTH * game->saveData.scale, SCREEN_HEIGHT * game->saveData.scale);
    }
}