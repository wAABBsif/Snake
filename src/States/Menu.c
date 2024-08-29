#include "Menu.h"
#include "../Drawing.h"

static const char* const s_gameName = "Snake";

static const char* const s_textOptions[] =
{
    "Highscore: %02i",
    "Play",
    "Scale: %i",
    "Windowed",
    "Borderless",
    "Fullscreen",
    "Filter: Point",
    "Filter: Bilinear",
    "Filter: Trilinear",
    "Quit"
};

static unsigned char s_menuSelection;

static unsigned short GetTextPosition(const char* text);
void DrawSnake(const GameData* game);

void _Menu_Start(const unsigned char prevState)
{
    s_menuSelection = 0;
}

void _Menu_Update(void)
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        s_menuSelection++;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        s_menuSelection--;

    s_menuSelection %= 5;

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (s_menuSelection)
        {
            case 0:
                SavePlayerData(&g_gameData->saveData);
                States_Change(GAMESTATE_GAMEPLAY);
                break;
            case 1:
                if (g_gameData->saveData.windowMode == WINDOW_MODE_FULLSCREEN)
                    break;
                g_gameData->saveData.scale++;
                if (g_gameData->saveData.scale > GetMonitorHeight(GetCurrentMonitor()) / SCREEN_HEIGHT)
                    g_gameData->saveData.scale = 1;
                if (g_gameData->saveData.windowMode == WINDOW_MODE_FULLSCREEN)
                    SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                else
                    SetWindowSize(SCREEN_WIDTH * g_gameData->saveData.scale, SCREEN_HEIGHT * g_gameData->saveData.scale);
                break;
            case 2:
                g_gameData->saveData.windowMode++;
                g_gameData->saveData.windowMode %= 3;
                SetWindowMode(g_gameData->saveData.windowMode);
                break;
            case 3:
                g_gameData->saveData.filter++;
                g_gameData->saveData.filter %= 3;
                SetTextureFilter(g_gameData->renderTexture.texture, g_gameData->saveData.filter);
                break;
            default:
                CloseWindow();
        }
    }
}

void _Menu_Draw(void)
{
    DrawText(s_gameName, (SCREEN_WIDTH - MeasureText(s_gameName, MENU_TITLE_SIZE)) / 2, MENU_TITLE_POSITION, MENU_TITLE_SIZE, MENU_TITLE_COLOR);

    const char* highScoreText = TextFormat(s_textOptions[0], g_gameData->saveData.highScore);
    const char* scaleText = TextFormat(s_textOptions[2], g_gameData->saveData.windowMode == WINDOW_MODE_FULLSCREEN ? 0 : g_gameData->saveData.scale);

    DrawText(highScoreText, GetTextPosition(highScoreText), MENU_TEXT_START_POSITION, MENU_TEXT_SIZE, RAYWHITE);
    DrawText(s_textOptions[1], GetTextPosition(s_textOptions[1]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING, MENU_TEXT_SIZE, s_menuSelection == 0 ? YELLOW : RAYWHITE);
    DrawText(scaleText, GetTextPosition(scaleText), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 2, MENU_TEXT_SIZE, s_menuSelection == 1 ? YELLOW : RAYWHITE);
    DrawText(s_textOptions[3 + g_gameData->saveData.windowMode], GetTextPosition(s_textOptions[3 + g_gameData->saveData.windowMode]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 3, MENU_TEXT_SIZE, s_menuSelection == 2 ? YELLOW : RAYWHITE);
    DrawText(s_textOptions[6 + g_gameData->saveData.filter], GetTextPosition(s_textOptions[5 + g_gameData->saveData.filter]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 4, MENU_TEXT_SIZE, s_menuSelection == 3 ? YELLOW : RAYWHITE);
    DrawText(s_textOptions[9], GetTextPosition(s_textOptions[9]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 5, MENU_TEXT_SIZE, s_menuSelection == 4 ? YELLOW : RAYWHITE);

    DrawSnake(g_gameData);
    DrawFade();
}

static unsigned short GetTextPosition(const char* text)
{
    return (SCREEN_WIDTH - MeasureText(text, MENU_TEXT_SIZE)) / 2;
}

void DrawSnake(const GameData* game)
{
    for (unsigned short pos = 40; pos < SCREEN_WIDTH - 8; pos += 16)
        DrawTexturePro(game->snake.texture, (Rectangle){16, 0, 16, 16}, (Rectangle){pos, 8, 16, 16}, (Vector2){8, 8}, 90, WHITE);
    for (unsigned short pos = 24; pos < SCREEN_WIDTH - 8; pos += 16)
        DrawTexturePro(game->snake.texture, (Rectangle){16, 0, 16, 16}, (Rectangle){pos, SCREEN_HEIGHT - 8, 16, 16}, (Vector2){8, 8}, 90, WHITE);
    for (unsigned short pos = 24; pos < SCREEN_HEIGHT - 8; pos += 16)
        DrawTexturePro(game->snake.texture, (Rectangle){16, 0, 16, 16}, (Rectangle){8, pos, 16, 16}, (Vector2){8, 8}, 0, WHITE);
    for (unsigned short pos = 24; pos < SCREEN_HEIGHT - 8; pos += 16)
        DrawTexturePro(game->snake.texture, (Rectangle){16, 0, 16, 16}, (Rectangle){SCREEN_WIDTH - 8, pos, 16, 16}, (Vector2){8, 8}, 0, WHITE);

    DrawTexturePro(game->snake.texture, (Rectangle){0, 0, 16, 16}, (Rectangle){8, 8, 16, 16}, (Vector2){8, 8}, 0, WHITE);
    DrawTexturePro(game->snake.texture, (Rectangle){0, 16, -16, 16}, (Rectangle){8, SCREEN_HEIGHT - 8, 16, 16}, (Vector2){8, 8}, 0, WHITE);
    DrawTexturePro(game->snake.texture, (Rectangle){0, 16, 16, 16}, (Rectangle){SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, 16, 16}, (Vector2){8, 8}, 0, WHITE);
    DrawTexturePro(game->snake.texture, (Rectangle){0, 16, 16, -16}, (Rectangle){SCREEN_WIDTH - 8, 8, 16, 16}, (Vector2){8, 8}, 0, WHITE);
    DrawTexturePro(game->snake.texture, (Rectangle){16, 16, 16, 16}, (Rectangle){24, 8, 16, 16}, (Vector2){8, 8}, 90, WHITE);
}