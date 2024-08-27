#include "Orb.h"ff
#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include "Snake.h"

void Orb_Spawn(Orb* orb, const Snake* snake)
{
    unsigned char* positions = alloca(snake->length * 2);
    Snake_GetPositions(snake, positions);

    orb->position[0] = 0;
    orb->position[1] = 0;

    const unsigned short randomNumber = GetRandomValue(0, 255 - snake->length);
    unsigned char i = 0;
    while (i <= randomNumber)
    {
        for (unsigned char j = 0; j < snake->length; j++)
        {
            if (memcmp(&positions[j * 2], orb->position, 2) == 0)
                i--;
        }

        orb->position[0]++;
        if (orb->position[0] >= 16)
        {
            orb->position[1]++;
            orb->position[0] -= 16;
        }
        i++;
    }
}

void Orb_Draw(const Orb* const orb)
{
    DrawRectangle(32 + orb->position[0] * 16, orb->position[1] * 16, 16, 16, BLUE);
}