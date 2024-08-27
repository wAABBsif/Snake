#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Core.h"
#include "Drawing.h"
#include "Snake.h"

#define BACKGROUND_COLOR (Color){0x08, 0x08, 0x08, 0x08}

GameData* game;

void Update();
void Draw();
void CheckCollision(GameData* game);

void Game()
{
    game = calloc(1,sizeof(GameData));

    LoadPlayerData(&game->saveData);

    game->snake.position[0] = 13;
    game->snake.position[1] = 15;
    game->snake.length = 3;

    SetRandomSeed(time(NULL));

    InitWindow(SCREEN_WIDTH * game->saveData.scale, SCREEN_HEIGHT * game->saveData.scale, "Snake");
    const RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    Orb_Spawn(&game->orb, &game->snake);

    game->snake.image = LoadImage("res/snake.png");
    game->snake.texture = LoadTextureFromImage(game->snake.image);
    game->orb.image = LoadImage("res/orb.png");
    game->orb.texture = LoadTextureFromImage(game->orb.image);

    while (!WindowShouldClose())
    {
        Update();
        BeginTextureMode(target);
        ClearBackground(BACKGROUND_COLOR);
        Draw();
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

void Update()
{
    Snake_Update(&game->snake);
    CheckCollision(game);
}

void Draw()
{
    CheckerboardDraw((Vector2){32, 0}, (Vector2){16, 16}, 16, 16, GRAY, DARKGRAY);
    char scoreText[4];
    ScoreToString(game->score, scoreText);
    Orb_Draw(&game->orb);
    Snake_Draw(&game->snake);
    DrawText(scoreText, 30 - MeasureText(scoreText, 20), 0, 20, RAYWHITE);
}

void CheckCollision(GameData* game)
{
    if (memcmp(&game->snake.position, &game->orb.position, 2) != 0)
        return;

    game->score++;
    game->snake.length++;
    Orb_Spawn(&game->orb, &game->snake);
}