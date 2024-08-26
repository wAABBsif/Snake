#include "Snake.h"
#include <string.h>
#include "Core.h"

void Snake_Update(Snake* snake)
{
    static float timer = UPDATE_TIME;
    static char input = 0b00000000;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        input = 0b00000010;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        input = 0b00000000;

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        input = 0b00000011;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        input = 0b00000001;

    timer -= GetFrameTime();
    if (timer > 0)
        return;

    timer = UPDATE_TIME;

    unsigned char currentTravel = snake->travel[0];

    if ((currentTravel & 0b00000001) != (input & 0b00000001))
        currentTravel = input;

    if ((currentTravel & 0b00000010) == (input & 0b00000010))
        currentTravel = input;

    snake->position[currentTravel & 0b00000001] += currentTravel & 0b00000010 ? 1 : -1;
    bool isHit = CheckForHit(snake);

    for (char i = 0; i < 2; i++)
    {
        if (snake->position[i] >= 16)
        {
            isHit = true;
        }
    }

    if (!isHit)
    {
        memcpy(snake->travel + 1, snake->travel, 0xFF);
        snake->travel[0] = currentTravel;
    }
    else
    {
        timer = 10;
        snake->position[snake->travel[0] & 0b00000001] -= snake->travel[0] & 0b00000010 ? 1 : -1;
    }
}

char CheckForHit(const Snake* const snake)
{
    unsigned char position[2];
    memcpy(position, snake->position, 2);
    for (unsigned char i = 0; i < snake->length; i++)
    {
        position[snake->travel[i] & 0b00000001] -= snake->travel[i] & 0b00000010 ? 1 : -1;
        if (memcmp(position, snake->position, 2) == 0)
            return true;
    }
    return false;
}

void Snake_Draw(const Snake* const snake)
{
    unsigned char position[2];
    memcpy(position, snake->position, 2);
    for (unsigned char i = 0; i < snake->length; i++)
    {
        DrawRectangle(32 + position[0] * 16, position[1] * 16, 16, 16, RED);
        position[snake->travel[i] & 0b00000001] -= snake->travel[i] & 0b00000010 ? 1 : -1;
    }
}