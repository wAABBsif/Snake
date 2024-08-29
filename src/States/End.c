#include "End.h"

static const char* const textOptions[] =
{
    "Score: %02i",
    "Highscore: %02i",
    "New high score!",
    "Press Enter to Continue"
};

static float textPositions[sizeof(textOptions) / sizeof(char*)];

static bool hasSetHighScore = false;

void End_Initialize()
{
    for (int i = 0; i < sizeof(textOptions) / sizeof(char*); i++)
        textPositions[i] = (SCREEN_WIDTH - MeasureText(TextFormat(textOptions[i], 99), END_TEXT_SIZE)) / 2;
}

void _End_Start(const unsigned char prevState)
{
    GameData* game = GameData_Get();
    hasSetHighScore = game->score > game->saveData.highScore;

    if (hasSetHighScore)
        game->saveData.highScore = game->score;
}

void _End_Update()
{
    GameData* game = GameData_Get();
    if (IsKeyPressed(KEY_ENTER))
    {
        SavePlayerData(&game->saveData);
        States_Change(GAMESTATE_MENU);
        return;
    }
}

void _End_Draw()
{
    const GameData* game = GameData_Get();
    DrawText(TextFormat(textOptions[0], game->score), textPositions[0], END_TEXT_START_POSITION, END_TEXT_SIZE, RAYWHITE);
    DrawText(TextFormat(textOptions[1], game->saveData.highScore), textPositions[1], END_TEXT_START_POSITION + END_TEXT_SPACING * 1, END_TEXT_SIZE, RAYWHITE);
    if (hasSetHighScore)
        DrawText(textOptions[2], textPositions[2], END_TEXT_START_POSITION + END_TEXT_SPACING * 2, END_TEXT_SIZE, YELLOW);

    DrawText(textOptions[3], textPositions[3], END_TEXT_START_POSITION + END_TEXT_SPACING * 4, END_TEXT_SIZE, RED);
}