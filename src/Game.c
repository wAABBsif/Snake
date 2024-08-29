#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Core.h"

#include "Objects/Snake.h"
#include "Objects/Orb.h"

GameData* game;

void Game()
{
    SetRandomSeed(time(NULL));
    game = calloc(1,sizeof(GameData));
    GameData_Set(game);
    LoadPlayerData(&game->saveData);

    InitWindow(SCREEN_WIDTH * game->saveData.scale, SCREEN_HEIGHT * game->saveData.scale, "Snake");
    SetExitKey(KEY_NULL);
    game->renderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTextureFilter(game->renderTexture.texture, TEXTURE_FILTER_POINT);
    SetWindowMode(game,game->saveData.windowMode);

    game->snake.image = LoadImage("res/snake.png");
    game->snake.texture = LoadTextureFromImage(game->snake.image);
    game->orb.image = LoadImage("res/orb.png");
    game->orb.texture = LoadTextureFromImage(game->orb.image);

    States_Initialize();
    States_Change(GAMESTATE_MENU);

    while (!WindowShouldClose())
    {
        game->gameStates[game->stateIndex].Update();
        BeginTextureMode(game->renderTexture);
        ClearBackground(BACKGROUND_COLOR);
        game->gameStates[game->stateIndex].Draw();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        float scale = (float)GetScreenHeight() / (float)SCREEN_HEIGHT;
        DrawTexturePro(game->renderTexture.texture, (Rectangle){ 0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT },
                           (Rectangle){ (GetScreenWidth() - SCREEN_WIDTH * scale) / 2, 0, SCREEN_WIDTH * scale, GetScreenHeight()},
                           (Vector2){ 0, 0 }, 0.0f, WHITE);
        DrawFPS(4, 4);
        EndDrawing();
    }

    CloseWindow();
}