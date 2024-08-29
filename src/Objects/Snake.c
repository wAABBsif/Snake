#include "Snake.h"

#include <stdlib.h>
#include <string.h>
#include "../Core.h"

bool Snake_CheckForHit(const Snake* const snake, unsigned char position[]);

void Snake_Update(Snake* snake)
{
    static float s_timer = UPDATE_TIME;
    static char s_inputBuffer[2];
    static char s_inputIndex = sizeof(s_inputBuffer);

    s_inputIndex--;
    if (s_inputIndex < 0)
        s_inputIndex = 0;

    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
        s_inputBuffer[s_inputIndex] = 0b00000101;
    else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
        s_inputBuffer[s_inputIndex] = 0b00000001;
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
        s_inputBuffer[s_inputIndex] = 0b00000111;
    else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
        s_inputBuffer[s_inputIndex] = 0b00000011;
    else
        s_inputIndex++;

    s_timer -= GetFrameTime();
    if (s_timer > 0)
        return;
    s_timer = UPDATE_TIME;

    unsigned char currentTravel = snake->travel[0];
    unsigned char position[2];
    memcpy(position, snake->position, 2);

    if (s_inputBuffer[sizeof(s_inputBuffer) - 1] & 0b00000001 != 0)
    {
        if ((currentTravel & 0b00000001) != (s_inputBuffer[sizeof(s_inputBuffer) - 1] >> 1 & 0b00000001))
            currentTravel = s_inputBuffer[sizeof(s_inputBuffer) - 1] >> 1;
        else if ((currentTravel & 0b00000010) == (s_inputBuffer[sizeof(s_inputBuffer) - 1] >> 1 & 0b00000010))
            currentTravel = s_inputBuffer[sizeof(s_inputBuffer) - 1] >> 1;
    }
    if (++s_inputIndex >= sizeof(s_inputBuffer))
        s_inputIndex = sizeof(s_inputBuffer);
    memcpy(s_inputBuffer + 1, s_inputBuffer, sizeof(s_inputBuffer) - 1);
    s_inputBuffer[0] = 0;

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
        States_Change(GAMESTATE_END);
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

    for (unsigned char i = 0; i < snake->length - 2; i++)
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
