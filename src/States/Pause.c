#include "Pause.h"

static const char* const s_textOptions[] =
{
    "Resume",
    "Exit to Menu"
};

static float s_textPositions[sizeof(s_textOptions) / sizeof(char*)];
static unsigned char s_menuSelection;

void Pause_Initialize(void)
{
    for (int i = 0; i < sizeof(s_textOptions) / sizeof(char*); i++)
        s_textPositions[i] = (SCREEN_WIDTH - MeasureText(s_textOptions[i], PAUSE_TEXT_SIZE)) / 2;
}

void _Pause_Start(const unsigned char prevState)
{
    s_menuSelection = 0;
}

void _Pause_Update(void)
{
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_PAUSE) || IsKeyPressed(KEY_ESCAPE))
    {
        States_Change(GAMESTATE_GAMEPLAY);
        return;
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        s_menuSelection++;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        s_menuSelection--;

    s_menuSelection %= 2;

    if (IsKeyPressed(KEY_ENTER))
    {
        States_Change(1 - s_menuSelection);
    }
}

void _Pause_Draw(void)
{
    g_gameData->gameStates[GAMESTATE_GAMEPLAY].Draw();
    DrawRectangle((SCREEN_WIDTH - PAUSE_WIDTH) / 2, (SCREEN_HEIGHT - PAUSE_HEIGHT) / 2, PAUSE_WIDTH, PAUSE_HEIGHT, BACKGROUND_COLOR);
    const char textHeight = PAUSE_HEIGHT / (sizeof(s_textOptions) / sizeof(char*));
    for (int i = 0; i < sizeof(s_textOptions) / sizeof(char*); i++)
        DrawText(s_textOptions[i], s_textPositions[i], (SCREEN_HEIGHT - PAUSE_HEIGHT) / 2 + textHeight - PAUSE_TEXT_SIZE + textHeight * i, PAUSE_TEXT_SIZE, i == s_menuSelection ? YELLOW : RAYWHITE);
}