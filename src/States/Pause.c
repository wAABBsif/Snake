#include "Pause.h"

static const char* const textOptions[] =
{
    "Resume",
    "Exit to Menu"
};

static float textPositions[sizeof(textOptions) / sizeof(char*)];
static unsigned char menuSelection;

void Pause_Initialize(GameData* game)
{
    for (int i = 0; i < sizeof(textOptions) / sizeof(char*); i++)
        textPositions[i] = (SCREEN_WIDTH - MeasureText(textOptions[i], PAUSE_TEXT_SIZE)) / 2;
}

void _Pause_Start(GameData* game, const unsigned char prevState)
{
    menuSelection = 0;
}

void _Pause_Update(GameData* game)
{
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_PAUSE) || IsKeyPressed(KEY_ESCAPE))
    {
        States_Change(game, GAMESTATE_GAMEPLAY);
        return;
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        menuSelection++;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        menuSelection--;

    menuSelection %= 2;

    if (IsKeyPressed(KEY_ENTER))
    {
        States_Change(game, 1 - menuSelection);
    }
}

void _Pause_Draw(const GameData* game)
{
    game->gameStates[GAMESTATE_GAMEPLAY].Draw(game);
    DrawRectangle((SCREEN_WIDTH - PAUSE_WIDTH) / 2, (SCREEN_HEIGHT - PAUSE_HEIGHT) / 2, PAUSE_WIDTH, PAUSE_HEIGHT, BACKGROUND_COLOR);
    const char textHeight = PAUSE_HEIGHT / (sizeof(textOptions) / sizeof(char*));
    for (int i = 0; i < sizeof(textOptions) / sizeof(char*); i++)
        DrawText(textOptions[i], textPositions[i], (SCREEN_HEIGHT - PAUSE_HEIGHT) / 2 + textHeight - PAUSE_TEXT_SIZE + textHeight * i, PAUSE_TEXT_SIZE, i == menuSelection ? YELLOW : RAYWHITE);
}