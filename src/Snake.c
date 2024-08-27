#include "Snake.h"

#include <stdlib.h>
#include <string.h>
#include "Core.h"

void Snake_Update(Snake* snake)
{
    static float timer = UPDATE_TIME;
    static char input = 0b00000000;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) && snake->travel[0] != 0b00000010)
        input = 0b00000010;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) && snake->travel[0] != 0b00000000)
        input = 0b00000000;

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) && snake->travel[0] != 0b00000011)
        input = 0b00000011;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) && snake->travel[0] != 0b00000001)
        input = 0b00000001;

    timer -= GetFrameTime();
    if (timer > 0)
        return;

    timer = UPDATE_TIME;

    unsigned char currentTravel = snake->travel[0];
    unsigned char position[2];
    memcpy(position, snake->position, 2);

    if ((currentTravel & 0b00000001) != (input & 0b00000001))
        currentTravel = input;

    if ((currentTravel & 0b00000010) == (input & 0b00000010))
        currentTravel = input;

    position[currentTravel & 0b00000001] += currentTravel & 0b00000010 ? 1 : -1;

    bool isHit = Snake_CheckForHit(snake, position);

    for (char i = 0; i < 2; i++)
    {
        if (position[i] >= 16)
            isHit = true;
    }

    if (!isHit)
    {
        memcpy(snake->position, position, 2);
        memmove(snake->travel + 1, snake->travel, 0xFF);
        snake->travel[0] = currentTravel;
    }
    else
    {
        timer = 10;
    }
}

void Snake_GetPositions(const Snake* const snake, unsigned char* positionBuffer)
{
    unsigned char position[2];
    memcpy(position, snake->position, 2);
    for (unsigned char i = 0; i < snake->length; i++)
    {
        position[snake->travel[i] & 0b00000001] -= snake->travel[i] & 0b00000010 ? 1 : -1;
        memcpy(&positionBuffer[i * 2], position, 2);
    }
}

bool Snake_CheckForHit(const Snake* const snake,  unsigned char position[])
{
    unsigned char* positionBuffer = alloca(snake->length * 2);
    Snake_GetPositions(snake, positionBuffer);
    for (unsigned char i = 0; i < snake->length; i++)
    {
        if (memcmp(position, &positionBuffer[i * 2], 2) == 0)
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
        char index;
        bool mirroredX = false;
        bool mirroredY = false;
        float rotation = snake->travel[i] * 90 - 90;
        if (i >= snake->length - 1)
        {
            rotation = snake->travel[i - 1] * 90 - 90;
            index = 3;
        }
        else if (i == 0)
            index = 0;
        else if (memcmp(&snake->travel[i - 1], &snake->travel[i], 1) != 0 && i > 0)
        {
            mirroredX = true;
            mirroredY = true;
            if (snake->travel[i] > snake->travel[i - 1] || snake->travel[i] == 0 & snake->travel[i - 1] == 3)
                mirroredX = false;
            if (snake->travel[i - 1] == 0 & snake->travel[i] == 3)
                mirroredX = true;
            index = 2;
        }
        else
            index = 1;
        const Rectangle srcRectangle = (Rectangle){(index & 0b00000001) * 16, ((index & 0b00000010) >> 1) * 16, mirroredX ? -16 : 16, mirroredY ? -16 : 16};
        DrawTexturePro(snake->texture, srcRectangle, (Rectangle){40 + 16 * position[0], 16 * position[1] + 8, 16, 16}, (Vector2){8, 8}, rotation, WHITE);
        position[snake->travel[i] & 0b00000001] -= snake->travel[i] & 0b00000010 ? 1 : -1;
    }
}
