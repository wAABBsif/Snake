#include <string.h>
#include "Gameplay.h"
#include "../Drawing.h"
#include "../Sound.h"

static void CheckCollision(GameData* game);

void _Gameplay_Start(void)
{
    if (g_gameData->prevStateIndex == GAMESTATE_PAUSE)
        return;

    g_gameData->snake.position[0] = 13;
    g_gameData->snake.position[1] = 15;
    g_gameData->snake.length = 2;
    g_gameData->score = 0;
    memset(g_gameData->snake.travel,0,sizeof(g_gameData->snake.travel));
    Orb_Spawn(&g_gameData->orb, &g_gameData->snake);
}

void _Gameplay_Update(void)
{
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_PAUSE) || IsKeyPressed(KEY_ESCAPE))
    {
        States_Change(GAMESTATE_PAUSE);
        return;
    }

    Snake_Update(&g_gameData->snake);
    CheckCollision(g_gameData);
}

void _Gameplay_Draw(void)
{
    Drawing_Checkerboard((Vector2){32, 0}, 16, 16, 16, GRAY, DARKGRAY);
    char scoreText[4];
    Drawing_ScoreToString(g_gameData->score, scoreText);
    Orb_Draw(&g_gameData->orb);
    Snake_Draw(&g_gameData->snake);
    DrawText(scoreText, 16 - MeasureText(scoreText, 20) / 2, 10, 20, RAYWHITE);
    Drawing_Fade();
}

static void CheckCollision(GameData* game)
{
    if (memcmp(game->snake.position, game->orb.position, 2) != 0)
        return;

    game->score++;
    game->snake.length++;
    Orb_Spawn(&game->orb, &game->snake);
    Sound_Play("orbCollect.wav");
}