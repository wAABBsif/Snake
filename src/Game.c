#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Core.h"
#include "Drawing.h"
#include "Sound.h"

#include "Objects/Snake.h"

void Game()
{
    SetRandomSeed(time(NULL));
    g_gameData = calloc(1,sizeof(GameData));
    LoadPlayerData(&g_gameData->saveData);

    InitWindow(SCREEN_WIDTH * g_gameData->saveData.scale, SCREEN_HEIGHT * g_gameData->saveData.scale, "Snake");
    SetExitKey(KEY_NULL);
	Drawing_Initialize();

	InitAudioDevice();
	Sound_Initialize();

	States_Initialize();
	States_Change(GAMESTATE_MENU);
	States_Get()->timeInState = 10;

    while (!WindowShouldClose())
    {
    	States_Get()->timeInState += GetFrameTime();
    	States_Get()->Update();
    	if (g_gameData->isExitWindowRequested)
    		break;

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

    	static bool isRenderingFPS = false;
    	if (IsKeyPressed(KEY_F))
    		isRenderingFPS = !isRenderingFPS;
    	if (isRenderingFPS)
			DrawFPS(4, 4);

        EndDrawing();
    }

	Drawing_Free();
	Sound_Free();
	free(g_gameData);
	CloseWindow();
}
