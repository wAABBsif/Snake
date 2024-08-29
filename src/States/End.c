#include "End.h"

static const char* const s_textOptions[] =
{
    "Score: %02i",
    "Highscore: %02i",
    "New high score!",
    "Press Enter to Continue"
};

static float s_textPositions[sizeof(s_textOptions) / sizeof(char*)];
static float s_timeInState;
static bool s_hasSetHighScore = false;

void End_Initialize()
{
    for (int i = 0; i < sizeof(s_textOptions) / sizeof(char*); i++)
        s_textPositions[i] = (SCREEN_WIDTH - MeasureText(TextFormat(s_textOptions[i], 99), END_TEXT_SIZE)) / 2;
}

void _End_Start(const unsigned char prevState)
{
    s_hasSetHighScore = g_gameData->score > g_gameData->saveData.highScore;

    if (s_hasSetHighScore)
        g_gameData->saveData.highScore = g_gameData->score;

    s_timeInState = 0;
}

void _End_Update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        SavePlayerData(&g_gameData->saveData);
        States_Change(GAMESTATE_MENU);
        return;
    }

    s_timeInState += GetFrameTime();
}

void _End_Draw()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ColorAlpha(BACKGROUND_COLOR, s_timeInState / END_FADE_TIME));
    DrawText(TextFormat(s_textOptions[0], g_gameData->score), s_textPositions[0], END_TEXT_START_POSITION, END_TEXT_SIZE, ColorAlpha(RAYWHITE, s_timeInState / END_FADE_TIME));
    DrawText(TextFormat(s_textOptions[1], g_gameData->saveData.highScore), s_textPositions[1], END_TEXT_START_POSITION + END_TEXT_SPACING * 1, END_TEXT_SIZE, ColorAlpha(RAYWHITE, s_timeInState / END_FADE_TIME));
    if (s_hasSetHighScore)
        DrawText(s_textOptions[2], s_textPositions[2], END_TEXT_START_POSITION + END_TEXT_SPACING * 2, END_TEXT_SIZE, ColorAlpha(YELLOW, s_timeInState / END_FADE_TIME));

    DrawText(s_textOptions[3], s_textPositions[3], END_TEXT_START_POSITION + END_TEXT_SPACING * 4, END_TEXT_SIZE, ColorAlpha(RED, s_timeInState / END_FADE_TIME));
}