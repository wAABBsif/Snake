#include "Core.h"

#include <stdio.h>

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
        //this doesn't seem to work?
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
    }
    else
    {
        SetWindowSize(SCREEN_WIDTH * game->saveData.scale, SCREEN_HEIGHT * game->saveData.scale);
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
}
