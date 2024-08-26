#include <stdlib.h>

#include "Core.h"
#include "Drawing.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}

unsigned char score = 0;
SaveData* saveData;

void Draw();

void Game()
{
    saveData = malloc(sizeof(SaveData));
    LoadPlayerData(saveData);

    InitWindow(SCREEN_WIDTH * saveData->scale, SCREEN_HEIGHT * saveData->scale, "Snake");
    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    while (!WindowShouldClose())
    {
        BeginTextureMode(target);
        ClearBackground(BACKGROUND_COLOR);
        Draw();
        EndTextureMode();
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (Rectangle){ (GetScreenWidth() - (float)SCREEN_WIDTH * saveData->scale)*0.5f, (GetScreenHeight() - (float)SCREEN_HEIGHT * saveData->scale) *0.5f,
                           (float)SCREEN_WIDTH * saveData->scale, (float)SCREEN_HEIGHT * saveData->scale}, (Vector2){ 0, 0 }, 0.0f, WHITE);        if (IsKeyDown(KEY_F))
            DrawFPS(4, 4);
        EndDrawing();
    }

    CloseWindow();
}

void Draw()
{
    CheckerboardDraw((Vector2){32, 0}, (Vector2){16, 16}, 16, 16, GRAY, DARKGRAY);
    char scoreText[4];
    ScoreToString(score, scoreText);
    DrawText(scoreText, 30 - MeasureText(scoreText, 20), 0, 20, RAYWHITE);
}
