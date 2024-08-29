#pragma once
#include "../Core.h"

#define PAUSE_WIDTH 224
#define PAUSE_HEIGHT 64
#define PAUSE_TEXT_SIZE 30

void Pause_Initialize(GameData* game);
void _Pause_Start(GameData* game, const unsigned char prevState);
void _Pause_Update(GameData* game);
void _Pause_Draw(const GameData* game);