#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Core.h"
#include "Drawing.h"

#include "Objects/Snake.h"
#include "Objects/Orb.h"

#include "States/Gameplay.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}

GameData* game;

void InitializeGameStates();

void Game()
{
    SetRandomSeed(time(NULL));
    game = calloc(1,sizeof(GameData));
    LoadPlayerData(&game->saveData);

    const RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    SetExitKey(KEY_NULL);
    InitWindow(SCREEN_WIDTH * game->saveData.scale, SCREEN_HEIGHT * game->saveData.scale, "Snake");

    game->snake.image = LoadImage("res/snake.png");
    game->snake.texture = LoadTextureFromImage(game->snake.image);
    game->orb.image = LoadImage("res/orb.png");
    game->orb.texture = LoadTextureFromImage(game->orb.image);

    InitializeGameStates();
    ChangeState(game, GAMESTATE_GAMEPLAY);

    while (!WindowShouldClose())
    {
        game->gameStates[game->stateIndex].Update(game);
        BeginTextureMode(target);
        ClearBackground(BACKGROUND_COLOR);
        game->gameStates[game->stateIndex].Draw(game);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (Rectangle){ (GetScreenWidth() - (float)SCREEN_WIDTH * game->saveData.scale)*0.5f, (GetScreenHeight() - (float)SCREEN_HEIGHT * game->saveData.scale) *0.5f,
                           (float)SCREEN_WIDTH * game->saveData.scale, (float)SCREEN_HEIGHT * game->saveData.scale}, (Vector2){ 0, 0 }, 0.0f, WHITE);
        if (IsKeyDown(KEY_F))
            DrawFPS(4, 4);
        EndDrawing();
    }

    CloseWindow();
}

void InitializeGameStates()
{
    game->gameStates[GAMESTATE_GAMEPLAY].Start = _Gameplay_Start;
    game->gameStates[GAMESTATE_GAMEPLAY].Update = _Gameplay_Update;
    game->gameStates[GAMESTATE_GAMEPLAY].Draw = _Gameplay_Draw;
}