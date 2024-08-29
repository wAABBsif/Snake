#pragma once
#include "../Core.h"

#define PAUSE_WIDTH 224
#define PAUSE_HEIGHT 64
#define PAUSE_TEXT_SIZE 30

void Pause_Initialize(void);
void _Pause_Start(const unsigned char prevState);
void _Pause_Update(void);
void _Pause_Draw(void);