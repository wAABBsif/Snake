#include "Pause.h"
#include "../Drawing.h"
#include "../Sound.h"

static const char* const s_textOptions[] =
{
    "Resume",
    "Exit to Menu"
};

static float s_textPositions[sizeof(s_textOptions) / sizeof(char*)];
static unsigned char s_menuSelection;

static RenderTexture2D s_renderTexture;

void Pause_Initialize(void)
{
    s_renderTexture = LoadRenderTexture(PAUSE_WIDTH, PAUSE_HEIGHT);
    for (int i = 0; i < sizeof(s_textOptions) / sizeof(char*); i++)
        s_textPositions[i] = (PAUSE_WIDTH - MeasureText(s_textOptions[i], PAUSE_TEXT_SIZE)) / 2;
}

void _Pause_Start(void)
{
    s_menuSelection = 0;
    Sound_Play("pauseEnter.wav");
}

void _Pause_Update(void)
{
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_PAUSE) || IsKeyPressed(KEY_ESCAPE))
    {
        Sound_Play("menuEnter.wav");
        States_Change(GAMESTATE_GAMEPLAY);

        //Save pause screen texture to previous render texture
        BeginTextureMode(g_gameData->prevRenderTexture);
        ClearBackground(BLANK);
        DrawTexture(s_renderTexture.texture, (SCREEN_WIDTH - PAUSE_WIDTH) / 2, (SCREEN_HEIGHT - PAUSE_HEIGHT) / 2, WHITE);
        EndTextureMode();

        return;
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        Sound_Play("menuMove.wav");
        s_menuSelection++;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        Sound_Play("menuMove.wav");
        s_menuSelection--;
    }

    s_menuSelection %= 2;

    if (IsKeyPressed(KEY_ENTER))
    {
        Sound_Play("menuEnter.wav");
        States_Change(1 - s_menuSelection);
    }
}

void _Pause_Draw(void)
{
    DrawTexture(g_gameData->prevRenderTexture.texture, 0, 0, WHITE);
    //Stop current render texture
    EndTextureMode();

    //Render pause screen to a render texture
    BeginTextureMode(s_renderTexture);
    ClearBackground(BLANK);
    DrawRectangle(0,0, PAUSE_WIDTH, PAUSE_HEIGHT, BACKGROUND_COLOR);
    const char textHeight = PAUSE_HEIGHT / (sizeof(s_textOptions) / sizeof(char*));
    for (int i = 0; i < sizeof(s_textOptions) / sizeof(char*); i++)
        DrawText(s_textOptions[i], s_textPositions[i], textHeight - PAUSE_TEXT_SIZE + textHeight * i, PAUSE_TEXT_SIZE, i == s_menuSelection ? YELLOW : RAYWHITE);
    EndTextureMode();

    //Render pause screen texture to game render texture
    BeginTextureMode(g_gameData->renderTexture);
    DrawTexturePro(s_renderTexture.texture, (Rectangle){0, 0, PAUSE_WIDTH, -PAUSE_HEIGHT}, (Rectangle){(SCREEN_WIDTH - PAUSE_WIDTH) / 2, (SCREEN_HEIGHT - PAUSE_HEIGHT) / 2, PAUSE_WIDTH, PAUSE_HEIGHT}, (Vector2){0, 0}, 0, ColorAlpha(WHITE, States_Get()->timeInState / FADE_TIME));
}

//This CANNOT be the best way to do this!
void Pause_Free(void)
{
    UnloadRenderTexture(s_renderTexture);
}