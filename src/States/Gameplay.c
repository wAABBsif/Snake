#include <string.h>

#include "Gameplay.h"
#include "../Drawing.h"

void CheckCollision(GameData* game);

void _Gameplay_Start(GameData* game, const unsigned char prevState)
{
    if (prevState == GAMESTATE_PAUSE)
        return;

    game->snake.position[0] = 13;
    game->snake.position[1] = 15;
    game->snake.length = 2;
    game->score = 0;
    memset(game->snake.travel,0,sizeof(game->snake.travel));
    Orb_Spawn(&game->orb, &game->snake);
}

void _Gameplay_Update(GameData* game)
{
    if (IsKeyDown(KEY_P) || IsKeyDown(KEY_PAUSE) || IsKeyDown(KEY_ESCAPE))
    {
        ChangeState(game, GAMESTATE_PAUSE);
        return;
    }

    Snake_Update(&game->snake);
    CheckCollision(game);
}

void _Gameplay_Draw(const GameData* game)
{
    CheckerboardDraw((Vector2){32, 0}, (Vector2){16, 16}, 16, 16, GRAY, DARKGRAY);
    char scoreText[4];
    ScoreToString(game->score, scoreText);
    Orb_Draw(&game->orb);
    Snake_Draw(&game->snake);
    DrawText(scoreText, 16 - MeasureText(scoreText, 20) / 2, 10, 20, RAYWHITE);
}


void CheckCollision(GameData* game)
{
    if (memcmp(game->snake.position, game->orb.position, 2) != 0)
        return;

    game->score++;
    game->snake.length++;
    Orb_Spawn(&game->orb, &game->snake);
}