#pragma once

#define UPDATE_TIME 0.125f

typedef struct Snake
{
    unsigned char position[2];
    unsigned char length;
    unsigned char travel[256];
} Snake;

void Snake_Update(Snake* snake);
char CheckForHit(const Snake* const snake);
void Snake_Draw(const Snake* const snake);