#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Drawing.h"
#include "States/Pause.h"

typedef struct dirent dirent;

static TextureEntry s_textureEntries[2];
static unsigned char s_textureEntryCount;

void Drawing_Initialize()
{
    g_gameData->renderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    g_gameData->prevRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    SetTextureFilter(g_gameData->renderTexture.texture, TEXTURE_FILTER_POINT);
    Drawing_SetWindowMode(g_gameData->saveData.windowMode);

    DIR* d = opendir("res/");;
    if (d)
    {
        while (true)
        {
			const dirent* dir = readdir(d);
            if (dir == NULL)
                break;
            if (strstr(dir->d_name, ".png"))
                _Drawing_Load(dir->d_name);
        }
        closedir(d);
    }
}

void _Drawing_Load(const char* name)
{
    char filePath[32] = "res/";
    strcpy(s_textureEntries[s_textureEntryCount].name, name);
    strcat(filePath, name);
    s_textureEntries[s_textureEntryCount].image = LoadImage(filePath);
    s_textureEntries[s_textureEntryCount].texture = LoadTextureFromImage(s_textureEntries[s_textureEntryCount].image);
    s_textureEntryCount++;
}

Texture2D* Drawing_GetTexture(const char* name)
{
    for (unsigned char i = 0; i < s_textureEntryCount; i++)
    {
        if (strcmp(s_textureEntries[i].name, name) == 0)
            return &s_textureEntries[i].texture;
    }

    printf("Texture [%s] could not be found!\n", name);
    return NULL;
}

void Drawing_Free()
{
    UnloadRenderTexture(g_gameData->renderTexture);
    UnloadRenderTexture(g_gameData->prevRenderTexture);
    Pause_Free();

    for (unsigned char i = 0; i < s_textureEntryCount; i++)
    {
        UnloadTexture(s_textureEntries[i].texture);
        UnloadImage(s_textureEntries[i].image);
    }
}

void Drawing_Checkerboard(const Vector2 position, const unsigned char squareSize, const char countX, const char countY, const Color color1, const Color color2)
{
    bool drawSecondColor = false;
    for (char i = 0; i < countX; i++)
    {
        for (char j = 0; j < countY; j++)
        {
            drawSecondColor = !drawSecondColor;
            DrawRectangle(position.x + squareSize * i, position.y + squareSize * j, squareSize, squareSize, drawSecondColor ? color2 : color1);
        }
        drawSecondColor = !drawSecondColor;
    }
}

void Drawing_ScoreToString(unsigned char score, char* str)
{
    if (score > 99)
    {
        str[0] = score / 100 + '0';
        score -= score / 100 * 100;
        str[1] = score / 10 + '0';
        score -= score / 10 * 10;
        str[2] = score + '0';
        str[3] = 0;
        return;
    }

    if (score > 9)
    {
        str[0] = score / 10 + '0';
        score -= score / 10 * 10;
        str[1] = score + '0';
        str[2] = 0;
        return;
    }

    str[0] = score + '0';
    str[1] = 0;
}

void Drawing_Fade()
{
    const float a = 1 - States_Get()->timeInState / FADE_TIME;
    if (a < 0)
        return;
    DrawTexture(g_gameData->prevRenderTexture.texture, 0, 0, ColorAlpha(WHITE, a));
}

void Drawing_SetWindowMode(const int mode)
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