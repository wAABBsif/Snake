#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Core.h"

#include "Objects/Snake.h"
#include "Objects/Orb.h"

void Game()
{
    SetRandomSeed(time(NULL));
    g_gameData = calloc(1,sizeof(GameData));
    LoadPlayerData(&g_gameData->saveData);

    InitWindow(SCREEN_WIDTH * g_gameData->saveData.scale, SCREEN_HEIGHT * g_gameData->saveData.scale, "Snake");
    SetExitKey(KEY_NULL);
    g_gameData->renderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_gameData->prevRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    SetTextureFilter(g_gameData->renderTexture.texture, TEXTURE_FILTER_POINT);
    SetWindowMode(g_gameData->saveData.windowMode);

    g_gameData->snake.image = LoadImage("res/snake.png");
    g_gameData->snake.texture = LoadTextureFromImage(g_gameData->snake.image);
    g_gameData->orb.image = LoadImage("res/orb.png");
    g_gameData->orb.texture = LoadTextureFromImage(g_gameData->orb.image);

    States_Initialize();
    States_Change(GAMESTATE_MENU);
	States_Get()->timeInState = 10;

    while (!WindowShouldClose())
    {
    	States_Get()->timeInState += GetFrameTime();
    	States_Get()->Update();
    	BeginTextureMode(g_gameData->renderTexture);
        ClearBackground(BACKGROUND_COLOR);
        States_Get()->Draw();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        const float scale = (float)GetScreenHeight() / (float)SCREEN_HEIGHT;
        DrawTexturePro(g_gameData->renderTexture.texture, (Rectangle){ 0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT },
                           (Rectangle){ (GetScreenWidth() - SCREEN_WIDTH * scale) / 2, 0, SCREEN_WIDTH * scale, GetScreenHeight()},
                           (Vector2){ 0, 0 }, 0.0f, WHITE);
        DrawFPS(4, 4);
        EndDrawing();
    }

    CloseWindow();
}