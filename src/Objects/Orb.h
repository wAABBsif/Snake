#pragma once
#include "Snake.h"

typedef struct Orb
{
    unsigned char position[2];
} Orb;

void Orb_Spawn(Orb* orb, const Snake* snake);
void Orb_Draw(const Orb* const orb);