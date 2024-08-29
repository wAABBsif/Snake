#include "Menu.h"

static const char* const gameName = "Snake";

static const char* const textOptions[] =
{
    "Highscore: %i",
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

static unsigned char menuSelection;

static unsigned short GetTextPosition(const char* text);
void DrawSnake(const GameData* game);

void _Menu_Start(const unsigned char prevState)
{
    menuSelection = 0;
}

void _Menu_Update(void)
{
    GameData* game = GameData_Get();
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        menuSelection++;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        menuSelection--;

    menuSelection %= 5;

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (menuSelection)
        {
            case 0:
                SavePlayerData(&game->saveData);
                States_Change(GAMESTATE_GAMEPLAY);
                break;
            case 1:
                if (game->saveData.windowMode == WINDOW_MODE_FULLSCREEN)
                    break;
                game->saveData.scale++;
                if (game->saveData.scale > GetMonitorHeight(GetCurrentMonitor()) / SCREEN_HEIGHT)
                    game->saveData.scale = 1;
                if (game->saveData.windowMode == WINDOW_MODE_FULLSCREEN)
                    SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                else
                    SetWindowSize(SCREEN_WIDTH * game->saveData.scale, SCREEN_HEIGHT * game->saveData.scale);
                break;
            case 2:
                game->saveData.windowMode++;
                game->saveData.windowMode %= 3;
                SetWindowMode(game, game->saveData.windowMode);
                break;
            case 3:
                game->saveData.filter++;
                game->saveData.filter %= 3;
                SetTextureFilter(game->renderTexture.texture, game->saveData.filter);
                break;
            default:
                CloseWindow();
        }
    }
}

void _Menu_Draw(void)
{
    const GameData* game = GameData_Get();
    DrawText(gameName, (SCREEN_WIDTH - MeasureText(gameName, MENU_TITLE_SIZE)) / 2, MENU_TITLE_POSITION, MENU_TITLE_SIZE, MENU_TITLE_COLOR);

    const char* highScoreText = TextFormat(textOptions[0], game->saveData.highScore);
    const char* scaleText = TextFormat(textOptions[2], game->saveData.windowMode == WINDOW_MODE_FULLSCREEN ? 0 : game->saveData.scale);

    DrawText(highScoreText, GetTextPosition(highScoreText), MENU_TEXT_START_POSITION, MENU_TEXT_SIZE, RAYWHITE);
    DrawText(textOptions[1], GetTextPosition(textOptions[1]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING, MENU_TEXT_SIZE, menuSelection == 0 ? YELLOW : RAYWHITE);
    DrawText(scaleText, GetTextPosition(scaleText), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 2, MENU_TEXT_SIZE, menuSelection == 1 ? YELLOW : RAYWHITE);
    DrawText(textOptions[3 + game->saveData.windowMode], GetTextPosition(textOptions[3 + game->saveData.windowMode]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 3, MENU_TEXT_SIZE, menuSelection == 2 ? YELLOW : RAYWHITE);
    DrawText(textOptions[6 + game->saveData.filter], GetTextPosition(textOptions[5 + game->saveData.filter]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 4, MENU_TEXT_SIZE, menuSelection == 3 ? YELLOW : RAYWHITE);
    DrawText(textOptions[9], GetTextPosition(textOptions[9]), MENU_TEXT_START_POSITION + MENU_TEXT_SPACING * 5, MENU_TEXT_SIZE, menuSelection == 4 ? YELLOW : RAYWHITE);

    DrawSnake(game);
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