#include <stdlib.h>
#include <string.h>
#include "../Drawing.h"
#include "raylib.h"
#include "Orb.h"
#include "Snake.h"

void Orb_Spawn(Orb* orb, const Snake* snake)
{
    unsigned char* positions = alloca(snake->length * 2);
    Snake_GetPositions(snake, positions);

    orb->position[0] = 0;
    orb->position[1] = 0;

    const unsigned short randomNumber = GetRandomValue(1, 255 - snake->length);
    for (unsigned char i = 0; i < randomNumber; i++)
    {
        orb->position[0]++;
        if (orb->position[0] >= 16)
        {
            orb->position[1]++;
            orb->position[0] -= 16;
        }
        for (unsigned char j = 0; j < snake->length; j++)
        {
            if (memcmp(&positions[j * 2], orb->position, 2) == 0)
                i--;
        }
    }
}

void Orb_Draw(const Orb* const orb)
{
    static Texture2D* s_texture = NULL;
    if (s_texture == NULL)
        s_texture = Drawing_GetTexture("orb.png");
    DrawTexture(*s_texture, 32 + orb->position[0] * 16, orb->position[1] * 16, WHITE);
}