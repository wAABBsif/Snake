#pragma once

#define PAUSE_WIDTH 224
#define PAUSE_HEIGHT 64
#define PAUSE_TEXT_SIZE 30

void Pause_Initialize(void);
void _Pause_Start(void);
void _Pause_Update(void);
void _Pause_Draw(void);
void Pause_Free(void);