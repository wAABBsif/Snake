#include "Core.h"

#include <stdio.h>

GameData* g_gameData = NULL;

void SetWindowMode(const int mode)
{
    static bool s_isFullscreen = false;
    static bool s_isBorderless = false;

    if (mode == WINDOW_MODE_BORDERLESS && !s_isBorderless)
    {
        ToggleBorderlessWindowed();
        s_isBorderless = true;
    }

    if (mode != WINDOW_MODE_BORDERLESS && s_isBorderless)
    {
        ToggleBorderlessWindowed();
        s_isBorderless = false;
    }

    if (mode == WINDOW_MODE_FULLSCREEN)
    {
        //does not work on some devices?
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
    }

    if (mode == WINDOW_MODE_FULLSCREEN && !s_isFullscreen)
    {
        ToggleFullscreen();
        s_isFullscreen = true;
    }

    if (mode != WINDOW_MODE_FULLSCREEN && s_isFullscreen)
    {
        ToggleFullscreen();
        s_isFullscreen = false;
    }

    if (mode != WINDOW_MODE_FULLSCREEN)
    {
        SetWindowSize(SCREEN_WIDTH * g_gameData->saveData.scale, SCREEN_HEIGHT * g_gameData->saveData.scale);
    }
}