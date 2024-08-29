#include "End.h"
#include "../Drawing.h"

static const char* const s_textOptions[] =
{
    "Score: %02i",
    "Highscore: %02i",
    "New high score!",
    "Press Enter to Continue"
};

static float s_textPositions[sizeof(s_textOptions) / sizeof(char*)];
static bool s_hasSetHighScore = false;

void End_Initialize()
{
    for (int i = 0; i < sizeof(s_textOptions) / sizeof(char*); i++)
        s_textPositions[i] = (SCREEN_WIDTH - MeasureText(TextFormat(s_textOptions[i], 99), END_TEXT_SIZE)) / 2;
}

void _End_Start(void)
{
    s_hasSetHighScore = g_gameData->score > g_gameData->saveData.highScore;

    if (s_hasSetHighScore)
        g_gameData->saveData.highScore = g_gameData->score;
}

void _End_Update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        SavePlayerData(&g_gameData->saveData);
        States_Change(GAMESTATE_MENU);
        return;
    }
}

void _End_Draw()
{
    DrawText(TextFormat(s_textOptions[0], g_gameData->score), s_textPositions[0], END_TEXT_START_POSITION, END_TEXT_SIZE, RAYWHITE);
    DrawText(TextFormat(s_textOptions[1], g_gameData->saveData.highScore), s_textPositions[1], END_TEXT_START_POSITION + END_TEXT_SPACING * 1, END_TEXT_SIZE, RAYWHITE);
    if (s_hasSetHighScore)
        DrawText(s_textOptions[2], s_textPositions[2], END_TEXT_START_POSITION + END_TEXT_SPACING * 2, END_TEXT_SIZE, YELLOW);

    DrawText(s_textOptions[3], s_textPositions[3], END_TEXT_START_POSITION + END_TEXT_SPACING * 4, END_TEXT_SIZE, RED);
    DrawFade();
}