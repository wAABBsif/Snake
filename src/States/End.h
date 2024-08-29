#pragma once
#include "../Core.h"

#define END_TEXT_SIZE 20
#define END_TEXT_START_POSITION 96
#define END_TEXT_SPACING 32

void End_Initialize(void);
void _End_Start(const unsigned char prevState);
void _End_Update(void);
void _End_Draw(void);